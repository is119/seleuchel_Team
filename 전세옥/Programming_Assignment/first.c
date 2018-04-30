#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <conio.h>

#define InitialCapital 5000
#pragma warning ( disable : 4996 )
#define _CRT_SECURE_NO_WARNINGS

// 이벤트 배열 순서 -> 그대로 사용

#define NONE 0
#define MT 1
#define SchoolBus 2
#define Previous_Exam_Paper 3
#define Scholarship 4

// 족보(아이템) 배열 순서 -> -5 해서 사용

#define FreePass 5
#define AvoidMT 6
#define BusCard 7
#define FreeOverWhelming 8
#define Donation 9

struct Player 
{   
	int PlaceOrder;
    int Money;
	int NumberOfDepartment;
	int Items[5];
	int Events[5];
	int boughtDepartment[20];
	int isAlive;
};

struct Map 
{
	char NameOfDepartment[30];
	int DepartmentOrder;
	int DepartmentPrice;
	int EventNumber;
	int Owner;
	int OverWhelmingDegree;
	COORD pos;
};

void InitMapAndPlayer(struct Player Players[], struct Map Maps[][7]);
void DrawCurrentBoard(struct Player Players[], struct Map Maps[][7], int currentTurn);
void PrintMapInfo(int indexX, int indexY, int startposx, int startposy, struct Map Maps[][7]);
void DrawMapEdge(int i, int j);
void DrawContents(struct Map Maps[][7]);
void PlayersInfo(struct Player Players[], char tmp1[], char tmp2[], char buffer[], struct Map Maps[][7]);
void CurrentPlayerInfo(struct Player Players[], int currentTurn, char tmp1[], char buffer[], struct Map Maps[][7]);
void SearchMapPlace(int* x, int* y, struct Map Maps[][7], struct Player Players[], int PlayerNumber);
void SearchMapPlaceForMap(int* x, int* y, struct Map Maps[][7], struct Player Players[], int PlayerNumber);
void gotoxyAndPrint(int x, int y, char *m);
void gotoxy(int x, int y);

int PlayGame(struct Player Players[], struct Map Maps[][7], int CurrentTurn);
void PlayerStartPosEventChecker(struct Player Players[], struct Map Maps[][7], int CurrentTurn);
void RollTheDIce(struct Player Players[], struct Map Maps[][7], int CurrentTurn);
void PlayerMovedPosEventChecker(struct Player Players[], struct Map Maps[][7], int CurrentTurn);
void BuyingDepartmentProcess(struct Player Players[], struct Map Maps[][7], int CurrentTurn);
void Previous_Exam_PaperEventHandler(struct Player Players[], struct Map Maps[][7], int CurrentTurn);
void DonationEventHandler(struct Player Players[], struct Map Maps[][7], int CurrentTurn);
void BankruptHandler(struct Player Players[], struct Map Maps[][7], int CurrentTurn, int MoneyToPay);
int FindMostExpensiveDepartment(struct Player Players[], struct Map Maps[][7], int CurrentTurn);
int Whoispoor(struct Player Players[]);
void PayTollFee(int Giver, int Recipient, int i, int j, struct Player Players[], struct Map Maps[][7]);

int main (void)
{
	struct Player player[4];
	struct Map map[5][7]; // 세로 5칸, 가로 7 칸
	int winner = 0;
	int currentTurn = 0;

	InitMapAndPlayer(player, map);
	winner = PlayGame(player, map, currentTurn);
	

	system("pause");
	return 0;
}

// 게임 진행 관련 함수들
//
//플레이어 사전 체크(이벤트 여부 & 이동)
//플레이어 이벤트가 MT라면 / MT로 쉬는 날에 - 1을 더한다.그리고 턴을 종료한다.
//플레이어 이벤트가 스쿨버스라면 / 플레이어가 원하는 맵 위치를 입력받아 변경한 후 이동을 종료한다.
//플레이어 이벤트가 스쿨버스나 MT가 아니라면 / 플레이어로부터 스페이스바 값을 주사위 값을 위해 입력 받는다.
//플레이어 현 위치 += 주사위 값 그리고 화면을 다시 출력 + 이동 종료 // 나중에 한칸씩 이동하는 것을 구현한다.
//플레이어 현재 위치 이벤트 여부 확인(턴 종료 or 이동 종료 ? )
//MT이면
//MT회피권이 있다면 / 턴 종료
//없다면 MT로 쉬는 날에 + 2를 한 후 바로 턴종료
//스쿨버스이면 / 플레이어 이벤트에 스쿨버스 변수에 + 1 후 턴 종료
//족보면 / 플레이어 아이템 배열에 랜덤하게 하나 추가
//버스카드이거나 무료 장악이거나 MT회피권 혹은 프리패스 이면 어떤 아이템인지 출력 후 턴 종료
//기부이면 / 모든 플레이어에게 자신이 갖고 있는 가장 비싼 과를 팔아서 가장 현금이 없는 플레이어에게 준다.이후 턴 종료

