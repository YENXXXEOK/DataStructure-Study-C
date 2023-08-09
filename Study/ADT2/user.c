#include "mylist.h"

typedef struct USERDATA
{
	// 멤버 함수 포인터
	const char* (*pfGetKey)(void*);

	char szName[64];
	char szPhone[64];
}USERDATA;

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

void PrintList(LIST_INFO* pListData)
{
	printf("PrintList() : g_nSize [%d], g_pHead [%p], g_pTail [%p]\n", pListData->nSize, pListData->pHead, pListData->pTail);
	NODE* pTmp = pListData->pHead->pNext;
	while (pTmp != pListData->pTail)
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


void main()
{
	LIST_INFO userList;
	InitList(&userList);

	USERDATA* pData = { 0 };
	pData = CreateUserData("ttt", "010-1111-1111");
	InsertAtTail(&userList, pData);

	pData = CreateUserData("yy", "010-2222-2222");
	InsertAtTail(&userList, pData);

	pData = CreateUserData("etwer", "010-3333-3333");
	InsertAtTail(&userList, pData);


	LIST_INFO userList2;
	InitList(&userList2);

	pData = CreateUserData("ttt", "010-1111-1111");
	InsertAtTail(&userList2, pData);

	pData = CreateUserData("yy", "010-2222-2222");
	InsertAtTail(&userList2, pData);

	pData = CreateUserData("etwer", "010-3333-3333");
	InsertAtTail(&userList2, pData);

	PrintList(&userList);
	//DeleteNode(&userList, "etwer");

	ReleaseList(&userList);

	PrintList(&userList2);
	//DeleteNode(&userList2, "etwer");

	ReleaseList(&userList2);
	return;
}
