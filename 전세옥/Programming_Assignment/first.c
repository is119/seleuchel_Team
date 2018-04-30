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

// ÀÌº¥Æ® ¹è¿­ ¼ø¼­ -> ±×´ë·Î »ç¿ë

#define NONE 0
#define MT 1
#define SchoolBus 2
#define Previous_Exam_Paper 3
#define Scholarship 4

// Á·º¸(¾ÆÀÌÅÛ) ¹è¿­ ¼ø¼­ -> -5 ÇØ¼­ »ç¿ë

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
	struct Map map[5][7]; // ¼¼·Î 5Ä­, °¡·Î 7 Ä­
	int winner = 0;
	int currentTurn = 0;

	InitMapAndPlayer(player, map);
	winner = PlayGame(player, map, currentTurn);
	
	system("cls");
	printf("ÇÃ·¹ÀÌ¾î%d¹øÀÌ ½Â¸®ÇÏ¼Ì½À´Ï´Ù.!!!", winner);
	system("pause");
	return 0;
}

int TurnOverFlag = 0;

// play °ü·Ã ÇÔ¼ö

int PlayGame(struct Player Players[], struct Map Maps[][7], int CurrentTurn) // ¾ÆÁ÷ ¾È¾¸
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

			for (int i = 0; i < 4; i++)
			{
				if (Players[i].isAlive == 0)
					deadpeople += 1;
			}

			if (deadpeople == 3)
			{
				for (int i = 0; i < 4; i++)
				{
					if (Players[i].isAlive == 1)
						return i+1;
				}
			}
			continue;
		}
	}
}  

void PlayerStartPosEventChecker(struct Player Players[], struct Map Maps[][7], int CurrentTurn)
{
	if (Players[CurrentTurn].Events[MT] > 0)
	{
		Players[CurrentTurn].Events[MT] -= 1;
		gotoxy(0, 33);
		printf("MT·Î %dÀÏ µ¿¾È ´õ ½¬¾î¾ß ÇÕ´Ï´Ù.", Players[CurrentTurn].Events[MT]);
		_sleep(3000);
		TurnOverFlag = 1;
	}
	else if (Players[CurrentTurn].Events[SchoolBus] > 0)
	{
		int wheretogo = 0;
		gotoxyAndPrint(0, 33, "½ºÄð¹ö½º¸¦ Å¸¼Ì½À´Ï´Ù. ¾îµð·Î °¡½Ã°Ú½À´Ï±î?\n(¿ÞÂÊ À§ºÎÅÍ 1¹øÀÌ°í ½Ã°è¹æÇâÀ¸·Î 1¾¿ ´õÇØÁö´Â ¼ø¼­ÀÔ´Ï´Ù.)\n °¡°íÀÚÇÏ´Â À§Ä¡¸¦ ÀÔ·ÂÇØÁÖ¼¼¿ä : ");
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
	gotoxyAndPrint(0, 33, "½ºÆäÀÌ½º¹Ù¸¦ ´­·¯ ÁÖ»çÀ§¸¦ ±¼¸®¼¼¿ä");
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
		if (Players[CurrentTurn].Items[MT] > 0) // MT È¸ÇÇ±ÇÀÌ ÀÖ´Ù¸é
		{
			int yesorno = 0;
			gotoxyAndPrint(2, 118, "MT È¸ÇÇ±ÇÀÌ ÀÖ½À´Ï´Ù. »ç¿ëÇÏ½Ã°Ú½À´Ï±î?(y = 1, n = 2)");
			scanf_s("%d", &yesorno);

			if (yesorno == 1) // ÇÃ·¹ÀÌ¾î°¡ y¸¦ ¼±ÅÃÇßÀ»¶§
			{
				TurnOverFlag = 1;
				Players[CurrentTurn].Items[MT] -= 1;
				return;
			}
		}
		else
		{
			gotoxyAndPrint(0, 33, "MT¿¡ µµÂøÇß½À´Ï´Ù¾Æ!!!!!!!");
			_sleep(3000);
			Players[CurrentTurn].Events[MT] += 3;
			TurnOverFlag = 1;
		}
		break;
	case SchoolBus:
		Players[CurrentTurn].Events[SchoolBus] += 1;
		gotoxyAndPrint(0, 33, "½ºÄð¹ö½º¿¡ µµÂøÇß½À´Ï´Ù¾Æ!!!!!!!");
		_sleep(3000);
		TurnOverFlag = 1;
		break;
	case Previous_Exam_Paper:
		gotoxyAndPrint(0, 33, "Á·º¸¿¡ µµÂøÇß½À´Ï´Ù¾Æ!!!!!!!");
		_sleep(3000);
		Previous_Exam_PaperEventHandler(Players, Maps, CurrentTurn);
		TurnOverFlag = 1;
		break;
	case Scholarship:
		gotoxyAndPrint(0, 33, "ÀåÇÐ±Ý¿¡ µµÂøÇß½À´Ï´Ù¾Æ!!!!!!! ¸Ó´Ï += 5000 ");
		_sleep(3000);
		Players[CurrentTurn].Money += InitialCapital;
		TurnOverFlag = 1;
		break;
	default : 
		BuyingDepartmentProcess(Players, Maps, CurrentTurn);
		TurnOverFlag = 1;
		break;
	}

} // ÀÌµ¿ ÈÄ À§Ä¡ ÀÌº¥Æ® È®ÀÎ

