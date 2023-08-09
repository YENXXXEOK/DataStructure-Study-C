#include "mylist.h"

///////////////////////////////////////////////////////////////////////////////////////////////////


void InitList(LIST_INFO* pListData)
{
	pListData->pHead = (NODE*)malloc(sizeof(NODE));
	pListData->pTail = (NODE*)malloc(sizeof(NODE));

	pListData->nSize = 0;
	memset(pListData->pHead, 0, sizeof(NODE));
	memset(pListData->pTail, 0, sizeof(NODE));

	pListData->pHead->pNext = pListData->pTail;
	pListData->pTail->pPrev = pListData->pHead;
}

void ReleaseList(LIST_INFO* pListData)
{
	printf("ReleaseList()\n");

	NODE* pTmp = pListData->pHead;
	while (pTmp != NULL)
	{
		NODE* pDelete = pTmp;
		pTmp = pTmp->pNext;

		printf("[%p] free\n", pDelete);

		free(pDelete->pData);
		free(pDelete);
	}

	printf("\n");
	pListData->pHead = NULL;
	pListData->pTail = NULL;
	pListData->nSize = 0;
}


NODE* GetAt(LIST_INFO* pListData, int nIdx)
{
	NODE* pTmp = pListData->pHead->pNext;
	int nCnt = 0;
	while (pTmp != pListData->pTail)
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

int InsertAt(LIST_INFO* pListData, int nIdx, void* pParam)
{
	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));

	pNode->pData = pParam;

	if (nIdx <= 0)
		InsertAtHead(pListData, pParam);
	else if (nIdx >= GetSize(pListData))
		InsertAtTail(pListData,  pParam);
	else
	{
		NODE* pTmp = pListData->pHead->pNext;
		int nCnt = 0;
		while (pTmp != pListData->pTail)
		{
			if (nIdx == nCnt)
			{
				InsertAtBefore(pListData, pTmp, pParam);
			}
			pTmp = pTmp->pNext;
			nCnt++;
		}
	}
	return 0;
}


int InsertAtHead(LIST_INFO* pListData, void* pParam)
{
	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));

	// 관리 대상 자료에 관한 초기화
	pNode->pData = pParam;

	// 연결 리스트에 관한 초기화
	pNode->pNext = pListData->pHead->pNext;
	pNode->pPrev = pListData->pHead;

	pListData->pHead->pNext = pNode;
	pNode->pNext->pPrev = pNode;

	pListData->nSize++;
	return pListData->nSize;
}

int InsertAtTail(LIST_INFO* pListData, void* pParam)
{
	InsertAtBefore(pListData, pListData->pTail, pParam);

	return pListData->nSize;
}

int InsertAtBefore(LIST_INFO* pListData, NODE* pDstNode, void* pParam)
{
	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));

	pNode->pData = pParam;

	pNode->pNext = pDstNode;
	pNode->pPrev = pDstNode->pPrev;

	pDstNode->pPrev->pNext = pNode;
	pDstNode->pPrev = pNode;

	pListData->nSize++;
	return pListData->nSize;
}

NODE* FindNode(LIST_INFO* pListData, const char* pszKey)
{
	NODE* pTmp = pListData->pHead->pNext;
	const char* (*pfGetKey)(void*) = NULL;

	while (pTmp != pListData->pTail)
	{
		pfGetKey = pTmp->pData;
		if (strcmp((*(const char* (**)(void*))pfGetKey)(pTmp->pData), pszKey) == 0)
			return pTmp;

		pTmp = pTmp->pNext;
	}

	return NULL;
}

int DeleteNode(LIST_INFO* pListData, const char* pszKey)
{
	NODE* pNode = FindNode(pListData, pszKey);

	if (pNode != NULL)
	{
		pNode->pPrev->pNext = pNode->pNext;
		pNode->pNext->pPrev = pNode->pPrev;

		printf("DeleteNode() \n");
		printf("[0x%p]\n\n", pNode);

		free(pNode->pData);
		free(pNode);

		pListData->nSize--;
	}

	return 0;
}

int GetSize(LIST_INFO* pListData)
{
	return pListData->nSize;
}
