#pragma once
#pragma warning(disable:4996)
#include "linkedlist.h"
enum { FALSE, TRUE };

typedef struct _stacknode Snode;

struct _stacknode
{
	int year;
	int month;
	int day;
	int money;
	char type[10];
	Snode *next;
};
int push(Snode* inData); /*  스택에 데이터 하나를 저장함 */
void pop(); /*  스택에서 데이터 하나를 꺼냄 */
Snode * dealarrange (linkedListDataType *account); // 거래내역 링크드리스트에 저장