void PayTollFee(int Giver, int Recipient, int i, int j, struct Player Players[], struct Map Maps[][7])
{
	if (Players[Giver].Items[FreePass - 5] > 0)
	{
		gotoxy(0, 33);
		printf("Player%d ´ÔÀÌ Player%dÀÇ ¶¥À» ¹âÀ¸¼Ì½À´Ï´Ù.\n", Giver + 1, Recipient + 1);
		printf("ÇÁ¸®ÆÐ½º ¾ÆÀÌÅÛÀ» ¾¹´Ï´Ù.", Giver + 1, Recipient + 1);
		_sleep(3000);

		Players[Giver].Items[FreePass - 5] -= 1;
		return;
	}
	gotoxy(0, 33);
	printf("Player%d ´ÔÀÌ Player%dÀÇ ¶¥À» ¹âÀ¸¼Ì½À´Ï´Ù.\n", Giver+1, Recipient+1);
	printf("ÅëÇà·á·Î %d¸¦ Player%d´Ô¿¡°Ô ÁÝ´Ï´Ù.", Maps[i][j].DepartmentPrice, Recipient+1);
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
						gotoxyAndPrint(0, 33, "Çö À§Ä¡ÀÇ °ú¸¦ Àå¾ÇÇÏ½Ã°Ú½À´Ï±î? (y = 1, n = 2) : ");
						scanf_s("%d", &input);
						if (input == 2) // nÀ» ÀÔ·Â¹ÞÀ¸¸é
						{
							TurnOverFlag = 1;
							return;
						}

						gotoxy(0, 33);
						printf("±âº»°¡°ÝÀº %d ÀÔ´Ï´Ù.                                \n", Maps[i][j].DepartmentPrice);
						printf("¾ó¸¶³ª Àå¾ÇÇÏ½Ã°Ú½À´Ï±î? (25, 50, 75, 100 Áß ÅÃ 1) : ");
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
								return;
							}
							Players[CurrentTurn].Money -= departmentprice;
							Maps[i][j].OverWhelmingDegree = 100;
							Maps[i][j].Owner = CurrentTurn;
							Players[CurrentTurn].NumberOfDepartment++;
							Players[CurrentTurn].boughtDepartment[Players[CurrentTurn].PlaceOrder] = 1;
							break;
						}
						gotoxyAndPrint(0, 33, "±¸¸Å¸¦ ¿Ï·áÇß½À´Ï´Ù.                                 ");
						_sleep(1500);
					}
					else
					{
						gotoxyAndPrint(0, 33, "¹«·áÀå¾Ç±ÇÀ» »ç¿ëÇÏ¼Ì½À´Ï´Ù.");
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
					gotoxyAndPrint(0, 33, "ÀÌ °úÀÇ Àå¾Ç·ÂÀº 100ÆÛ¼¾Æ®ÀÌ±â¿¡ ±¸¸ÅÇÒ ¼ö ¾ø½À´Ï´Ù!");
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
	randomNumber = (rand() % 5) + 5; // ¾ÆÀÌÅÛ ¹è¿­ÀÇ »ó¼öµéÀº À§¿¡ °¢°¢ 5,6,7,8,9·Î ÃÊ±âÈ­ÇÔ
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
		Players[CurrentTurn].PlaceOrder = 11; // ½ºÄð¹ö½º À§Ä¡·Î ÀÌµ¿
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
		printf("%d¹ø ÇÃ·¹ÀÌ¾î°¡ %d¹ø ÇÃ·¹ÀÌ¾î¿¡°Ô ±âºÎ¸¦ ÇÕ´Ï´Ù.", CurrentTurn+1, PoorestPlayer+1);
		_sleep(3000);
	}
}

