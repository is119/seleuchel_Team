#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#pragma warning ( disable : 4996 )

#define InitialCapital 5000
#define _CRT_SECURE_NO_WARNINGS

// 檜漸お 寡翮 牖憮 -> 斜渠煎 餌辨

#define NONE 0
#define MT 1
#define SchoolBus 2
#define Previous_Exam_Paper 3
#define Scholarship 4

// 褶爾(嬴檜蠱) 寡翮 牖憮 -> -5 п憮 餌辨

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
	struct Map map[5][7]; // 撮煎 5蘊, 陛煎 7 蘊
	int winner = 0;
	int currentTurn = 0;

	InitMapAndPlayer(player, map);
	winner = PlayGame(player, map, currentTurn);
	
	system("cls");
	printf("Ы溯檜橫%d廓檜 蝓葬ж樟蝗棲棻.!!!", winner);
	system("pause");
	return 0;
}

int TurnOverFlag = 0;

// play 婦溼 л熱

int PlayGame(struct Player Players[], struct Map Maps[][7], int CurrentTurn) // 嬴霜 寰噪
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
		gotoxy(0, 33);
		printf("MT煎 %d橾 翕寰 渦 蓮橫撿 м棲棻.", Players[CurrentTurn].Events[MT]);
		_sleep(3000);
		TurnOverFlag = 1;
		Players[CurrentTurn].Events[MT] -= 1;
	}
	else if (Players[CurrentTurn].Events[SchoolBus] > 0)
	{
		int wheretogo = 0;
		gotoxyAndPrint(0, 33, "蝶籐幗蝶蒂 顫樟蝗棲棻. 橫蛤煎 陛衛啊蝗棲梱?\n(豭薹 嬪睡攪 1廓檜堅 衛啗寞щ戲煎 1噶 渦п雖朝 牖憮殮棲棻.)\n 陛堅濠ж朝 嬪纂蒂 殮溘п輿撮蹂 : ");
		scanf_s("%d", &wheretogo);
		Players[CurrentTurn].PlaceOrder = wheretogo;
		Players[CurrentTurn].Events[SchoolBus] -= 1;
	}
	else
		RollTheDIce(Players, Maps, CurrentTurn);
}

void RollTheDIce(struct Player Players[], struct Map Maps[][7], int CurrentTurn)
{

	char SpaceBarInput = 0;
	int randomNumber = 0;

	srand(time(NULL));
	gotoxyAndPrint(0, 33, "蝶む檜蝶夥蒂 揚楝 輿餌嬪蒂 掉葬撮蹂");
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
				gotoxyAndPrint(0, 33, "濰з旎擊 雖釭蟻蝗棲棻嬴!!!!!!! 該棲 += 5000 ");
				_sleep(3000);
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
		if (Players[CurrentTurn].Items[MT] > 0) // MT �裔ДШ� 氈棻賊
		{
			int yesorno = 0;
			gotoxyAndPrint(2, 118, "MT �裔ДШ� 氈蝗棲棻. 餌辨ж衛啊蝗棲梱?(y = 1, n = 2)");
			scanf_s("%d", &yesorno);

			if (yesorno == 1) // Ы溯檜橫陛 y蒂 摹鷗ц擊陽
			{
				TurnOverFlag = 1;
				Players[CurrentTurn].Items[MT] -= 1;
				return;
			}
		}
		else
		{
			gotoxyAndPrint(0, 33, "MT縑 紫雜ц蝗棲棻嬴!!!!!!!");
			_sleep(3000);
			Players[CurrentTurn].Events[MT] += 3;
			TurnOverFlag = 1;
		}
		break;
	case SchoolBus:
		Players[CurrentTurn].Events[SchoolBus] += 1;
		gotoxyAndPrint(0, 33, "蝶籐幗蝶縑 紫雜ц蝗棲棻嬴!!!!!!!");
		_sleep(3000);
		TurnOverFlag = 1;
		break;
	case Previous_Exam_Paper:
		gotoxyAndPrint(0, 33, "褶爾縑 紫雜ц蝗棲棻嬴!!!!!!!");
		_sleep(3000);
		Previous_Exam_PaperEventHandler(Players, Maps, CurrentTurn);
		TurnOverFlag = 1;
		break;
	case Scholarship:
		gotoxyAndPrint(0, 33, "濰з旎縑 紫雜ц蝗棲棻嬴!!!!!!! 該棲 += 5000 ");
		_sleep(3000);
		Players[CurrentTurn].Money += InitialCapital;
		TurnOverFlag = 1;
		break;
	default : 
		BuyingDepartmentProcess(Players, Maps, CurrentTurn);
		TurnOverFlag = 1;
		break;
	}

} // 檜翕 �� 嬪纂 檜漸お �挫�

