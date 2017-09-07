#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include "linkedlist.h"
#include <windows.h>
#include <stdlib.h>

void create(LinkedList *lp){
	lp->head = (Node *)calloc(1, sizeof(Node));//헤드노드생성
	lp->tail = (Node *)calloc(1, sizeof(Node));//테일노드생성

	lp->head->next = lp->tail;
	lp->tail->prev = lp->head;
	lp->head->prev = lp->head;
	lp->tail->next = lp->tail;
	lp->cur = NULL;
	lp->length = 0;

}
void myflush();

Node * searchUnique(LinkedList *lp, linkedListDataType *dataPtr, int(*compare)(linkedListDataType *, linkedListDataType*))
{

	int i;
	lp->cur = lp->head->next;

	for (i = 0; i < lp->length; i++)
	{
		if ((compare(&lp->cur->data, dataPtr)) == 0)
		{
			return lp->cur;
		}
		lp->cur = lp->cur->next;


	}

	return NULL;
}
//찾는 대상이 중복일경우 모두 다 찾음

//------------------------------------------------------------------------------------

//위의 함수들로 만든 함수

void AllClient()  //모든 회원 출력
{
	Node* temp=Clientarrange(); //텍스틍있는 회원 링크드리스트에 읽어오기
	int COUNT=1;
	while(temp!=NULL)
	{
		printf("#%d\n--------------------\n",COUNT);
		printf("예금주 : %s\n",temp->data.name);
		printf("계좌번호 : %d\n",temp->data.accountNumber);
		printf("비밀번호 : %d\n",temp->data.password);
		printf("예금액 : %d 원\n\n",temp->data.balance);

		COUNT++;
		temp=temp->next;
	}
}
void mySearchAccountNumber()//계좌번호로 회원검색
{
	Node *res;
	res= Clientarrange ();
	int ACCOUNTNUMBER;

	printf("(검색)할 회원의 계좌를 입력하시오:");
	scanf("%d", &ACCOUNTNUMBER);
	while(res!=NULL)
	{
		if(res->data.accountNumber==ACCOUNTNUMBER)
		{
			printf("예금주 : %s\n계좌번호 : %d\n비밀번호 : %d\n예금액 : %d 원\n",res->data.name, res->data.accountNumber, res->data.password,res->data.balance);
			return;
		}	
			res=res->next;	
	}

	if (res == NULL)
		printf("일치하는 회원정보가 없습니다.");
}


void mySidSearchAndModify()//계좌번호로 회원 검색후 회원정보수정,비번검사구현아직안함
{
	Node *temp,*tmp;
	temp = tmp =Clientarrange();
	int num;
	int ACCOUNTNUMBER;
	int PASSWORD;
	char NAME[50];
	FILE *fp;

	printf("--------고객확인--------\n");
	printf("계좌를 입력하시오:");
	scanf("%d", &ACCOUNTNUMBER);
	printf("비밀번호를 입력하시오:");
	scanf("%d", &PASSWORD);

	while(temp!=NULL)
	{
		if(temp->data.accountNumber==ACCOUNTNUMBER && temp->data.password==PASSWORD)
		{
			
			printf("--------고객정보수정--------\n");
			printf("원하시는 예금주 명 :");
			scanf("%s",NAME);
			printf("원하시는 비밀번호 : ");
			scanf("%d", &PASSWORD);

			strcpy(temp->data.name,NAME);
			temp->data.password=PASSWORD;

			fp = fopen("client.txt","wt");
			
			while(tmp!=NULL)
			{
				fprintf(fp,"%d | %d | %d | %s\n",tmp->data.accountNumber,tmp->data.password,tmp->data.balance,tmp->data.name);
				tmp=tmp->next;			
			}

			fclose(fp);
			return;
		}

		temp = temp -> next;
	}

	if(temp==NULL)
		printf("일치하는 회원정보가 없습니다.\n");


}


void mySearchName()//이름은 중복 될 수 있으니 검색한 이름의 회원모두 출력
{
	int count = 0;
	int i;
	Node *temp=Clientarrange();
	char NAME[50];

	printf("회원 이름을 입력하시오:");
	scanf("%s", NAME);
	
	while(temp!=NULL)
	{
		if(strcmp(NAME,temp->data.name)==0)
		{	
			count++;
			printf("예금주 : %s\n계좌번호 : %d\n비밀번호 : %d\n예금액 : %d 원\n",temp->data.name, temp->data.accountNumber, temp->data.password, temp->data.balance);
		}

		temp=temp->next;
	}

	if(count==0)
	{
		printf("일치하는 회원정보가 없습니다.");
	}

}

int makeAccount(LinkedList *account) //회원생성
{
	linkedListDataType temp = { "",0,0 };
	int menuNum;
	int money=0;
	printf("#계좌생성모드\n");
	
	FILE *fp;
	fp = fopen("client.txt","at");
	
	while (1) {
		printf("이름을 입력하세요:");
		scanf("%s",temp.name);
		if (getchar() != '\n')
		{
			printf("재입력하시오\n");
			myflush();
		}
		else
		{
			break;
		}
	}
	while (1) {
		printf("계좌번호를 입력하세요:");
		scanf("%d", &temp.accountNumber);

		if (getchar() != '\n')
		{
			printf("재입력하시오\n");
			myflush();
		}
		else
		{
			if (searchUnique(account, &temp, compareAccountNumber) != NULL)
				printf("계좌 중복입니다.재입력하시오\n");
			else
				break;
		}
	}
	while (1) {
		printf("비밀번호를 입력하세요:");
		scanf("%d", &temp.password);
		if (getchar() != '\n')
		{
			printf("재입력하시오\n");
			myflush();
		}
		else
		{
			break;
		}
	}

	fprintf(fp, "%d | %d | %d | %s\n", temp.accountNumber,temp.password,money,temp.name);
	fclose(fp);
	printf("계좌등록완료\n");
	return 0;
}