void BankruptHandler(struct Player Players[], struct Map Maps[][7], int CurrentTurn, int MoneyToPay) // ÇÃ·¹ÀÌ¾î°¡ ¼ÒÀ¯ÇÑ °ú°¡ ¾îµòÁö¾Ë¾Æ¾ßÇÔ.
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
			printf("Player%d ´Â ÆÄ»êÀÔ´Ï´Ù.", CurrentTurn+1);
			Players[Whoispoor(Players)].Money += Players[CurrentTurn].Money;
			Players[CurrentTurn].isAlive = 0;
			return;
		}
			
	}
}

int FindMostExpensiveDepartment(struct Player Players[], struct Map Maps[][7], int CurrentTurn)
{
	int TheMostExpensiveDepartment = 0;
	int ExpensiveDepartmentOrder = 0;
	for (int i = 0; i < 20; i++)
	{
		if (Players[CurrentTurn].boughtDepartment[i] == 1) // ÇØ´ç °ú¸¦ ÇØ´ç ÇÃ·¹ÀÌ¾î°¡ »ò¾ú´Ù¸é
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


// ¸Ê ±×¸®´Â ÇÔ¼öµé

void InitMapAndPlayer(struct Player Players[], struct Map Maps[][7])
	{
		// ÇÃ·¹ÀÌ¾î ÃÊ±âÈ­

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

		// ¸Ê ÃÊ±âÈ­

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

			// ÀÌ¸§, ÇÐ°ú¼ø¼­, °¡°Ý, ÀÌº¥Æ® ¼ýÀÚ, ¼ÒÀ¯ÁÖ¼ýÀÚ, Àå¾ÇÁ¤µµ

			strcpy(Maps[0][0].NameOfDepartment, "ÀåÇÐ±Ý");
			Maps[0][0].DepartmentOrder = 1;
			Maps[0][0].DepartmentPrice = 0;
			Maps[0][0].EventNumber = Scholarship;
			Maps[0][0].Owner = 5;
			Maps[0][0].OverWhelmingDegree = NONE;
			Maps[0][0].pos.X = 4;
			Maps[0][0].pos.Y = 6;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[0][1].NameOfDepartment, "°ÇÃàµµ½Ã¼³°èÀü°ø");
			Maps[0][1].DepartmentOrder = 2;
			Maps[0][1].DepartmentPrice = DepartmentPrice;
			Maps[0][1].Owner = 5;
			Maps[0][1].OverWhelmingDegree = NONE;
			Maps[0][1].pos.X = 22;
			Maps[0][1].pos.Y = 6;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[0][2].NameOfDepartment, "°ÇÃà°øÇÐÀü°ø");
			Maps[0][2].DepartmentOrder = 3;
			Maps[0][2].DepartmentPrice = DepartmentPrice;
			Maps[0][2].Owner = 5;
			Maps[0][2].OverWhelmingDegree = NONE;
			Maps[0][2].pos.X = 40;
			Maps[0][2].pos.Y = 6;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[0][3].NameOfDepartment, "°íºÐÀÚ°øÇÐÀü°ø");
			Maps[0][3].DepartmentOrder = 4;
			Maps[0][3].DepartmentPrice = DepartmentPrice;
			Maps[0][3].Owner = 5;
			Maps[0][3].OverWhelmingDegree = NONE;
			Maps[0][3].pos.X = 58;
			Maps[0][3].pos.Y = 6;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[0][4].NameOfDepartment, "À¶ÇÕ¼¶À¯°øÇÐÀü°ø");
			Maps[0][4].DepartmentOrder = 5;
			Maps[0][4].DepartmentPrice = DepartmentPrice;
			Maps[0][4].Owner = 5;
			Maps[0][4].OverWhelmingDegree = NONE;
			Maps[0][4].pos.X = 76;
			Maps[0][4].pos.Y = 6;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[0][5].NameOfDepartment, "±â°è°øÇÐÀü°ø");
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
			strcpy(Maps[1][6].NameOfDepartment, "ÀüÀÚÁ¤º¸Åë½Å°øÇÐÀü°ø");
			Maps[1][6].DepartmentOrder = 8;
			Maps[1][6].DepartmentPrice = DepartmentPrice;
			Maps[1][6].Owner = 5;
			Maps[1][6].OverWhelmingDegree = NONE;
			Maps[1][6].pos.X = 112;
			Maps[1][6].pos.Y = 12;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[2][6].NameOfDepartment, "ÄÄÇ»ÅÍÁ¤º¸Åë½Å°øÇÐÀü°ø");
			Maps[2][6].DepartmentOrder = 9;
			Maps[2][6].DepartmentPrice = DepartmentPrice;
			Maps[2][6].Owner = 5;
			Maps[2][6].OverWhelmingDegree = NONE;
			Maps[2][6].pos.X = 112;
			Maps[2][6].pos.Y = 18;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[3][6].NameOfDepartment, "¼ÒÇÁÆ®¿þ¾î°øÇÐÀü°ø");
			Maps[3][6].DepartmentOrder = 10;
			Maps[3][6].DepartmentPrice = DepartmentPrice;
			Maps[3][6].Owner = 5;
			Maps[3][6].OverWhelmingDegree = NONE;
			Maps[3][6].pos.X = 112;
			Maps[3][6].pos.Y = 24;

			strcpy(Maps[4][6].NameOfDepartment, "½ºÄð¹ö½º");
			Maps[4][6].DepartmentOrder = 11;
			Maps[4][6].DepartmentPrice = 0;
			Maps[4][6].EventNumber = SchoolBus;
			Maps[4][6].Owner = 5;
			Maps[4][6].OverWhelmingDegree = NONE;
			Maps[4][6].pos.X = 112;
			Maps[4][6].pos.Y = 30;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[4][5].NameOfDepartment, "È¯°æ¿¡³ÊÁö°øÇÐ°ú");
			Maps[4][5].DepartmentOrder = 12;
			Maps[4][5].DepartmentPrice = DepartmentPrice;
			Maps[4][5].Owner = 5;
			Maps[4][5].OverWhelmingDegree = NONE;
			Maps[4][5].pos.X = 94;
			Maps[4][5].pos.Y = 30;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[4][4].NameOfDepartment, "»ý¹°°øÇÐ°ú");
			Maps[4][4].DepartmentOrder = 13;
			Maps[4][4].DepartmentPrice = DepartmentPrice;
			Maps[4][4].Owner = 5;
			Maps[4][4].OverWhelmingDegree = NONE;
			Maps[4][4].pos.X = 76;
			Maps[4][4].pos.Y = 30;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[4][3].NameOfDepartment, "±Ý¼ÓÀç·á°øÇÐÀü°ø");
			Maps[4][3].DepartmentOrder = 14;
			Maps[4][3].DepartmentPrice = DepartmentPrice;
			Maps[4][3].Owner = 5;
			Maps[4][3].OverWhelmingDegree = NONE;
			Maps[4][3].pos.X = 58;
			Maps[4][3].pos.Y = 30;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[4][2].NameOfDepartment, "¼¼¶ó¹ÍÀç·á°øÇÐÀü°ø");
			Maps[4][2].DepartmentOrder = 15;
			Maps[4][2].DepartmentPrice = DepartmentPrice;
			Maps[4][2].Owner = 5;
			Maps[4][2].OverWhelmingDegree = NONE;
			Maps[4][2].pos.X = 40;
			Maps[4][2].pos.Y = 30;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[4][1].NameOfDepartment, "±¤.ÀüÀÚÀç·áÀü°ø");
			Maps[4][1].DepartmentOrder = 16;
			Maps[4][1].DepartmentPrice = DepartmentPrice;
			Maps[4][1].Owner = 5;
			Maps[4][1].OverWhelmingDegree = NONE;
			Maps[4][1].pos.X = 22;
			Maps[4][1].pos.Y = 30;

			strcpy(Maps[4][0].NameOfDepartment, "Á·º¸");
			Maps[4][0].DepartmentOrder = 17;
			Maps[4][0].DepartmentPrice = DepartmentPrice;
			Maps[4][0].EventNumber = Previous_Exam_Paper;
			Maps[4][0].Owner = 5;
			Maps[4][0].OverWhelmingDegree = NONE;
			Maps[4][0].pos.X = 4;
			Maps[4][0].pos.Y = 30;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[3][0].NameOfDepartment, "È­°ø¼ÒÀçÀü°ø");
			Maps[3][0].DepartmentOrder = 18;
			Maps[3][0].DepartmentPrice = DepartmentPrice;
			Maps[3][0].Owner = 5;
			Maps[3][0].OverWhelmingDegree = NONE;
			Maps[3][0].pos.X = 4;
			Maps[3][0].pos.Y = 24;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[2][0].NameOfDepartment, "Àü±â°øÇÐ°ú");
			Maps[2][0].DepartmentOrder = 19;
			Maps[2][0].DepartmentPrice = DepartmentPrice;
			Maps[2][0].Owner = 5;
			Maps[2][0].OverWhelmingDegree = NONE;
			Maps[2][0].pos.X = 4;
			Maps[2][0].pos.Y = 18;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[1][0].NameOfDepartment, "Åä¸ñ°øÇÐ°ú");
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

		// ¸ÊÀÇ ÀüÃ¼ÀûÀÎ ¿ÜÇü ¸¸µé±â

		DrawMapEdge(i, j);

		// ÄÁÅÙÃ÷ Ç¥Çö

		DrawContents(Maps);


		char buffer[50] = "";
		char tmp1[50] = "";
		char tmp2[50] = "";

		//ÇÃ·¹ÀÌ¾îµé ½ºÅÈ, Çö À§Ä¡ Ç¥Çö

		PlayersInfo(Players, tmp1, tmp2, buffer, Maps);

		// Çö ÇÃ·¹ÀÌ¾îÀÇ Á¤º¸( ¾ÆÀÌÅÛ, À§Ä¡ÇÑ Àå¼Ò )Ç¥Çö

		CurrentPlayerInfo(Players, currentTurn, tmp1, buffer, Maps);
		gotoxy(0, 32);
		printf("%d ¹ø ÇÃ·¹ÀÌ¾î Â÷·Ê ÀÔ´Ï´Ù.\n", currentTurn + 1);
	}