void PayTollFee(int Giver, int Recipient, int i, int j, struct Player Players[], struct Map Maps[][7])
{
	if (Players[Giver].Items[FreePass - 5] > 0)
	{
		gotoxy(0, 33);
		printf("Player%d 椒檜 Player%d曖 階擊 嫖戲樟蝗棲棻.\n", Giver + 1, Recipient + 1);
		printf("Щ葬ぬ蝶 嬴檜蠱擊 器棲棻.");
		_sleep(3000);

		Players[Giver].Items[FreePass - 5] -= 1;
		return;
	}
	gotoxy(0, 33);
	printf("Player%d 椒檜 Player%d曖 階擊 嫖戲樟蝗棲棻.\n", Giver+1, Recipient+1);
	printf("鱔ч猿煎 %d蒂 Player%d椒縑啪 鄹棲棻.", Maps[i][j].DepartmentPrice, Recipient+1);
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
						gotoxyAndPrint(0, 33, "⑷ 嬪纂曖 婁蒂 濰學ж衛啊蝗棲梱? (y = 1, n = 2) : ");
						scanf_s("%d", &input);
						if (input == 2) // n擊 殮溘嫡戲賊
						{
							TurnOverFlag = 1;
							return;
						}

						gotoxy(0, 33);
						printf("晦獄陛問擎 %d 殮棲棻.                                \n", Maps[i][j].DepartmentPrice);
						printf("橡葆釭 濰學ж衛啊蝗棲梱? (25, 50, 75, 100 醞 鷗 1) : ");
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
						gotoxyAndPrint(0, 33, "掘衙蒂 諫猿ц蝗棲棻.                                 ");
						_sleep(1500);
					}
					else
					{
						gotoxyAndPrint(0, 33, "鼠猿濰學掏擊 餌辨ж樟蝗棲棻.");
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
					gotoxyAndPrint(0, 33, "檜 婁曖 濰學溘擎 100ぷ撫お檜晦縑 掘衙й 熱 橈蝗棲棻!");
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
	randomNumber = (rand() % 5) + 5; // 嬴檜蠱 寡翮曖 鼻熱菟擎 嬪縑 陝陝 5,6,7,8,9煎 蟾晦�倆�
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
		Players[CurrentTurn].PlaceOrder = 11; // 蝶籐幗蝶 嬪纂煎 檜翕
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
		printf("%d廓 Ы溯檜橫陛 %d廓 Ы溯檜橫縑啪 晦睡蒂 м棲棻.", CurrentTurn+1, PoorestPlayer+1);
		_sleep(3000);
	}
}

void BankruptHandler(struct Player Players[], struct Map Maps[][7], int CurrentTurn, int MoneyToPay) // Ы溯檜橫陛 模嶸и 婁陛 橫蛞雖憲嬴撿л.
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
			printf("Player%d 朝 だ骯殮棲棻.", CurrentTurn+1);
			_sleep(3000);
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
		if (Players[CurrentTurn].boughtDepartment[i] == 1) // п渡 婁蒂 п渡 Ы溯檜橫陛 麼歷棻賊
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


// 裘 斜葬朝 л熱菟