int TurnOverFlag = 0;

int PlayGame(struct Player Players[], struct Map Maps[][7], int CurrentTurn) // 아직 안씀
{

	int deadpeople = 0;

	while (1)
	{
		DrawCurrentBoard(Players, Maps, CurrentTurn);
		PlayerStartPosEventChecker(Players, Maps, CurrentTurn);
		DrawCurrentBoard(Players, Maps, CurrentTurn);
		
		if (TurnOverFlag != 1 )
		{
			PlayerMovedPosEventChecker(Players, Maps, CurrentTurn);
		}

		if (TurnOverFlag == 1)
		{
			TurnOverFlag = 0;
			CurrentTurn += 1;
			while (Players[CurrentTurn].isAlive != 1)
			{
				CurrentTurn += 1;

				if (CurrentTurn >= 4)
					CurrentTurn = 0;
			}

			if (CurrentTurn >= 4)
				CurrentTurn = 0;

			continue;
		}

		for (int i = 0; i < 4; i++)
		{
			if (Players[i].isAlive == 0)
				deadpeople += 1;
		}

		if (deadpeople == 3)
		{
			for (int i = 0; i < 4; i++)
			{
				if (Players[i].isAlive == 0)
					return i;
			}
		}
	}
}  

void PlayerStartPosEventChecker(struct Player Players[], struct Map Maps[][7], int CurrentTurn)
{
	if (Players[CurrentTurn].Events[MT] > 0)
	{
		Players[CurrentTurn].Events[MT] -= 1;
		gotoxy(0, 33);
		printf("MT로 %d일 동안 더 쉬어야 합니다.", Players[CurrentTurn].Events[MT]);
		_sleep(3000);
		TurnOverFlag = 1;
	}
	else if (Players[CurrentTurn].Events[SchoolBus] > 0)
	{
		int wheretogo = 0;
		gotoxyAndPrint(0, 33, "스쿨버스를 타셨습니다. 어디로 가시겠습니까?\n(왼쪽 위부터 1번이고 시계방향으로 1씩 더해지는 순서입니다.)\n 가고자하는 위치를 입력해주세요 : ");
		scanf_s("%d", &wheretogo);
		Players[CurrentTurn].PlaceOrder = wheretogo;
	}
	else
		RollTheDIce(Players, Maps, CurrentTurn);
}

void RollTheDIce(struct Player Players[], struct Map Maps[][7], int CurrentTurn)
{

	char SpaceBarInput = 0;
	int randomNumber = 0;

	srand(time(NULL));
	gotoxyAndPrint(0, 33, "스페이스바를 눌러 주사위를 굴리세요");
	while (1)
	{
		
		kbhit();
		SpaceBarInput = getch();
		if (SpaceBarInput == 32)
		{
			randomNumber = (rand() % 6) + 1;
			Players[CurrentTurn].PlaceOrder += randomNumber;
			if (Players[CurrentTurn].PlaceOrder > 20)
			{
				Players[CurrentTurn].PlaceOrder -= 20;
				Players[CurrentTurn].Money += 5000;
			}
				
			DrawCurrentBoard(Players, Maps, CurrentTurn);
			return;
		}
	}
}

void PlayerMovedPosEventChecker(struct Player Players[], struct Map Maps[][7], int CurrentTurn )
{
	int NumberForEvent = 0;

	for (int i = 0; i <= 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (Maps[i][j].DepartmentOrder == Players[CurrentTurn].PlaceOrder)
			{
				NumberForEvent = Maps[i][j].EventNumber;
				if (Maps[i][j].Owner >= 0 && Maps[i][j].Owner < 5)
				{
					PayTollFee(CurrentTurn, Maps[i][j].Owner, i, j, Players, Maps);
					TurnOverFlag = 1;
					return;
				}
			}
		}
	}
	switch (NumberForEvent)
	{
	case MT:
		if (Players[CurrentTurn].Items[MT] > 0) // MT 회피권이 있다면
		{
			int yesorno = 0;
			gotoxyAndPrint(2, 118, "MT 회피권이 있습니다. 사용하시겠습니까?(y = 1, n = 2)");
			scanf_s("%d", &yesorno);

			if (yesorno == 1) // 플레이어가 y를 선택했을때
			{
				TurnOverFlag = 1;
				Players[CurrentTurn].Items[MT] -= 1;
				return;
			}
		}
		else
		{
			gotoxyAndPrint(0, 33, "MT에 도착했습니다아!!!!!!!");
			_sleep(3000);
			Players[CurrentTurn].Events[MT] += 3;
			TurnOverFlag = 1;
		}
		break;
	case SchoolBus:
		Players[CurrentTurn].Events[SchoolBus] += 1;
		gotoxyAndPrint(0, 33, "스쿨버스에 도착했습니다아!!!!!!!");
		_sleep(3000);
		TurnOverFlag = 1;
		break;
	case Previous_Exam_Paper:
		gotoxyAndPrint(0, 33, "족보에 도착했습니다아!!!!!!!");
		_sleep(3000);
		Previous_Exam_PaperEventHandler(Players, Maps, CurrentTurn);
		TurnOverFlag = 1;
		break;
	case Scholarship:
		gotoxyAndPrint(0, 33, "장학금에 도착했습니다아!!!!!!! 머니 += 5000 ");
		_sleep(3000);
		Players[CurrentTurn].Money += InitialCapital;
		TurnOverFlag = 1;
		break;
	default : 
		BuyingDepartmentProcess(Players, Maps, CurrentTurn);
		TurnOverFlag = 1;
		break;
	}

} // 이동 후 위치 이벤트 확인