void PrintMapInfo(int indexX, int indexY, int startposx, int startposy, struct Map Maps[][7])
	{
		gotoxyAndPrint(startposx, startposy, Maps[indexX][indexY].NameOfDepartment);

		if (Maps[indexX][indexY].EventNumber == 0)
		{
			switch (Maps[indexX][indexY].Owner)
			{
			case 0:
				gotoxyAndPrint(startposx, startposy + 1, "ÁÖÀÎ : Player1");
				break;
			case 1:
				gotoxyAndPrint(startposx, startposy + 1, "ÁÖÀÎ : Player2");
				break;
			case 2:
				gotoxyAndPrint(startposx, startposy + 1, "ÁÖÀÎ : Player3");
				break;
			case 3:
				gotoxyAndPrint(startposx, startposy + 1, "ÁÖÀÎ : Player4");
				break;
			default:
				gotoxyAndPrint(startposx, startposy + 1, "ÁÖÀÎ : ¾øÀ½");
				break;
			}

			switch (Maps[indexX][indexY].OverWhelmingDegree)
			{
			case 0:
				gotoxyAndPrint(startposx, startposy + 2, "Àå¾Ç·Â : ¾øÀ½");
				break;
			case 25:
				gotoxyAndPrint(startposx, startposy + 2, "Àå¾Ç·Â : 25%");
				break;
			case 50:
				gotoxyAndPrint(startposx, startposy + 2, "Àå¾Ç·Â : 50%");
				break;
			case 75:
				gotoxyAndPrint(startposx, startposy + 2, "Àå¾Ç·Â : 75%");
				break;
			case 100:
				gotoxyAndPrint(startposx, startposy + 2, "Àå¾Ç·Â : 100%");
				break;
			}
		}
	}