void InitMapAndPlayer(struct Player Players[], struct Map Maps[][7])
	{
		// Ы溯檜橫 蟾晦��

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

		// 裘 蟾晦��

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

			// 檜葷, з婁牖憮, 陛問, 檜漸お 璋濠, 模嶸輿璋濠, 濰學薑紫

			strcpy(Maps[0][0].NameOfDepartment, "濰з旎");
			Maps[0][0].DepartmentOrder = 1;
			Maps[0][0].DepartmentPrice = 0;
			Maps[0][0].EventNumber = Scholarship;
			Maps[0][0].Owner = 5;
			Maps[0][0].OverWhelmingDegree = NONE;
			Maps[0][0].pos.X = 4;
			Maps[0][0].pos.Y = 6;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[0][1].NameOfDepartment, "勒蹴紫衛撲啗瞪奢");
			Maps[0][1].DepartmentOrder = 2;
			Maps[0][1].DepartmentPrice = DepartmentPrice;
			Maps[0][1].Owner = 5;
			Maps[0][1].OverWhelmingDegree = NONE;
			Maps[0][1].pos.X = 22;
			Maps[0][1].pos.Y = 6;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[0][2].NameOfDepartment, "勒蹴奢з瞪奢");
			Maps[0][2].DepartmentOrder = 3;
			Maps[0][2].DepartmentPrice = DepartmentPrice;
			Maps[0][2].Owner = 5;
			Maps[0][2].OverWhelmingDegree = NONE;
			Maps[0][2].pos.X = 40;
			Maps[0][2].pos.Y = 6;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[0][3].NameOfDepartment, "堅碟濠奢з瞪奢");
			Maps[0][3].DepartmentOrder = 4;
			Maps[0][3].DepartmentPrice = DepartmentPrice;
			Maps[0][3].Owner = 5;
			Maps[0][3].OverWhelmingDegree = NONE;
			Maps[0][3].pos.X = 58;
			Maps[0][3].pos.Y = 6;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[0][4].NameOfDepartment, "懦м撰嶸奢з瞪奢");
			Maps[0][4].DepartmentOrder = 5;
			Maps[0][4].DepartmentPrice = DepartmentPrice;
			Maps[0][4].Owner = 5;
			Maps[0][4].OverWhelmingDegree = NONE;
			Maps[0][4].pos.X = 76;
			Maps[0][4].pos.Y = 6;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[0][5].NameOfDepartment, "晦啗奢з瞪奢");
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
			strcpy(Maps[1][6].NameOfDepartment, "瞪濠薑爾鱔褐奢з瞪奢");
			Maps[1][6].DepartmentOrder = 8;
			Maps[1][6].DepartmentPrice = DepartmentPrice;
			Maps[1][6].Owner = 5;
			Maps[1][6].OverWhelmingDegree = NONE;
			Maps[1][6].pos.X = 112;
			Maps[1][6].pos.Y = 12;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[2][6].NameOfDepartment, "闡У攪薑爾鱔褐奢з瞪奢");
			Maps[2][6].DepartmentOrder = 9;
			Maps[2][6].DepartmentPrice = DepartmentPrice;
			Maps[2][6].Owner = 5;
			Maps[2][6].OverWhelmingDegree = NONE;
			Maps[2][6].pos.X = 112;
			Maps[2][6].pos.Y = 18;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[3][6].NameOfDepartment, "模Щお錚橫奢з瞪奢");
			Maps[3][6].DepartmentOrder = 10;
			Maps[3][6].DepartmentPrice = DepartmentPrice;
			Maps[3][6].Owner = 5;
			Maps[3][6].OverWhelmingDegree = NONE;
			Maps[3][6].pos.X = 112;
			Maps[3][6].pos.Y = 24;

			strcpy(Maps[4][6].NameOfDepartment, "蝶籐幗蝶");
			Maps[4][6].DepartmentOrder = 11;
			Maps[4][6].DepartmentPrice = 0;
			Maps[4][6].EventNumber = SchoolBus;
			Maps[4][6].Owner = 5;
			Maps[4][6].OverWhelmingDegree = NONE;
			Maps[4][6].pos.X = 112;
			Maps[4][6].pos.Y = 30;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[4][5].NameOfDepartment, "�秣瞈○岏鰤醾訄�");
			Maps[4][5].DepartmentOrder = 12;
			Maps[4][5].DepartmentPrice = DepartmentPrice;
			Maps[4][5].Owner = 5;
			Maps[4][5].OverWhelmingDegree = NONE;
			Maps[4][5].pos.X = 94;
			Maps[4][5].pos.Y = 30;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[4][4].NameOfDepartment, "儅僭奢з婁");
			Maps[4][4].DepartmentOrder = 13;
			Maps[4][4].DepartmentPrice = DepartmentPrice;
			Maps[4][4].Owner = 5;
			Maps[4][4].OverWhelmingDegree = NONE;
			Maps[4][4].pos.X = 76;
			Maps[4][4].pos.Y = 30;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[4][3].NameOfDepartment, "旎樓營猿奢з瞪奢");
			Maps[4][3].DepartmentOrder = 14;
			Maps[4][3].DepartmentPrice = DepartmentPrice;
			Maps[4][3].Owner = 5;
			Maps[4][3].OverWhelmingDegree = NONE;
			Maps[4][3].pos.X = 58;
			Maps[4][3].pos.Y = 30;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[4][2].NameOfDepartment, "撮塭嗶營猿奢з瞪奢");
			Maps[4][2].DepartmentOrder = 15;
			Maps[4][2].DepartmentPrice = DepartmentPrice;
			Maps[4][2].Owner = 5;
			Maps[4][2].OverWhelmingDegree = NONE;
			Maps[4][2].pos.X = 40;
			Maps[4][2].pos.Y = 30;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[4][1].NameOfDepartment, "惜.瞪濠營猿瞪奢");
			Maps[4][1].DepartmentOrder = 16;
			Maps[4][1].DepartmentPrice = DepartmentPrice;
			Maps[4][1].Owner = 5;
			Maps[4][1].OverWhelmingDegree = NONE;
			Maps[4][1].pos.X = 22;
			Maps[4][1].pos.Y = 30;

			strcpy(Maps[4][0].NameOfDepartment, "褶爾");
			Maps[4][0].DepartmentOrder = 17;
			Maps[4][0].DepartmentPrice = DepartmentPrice;
			Maps[4][0].EventNumber = Previous_Exam_Paper;
			Maps[4][0].Owner = 5;
			Maps[4][0].OverWhelmingDegree = NONE;
			Maps[4][0].pos.X = 4;
			Maps[4][0].pos.Y = 30;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[3][0].NameOfDepartment, "�降虃甡蝩�奢");
			Maps[3][0].DepartmentOrder = 18;
			Maps[3][0].DepartmentPrice = DepartmentPrice;
			Maps[3][0].Owner = 5;
			Maps[3][0].OverWhelmingDegree = NONE;
			Maps[3][0].pos.X = 4;
			Maps[3][0].pos.Y = 24;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[2][0].NameOfDepartment, "瞪晦奢з婁");
			Maps[2][0].DepartmentOrder = 19;
			Maps[2][0].DepartmentPrice = DepartmentPrice;
			Maps[2][0].Owner = 5;
			Maps[2][0].OverWhelmingDegree = NONE;
			Maps[2][0].pos.X = 4;
			Maps[2][0].pos.Y = 18;

			DepartmentPrice = ((rand() % 10) + 1) * 100;
			strcpy(Maps[1][0].NameOfDepartment, "饜跡奢з婁");
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

		// 裘曖 瞪羹瞳檣 諼⑽ 虜菟晦

		DrawMapEdge(i, j);

		// 鐘蘸隴 ル⑷

		DrawContents(Maps);


		char buffer[50] = "";
		char tmp1[50] = "";
		char tmp2[50] = "";

		//Ы溯檜橫菟 蝶囌, ⑷ 嬪纂 ル⑷

		PlayersInfo(Players, tmp1, tmp2, buffer, Maps);

		// ⑷ Ы溯檜橫曖 薑爾( 嬴檜蠱, 嬪纂и 濰模 )ル⑷

		CurrentPlayerInfo(Players, currentTurn, tmp1, buffer, Maps);
		gotoxy(0, 32);
		printf("%d 廓 Ы溯檜橫 離滔 殮棲棻.\n", currentTurn + 1);
	}