void PayTollFee(int Giver, int Recipient, int i, int j, struct Player Players[], struct Map Maps[][7])
{
	if (Players[Giver].Items[FreePass - 5] > 0)
	{
		gotoxy(0, 33);
		printf("Player%d 님이 Player%d의 땅을 밟으셨습니다.\n", Giver + 1, Recipient + 1);
		printf("프리패스 아이템을 씁니다.", Giver + 1, Recipient + 1);
		_sleep(3000);

		Players[Giver].Items[FreePass - 5] -= 1;
		return;
	}
	gotoxy(0, 33);
	printf("Player%d 님이 Player%d의 땅을 밟으셨습니다.\n", Giver+1, Recipient+1);
	printf("통행료로 %d를 Player%d님에게 줍니다.", Maps[i][j].DepartmentPrice, Recipient+1);
	_sleep(3000);

	Players[Giver].Money -= Maps[i][j].DepartmentPrice;
	Players[Recipient].Money += Maps[i][j].DepartmentPrice;
}

void BuyingDepartmentProcess(struct Player Players[], struct Map Maps[][7], int CurrentTurn)
{
	for (int i = 0; i <= 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (Maps[i][j].DepartmentOrder == Players[CurrentTurn].PlaceOrder)
			{
				if (Maps[i][j].OverWhelmingDegree != 100)
				{
					if (Players[CurrentTurn].Items[FreeOverWhelming-5] == 0)
					{
						int input = 0;
						int OverwhelmingDegree = 0;
						int departmentprice = 0;
						gotoxyAndPrint(0, 33, "현 위치의 과를 장악하시겠습니까? (y = 1, n = 2) : ");
						scanf_s("%d", &input);
						if (input == 2) // n을 입력받으면
						{
							TurnOverFlag = 1;
							return;
						}

						gotoxy(0, 33);
						printf("기본가격은 %d 입니다.                                \n", Maps[i][j].DepartmentPrice);
						printf("얼마나 장악하시겠습니까? (25, 50, 75, 100 중 택 1) : ");
						scanf_s("%d", &OverwhelmingDegree);
						departmentprice = Maps[i][j].DepartmentPrice;

						switch (OverwhelmingDegree)
						{

						case 25:
							if (Players[CurrentTurn].Money < departmentprice)
							{
								BankruptHandler(Players, Maps, CurrentTurn, departmentprice);
							}
							Maps[i][j].OverWhelmingDegree = 25;
							Players[CurrentTurn].Money -= departmentprice;
							break;
						case 50:
							departmentprice = departmentprice * 2;
							if (Players[CurrentTurn].Money < departmentprice)
							{
								BankruptHandler(Players, Maps, CurrentTurn, departmentprice);
							}
							Maps[i][j].OverWhelmingDegree = 50;
							Players[CurrentTurn].Money -= departmentprice;
							break;
						case 75:
							departmentprice = departmentprice * 3;
							if (Players[CurrentTurn].Money < departmentprice)
							{
								BankruptHandler(Players, Maps, CurrentTurn, departmentprice);
							}
							Maps[i][j].OverWhelmingDegree = 75;
							Players[CurrentTurn].Money -= departmentprice;
							break;
						case 100:
							departmentprice = departmentprice * 4;
							if (Players[CurrentTurn].Money < departmentprice)
							{
								BankruptHandler(Players, Maps, CurrentTurn, departmentprice);
							}
							Players[CurrentTurn].Money -= departmentprice;
							Maps[i][j].OverWhelmingDegree = 100;
							Maps[i][j].Owner = CurrentTurn;
							Players[CurrentTurn].NumberOfDepartment++;
							Players[CurrentTurn].boughtDepartment[Players[CurrentTurn].PlaceOrder] = 1;
							break;
						}
						gotoxyAndPrint(0, 33, "구매를 완료했습니다.                                 ");
						_sleep(1500);
					}
					else
					{
						gotoxyAndPrint(0, 33, "무료장악권을 사용하셨습니다.");
						Players[CurrentTurn].Items[FreeOverWhelming - 5] -= 1;
						_sleep(3000);
						Maps[i][j].OverWhelmingDegree = 100;
						Maps[i][j].Owner = CurrentTurn;
						Players[CurrentTurn].NumberOfDepartment++;
						Players[CurrentTurn].boughtDepartment[Players[CurrentTurn].PlaceOrder] = 1;
					}
					
				}
				else
				{
					gotoxyAndPrint(0, 33, "이 과의 장악력은 100퍼센트이기에 구매할 수 없습니다!");
					_sleep(3000);
				}
				return;
					
			}
		}
	}
}

