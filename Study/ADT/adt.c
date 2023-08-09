#include <stdio.h>
#include <string.h>
#include <malloc.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct NODE
{
	// 관리 대상 자료
	void* pData;

	// 자료 구조
	struct NODE* pPrev;
	struct NODE* pNext;
}NODE;

typedef struct USERDATA
{
	// 멤버 함수 포인터
	const char* (*pfGetKey)(void*);
	
	char szName[64];
	char szPhone[64];
}USERDATA;

NODE*	g_pHead;
NODE*	g_pTail;
int		g_nSize;

///////////////////////////////////////////////////////////////////////////////////////////////////
int InsertAtHead(void* pParam);
int InsertAtTail(void* pParam);
int GetLength();
int InsertAtBefore(NODE* pDstNode, void* pParam);


///////////////////////////////////////////////////////////////////////////////////////////////////
const char* GetKeyFromUserData(USERDATA* pParam)
{
	return pParam->szName;
}


USERDATA* CreateUserData(const char* pszName, const char* pszPhone)
{
	USERDATA* pNew = (USERDATA*)malloc(sizeof(USERDATA));
	memset(pNew, 0, sizeof(USERDATA));
	memcpy(pNew->szName, pszName, sizeof(pNew->szName));
	memcpy(pNew->szPhone, pszPhone, sizeof(pNew->szPhone));

	pNew->pfGetKey = GetKeyFromUserData;

	return pNew;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void InitList()
{
	g_pHead = (NODE*)malloc(sizeof(NODE));
	g_pTail = (NODE*)malloc(sizeof(NODE));

	g_nSize = 0;
	memset(g_pHead, 0, sizeof(NODE));
	memset(g_pTail, 0, sizeof(NODE));

	g_pHead->pNext = g_pTail;
	g_pTail->pPrev = g_pHead;
}

void ReleaseList()
{
	printf("ReleaseList()\n");

	NODE* pTmp = g_pHead;
	while (pTmp != NULL)
	{
		NODE* pDelete = pTmp;
		pTmp = pTmp->pNext;

		printf("[%p] free\n", pDelete);

		free(pDelete->pData);
		free(pDelete);
	}

	printf("\n");
	g_pHead = NULL;
	g_pTail = NULL;
	g_nSize = 0;
}

void PrintList()
{
	printf("PrintList() : g_nSize [%d], g_pHead [%p], g_pTail [%p]\n", g_nSize, g_pHead, g_pTail);
	NODE* pTmp = g_pHead->pNext;
	while (pTmp != g_pTail)
	{
		USERDATA* pUser = pTmp->pData;
		printf("[0x%p] [%s\t] [0x%p]\n", 
			pTmp->pPrev,
			pUser->pfGetKey(pTmp->pData), 
			pTmp->pNext);
		pTmp = pTmp->pNext;
	}
	printf("\n");
}

NODE* GetAt(int nIdx)
{
	NODE* pTmp = g_pHead->pNext;
	int nCnt = 0;
	while (pTmp != g_pTail)
	{
		if (nIdx == nCnt)
		{
			return pTmp;
		}
		pTmp = pTmp->pNext;
		nCnt++;
	}

	return NULL;
}

int InsertAt(int nIdx, void* pParam)
{
	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));

	pNode->pData = pParam;

	if (nIdx <= 0)
		InsertAtHead(pParam);
	else if (nIdx >= GetLength())
		InsertAtTail(pParam);
	else
	{
		NODE* pTmp = g_pHead->pNext;
		int nCnt = 0;
		while (pTmp != g_pTail)
		{
			if (nIdx == nCnt)
			{
				InsertAtBefore(pTmp, pParam);
			}
			pTmp = pTmp->pNext;
			nCnt++;
		}
	}
	return 0;
}


int InsertAtHead(void* pParam)
{
	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));

	// 관리 대상 자료에 관한 초기화
	pNode->pData = pParam;

	// 연결 리스트에 관한 초기화
	pNode->pNext = g_pHead->pNext;
	pNode->pPrev = g_pHead;

	g_pHead->pNext = pNode;
	pNode->pNext->pPrev = pNode;

	g_nSize++;
	return g_nSize;
}

int InsertAtTail(void* pParam)
{
	InsertAtBefore(g_pTail, pParam);

	return g_nSize;
}

int InsertAtBefore(NODE* pDstNode, void* pParam)
{
	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));

	pNode->pData = pParam;

	pNode->pNext = pDstNode;
	pNode->pPrev = pDstNode->pPrev;

	pDstNode->pPrev->pNext = pNode;
	pDstNode->pPrev = pNode;

	g_nSize++;
	return g_nSize;
}

NODE* FindNode(const char* pszKey)
{
	NODE* pTmp = g_pHead->pNext;
	// 구조체를 함수 포인터로 변경하려는 시도	
	// USERDATA 구조체

	// 함수 포인터
	const char* (*pfGetKey)(void*) = NULL;

	while (pTmp != g_pTail)
	{
		// 함수포인터에 pTmp->pData 대입
		pfGetKey = pTmp->pData;
		
		// 함수포인터 
		if (strcmp((*(const char* (**)(void*))pfGetKey)(pTmp->pData), pszKey) == 0)
			return pTmp;
		 
		pTmp = pTmp->pNext;
	}
	return NULL;
}

int DeleteNode(const char* pszKey)
{
	NODE* pNode = FindNode(pszKey);
	//const char* (*pfGetKey)(void*) = NULL;
	//pfGetKey = pNode->pData;

	if (pNode != NULL)
	{
		USERDATA* pUser = pNode->pData;

		pNode->pPrev->pNext = pNode->pNext;
		pNode->pNext->pPrev = pNode->pPrev;

		g_nSize--;
		printf("DeleteNode() \n");
		printf("[0x%p][0x%p\t %s\t][0x%p]\n", pNode->pPrev, pNode, pUser->pfGetKey(pNode->pData), pNode->pNext);
		printf("\n");

		free(pNode->pData);
		free(pNode);
	}
	
	return 0;
}

int GetSize()
{
	return g_nSize;
}

int GetLength()
{
	return GetSize();
}


void main()
{
	InitList();

	USERDATA* pData = NULL;
	pData = CreateUserData("ttt", "010-1111-1111");
	InsertAtTail(pData);
	
	pData = CreateUserData("yy", "010-2222-2222");
	InsertAtTail(pData);

	pData = CreateUserData("etwer", "010-3333-3333");
	InsertAtTail(pData);

	PrintList();

	DeleteNode("etwer");

	ReleaseList();
	return;
}