void PrintMapInfo(int indexX, int indexY, int startposx, int startposy, struct Map Maps[][7])
	{
		gotoxyAndPrint(startposx, startposy, Maps[indexX][indexY].NameOfDepartment);

		if (Maps[indexX][indexY].EventNumber == 0)
		{
			switch (Maps[indexX][indexY].Owner)
			{
			case 0:
				gotoxyAndPrint(startposx, startposy + 1, "輿檣 : Player1");
				break;
			case 1:
				gotoxyAndPrint(startposx, startposy + 1, "輿檣 : Player2");
				break;
			case 2:
				gotoxyAndPrint(startposx, startposy + 1, "輿檣 : Player3");
				break;
			case 3:
				gotoxyAndPrint(startposx, startposy + 1, "輿檣 : Player4");
				break;
			default:
				gotoxyAndPrint(startposx, startposy + 1, "輿檣 : 橈擠");
				break;
			}

			switch (Maps[indexX][indexY].OverWhelmingDegree)
			{
			case 0:
				gotoxyAndPrint(startposx, startposy + 2, "濰學溘 : 橈擠");
				break;
			case 25:
				gotoxyAndPrint(startposx, startposy + 2, "濰學溘 : 25%");
				break;
			case 50:
				gotoxyAndPrint(startposx, startposy + 2, "濰學溘 : 50%");
				break;
			case 75:
				gotoxyAndPrint(startposx, startposy + 2, "濰學溘 : 75%");
				break;
			case 100:
				gotoxyAndPrint(startposx, startposy + 2, "濰學溘 : 100%");
				break;
			}
		}
	}

