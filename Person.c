#include "linkedListDataType.h"
#include<string.h>
#include<stdio.h>



int compareAccountNumber(linkedListDataType *p1, linkedListDataType* p2)
{

	int res;
	if (p1->accountNumber > p2->accountNumber) 
	{

		return 1;
	}
	else if (p1->accountNumber< p2->accountNumber)
	{
		return -1;
	}
	else
	{
		return 0;//계좌가 같으면 0 리턴한다
	}

	return 0;
}

int compareName(linkedListDataType *p1, linkedListDataType *p2)
{

	if (strcmp((p1->name), (p2->name))>0)
	{
		return 1;
	}
	else if (strcmp((p1->name), (p2->name))<0)
	{
		return -1;
	}
	else
	{
		return 0;//이름이같으면 0리턴한다
	}

	return 0;

}
int comparePassword(linkedListDataType *p1, linkedListDataType* p2)
{

	int res;
	if (p1->password > p2->password)
	{

		return 1;
	}
	else if (p1->password< p2->password)
	{
		return -1;
	}
	else
	{
		return 0;//계좌가 같으면 0 리턴한다
	}

	return 0;
}

void printPerson(linkedListDataType *p)
{
	printf("회원이름:%s,회원계좌:%d,회원비밀번호:%d\n", p->name, p->accountNumber, p->password);
}
