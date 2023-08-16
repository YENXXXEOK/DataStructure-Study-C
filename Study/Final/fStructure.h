#pragma once
typedef struct NODE
{
	void* pData;

	struct NODE* next;
}NODE;

typedef struct LIST_INFO
{
	const char (*fpGetKey)(void*);

}LIST_INFO;


InsertNode(LIST_INFO* info);