Node * Clientarrange (){//client linkedlist 짜기(txt파일에서 읽어옴)
	Node * ctmp = NULL, * chead=NULL,*ctmp2=NULL;
	FILE * cf= fopen("client.txt","rt");
	ctmp = ctmp2 = chead = (Node *)malloc(sizeof(Node));
	while(fscanf(cf,"%d | %d | %d | %s\n",&(ctmp->data.accountNumber),&(ctmp->data.password),&(ctmp->data.balance),ctmp->data.name)!=EOF){
		ctmp2 = ctmp;
		ctmp ->next= (Node *)malloc(sizeof(Node));
		ctmp = ctmp->next;
	}
	ctmp2 ->next=NULL;
	free(ctmp);
	fclose(cf);
	return chead;
}

void del_user(){            //계좌 해지
	int ACCOUNTNUMBER;
	int PASSWORD;
	char name[50];
	int n=0;

	printf("예금주 : ");
	scanf("%s",name);
	printf("계좌번호 : ");
	scanf("%d", &ACCOUNTNUMBER);
	printf("비밀번호 : ");
	scanf("%d", &PASSWORD);

	Node * c=NULL, * tmp=NULL,*head = NULL;
	c=tmp=head=Clientarrange();   // 링크드리스트 짜기


	while(tmp!=NULL){
		if(n==0 && c->data.accountNumber==ACCOUNTNUMBER && c->data.password==PASSWORD && strcmp(name,c->data.name)==0 )
		{			
			head= head-> next;
			free(c);
			break;
		}  //삭제할 정보의 위치가 맨앞일때

		n = 1;
		tmp = c;
		c= c-> next;
		if(c->data.accountNumber==ACCOUNTNUMBER && c->data.password==PASSWORD && strcmp(name,c->data.name)==0){
			if(c->next==NULL){				
				tmp->next=NULL;
				free(c);
				break;
			}
			tmp->next=c->next;
			c->next=NULL;
			free(c);
			break;
		}
	}
	
	tmp=head;
	
	FILE * f=fopen("Client.txt","wt");
   	while((tmp->next)!=NULL){
		fprintf(f,"%d | %d | %d | %s\n",head->data.accountNumber,head->data.password,head->data.balance,head->data.name);
		tmp=head;
		head=head->next;
		}
		fclose(f);
		printf("\n탈퇴!!\n");getchar();
		while(getchar()!='\n');
}

void login()     //로그인 함수
{		
	int check=1,check2=0;
	int num;
	int count=0;

	int ACCOUNTNUMBER;
	int PASSWORD;
	char NAME[40];

	Node *c=NULL,*tmp=NULL;

	printf(">>로그인<<");
	printf("\n1. 계좌번호로 확인 2. 이름으로 확인");
	scanf("%d",&num);

	

	tmp=c=Clientarrange();

	if(num == 1){        //계좌번호로 확인

		printf("\n계좌번호 : ");
		scanf("%d",&ACCOUNTNUMBER);
		printf("\n비밀번호 : ");
		scanf("%d",&PASSWORD);

		while(tmp->next!=NULL)//첨부터 끝까지 링크드리스트 돌기
		{	
		
		if(c->data.accountNumber==ACCOUNTNUMBER && c->data.password==PASSWORD)//계좌번호와 PASSWORD 확인
			{
			check=2;
			break;
			}
		tmp=c;
		c=c->next;
		}
	}
	else if(num == 2){     //고객명으로 확인
		printf("\n고객명 : ");
		scanf("%s",NAME);
		printf("\n비밀번호 : ");
		scanf("%d",&PASSWORD);

		while(tmp->next!=NULL)//첨부터 끝까지 링크드리스트 돌기
		{	
		
			if(c->data.password==PASSWORD && strcmp(NAME,c->data.name)==0)//고객명과 PASSWORD 확인
			{					

				if(count==0)
				{
					check=2;
					break;
				}

				count=0;
			}

			tmp=c;
			c=c->next;
		}
	}

	switch(check)
	{
		case 1:
			system("clear");
			printf("\n 등록된 회원이 아닙니다.\n");
			break;
		case 2:
			client(c->data); //회원메뉴
			break;
	}
}

void MoneySelectionSort()     //예금액 순위 선택정렬사용
{	
	int COUNT=1;
	linkedListDataType tmp = { "",0,0,0 };
	Node* cur, *temp, *max, *first;
	first = cur = Clientarrange(); //파일로부터 링크드리스트 생성

	while(cur != NULL)             //선택정렬사용
	{

		if(cur->next ==NULL)
			break;

		temp = cur->next;
		max = temp;

		while(temp != NULL)
		{
			if(max->data.balance < temp->data.balance)
				max=temp;

			temp = temp->next;
		}

		if(cur->data.balance < max->data.balance)      //금액교환
		{
			tmp.balance = max->data.balance; 
			max->data.balance = cur->data.balance;
			cur->data.balance = tmp.balance;

			for(int i=0;i<50;i++)                     //이름교환
			{
				tmp.name[i] = max->data.name[i];
				max->data.name[i] = cur->data.name[i];
				cur->data.name[i] = tmp.name[i];
			}
		}

		cur=cur->next;
	}

	printf("예금액 순위\n");
	printf("---------------------------\n");
	while(first!=NULL)       //바뀐 링크드리스트 그대로 출력     
	{
		printf("%d 등 | %d 원 | %s\n",COUNT, first->data.balance, first->data.name);

		COUNT++;
		first=first->next;
	}

}