void Previous_Exam_PaperEventHandler(struct Player Players[], struct Map Maps[][7], int CurrentTurn)
{
	int randomNumber = 0;
	srand(time(NULL));
	randomNumber = (rand() % 5) + 5; // 아이템 배열의 상수들은 위에 각각 5,6,7,8,9로 초기화함
	switch (randomNumber)
	{
	case FreePass:
		Players[CurrentTurn].Items[FreePass-5] += 1;
		TurnOverFlag = 1;
		break;
	case AvoidMT:
		Players[CurrentTurn].Items[AvoidMT-5] += 1;
		TurnOverFlag = 1;
		break;
	case BusCard:
		Players[CurrentTurn].PlaceOrder = 11; // 스쿨버스 위치로 이동
		Players[CurrentTurn].Events[SchoolBus-5] += 1;
		TurnOverFlag = 1;
		break;
	case FreeOverWhelming:
		Players[CurrentTurn].Items[FreeOverWhelming-5] += 1;
		TurnOverFlag = 1;
		break;
	case Donation :
		DonationEventHandler(Players, Maps, CurrentTurn);
		TurnOverFlag = 1;
		break;
	}
}

void DonationEventHandler(struct Player Players[] ,struct Map Maps[][7], int CurrentTurn)
{
	if (Players[CurrentTurn].Money < 2000)
		BankruptHandler(Players, Maps, CurrentTurn, 2000);
	else
	{
		int PoorestPlayer = Whoispoor(Players);
		Players[CurrentTurn].Money -= 2000;
		Players[PoorestPlayer].Money += 2000;
		gotoxy(0, 33);
		printf("%d번 플레이어가 %d번 플레이어에게 기부를 합니다.", CurrentTurn+1, PoorestPlayer+1);
		_sleep(3000);
	}
}

void BankruptHandler(struct Player Players[], struct Map Maps[][7], int CurrentTurn, int MoneyToPay) // 플레이어가 소유한 과가 어딘지알아야함.
{
	for (int i = 0; Players[CurrentTurn].Money < MoneyToPay; i++)
	{
		int MostExpensiveDepartment = FindMostExpensiveDepartment(Players, Maps, CurrentTurn);
		
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if (Maps[i][j].DepartmentOrder == MostExpensiveDepartment)
				{
					Players[CurrentTurn].Money += Maps[i][j].DepartmentPrice;
					Players[CurrentTurn].boughtDepartment[MostExpensiveDepartment] = 0;
				}
			}
		}
		if (i == 19)
		{
			gotoxy(2, 118);
			printf("Player%d 는 파산입니다.", CurrentTurn+1);
			Players[Whoispoor(Players)].Money += Players[CurrentTurn].Money;
			Players[CurrentTurn].isAlive = 0;
		}
			
	}
}

int FindMostExpensiveDepartment(struct Player Players[], struct Map Maps[][7], int CurrentTurn)
{
	int TheMostExpensiveDepartment = 0;
	int ExpensiveDepartmentOrder = 0;
	for (int i = 0; i < 20; i++)
	{
		if (Players[CurrentTurn].boughtDepartment[i] == 1) // 해당 과를 해당 플레이어가 샀었다면
		{
			for (int j = 0; j < 5; j++)
			{
				for (int k = 0; k < 7; k++)
				{
					if (Maps[j][k].DepartmentOrder == i && TheMostExpensiveDepartment < Maps[j][k].DepartmentPrice)
					{
						TheMostExpensiveDepartment = Maps[j][k].DepartmentPrice;
						ExpensiveDepartmentOrder = Maps[j][k].DepartmentOrder;
					}
				}
			}
		}
	}
	return ExpensiveDepartmentOrder;
}

int Whoispoor(struct Player Players[])
{
	int money = Players[0].Money;
	int who = 0;
	if (Players[1].Money < money)
	{
		money = Players[1].Money;
		who = 1;
	}
	else if (Players[2].Money < money)
	{
		money = Players[2].Money;
		who = 2;
	}
	else if (Players[3].Money < money)
	{
		money = Players[3].Money;
		who = 3;
	}

	return who;
}


// 맵 그리는 함수들

