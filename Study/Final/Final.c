#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct NODE
{
	char szName[64];
	NODE* next;
}NODE;

NODE* g_head = NULL;


void PrintList()
{
	NODE* pTmp;
}

void InsertNode(const char* szName)
{
	NODE* pNode = (NODE*)malloc(sizeof(pNode));
	memset(pNode, 0, sizeof(pNode));
	memcpy(pNode->szName, szName, sizeof(pNode->szName));

	if (g_head == NULL)
		g_head = pNode;
	else
	{
		pNode->next = g_head->next;
		g_head = pNode;
	}
}
main()
{

}