#include <stdio.h>

typedef struct NODE
{
	int nData;
	struct NODE* next;
}NODE;

main()
{
	NODE list[5] = { 0, };

	for (int i = 0; i < 4; i++)
	{
		list[i].nData = (i + 1) * 100;
		list[i].next = &list[i + 1];
	}
	list[4].nData = 500;
	list[4].next = NULL;

	for (int i = 0; i < 5; i++)
		printf("[%d] %d\n",i,  list[i].nData);

	NODE* pHead = &list[0];
	for(pHead; pHead != NULL; pHead = pHead->next)
		printf("[0x%p] %d\n", pHead, pHead->nData);
}