void DrawMapEdge(int i, int j)
	{
		// ¿ÜºÎÅ×µÎ¸®
		gotoxyAndPrint(2, 1, "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
		for (i = 2; i<31; i++)
			gotoxyAndPrint(2, i, "¦­                                                                                                                                   ¦­");
		gotoxyAndPrint(2, i, "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");

		// ³»ºÎÅ×µÎ¸®
		gotoxyAndPrint(20, 7, "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
		for (i = 8; i<25; i++)
			gotoxyAndPrint(20, i, "¦­                                                                                         ¦­");
		gotoxyAndPrint(20, i, "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");

		// À§ÂÊÁÙ
		for (j = 0; j<6; j++)
		{
			int l = 0;
			if (l == 0)
				l = 20;
			gotoxyAndPrint(l + 20 * j - j * 2, 1, "¦³");
			for (i = 2; i<7; i++)
				gotoxyAndPrint(l + 20 * j - j * 2, i, "¦­");
			if (j == 0)
				gotoxyAndPrint(l + 20 * j - j * 2, i, "¦¶");
			else
				gotoxyAndPrint(l + 20 * j - j * 2, i, "¦µ");

		}

		// ¾Æ·¡ÂÊÁÙ
		for (j = 0; j<6; j++)
		{
			int l = 0;
			if (l == 0)
				l = 20;
			if (j == 0)
				gotoxyAndPrint(l + 20 * j - j * 2, 25, "¦¶");
			else
				gotoxyAndPrint(l + 20 * j - j * 2, 25, "¦³");
			for (i = 26; i<31; i++)
				gotoxyAndPrint(l + 20 * j - j * 2, i, "¦­");
			gotoxyAndPrint(l + 20 * j - j * 2, i, "¦µ");
		}

		// ¿ÞÂÊÁÙ
		gotoxyAndPrint(2, 7, "¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬");
		gotoxyAndPrint(2, 13, "¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦´");
		gotoxyAndPrint(2, 19, "¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦´");
		gotoxyAndPrint(2, 25, "¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬");

		// ¿À¸¥ÂÊÁÙ
		gotoxyAndPrint(110, 7, "¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦´");
		gotoxyAndPrint(110, 13, "¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦´");
		gotoxyAndPrint(110, 19, "¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦´");
		gotoxyAndPrint(110, 25, "¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦´");

		gotoxyAndPrint(109, 7, "¦¬");
		gotoxyAndPrint(109, 25, "¦¬");
	}

void DrawContents(struct Map Maps[][7])
	{
		// ÄÁÅÙÃ÷ À§ÂÊ

		int indexy = 0;
		for (int startposx = 4; startposx <= 112; startposx += 18)
		{
			int const startposy = 2;
			PrintMapInfo(0, indexy, startposx, startposy, Maps);
			indexy++;
		}

		// ÄÁÅÙÃ÷ ¾Æ·¡ÂÊ
		indexy = 0;
		for (int startposx = 4; startposx <= 112; startposx += 18)
		{
			int const startposy = 26;
			PrintMapInfo(4, indexy, startposx, startposy, Maps);
			indexy++;
		}

		// ÄÁÅÙÃ÷ ¿ÞÂÊ
		PrintMapInfo(1, 0, 4, 8, Maps);
		PrintMapInfo(2, 0, 4, 14, Maps);
		PrintMapInfo(3, 0, 4, 20, Maps);

		// ÄÁÅÙÃ÷ ¿À¸¥ÂÊ
		PrintMapInfo(1, 6, 112, 8, Maps);
		PrintMapInfo(2, 6, 112, 14, Maps);
		PrintMapInfo(3, 6, 112, 20, Maps);
	}

void PlayersInfo(struct Player Players[], char tmp1[], char tmp2[], char buffer[], struct Map Maps[][7])
	{
		// °Ç¹° ¼ö¿Í Àç»ê

		gotoxyAndPrint(22, 9, "[ ÇÃ·¹ÀÌ¾î : °Ç¹°¼ö / Àç»ê ]");

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

		// ÇÃ·¹ÀÌ¾îµé ¸Ê»ó À§Ä¡ Ç¥Çö

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
		// Çö ÇÃ·¹ÀÌ¾î°¡ °¡Áö°í ÀÖ´Â ¾ÆÀÌÅÛ

		int x = 0;
		int y = 0;

		gotoxyAndPrint(80, 9, "[ Çö ÇÃ·¹ÀÌ¾îÀÇ ¾ÆÀÌÅÛ ¸ñ·Ï ]");

		itoa(Players[currentTurn].Items[FreePass - 5], tmp1, 10);
		sprintf(buffer, "ÇÁ¸®ÆÐ½º : %s", tmp1);
		gotoxyAndPrint(80, 10, buffer);

		itoa(Players[currentTurn].Items[AvoidMT - 5], tmp1, 10);
		sprintf(buffer, "MTÈ¸ÇÇ±Ç : %s", tmp1);
		gotoxyAndPrint(80, 11, buffer);

		itoa(Players[currentTurn].Items[BusCard - 5], tmp1, 10);
		sprintf(buffer, "¹ö½ºÄ«µå : %s", tmp1);
		gotoxyAndPrint(80, 12, buffer);

		itoa(Players[currentTurn].Items[FreeOverWhelming - 5], tmp1, 10);
		sprintf(buffer, "¹«·áÀå¾Ç : %s", tmp1);
		gotoxyAndPrint(80, 13, buffer);

		itoa(Players[currentTurn].Items[Donation - 5], tmp1, 10);
		sprintf(buffer, "±âºÎ     : %s", tmp1);
		gotoxyAndPrint(80, 14, buffer);

		// Çö À§Ä¡¿¡ ´ëÇÑ Á¤º¸ Ç¥Çö

		gotoxyAndPrint(22, 20, "[ÇöÀç ÇÃ·¹ÀÌ¾î°¡ À§Ä¡ÇÑ Àå¼ÒÀÇ Á¤º¸]");
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
						sprintf(buffer, "±âº» °¡°Ý : %s", tmp1);
						gotoxyAndPrint(22, 22, buffer);

						itoa(Maps[x][y].OverWhelmingDegree, tmp1, 10);
						sprintf(buffer, "Àå¾Ç Á¤µµ : %s", tmp1);
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
