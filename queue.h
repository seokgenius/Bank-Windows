
#pragma once 
#pragma warning(disable:4996)


typedef struct No{
	char data[10]; //고객명
	struct No* link;
}No;                        //노드 구조체 정의

typedef struct Queuetype{
	No* front;
	No* rear;
}Queuetype;				//큐 구조체 정의

Queuetype* createqueue(); //큐 초기화
int isEmpty(Queuetype *lq); //큐가 비어있는지 검사
void enQueue(Queuetype *lq,char newdata[]); //큐에 데이터하나 추가
void deQueue(Queuetype *lq); //큐에서 데이터 하나 제거
char* peek(Queuetype *LQ); //큐의 front에 있는 data 출력
