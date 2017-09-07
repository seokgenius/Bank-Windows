#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "stack.h"
#include "linkedlist.h"

Queuetype *lq; //큐선언
int totalnum; //총방문인원
int num; //방문대기자수
int mainMenu();//메뉴번호 입력 받아서 main()으로 리턴
void myflush();
void admin(LinkedList *lp);//관리자 메뉴
void printwait(); //대기표발급
void add_Wait(); //대기자 추가
void MoneySelectionSort();//예금액 순위

int main()
{
	int ID;
	lq=createqueue(); // 큐생성
	num=0; 
	totalnum=0; 
	LinkedList Account;
	create(&Account);
	int menuNum;
	while (1)
	{
		printwait(); 
		menuNum = mainMenu();
		if (menuNum == 1)        //계좌생성업무
		{
			system("clear");
			printwait();
			makeAccount(&Account);
		}
		else if (menuNum == 2)    //계좌해지업무
		{
			system("clear");
			printwait();
			del_user();
		}
		else if (menuNum == 3)    //관리자업무
		{
			system("clear");
			printwait();
			admin(&Account);
		}
		else if (menuNum == 4)		//고객업무
		{
			system("clear");
			printwait();
			login();
		}
		else if (menuNum == 5)    //대기열
		{	
			add_Wait();
			system("clear");
		}
		else if(menuNum == 6) //고객1명 업무종료
		{
			deQueue(lq); //업무종료된 고객 delete
			num--;	//대기자수 1감소
			system("clear");
		}
		else if (menuNum ==0)
		{
			exit(-1);
		}

		system("clear");
	}
}
void myflush()
{
	while (getchar() != '\n');
}
int mainMenu()//프로그램 실행시 처음으로 만나는 메인화면,입력후 리턴값 main()으로 전달
{
	char menuNum;
	while (1)
	{
		printf("1.계좌생성\n2.계좌해지\n3.관리자업무\n4.고객업무\np.대기표발급\nq.대기자감소\n0.업무종료\n#메뉴입력:");
		scanf(" %c", &menuNum);

		if (getchar() != '\n')
		{
			printf("입력오류입니다. 다시입력하세요\n");
			myflush();
		}
		else
		{
			if (menuNum == '1')
			{
				return 1;
			}
			else if (menuNum == '2')
			{
				return 2;
			}
			else if (menuNum == '3')
			{
				return 3;
			}
			else if (menuNum == '4')
			{
				return 4;
			}
			else if(menuNum == 'p' || menuNum == 'P')
			{
				return 5;
			}
			else if(menuNum == 'q' || menuNum =='Q')
			{
				return 6;
			}
			else if (menuNum == '0')
			{
				return 0;
			}
			else
			{
				printf("다시 입력하세요\n");
				return mainMenu();
			}
		}
	}

}
void admin(LinkedList *lp)//관리자 메뉴
{
	int menuNum;
	while (1)
	{
		printf("1.고객 정보 검색\n2.고객 정보 수정\n3.예금액 순위\n4.고객 전체 보기\n0.관리자 메뉴 종료\n");
		while (1)
		{
			printf("#메뉴 입력:");
			scanf("%d", &menuNum);
			if (getchar() != '\n')
			{
				printf("재입력하시오\n");
				myflush();

			}
			else
				break;
		}
		if (menuNum == 1)
		{
			while (1)
			{
				printf("#고객정보검색\n1.계좌번호로 검색\n2.예금주 명으로 검색\n");
				scanf("%d", &menuNum);
				if (getchar() != '\n')
				{
					printf("재입력하시오\n");
					myflush();

				}
				else
				{
					if (menuNum == 1)
					{
						mySearchAccountNumber();//계좌번호로 검색
						break;

					}
					else if (menuNum == 2)
					{
						mySearchName();//예금주 명으로 검색
						break;

					}
					else
					{
						printf("재입력하시오\n");
					}
				}
			}

		}
		else if (menuNum == 2)
		{
			mySidSearchAndModify(lp); //고객정보 수정
		}
		else if (menuNum == 3)  //예금액 순위로 소트해서 보여줌.
		{
			MoneySelectionSort();
		}
		else if (menuNum == 4) //모든 고객정보 출력
		{
			AllClient();
		}
		else if (menuNum == 0)
		{
			system("clear"); //관리자 메뉴 종료
			break;
		}
		else
		{
			printf("재입력하시오\n");

		}
	}

}

void printwait()//대기현황,콘솔에 항상 출력되도록 visual 요소 구
{		
		printf("			-------------------------\n");
	 	printf("			총방문자 수 : %d\n",totalnum);
		printf("			대기인원 : %d\n",num);
		printf("			다음차례 : %s\n",peek(lq));
		printf("			-------------------------\n");
}

void add_Wait() //큐를 이용하여 대기표 발급
{
		char name[10];
		printf("이름 : ");
		scanf("%s",name);
		enQueue(lq,name);
		num++;
		totalnum++;
}
