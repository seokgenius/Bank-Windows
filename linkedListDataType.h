#pragma once
#pragma once
typedef struct _Person //고객정보 구조체
{
	char name[50]; //예금주명
	int accountNumber; //계좌번호
	int password; //비밀번호
	int balance; //잔액
}Person;


typedef Person linkedListDataType; //고객정보 구조체 형명 재정의

int compareAccountNumber(linkedListDataType *p1, linkedListDataType* p2); //계좌번호 비교
int compareName(linkedListDataType *p1, linkedListDataType *p2); //예금주명 비교
int comparePassword(linkedListDataType *p1, linkedListDataType* p2); //비밀번호 비교
void printPerson(linkedListDataType *p); //고객정보 출력
