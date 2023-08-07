#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct NODE {
	char szData[64];
	struct NODE* next;
}NODE;

NODE* g_pHead = NULL;
void PrintList()
{
	NODE* pHead = g_pHead;
	while (pHead != NULL)
	{
		printf("[%p] %s (next[%p])\n", pHead, pHead->szData, pHead->next);
		pHead = pHead->next;
	}

	//while (g_pHead != NULL)
	//{
	//	printf("[%p] %s (next[%p])\n", g_pHead, g_pHead->szData, g_pHead->next);
	//	g_pHead = g_pHead->next;
	//}
	printf("\n");
}

int InsertNewNode(char* pszData)
{
	NODE* pNode;
	pNode = (NODE*)malloc(sizeof(NODE));

	memset(pNode, 0, sizeof(NODE));

	strcpy_s(pNode->szData, sizeof(pNode->szData), pszData);

	if (g_pHead == NULL)
		g_pHead = pNode;
	else
	{
		pNode->next = g_pHead;
		g_pHead = pNode;
	}
	return 1;
}

int FindData(char* pszData)
{
	NODE* pTmp = g_pHead;
	while (pTmp != NULL)
	{
		if (strcmp(pTmp->szData, pszData) == 0)
			return 1;
		pTmp = pTmp->next;
	}
	return 0;
}

int DeleteData(char* pszData)
{
	NODE* pTmp = g_pHead;
	NODE* pPrev = NULL;
	while (pTmp != NULL)
	{
		if (strcmp(pTmp->szData, pszData) == 0)
		{ 
			printf("DeleteData() [%p] %s\n", pTmp, pTmp->szData);

			if (pPrev != NULL)
				pPrev->next = pTmp->next;
			else
				g_pHead = pTmp->next;

			free(pTmp);
			return 1;
		}
		pPrev = pTmp;
		pTmp = pTmp->next;
	}
	return 0;
}

void ReleaseList()
{
	NODE* pTmp = g_pHead;
	NODE* pDelete;
	while (pTmp != NULL)
	{
		pDelete = pTmp;
		pTmp = pTmp->next;

		printf("Release : [%p] %s\n", pDelete, pDelete->szData);
		free(pDelete);
	}
	g_pHead = NULL;
}
main()
{
	InsertNewNode("test01");
	PrintList();

	InsertNewNode("test02");
	PrintList();

	InsertNewNode("test03");
	PrintList();

	if (FindData("test01") == 1)
		printf("FindData() test01\n");

	DeleteData("test02");

	ReleaseList();
}