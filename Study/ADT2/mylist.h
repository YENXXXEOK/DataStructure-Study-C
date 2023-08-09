#pragma once
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct NODE
{
	// 관리 대상 자료
	void* pData;

	// 자료 구조
	struct NODE* pPrev;
	struct NODE* pNext;
}NODE;

typedef struct LIST_INFO
{
	NODE*	pHead;
	NODE*	pTail;

	int		nSize;
}LIST_INFO;

void InitList(LIST_INFO* pListData);
void ReleaseList(LIST_INFO* pListData);
NODE* GetAt(LIST_INFO* pListData, int nIdx);
int InsertAt(LIST_INFO* pListData, int nIdx, void* pParam);
int InsertAtHead(LIST_INFO* pListData, void* pParam);
int InsertAtTail(LIST_INFO* pListData, void* pParam);
int InsertAtBefore(LIST_INFO* pListData, NODE* pDstNode, void* pParam);
NODE* FindNode(LIST_INFO* pListData, const char* pszKey);
int DeleteNode(LIST_INFO* pListData, const char* pszKey);
int GetSize(LIST_INFO* pListData);