void DrawMapEdge(int i, int j)
	{
		// 諼睡纔舒葬
		gotoxyAndPrint(2, 1, "旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
		for (i = 2; i<31; i++)
			gotoxyAndPrint(2, i, "早                                                                                                                                   早");
		gotoxyAndPrint(2, i, "曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");

		// 頂睡纔舒葬
		gotoxyAndPrint(20, 7, "旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
		for (i = 8; i<25; i++)
			gotoxyAndPrint(20, i, "早                                                                                         早");
		gotoxyAndPrint(20, i, "曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");

		// 嬪薹還
		for (j = 0; j<6; j++)
		{
			int l = 0;
			if (l == 0)
				l = 20;
			gotoxyAndPrint(l + 20 * j - j * 2, 1, "有");
			for (i = 2; i<7; i++)
				gotoxyAndPrint(l + 20 * j - j * 2, i, "早");
			if (j == 0)
				gotoxyAndPrint(l + 20 * j - j * 2, i, "朱");
			else
				gotoxyAndPrint(l + 20 * j - j * 2, i, "朴");

		}

		// 嬴楚薹還
		for (j = 0; j<6; j++)
		{
			int l = 0;
			if (l == 0)
				l = 20;
			if (j == 0)
				gotoxyAndPrint(l + 20 * j - j * 2, 25, "朱");
			else
				gotoxyAndPrint(l + 20 * j - j * 2, 25, "有");
			for (i = 26; i<31; i++)
				gotoxyAndPrint(l + 20 * j - j * 2, i, "早");
			gotoxyAndPrint(l + 20 * j - j * 2, i, "朴");
		}

		// 豭薹還
		gotoxyAndPrint(2, 7, "曳收收收收收收收收收收收收收收收收");
		gotoxyAndPrint(2, 13, "曳收收收收收收收收收收收收收收收收收朽");
		gotoxyAndPrint(2, 19, "曳收收收收收收收收收收收收收收收收收朽");
		gotoxyAndPrint(2, 25, "曳收收收收收收收收收收收收收收收收");

		// 螃艇薹還
		gotoxyAndPrint(110, 7, "朱收收收收收收收收收收收收收收收收收收收收收收收朽");
		gotoxyAndPrint(110, 13, "曳收收收收收收收收收收收收收收收收收收收收收收收朽");
		gotoxyAndPrint(110, 19, "曳收收收收收收收收收收收收收收收收收收收收收收收朽");
		gotoxyAndPrint(110, 25, "朱收收收收收收收收收收收收收收收收收收收收收收收朽");

		gotoxyAndPrint(109, 7, "收");
		gotoxyAndPrint(109, 25, "收");
	}

void DrawContents(struct Map Maps[][7])
	{
		// 鐘蘸隴 嬪薹

		int indexy = 0;
		for (int startposx = 4; startposx <= 112; startposx += 18)
		{
			int const startposy = 2;
			PrintMapInfo(0, indexy, startposx, startposy, Maps);
			indexy++;
		}

		// 鐘蘸隴 嬴楚薹
		indexy = 0;
		for (int startposx = 4; startposx <= 112; startposx += 18)
		{
			int const startposy = 26;
			PrintMapInfo(4, indexy, startposx, startposy, Maps);
			indexy++;
		}

		// 鐘蘸隴 豭薹
		PrintMapInfo(1, 0, 4, 8, Maps);
		PrintMapInfo(2, 0, 4, 14, Maps);
		PrintMapInfo(3, 0, 4, 20, Maps);

		// 鐘蘸隴 螃艇薹
		PrintMapInfo(1, 6, 112, 8, Maps);
		PrintMapInfo(2, 6, 112, 14, Maps);
		PrintMapInfo(3, 6, 112, 20, Maps);
	}

void PlayersInfo(struct Player Players[], char tmp1[], char tmp2[], char buffer[], struct Map Maps[][7])
	{
		// 勒僭 熱諦 營骯

		gotoxyAndPrint(22, 9, "[ Ы溯檜橫 : 勒僭熱 / 營骯 ]");

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

		// Ы溯檜橫菟 裘鼻 嬪纂 ル⑷

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
		// ⑷ Ы溯檜橫陛 陛雖堅 氈朝 嬴檜蠱

		int x = 0;
		int y = 0;

		gotoxyAndPrint(80, 9, "[ ⑷ Ы溯檜橫曖 嬴檜蠱 跡煙 ]");

		itoa(Players[currentTurn].Items[FreePass - 5], tmp1, 10);
		sprintf(buffer, "Щ葬ぬ蝶 : %s", tmp1);
		gotoxyAndPrint(80, 10, buffer);

		itoa(Players[currentTurn].Items[AvoidMT - 5], tmp1, 10);
		sprintf(buffer, "MT�裔Д� : %s", tmp1);
		gotoxyAndPrint(80, 11, buffer);

		itoa(Players[currentTurn].Items[BusCard - 5], tmp1, 10);
		sprintf(buffer, "幗蝶蘋萄 : %s", tmp1);
		gotoxyAndPrint(80, 12, buffer);

		itoa(Players[currentTurn].Items[FreeOverWhelming - 5], tmp1, 10);
		sprintf(buffer, "鼠猿濰學 : %s", tmp1);
		gotoxyAndPrint(80, 13, buffer);

		itoa(Players[currentTurn].Items[Donation - 5], tmp1, 10);
		sprintf(buffer, "晦睡     : %s", tmp1);
		gotoxyAndPrint(80, 14, buffer);

		// ⑷ 嬪纂縑 渠и 薑爾 ル⑷

		gotoxyAndPrint(22, 20, "[⑷營 Ы溯檜橫陛 嬪纂и 濰模曖 薑爾]");
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
						sprintf(buffer, "晦獄 陛問 : %s", tmp1);
						gotoxyAndPrint(22, 22, buffer);

						itoa(Maps[x][y].OverWhelmingDegree, tmp1, 10);
						sprintf(buffer, "濰學 薑紫 : %s", tmp1);
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
