#include <stdio.h> 
#include <malloc.h> 
#include <assert.h> 
#include "queue.h" 
#include "stack.h"

/*--------------------------------------------------------------------------------------
함수명및기능 : initQueue() - 큐 초기화 함수
--------------------------------------------------------------------------------------*/
Queuetype* createqueue()      
{
	Queuetype *LQ;
	LQ=(Queuetype*)malloc(sizeof(Queuetype));
	LQ->front=NULL;
	LQ->rear=NULL;

	return LQ;
}

/*--------------------------------------------------------------------------------------
함수명 및 기능: isEmpty() - 큐가 비어있는가 검사

리턴값: 비어있으면 1 리턴, 비어있지 않으면 0 리턴
--------------------------------------------------------------------------------------*/
int isEmpty(Queuetype *lq)
{
	if(lq->front==NULL)
		return 1;
	else 
		return 0;
}
/*--------------------------------------------------------------------------------------
함수명및기능 : enqueue() - 큐에 데이터 하나를 저장함
--------------------------------------------------------------------------------------*/
void enQueue(Queuetype *lq,char newdata[])
{	
	No* newNo=(No*)malloc(sizeof(No));
	for(int i=0;i<10;i++)
	{
	newNo->data[i]=newdata[i];
	}
	newNo->link=NULL;

	if(isEmpty(lq))
	{
		lq->front=newNo;
		lq->rear=newNo;
	}
	else
	{
		lq->rear->link=newNo; //틀림
		lq->rear=newNo;
	}
}

/*--------------------------------------------------------------------------------------
함수명 및 기능 : dequeue() - 큐에서 데이터 하나를 꺼냄
--------------------------------------------------------------------------------------*/
void deQueue(Queuetype *lq)
{
	No* old=lq->front;

	if(isEmpty(lq))return ;
	else
	{
		lq->front=lq->front->link; //
		if(lq->front==NULL)
			lq->rear=NULL;
		
		free(old);
	}
}

/*--------------------------------------------------------------------------------------
함수명 및 기능 : peek() - 큐의 front값 리턴

리턴값: item - 큐의 front값 
--------------------------------------------------------------------------------------*/
char* peek(Queuetype *LQ){
    
    char* item;
    char* nPerson="no";
    if(isEmpty(LQ)) return nPerson;
    else{
        item = LQ->front->data;
        return item;
    }

}
