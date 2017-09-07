#include "stack.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "linkedlist.h"
#include <string.h>

Snode* top;

/*--------------------------------------------------------------------------------------
함수명및기능 : push() - 스택에 데이터 하나를 저장함

리턴값 : 성공적으로 저장하면 TRUE, 실패하면 FALSE 리턴
--------------------------------------------------------------------------------------*/
int push(Snode* inData) /* stack에 데이터 저장하기 */
{
 	Snode* temp=(Snode *)malloc(sizeof(Snode));
 	temp->year=inData->year;
 	temp->month=inData->month;
 	temp->day=inData->day;
 	temp->money=inData->money;
 	for(int i=0;i<10;i++)
 	{
 		temp->type[i]=inData->type[i];
 	}

 	temp->next=top;
 	top=temp;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능 : pop() - 스택에서 데이터 하나를 꺼냄

리턴값 : 성공적으로 꺼내면 TRUE, 실패하면 FALSE 리턴
--------------------------------------------------------------------------------------*/
void pop()
{
	Snode * temp=top;
	Snode *tmp;
	if (top==NULL)  // stack이 비어있으면 pop실패
	{	
		return ;
	}
	printf("%d-%d-%d|%d|%s\n",temp->year,temp->month,temp->day,temp->money,temp->type);
	top=temp->next;
	free(temp);

}

Snode * dealarrange (linkedListDataType *account){//거래내역 linkedlist 짜기
	Snode * ctmp = NULL, * chead=NULL,*ctmp2=NULL;
	FILE * cf= fopen(strcat(account->name,".txt"),"rt");
	ctmp = ctmp2 = chead = (Snode *)malloc(sizeof(Snode));
	while(fscanf(cf,"%d-%d-%d |%d|%s\n",&(ctmp->year),&(ctmp->month),&(ctmp->day),&(ctmp->money),ctmp->type)!=EOF){
		ctmp2 = ctmp;
		ctmp ->next= (Snode *)malloc(sizeof(Snode));
		ctmp = ctmp->next;
	}
	ctmp2 ->next=NULL;
	free(ctmp);
	fclose(cf);
	return chead;
}
