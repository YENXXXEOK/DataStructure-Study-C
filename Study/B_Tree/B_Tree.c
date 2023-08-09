#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct NODE
{
	char szData[64];
	struct NODE* pLeft;
	struct NODE* pRight;
}NODE;

NODE*	g_pRoot = NULL;
int		g_nSize = 0;

int GetLength();

void ReleaseTree(NODE* pParent)
{
	if (pParent == NULL)
		return;

	ReleaseTree(pParent->pLeft);
	ReleaseTree(pParent->pRight);

	printf("free() : [%p] %s\n", pParent, pParent->szData);

	free(pParent);
	g_pRoot = NULL;
}

void PrintTree(NODE* pParent)
{
	if (pParent == NULL)
		return;
	
	PrintTree(pParent->pLeft);

	printf("[%d] [%p] [%p\t%s\t] [%p]\n", 
		g_nSize,
		pParent->pLeft, 
		pParent, 
		pParent->szData, 
		pParent->pRight);

	PrintTree(pParent->pRight);

	return;
}

NODE* InsertNode(NODE* pParent, const char* pszData)
{
	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));
	memcpy(pNode->szData, pszData, sizeof(pNode->szData));

	if (pParent == NULL)
	{
		pParent = pNode;
		g_nSize++;
		return pParent;
	}

	if (strcmp(pParent->szData, pNode->szData) > 0)
	{
		pParent->pLeft = InsertNode(pParent->pLeft, pszData);
	}
	else
	{
		pParent->pRight = InsertNode(pParent->pRight, pszData);
	}

	return pParent;
}

NODE* FindNode(NODE* pParent, const char* pszData)
{
	if (pParent == NULL)
	{
		return NULL;
	}

	if (strcmp(pParent->szData, pszData) == 0)
	{
		return pParent;
	}
	else if(strcmp(pParent->szData, pszData) > 0)
	{
		return FindNode(pParent->pLeft, pszData);
	}
	else
	{
		return FindNode(pParent->pRight, pszData);
	}
	return NULL;
}


NODE* FindMinNode(NODE* pParent)
{
	if (pParent->pLeft == NULL)
		return pParent;

	return FindMinNode(pParent->pLeft);
}

NODE* DeleteNode(NODE* pParent, const char* pszData)
{ // key ��� ���� �� ��Ʈ ��ȯ
	if (pParent == NULL) 
		return pParent;

	if (strcmp(pParent->szData, pszData) > 0) 			// Ű�� ��Ʈ���� ������ ���� ���� Ʈ���� ����
		pParent->pLeft = DeleteNode(pParent->pLeft, pszData);

	else if (strcmp(pParent->szData, pszData) < 0) 		// Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� ����
		pParent->pRight = DeleteNode(pParent->pRight, pszData);

	else 
	{				
		if (pParent->pLeft == NULL)
		{	
			NODE* pTmp = pParent->pRight;
			free(pParent);
			return pTmp;
		}
		else if (pParent->pRight == NULL)
		{	
			NODE* pTmp = pParent->pLeft;
			free(pParent);
			return pTmp;
		}

		NODE* pTmp = FindMinNode(pParent->pRight); 		// (3)
		memcpy(pParent->szData, pTmp->szData, sizeof(pParent->szData)); 				// ���� Ű ����
		pParent->pRight = DeleteNode(pParent->pRight, pTmp->szData); 	// ���� ��� ����

	}

	return pParent;
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
	g_pRoot = InsertNode(g_pRoot, "05��");
	g_pRoot = InsertNode(g_pRoot, "04��");
	g_pRoot = InsertNode(g_pRoot, "02��");
	g_pRoot = InsertNode(g_pRoot, "01��");
	g_pRoot = InsertNode(g_pRoot, "03��");
	g_pRoot = InsertNode(g_pRoot, "08��");
	g_pRoot = InsertNode(g_pRoot, "06��");
	g_pRoot = InsertNode(g_pRoot, "07��");
	g_pRoot = InsertNode(g_pRoot, "09��");

	PrintTree(g_pRoot);

	g_pRoot = DeleteNode(g_pRoot, "05��");

	printf("\n");
	PrintTree(g_pRoot);

	ReleaseTree(g_pRoot);
}
