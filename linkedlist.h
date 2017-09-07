#pragma once
#pragma once
#pragma warning(disable:4996)
#include "linkedListDataType.h"

typedef struct _node Node;

struct _node {

	Node *prev;
	linkedListDataType data;
	Node *next;

};

typedef struct _linkedList
{
	Node *head;
	Node *cur;
	Node *tail;
	int length;

}LinkedList;
void del_user(); //회원삭제
Node * Clientarrange (); //txt파일 읽어와 링크드리스트에 넣어주기
void create(LinkedList *lp); //링크드리스트생성

Node * searchUnique(LinkedList *lp, linkedListDataType *dataptr, int(*compare)(linkedListDataType *, linkedListDataType *));
void mySearchAccountNumber();//계좌번호로 회원검색
void mySidSearchAndModify();//계좌번호로 회원 검색후 회원정보수정,비번검사구현아직안함
void mySearchName();//이름은 중복 될 수 있으니 검색한 이름의 회원모두 출력
void myDleltePerson(LinkedList *lp);//회원 삭제
int makeAccount(LinkedList *); //회원추가
void login();//로그인
void client();//고객기능 메뉴
void AllClient();//모든 회원 출력
