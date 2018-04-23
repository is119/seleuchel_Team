#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define InitialCapital 5000

#pragma warning ( disable : 4996 )
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
	int Order;
    int CurrentPlaceX;
	int CurrentPlaceY;
    int Money;
	int NumberOfDepartment;
	int Items[5];
	int Events[5];
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
void PrintMapInfo(int i, int j, int startposx, int startposy, struct Map Maps[][7]);
void DrawMapEdge(int i, int j);
void DrawContents(struct Map Maps[][7]);
void PlayersInfo(struct Player Players[], char tmp1[], char tmp2[], char buffer[], struct Map Maps[][7]);
void CurrentPlayerInfo(struct Player Players[], int currentTurn, char tmp1[], char buffer[], struct Map Maps[][7]);
void SearchMapPlace(int* x, int* y, struct Map Maps[][7], struct Player Players[], int PlayerNumber);

int main (void)
{
	struct Player player[4];
	struct Map map[5][7]; // 撮煎 5蘊, 陛煎 7 蘊
	int currentTurn = 0;
	InitMapAndPlayer(player, map);
	DrawCurrentBoard(player, map, currentTurn);
	system("pause");
	return 0;
}

void InitMapAndPlayer(struct Player Players[], struct Map Maps[][7])
{
	// Ы溯檜橫 蟾晦��

	int const NumberOfPlayers = 4;

	for(int i = 0; i < NumberOfPlayers; i++ )
	{
		Players[i].Order = i;
		Players[i].CurrentPlaceX = 0;
		Players[i].CurrentPlaceY = 0;
		Players[i].Money = InitialCapital;
		Players[i].NumberOfDepartment = 0;
		for (int j = 0; j < 5; j++)
		{
			Players[i].Items[j] = 0;
			Players[i].Events[j] = 0;
		}
	}
	
	// 裘 蟾晦��

	{
		int DepartmentPrice = ((rand() % 10) + 1) * 100;

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				/*for (int str = 0; str < 20; str++)
				{
				Maps[i][j].NameOfDepartment[str] = "0";
				}*/

				strcpy(Maps[i][j].NameOfDepartment, "NONE");
				Maps[i][j].DepartmentOrder = 0;
				Maps[i][j].DepartmentPrice = 0;
				Maps[i][j].EventNumber = NONE;
				Maps[i][j].Owner = 0;
				Maps[i][j].OverWhelmingDegree = 0;
				Maps[i][j].pos.X = 0;
				Maps[i][j].pos.Y = 0;
			}
		}

		srand(time(NULL));

		// 檜葷, з婁牖憮, 陛問, 檜漸お 璋濠, 模嶸輿璋濠, 濰學薑紫

		strcpy(Maps[0][0].NameOfDepartment, "濰з旎");
		Maps[0][0].DepartmentOrder = 0;
		Maps[0][0].DepartmentPrice = 0;
		Maps[0][0].EventNumber = Scholarship;
		Maps[0][0].Owner = NONE;
		Maps[0][0].OverWhelmingDegree = NONE;
		Maps[0][0].pos.X = 6;
		Maps[0][0].pos.Y = 4;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[0][1].NameOfDepartment, "勒蹴紫衛撲啗瞪奢");
		Maps[0][1].DepartmentOrder = 1;
		Maps[0][1].DepartmentPrice = DepartmentPrice;
		Maps[0][1].Owner = NONE;
		Maps[0][1].OverWhelmingDegree = NONE;
		Maps[0][1].pos.X = 22;
		Maps[0][1].pos.Y = 4;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[0][2].NameOfDepartment, "勒蹴奢з瞪奢");
		Maps[0][2].DepartmentOrder = 2;
		Maps[0][2].DepartmentPrice = DepartmentPrice;
		Maps[0][2].Owner = NONE;
		Maps[0][2].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[0][3].NameOfDepartment, "堅碟濠奢з瞪奢");
		Maps[0][3].DepartmentOrder = 3;
		Maps[0][3].DepartmentPrice = DepartmentPrice;
		Maps[0][3].Owner = NONE;
		Maps[0][3].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[0][4].NameOfDepartment, "懦м撰嶸奢з瞪奢");
		Maps[0][4].DepartmentOrder = 4;
		Maps[0][4].DepartmentPrice = DepartmentPrice;
		Maps[0][4].Owner = NONE;
		Maps[0][4].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[0][5].NameOfDepartment, "晦啗奢з瞪奢");
		Maps[0][5].DepartmentOrder = 5;
		Maps[0][5].DepartmentPrice = DepartmentPrice;
		Maps[0][5].Owner = NONE;
		Maps[0][5].OverWhelmingDegree = NONE;

		strcpy(Maps[0][6].NameOfDepartment, "MT");
		Maps[0][6].DepartmentOrder = 6;
		Maps[0][6].DepartmentPrice = 0;
		Maps[0][6].EventNumber = MT;
		Maps[0][6].Owner = NONE;
		Maps[0][6].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[1][6].NameOfDepartment, "瞪濠薑爾鱔褐奢з瞪奢");
		Maps[1][6].DepartmentOrder = 7;
		Maps[1][6].DepartmentPrice = DepartmentPrice;
		Maps[1][6].Owner = NONE;
		Maps[1][6].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[2][6].NameOfDepartment, "闡У攪薑爾鱔褐奢з瞪奢");
		Maps[2][6].DepartmentOrder = 8;
		Maps[2][6].DepartmentPrice = DepartmentPrice;
		Maps[2][6].Owner = NONE;
		Maps[2][6].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[3][6].NameOfDepartment, "模Щお錚橫奢з瞪奢");
		Maps[3][6].DepartmentOrder = 9;
		Maps[3][6].DepartmentPrice = DepartmentPrice;
		Maps[3][6].Owner = NONE;
		Maps[3][6].OverWhelmingDegree = NONE;

		strcpy(Maps[4][6].NameOfDepartment, "蝶籐幗蝶");
		Maps[4][6].DepartmentOrder = 10;
		Maps[4][6].DepartmentPrice = 0;
		Maps[4][6].EventNumber = SchoolBus;
		Maps[4][6].Owner = NONE;
		Maps[4][6].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[4][5].NameOfDepartment, "�秣瞈○岏鰤醾訄�");
		Maps[4][5].DepartmentOrder = 11;
		Maps[4][5].DepartmentPrice = DepartmentPrice;
		Maps[4][5].Owner = NONE;
		Maps[4][5].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[4][4].NameOfDepartment, "儅僭奢з婁");
		Maps[4][4].DepartmentOrder = 12;
		Maps[4][4].DepartmentPrice = DepartmentPrice;
		Maps[4][4].Owner = NONE;
		Maps[4][4].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[4][3].NameOfDepartment, "旎樓營猿奢з瞪奢");
		Maps[4][3].DepartmentOrder = 13;
		Maps[4][3].DepartmentPrice = DepartmentPrice;
		Maps[4][3].Owner = NONE;
		Maps[4][3].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[4][2].NameOfDepartment, "撮塭嗶營猿奢з瞪奢");
		Maps[4][2].DepartmentOrder = 14;
		Maps[4][2].DepartmentPrice = DepartmentPrice;
		Maps[4][2].Owner = NONE;
		Maps[4][2].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[4][1].NameOfDepartment, "惜.瞪濠營猿瞪奢");
		Maps[4][1].DepartmentOrder = 15;
		Maps[4][1].DepartmentPrice = DepartmentPrice;
		Maps[4][1].Owner = NONE;
		Maps[4][1].OverWhelmingDegree = NONE;

		strcpy(Maps[4][0].NameOfDepartment, "褶爾");
		Maps[4][0].DepartmentOrder = 16;
		Maps[4][0].DepartmentPrice = DepartmentPrice;
		Maps[4][0].EventNumber = Previous_Exam_Paper;
		Maps[4][0].Owner = NONE;
		Maps[4][0].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[3][0].NameOfDepartment, "�降虃甡蝩�奢");
		Maps[3][0].DepartmentOrder = 17;
		Maps[3][0].DepartmentPrice = DepartmentPrice;
		Maps[3][0].Owner = NONE;
		Maps[3][0].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[2][0].NameOfDepartment, "瞪晦奢з婁");
		Maps[2][0].DepartmentOrder = 18;
		Maps[2][0].DepartmentPrice = DepartmentPrice;
		Maps[2][0].Owner = NONE;
		Maps[2][0].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[1][0].NameOfDepartment, "饜跡奢з婁");
		Maps[1][0].DepartmentOrder = 19;
		Maps[1][0].DepartmentPrice = DepartmentPrice;
		Maps[1][0].Owner = NONE;
		Maps[1][0].OverWhelmingDegree = NONE;
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
	int i = 0 , j = 0;
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

	// 輿餌嬪 蹺陛 й 匙!!!

	gotoxyAndPrint(2, 32, "this is for test");
}