void InitMapAndPlayer(struct Player Players[], struct Map Maps[][7])
	{
		// 플레이어 초기화

		int const NumberOfPlayers = 4;

		for (int i = 0; i < NumberOfPlayers; i++)
		{
			Players[i].PlaceOrder = 1;
			Players[i].Money = InitialCapital;
			Players[i].NumberOfDepartment = 0;
			Players[i].isAlive = 1;

			for (int j = 0; j < 5; j++)
			{
				Players[i].Items[j] = 0;
				Players[i].Events[j] = 0;
			}

			for (int k = 0; k < 20; k++)
			{
				Players[i].boughtDepartment[k] = 0;
			}
		}

		// 맵 초기화

		{
			int DepartmentPrice = ((rand() % 10) + 1) * 100;

			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					strcpy(Maps[i][j].NameOfDepartment, "NONE");
					Maps[i][j].DepartmentOrder = 0;
					Maps[i][j].DepartmentPrice = 0;
					Maps[i][j].EventNumber = NONE;
					Maps[i][j].Owner = 5;
					Maps[i][j].OverWhelmingDegree = 0;
					Maps[i][j].pos.X = 0;
					Maps[i][j].pos.Y = 0;
				}
			}

			srand(time(NULL));

			// 이름, 학과순서, 가격, 이벤트 숫자, 소유주숫자, 장악정도

			strcpy(Maps[0][0].NameOfDepartment, "장학금");
			Maps[0][0].DepartmentOrder = 1;
			Maps[0][0].DepartmentPrice = 0;
			Maps[0][0].EventNumber = Scholarship;
			Maps[0][0].Owner = 5;
			Maps[0][0].OverWhelmingDegree = NONE;
			Maps[0][0].pos.X = 4;
			Maps[0][0].pos.Y = 6;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[0][1].NameOfDepartment, "건축도시설계전공");
			Maps[0][1].DepartmentOrder = 2;
			Maps[0][1].DepartmentPrice = DepartmentPrice;
			Maps[0][1].Owner = 5;
			Maps[0][1].OverWhelmingDegree = NONE;
			Maps[0][1].pos.X = 22;
			Maps[0][1].pos.Y = 6;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[0][2].NameOfDepartment, "건축공학전공");
			Maps[0][2].DepartmentOrder = 3;
			Maps[0][2].DepartmentPrice = DepartmentPrice;
			Maps[0][2].Owner = 5;
			Maps[0][2].OverWhelmingDegree = NONE;
			Maps[0][2].pos.X = 40;
			Maps[0][2].pos.Y = 6;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[0][3].NameOfDepartment, "고분자공학전공");
			Maps[0][3].DepartmentOrder = 4;
			Maps[0][3].DepartmentPrice = DepartmentPrice;
			Maps[0][3].Owner = 5;
			Maps[0][3].OverWhelmingDegree = NONE;
			Maps[0][3].pos.X = 58;
			Maps[0][3].pos.Y = 6;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[0][4].NameOfDepartment, "융합섬유공학전공");
			Maps[0][4].DepartmentOrder = 5;
			Maps[0][4].DepartmentPrice = DepartmentPrice;
			Maps[0][4].Owner = 5;
			Maps[0][4].OverWhelmingDegree = NONE;
			Maps[0][4].pos.X = 76;
			Maps[0][4].pos.Y = 6;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[0][5].NameOfDepartment, "기계공학전공");
			Maps[0][5].DepartmentOrder = 6;
			Maps[0][5].DepartmentPrice = DepartmentPrice;
			Maps[0][5].Owner = 5;
			Maps[0][5].OverWhelmingDegree = NONE;
			Maps[0][5].pos.X = 94;
			Maps[0][5].pos.Y = 6;

			strcpy(Maps[0][6].NameOfDepartment, "MT");
			Maps[0][6].DepartmentOrder = 7;
			Maps[0][6].DepartmentPrice = 0;
			Maps[0][6].EventNumber = MT;
			Maps[0][6].Owner = 5;
			Maps[0][6].OverWhelmingDegree = NONE;
			Maps[0][6].pos.X = 112;
			Maps[0][6].pos.Y = 6;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[1][6].NameOfDepartment, "전자정보통신공학전공");
			Maps[1][6].DepartmentOrder = 8;
			Maps[1][6].DepartmentPrice = DepartmentPrice;
			Maps[1][6].Owner = 5;
			Maps[1][6].OverWhelmingDegree = NONE;
			Maps[1][6].pos.X = 112;
			Maps[1][6].pos.Y = 12;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[2][6].NameOfDepartment, "컴퓨터정보통신공학전공");
			Maps[2][6].DepartmentOrder = 9;
			Maps[2][6].DepartmentPrice = DepartmentPrice;
			Maps[2][6].Owner = 5;
			Maps[2][6].OverWhelmingDegree = NONE;
			Maps[2][6].pos.X = 112;
			Maps[2][6].pos.Y = 18;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[3][6].NameOfDepartment, "소프트웨어공학전공");
			Maps[3][6].DepartmentOrder = 10;
			Maps[3][6].DepartmentPrice = DepartmentPrice;
			Maps[3][6].Owner = 5;
			Maps[3][6].OverWhelmingDegree = NONE;
			Maps[3][6].pos.X = 112;
			Maps[3][6].pos.Y = 24;

			strcpy(Maps[4][6].NameOfDepartment, "스쿨버스");
			Maps[4][6].DepartmentOrder = 11;
			Maps[4][6].DepartmentPrice = 0;
			Maps[4][6].EventNumber = SchoolBus;
			Maps[4][6].Owner = 5;
			Maps[4][6].OverWhelmingDegree = NONE;
			Maps[4][6].pos.X = 112;
			Maps[4][6].pos.Y = 30;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[4][5].NameOfDepartment, "환경에너지공학과");
			Maps[4][5].DepartmentOrder = 12;
			Maps[4][5].DepartmentPrice = DepartmentPrice;
			Maps[4][5].Owner = 5;
			Maps[4][5].OverWhelmingDegree = NONE;
			Maps[4][5].pos.X = 94;
			Maps[4][5].pos.Y = 30;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[4][4].NameOfDepartment, "생물공학과");
			Maps[4][4].DepartmentOrder = 13;
			Maps[4][4].DepartmentPrice = DepartmentPrice;
			Maps[4][4].Owner = 5;
			Maps[4][4].OverWhelmingDegree = NONE;
			Maps[4][4].pos.X = 76;
			Maps[4][4].pos.Y = 30;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[4][3].NameOfDepartment, "금속재료공학전공");
			Maps[4][3].DepartmentOrder = 14;
			Maps[4][3].DepartmentPrice = DepartmentPrice;
			Maps[4][3].Owner = 5;
			Maps[4][3].OverWhelmingDegree = NONE;
			Maps[4][3].pos.X = 58;
			Maps[4][3].pos.Y = 30;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[4][2].NameOfDepartment, "세라믹재료공학전공");
			Maps[4][2].DepartmentOrder = 15;
			Maps[4][2].DepartmentPrice = DepartmentPrice;
			Maps[4][2].Owner = 5;
			Maps[4][2].OverWhelmingDegree = NONE;
			Maps[4][2].pos.X = 40;
			Maps[4][2].pos.Y = 30;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[4][1].NameOfDepartment, "광.전자재료전공");
			Maps[4][1].DepartmentOrder = 16;
			Maps[4][1].DepartmentPrice = DepartmentPrice;
			Maps[4][1].Owner = 5;
			Maps[4][1].OverWhelmingDegree = NONE;
			Maps[4][1].pos.X = 22;
			Maps[4][1].pos.Y = 30;

			strcpy(Maps[4][0].NameOfDepartment, "족보");
			Maps[4][0].DepartmentOrder = 17;
			Maps[4][0].DepartmentPrice = DepartmentPrice;
			Maps[4][0].EventNumber = Previous_Exam_Paper;
			Maps[4][0].Owner = 5;
			Maps[4][0].OverWhelmingDegree = NONE;
			Maps[4][0].pos.X = 4;
			Maps[4][0].pos.Y = 30;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[3][0].NameOfDepartment, "화공소재전공");
			Maps[3][0].DepartmentOrder = 18;
			Maps[3][0].DepartmentPrice = DepartmentPrice;
			Maps[3][0].Owner = 5;
			Maps[3][0].OverWhelmingDegree = NONE;
			Maps[3][0].pos.X = 4;
			Maps[3][0].pos.Y = 24;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[2][0].NameOfDepartment, "전기공학과");
			Maps[2][0].DepartmentOrder = 19;
			Maps[2][0].DepartmentPrice = DepartmentPrice;
			Maps[2][0].Owner = 5;
			Maps[2][0].OverWhelmingDegree = NONE;
			Maps[2][0].pos.X = 4;
			Maps[2][0].pos.Y = 18;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[1][0].NameOfDepartment, "토목공학과");
			Maps[1][0].DepartmentOrder = 20;
			Maps[1][0].DepartmentPrice = DepartmentPrice;
			Maps[1][0].Owner = 5;
			Maps[1][0].OverWhelmingDegree = NONE;
			Maps[1][0].pos.X = 4;
			Maps[1][0].pos.Y = 12;
		}

	}

