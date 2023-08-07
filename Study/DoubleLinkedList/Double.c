#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct NODE
{
	char szData[64];
	struct NODE* pPrev;
	struct NODE* pNext;
}NODE;

NODE*	g_pHead;
NODE*	g_pTail;
int		g_nSize;

int InsertAtHead(const char* pszData);
int InsertAtTail(const char* pszData);
int GetLength();
int InsertAtBefore(NODE* pDstNode, const char* pszData);

void InitList()
{
	g_pHead = (NODE*)malloc(sizeof(NODE));
	g_pTail = (NODE*)malloc(sizeof(NODE));
	
	g_nSize = 0;
	memset(g_pHead, 0, sizeof(NODE));
	memset(g_pTail, 0, sizeof(NODE));

	memcpy(g_pHead->szData, "DUMMY HEAD", sizeof(g_pHead->szData));
	memcpy(g_pTail->szData, "DUMMY TAIL", sizeof(g_pTail->szData));

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

		printf("[%p] %s free\n", pDelete, pDelete->szData);
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
	NODE* pTmp = g_pHead;
	while (pTmp != NULL)
	{
		printf("[0x%p] [0x%p\t %s\t] [0x%p]\n", pTmp->pPrev, pTmp, pTmp->szData, pTmp->pNext);
		pTmp = pTmp->pNext;
	}
	printf("\n");
}

int InsertAt(int nIdx, const char *pszData)
{
	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));
	memcpy(pNode, pszData, sizeof(NODE));

	if (nIdx <= 0)
		InsertAtHead(pszData);
	else if (nIdx >= GetLength())
		InsertAtTail(pszData);
	else
	{
		NODE* pTmp = g_pHead->pNext;
		int nCnt = 0;
		while (pTmp != g_pTail)
		{
			if (nIdx == nCnt)
			{
				InsertAtBefore(pTmp, pszData);
			}
			pTmp = pTmp->pNext;
			nCnt++;
		}
	}

	return 0;
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

int InsertAtHead(const char *pszData)
{
	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));
	memcpy(pNode, pszData, sizeof(NODE));

	pNode->pNext = g_pHead->pNext;
	pNode->pPrev = g_pHead;

	g_pHead->pNext = pNode;
	pNode->pNext->pPrev = pNode;

	g_nSize++;
	return g_nSize;
}

int InsertAtBefore(NODE* pDstNode, const char* pszData)
{
	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));
	memcpy(pNode, pszData, sizeof(NODE));

	pNode->pNext = pDstNode;
	pNode->pPrev = pDstNode->pPrev;

	pDstNode->pPrev->pNext = pNode;
	pDstNode->pPrev = pNode;

	g_nSize++;
	return g_nSize;
}

int InsertAtTail(const char* pszData)
{
	InsertAtBefore(g_pTail, pszData);

	//g_nSize++;
	return g_nSize;
}

NODE* FindNode(const char* pszData)
{
	NODE* pTmp = g_pHead->pNext;
	while (pTmp != g_pTail)
	{
		if (strcmp(pTmp->szData, pszData) == 0)
			return pTmp;

		pTmp = pTmp->pNext;
	}

	return NULL;
}

int DeleteNode(const char* pszData)
{
	NODE* pNode = FindNode(pszData);

	pNode->pPrev->pNext = pNode->pNext;
	pNode->pNext->pPrev = pNode->pPrev;
	g_nSize--;

	printf("DeleteNode() \n");
	printf("[0x % p][0x % p\t % s\t][0x % p]\n", pNode->pPrev, pNode, pNode->szData, pNode->pNext);
	printf("\n");
	free(pNode);
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

	InsertAtTail("TEST01");
	InsertAtTail("TEST02");
	InsertAtTail("TEST03");
	InsertAt(2, "TEST00");

	DeleteNode("TEST00");

	NODE* pNode = GetAt(2);
	printf("\n\n%s\n\n", pNode->szData);

	PrintList();

}
