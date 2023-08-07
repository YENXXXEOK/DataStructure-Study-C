#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct NODE {
	char szData[64];
	struct NODE* next;
}NODE;

NODE g_head = { 0 };

int IsEmpty()
{
	if (g_head.next == NULL)
		return 1;

	return 0;
}
void PrintList()
{
	NODE* pHead = g_head.next;
	while (pHead != NULL)
	{
		printf("[%p] %s (next[%p])\n", pHead, pHead->szData, pHead->next);
		pHead = pHead->next;
	}

	printf("\n");
}

int InsertAtHead(char* pszData)
{
	NODE* pNode;
	pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));
	strcpy_s(pNode->szData, sizeof(pNode->szData), pszData);

	if (IsEmpty() == 1)
		g_head.next = pNode;
	else
	{
		pNode->next = g_head.next;
		g_head.next = pNode;
	}
	return 1;
}


int InsertAtTail(char* pszData)
{
	NODE* pTmp = &g_head;
	while (pTmp->next != NULL)
		pTmp = pTmp->next;


	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));
	strcpy_s(pNode->szData, sizeof(pNode->szData), pszData);

	pTmp->next = pNode;

	return 1;
}
NODE* FindData(char* pszData)
{
	NODE* pCur = g_head.next;
	NODE* pPrev = &g_head;
	while (pCur != NULL)
	{
		if (strcmp(pCur->szData, pszData) == 0)
		{
			return pPrev;
		}
		pCur = pCur->next;
		pPrev = pPrev->next;
	}
	return 0;
}

int DeleteData(char* pszData)
{
	NODE* pPrev = FindData(pszData);
	if (pPrev != NULL)
	{
		NODE* pDelete = pPrev->next;
		pPrev->next = pDelete->next;
		printf("DeleteData() %s\n", pDelete->szData);
		free(pDelete);
		return 1;
	}
	return 0;
}

void ReleaseList()
{
	NODE* pTmp = g_head.next;
	NODE* pDelete;
	while (pTmp != NULL)
	{
		pDelete = pTmp;
		pTmp = pTmp->next;

		printf("Release : [%p] %s\n", pDelete, pDelete->szData);
		free(pDelete);
	}
	g_head.next = NULL;
}

void enQueue(char* pszData)
{
	InsertAtTail(pszData);
}

int deQueue(NODE* queueNode)
{
	NODE* sp = g_head.next;
	if (IsEmpty())
		return 0;

	memcpy(queueNode, sp, sizeof(NODE));
	g_head.next = sp->next;
	free(sp);
	return 1;
}
/*
void enQueue(char* pszData)
{
	InsertAtHead(pszData);
}

int deQueue(NODE* popNode)
{
	NODE* pPre = NULL;
	NODE* pPrev = &g_head;
	NODE* sp = g_head.next;

	if (IsEmpty())
		return 0;

	while (sp != NULL)
	{
		pPre = pPrev;
		pPrev = sp;
		sp = sp->next;
	}

	memcpy(popNode, pPrev, sizeof(NODE));
	pPre->next = NULL;
	free(pPrev);
	return 1;
}
*/
main()
{
	enQueue("TEST01");
	enQueue("TEST02");
	enQueue("TEST03");
	PrintList();

	NODE node = { 0 };

	deQueue(&node);
	printf("deQueue %s \n", node.szData);
	deQueue(&node);
	printf("deQueue %s \n", node.szData);
	deQueue(&node);
	printf("deQueue %s \n", node.szData);

	ReleaseList();
}