void gotoxy(int x, int y)
	{
		COORD Cur;
		Cur.X = x;
		Cur.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
	}

void gotoxyAndPrint(int x, int y, char *m)
	{
		gotoxy(x, y);
		puts(m);
	}

void DrawCurrentBoard(struct Player Players[], struct Map Maps[][7], int currentTurn)
	{
		int i = 0, j = 0;
		system("cls");
		system("mode con: cols=138 lines=48");

		// 맵의 전체적인 외형 만들기

		DrawMapEdge(i, j);

		// 컨텐츠 표현

		DrawContents(Maps);


		char buffer[50] = "";
		char tmp1[50] = "";
		char tmp2[50] = "";

		//플레이어들 스탯, 현 위치 표현

		PlayersInfo(Players, tmp1, tmp2, buffer, Maps);

		// 현 플레이어의 정보( 아이템, 위치한 장소 )표현

		CurrentPlayerInfo(Players, currentTurn, tmp1, buffer, Maps);
		gotoxy(0, 32);
		printf("%d 번 플레이어 차례 입니다.\n", currentTurn + 1);
	}

void PrintMapInfo(int indexX, int indexY, int startposx, int startposy, struct Map Maps[][7])
	{
		gotoxyAndPrint(startposx, startposy, Maps[indexX][indexY].NameOfDepartment);

		if (Maps[indexX][indexY].EventNumber == 0)
		{
			switch (Maps[indexX][indexY].Owner)
			{
			case 0:
				gotoxyAndPrint(startposx, startposy + 1, "주인 : Player1");
				break;
			case 1:
				gotoxyAndPrint(startposx, startposy + 1, "주인 : Player2");
				break;
			case 2:
				gotoxyAndPrint(startposx, startposy + 1, "주인 : Player3");
				break;
			case 3:
				gotoxyAndPrint(startposx, startposy + 1, "주인 : Player4");
				break;
			default:
				gotoxyAndPrint(startposx, startposy + 1, "주인 : 없음");
				break;
			}

			switch (Maps[indexX][indexY].OverWhelmingDegree)
			{
			case 0:
				gotoxyAndPrint(startposx, startposy + 2, "장악력 : 없음");
				break;
			case 25:
				gotoxyAndPrint(startposx, startposy + 2, "장악력 : 25%");
				break;
			case 50:
				gotoxyAndPrint(startposx, startposy + 2, "장악력 : 50%");
				break;
			case 75:
				gotoxyAndPrint(startposx, startposy + 2, "장악력 : 75%");
				break;
			case 100:
				gotoxyAndPrint(startposx, startposy + 2, "장악력 : 100%");
				break;
			}
		}
	}

