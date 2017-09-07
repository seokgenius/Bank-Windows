#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include "stack.h"
#include "queue.h"
#include "linkedlist.h"

void client(linkedListDataType *); 
//linkedlist로 이용하여 로그인한 고객정보를 인자로 받고,clientMenu()에서 선택한 메뉴를 리턴값으로 받아서 세부메뉴 진입
int clientMenu(); //고객업무 진입시 만나게 되는 화면
void myflush(); 
void deposit(linkedListDataType *); //입금
void withdraw(linkedListDataType *); //출금
void transactionInfo(linkedListDataType *); //거래내역 확인
int main();
void printwait(); //대기현황 출력(어떤 메뉴에서도 항상 출력)
Node * Clientarrange();
void client(linkedListDataType *account)
{
	int menuNum;
	menuNum = clientMenu();
	while(1)
	{
			if (menuNum == 1)
			{
				system("clear");
				printwait();
				deposit(account);
			}
			else if (menuNum == 2)
			{
				system("clear");
				printwait();
				withdraw(account);
			}
			else if (menuNum == 3)
			{
				transactionInfo(account);
			}
			else if (menuNum == 0)
			{
				main();
			}
			else
			{
				printf("다시 입력하세요\n");
				client(account);
			}
	}
}

int clientMenu() //메뉴번호 입력 받아서 client()함수로 리턴값 전달
{
	char menuNum;
	while(1)
	{
		printf("1.입금 \n2.출금 \n3.거래내역확인 \n0.고객업무종료\n#메뉴입력:");
		scanf(" %c", &menuNum);
		if(getchar() != '\n')
		{
			printf("다시 입력하세요 \n");
			myflush();
		}
		else
		{
			if (menuNum == '1') return 1;
			else if(menuNum == '2') return 2;
			else if(menuNum == '3') return 3;
			else if(menuNum == '0') return 0;
		}
	}
}
void deposit(linkedListDataType *account){ // 입금 
	int d; //입금액
	FILE *fp,*fp2;
	FILE *ifp;
	Node* temp=	Clientarrange();
	fp = fopen("account.txt", "at"); //account.txt에 거래과정 저장
	printf("입금\n-----------------\n입금액 : ");
	scanf("%d", &d);
	account->balance = (account->balance) + d; //입력받은 입금액을 더하여 잔액을 갱신함
	ifp = fopen("client.txt", "wt"); //거래 후 잔액을 client.txt에 덮어쓰기 위함
	
	Node* tmp;
	tmp=temp;
	while(temp!=NULL) //인자로 받은 계좌번호와 일치하는 고객의 잔액을 갱신함
	{
		if(temp->data.accountNumber == account->accountNumber){
			temp->data.balance = account->balance;
		}
		temp = temp->next;
	}
	while(tmp!=NULL) //client.txt에 파일출력
	{
		fprintf(ifp,"%d | %d | %d | %s\n",tmp->data.accountNumber,tmp->data.password,tmp->data.balance,tmp->data.name);
		tmp=tmp->next;
	}
	fclose(ifp);

	fprintf(fp, "%d | %d | %s\n", account->accountNumber,account->balance, account->name); 
	//account.txt에 계좌번호,잔액,이름을 파일출력
	
	fp2 = fopen(strcat(account->name,".txt"),"at");//strcat()함수를 활용하여 고객명 별로 거래내역 파일 생성
	struct tm *t;
	time_t timer;
	timer = time(NULL);
	t = localtime(&timer);
	fprintf(fp2, "%d-%d-%d |%d|입금\n",t->tm_year+1900,t->tm_mon+1,t->tm_mday,d); //거래내역을 현재시각으로 받아서 파일출력
	fclose(fp2);
	printf("\n거래 후 잔액 : %d\n",account->balance); //거래후 잔액 출력
	fclose(fp);
	main(); //메인메뉴로 돌아감
}

void withdraw(linkedListDataType *account){ // 출금(입금 함수와 대부분 유사함)
	int w; //출금액
	FILE *fp,*fp2;
	FILE *ifp;
	Node* temp = Clientarrange();
	fp = fopen("account.txt", "at");
	printf("출금\n-----------------\n출금액 : ");
	scanf("%d", &w);
	account->balance = (account->balance) - w;
	ifp = fopen("client.txt", "wt");

	Node* tmp;
	tmp=temp;
	while(temp!=NULL)
	{
		if(temp->data.accountNumber == account->accountNumber){
			temp->data.balance = account->balance;
		}
		temp = temp->next;
	}
	while(tmp!=NULL)
	{
		fprintf(ifp,"%d | %d | %d | %s\n",tmp->data.accountNumber,tmp->data.password,tmp->data.balance,tmp->data.name);
		tmp=tmp->next;
	}
	fclose(ifp);

	fprintf(fp, "%d | %d | %s\n", account->accountNumber,account->balance,account->name);
	//계좌번호, 이름, 금액 순 파일 출력
	
	fp2 = fopen(strcat(account->name,".txt"),"at");//고객명 별로 거래내역 저장
	struct tm *t;
	time_t timer;
	timer = time(NULL);
	t = localtime(&timer);
	fprintf(fp2, "%d-%d-%d |%d|출금\n",t->tm_year+1900,t->tm_mon+1,t->tm_mday,w);
	fclose(fp2);//거래내역 파일출력
	printf("\n거래 후 잔액 : %d\n",account->balance);
	fclose(fp);
	main();
}

void transactionInfo(linkedListDataType *account){ // 거래내역 확인 
	int a=3; //출력할 거래 내역 건수 지정
	Snode* temp;
	Snode* tmp;
	temp=dealarrange(account);

	printf("\n");
	while(temp!=NULL)
	{
		push(temp); //스택에 거래내역 쌓음
		temp=temp->next;
	}
	
	printf("거래내역\n---------------\n");
	while(a)
	{
		pop(); //가장 최근에 거래한 내역부터 꺼냄
		a--;
	}
	
	main();
}