void PrintMapInfo(int indexX, int indexY, int startposx, int startposy, struct Map Maps[][7]) 
{
	gotoxyAndPrint(startposx, startposy, Maps[indexX][indexY].NameOfDepartment);
	
			if (Maps[indexX][indexY].EventNumber == 0)
			{
				switch (Maps[indexX][indexY].Owner)
				{	
				case 0:	
					gotoxyAndPrint(startposx, startposy + 1, "輿檣 : 橈擠");
					break;
				case 1:
					gotoxyAndPrint(startposx, startposy + 1, "輿檣 : Player1");
					break;
				case 2:
					gotoxyAndPrint(startposx, startposy + 1, "輿檣 : Player2");
					break;
				case 3:
					gotoxyAndPrint(startposx, startposy + 1, "輿檣 : Player3");
					break;
				case 4:
					gotoxyAndPrint(startposx, startposy + 1, "輿檣 : Player4");
					break;
				}
	
				switch (Maps[indexX][indexY].OverWhelmingDegree)
				{
				case 0:
					gotoxyAndPrint(startposx, startposy + 2, "濰學溘 : 橈擠");
					break;
				case 1:
					gotoxyAndPrint(startposx, startposy + 2, "濰學溘 : 25%");
					break;
				case 2:
					gotoxyAndPrint(startposx, startposy + 2, "濰學溘 : 50%");
					break;
				case 3:
					gotoxyAndPrint(startposx, startposy + 2, "濰學溘 : 75%");
					break;
				case 4:
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

	itoa(Players[0].NumberOfDepartment, tmp1, 10);
	itoa(Players[0].Money, tmp2, 10);
	sprintf(buffer, "Player1 : %s / %s", tmp1, tmp2);
	gotoxyAndPrint(22, 10, buffer);

	itoa(Players[1].NumberOfDepartment, tmp1, 10);
	itoa(Players[1].Money, tmp2, 10);
	sprintf(buffer, "Player2 : %s / %s", tmp1, tmp2);
	gotoxyAndPrint(22, 11, buffer);

	itoa(Players[2].NumberOfDepartment, tmp1, 10);
	itoa(Players[2].Money, tmp2, 10);
	sprintf(buffer, "Player3 : %s / %s", tmp1, tmp2);
	gotoxyAndPrint(22, 12, buffer);

	itoa(Players[3].NumberOfDepartment, tmp1, 10);
	itoa(Players[3].Money, tmp2, 10);
	sprintf(buffer, "Player4 : %s / %s", tmp1, tmp2);
	gotoxyAndPrint(22, 13, buffer);

	// Ы溯檜橫菟 裘鼻 嬪纂 ル⑷

	for (int NumberOfPlayers = 0; NumberOfPlayers < 4; NumberOfPlayers++)
	{
		int x, y;
		itoa(NumberOfPlayers + 1, buffer, 10);
		SearchMapPlace(&x, &y, Maps, Players, NumberOfPlayers);
		gotoxyAndPrint(x, y, buffer);
	}
	
}

void CurrentPlayerInfo(struct Player Players[], int currentTurn, char tmp1[], char buffer[], struct Map Maps[][7])
{
	// ⑷ Ы溯檜橫陛 陛雖堅 氈朝 嬴檜蠱

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

	if (Maps[Players[currentTurn].CurrentPlaceX][Players[currentTurn].CurrentPlaceY].EventNumber == NONE)
	{
		itoa(Maps[Players[currentTurn].CurrentPlaceX][Players[currentTurn].CurrentPlaceY].DepartmentPrice, tmp1, 10);
		sprintf(buffer, "晦獄 陛問 : %s", tmp1);
		gotoxyAndPrint(22, 21, buffer);

		itoa(Maps[Players[currentTurn].CurrentPlaceX][Players[currentTurn].CurrentPlaceY].OverWhelmingDegree, tmp1, 10);
		sprintf(buffer, "濰學 薑紫 : %s", tmp1);
		gotoxyAndPrint(22, 22, buffer);
	}
	else
	{
		gotoxyAndPrint(22, 21, Maps[Players[currentTurn].CurrentPlaceX][Players[currentTurn].CurrentPlaceY].NameOfDepartment);
	}

}

void SearchMapPlace(int* x, int* y, struct Map Maps[][7], struct Player Players[], int PlayerNumber)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if ( Maps[i][j].pos.X == Players[PlayerNumber].CurrentPlaceX && Maps[i][j].pos.Y == Players[PlayerNumber].CurrentPlaceY )
			{
				*x = Maps[i][j].pos.X;
				*y = Maps[i][j].pos.Y;
				return;
			}
		}
	}
}