void DrawMapEdge(int i, int j)
	{
		// 외부테두리
		gotoxyAndPrint(2, 1, "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
		for (i = 2; i<31; i++)
			gotoxyAndPrint(2, i, "┃                                                                                                                                   ┃");
		gotoxyAndPrint(2, i, "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

		// 내부테두리
		gotoxyAndPrint(20, 7, "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
		for (i = 8; i<25; i++)
			gotoxyAndPrint(20, i, "┃                                                                                         ┃");
		gotoxyAndPrint(20, i, "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

		// 위쪽줄
		for (j = 0; j<6; j++)
		{
			int l = 0;
			if (l == 0)
				l = 20;
			gotoxyAndPrint(l + 20 * j - j * 2, 1, "┳");
			for (i = 2; i<7; i++)
				gotoxyAndPrint(l + 20 * j - j * 2, i, "┃");
			if (j == 0)
				gotoxyAndPrint(l + 20 * j - j * 2, i, "╋");
			else
				gotoxyAndPrint(l + 20 * j - j * 2, i, "┻");

		}

		// 아래쪽줄
		for (j = 0; j<6; j++)
		{
			int l = 0;
			if (l == 0)
				l = 20;
			if (j == 0)
				gotoxyAndPrint(l + 20 * j - j * 2, 25, "╋");
			else
				gotoxyAndPrint(l + 20 * j - j * 2, 25, "┳");
			for (i = 26; i<31; i++)
				gotoxyAndPrint(l + 20 * j - j * 2, i, "┃");
			gotoxyAndPrint(l + 20 * j - j * 2, i, "┻");
		}

		// 왼쪽줄
		gotoxyAndPrint(2, 7, "┣━━━━━━━━━━━━━━━━");
		gotoxyAndPrint(2, 13, "┣━━━━━━━━━━━━━━━━━┫");
		gotoxyAndPrint(2, 19, "┣━━━━━━━━━━━━━━━━━┫");
		gotoxyAndPrint(2, 25, "┣━━━━━━━━━━━━━━━━");

		// 오른쪽줄
		gotoxyAndPrint(110, 7, "╋━━━━━━━━━━━━━━━━━━━━━━━┫");
		gotoxyAndPrint(110, 13, "┣━━━━━━━━━━━━━━━━━━━━━━━┫");
		gotoxyAndPrint(110, 19, "┣━━━━━━━━━━━━━━━━━━━━━━━┫");
		gotoxyAndPrint(110, 25, "╋━━━━━━━━━━━━━━━━━━━━━━━┫");

		gotoxyAndPrint(109, 7, "━");
		gotoxyAndPrint(109, 25, "━");
	}

void DrawContents(struct Map Maps[][7])
	{
		// 컨텐츠 위쪽

		int indexy = 0;
		for (int startposx = 4; startposx <= 112; startposx += 18)
		{
			int const startposy = 2;
			PrintMapInfo(0, indexy, startposx, startposy, Maps);
			indexy++;
		}

		// 컨텐츠 아래쪽
		indexy = 0;
		for (int startposx = 4; startposx <= 112; startposx += 18)
		{
			int const startposy = 26;
			PrintMapInfo(4, indexy, startposx, startposy, Maps);
			indexy++;
		}

		// 컨텐츠 왼쪽
		PrintMapInfo(1, 0, 4, 8, Maps);
		PrintMapInfo(2, 0, 4, 14, Maps);
		PrintMapInfo(3, 0, 4, 20, Maps);

		// 컨텐츠 오른쪽
		PrintMapInfo(1, 6, 112, 8, Maps);
		PrintMapInfo(2, 6, 112, 14, Maps);
		PrintMapInfo(3, 6, 112, 20, Maps);
	}

void PlayersInfo(struct Player Players[], char tmp1[], char tmp2[], char buffer[], struct Map Maps[][7])
	{
		// 건물 수와 재산

		gotoxyAndPrint(22, 9, "[ 플레이어 : 건물수 / 재산 ]");

		for (int i = 0; i < 5; i++)
		{
			if (Players[i].isAlive == 1)
			{
				itoa(Players[i].NumberOfDepartment, tmp1, 10);
				itoa(Players[i].Money, tmp2, 10);
				sprintf(buffer, "Player %d : %s / %s", i + 1, tmp1, tmp2);
				gotoxyAndPrint(22, 10 + i, buffer);
			}
			
		}

		// 플레이어들 맵상 위치 표현

		for (int NumberOfPlayers = 0; NumberOfPlayers < 4; NumberOfPlayers++)
		{
			if (Players[NumberOfPlayers].isAlive == 1)
			{
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 7; j++)
					{
						if (Maps[i][j].DepartmentOrder == Players[NumberOfPlayers].PlaceOrder)
						{
							itoa(NumberOfPlayers + 1, buffer, 10);
							gotoxyAndPrint(Maps[i][j].pos.X + NumberOfPlayers , Maps[i][j].pos.Y, buffer);
						}
					}
				}
			}
		}
	}

void CurrentPlayerInfo(struct Player Players[], int currentTurn, char tmp1[], char buffer[], struct Map Maps[][7])
	{
		// 현 플레이어가 가지고 있는 아이템

		int x = 0;
		int y = 0;

		gotoxyAndPrint(80, 9, "[ 현 플레이어의 아이템 목록 ]");

		itoa(Players[currentTurn].Items[FreePass - 5], tmp1, 10);
		sprintf(buffer, "프리패스 : %s", tmp1);
		gotoxyAndPrint(80, 10, buffer);

		itoa(Players[currentTurn].Items[AvoidMT - 5], tmp1, 10);
		sprintf(buffer, "MT회피권 : %s", tmp1);
		gotoxyAndPrint(80, 11, buffer);

		itoa(Players[currentTurn].Items[BusCard - 5], tmp1, 10);
		sprintf(buffer, "버스카드 : %s", tmp1);
		gotoxyAndPrint(80, 12, buffer);

		itoa(Players[currentTurn].Items[FreeOverWhelming - 5], tmp1, 10);
		sprintf(buffer, "무료장악 : %s", tmp1);
		gotoxyAndPrint(80, 13, buffer);

		itoa(Players[currentTurn].Items[Donation - 5], tmp1, 10);
		sprintf(buffer, "기부     : %s", tmp1);
		gotoxyAndPrint(80, 14, buffer);

		// 현 위치에 대한 정보 표현

		gotoxyAndPrint(22, 20, "[현재 플레이어가 위치한 장소의 정보]");
		for (int x = 0; x < 5; x++)
		{
			for (int y = 0; y < 7; y++)
			{
				if (Players[currentTurn].PlaceOrder == Maps[x][y].DepartmentOrder)
				{
					gotoxyAndPrint(22, 21, Maps[x][y].NameOfDepartment);

					if (Maps[x][y].EventNumber == 0)
					{
						itoa(Maps[x][y].DepartmentPrice, tmp1, 10);
						sprintf(buffer, "기본 가격 : %s", tmp1);
						gotoxyAndPrint(22, 22, buffer);

						itoa(Maps[x][y].OverWhelmingDegree, tmp1, 10);
						sprintf(buffer, "장악 정도 : %s", tmp1);
						gotoxyAndPrint(22, 23, buffer);
					}
				}
			}
		}
	}

void SearchMapPlace(int* x, int* y, struct Map Maps[][7], struct Player Players[], int PlayerNumber)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if (Maps[i][j].DepartmentOrder == Players[PlayerNumber].PlaceOrder)
				{
					*x = Maps[i][j].pos.X + PlayerNumber;
					*y = Maps[i][j].pos.Y;
					return;
				}
			}
		}
	}

void SearchMapPlaceForMap(int* x, int* y, struct Map Maps[][7], struct Player Players[], int PlayerNumber)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (Maps[i][j].DepartmentOrder == Players[PlayerNumber].PlaceOrder)
			{
				*x = i;
				*y = j;
				return;
			}
		}
	}
}



//디버깅 해야 될 것들
//4. 1명이라도 파산되면 이후 게임 진행이 안됨.
// 마지막. 아이템 사용 함수 작동 여부