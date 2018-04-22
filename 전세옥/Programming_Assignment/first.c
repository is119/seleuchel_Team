#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
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
};

void InitMapAndPlayer(struct Player Players[], struct Map Maps[][7]);
void DrawCurrentBoard(struct Player Players[], struct Map Maps[][7], int currentTurn);
void PrintMapInfo(int i, int j, int startposx, int startposy, struct Map Maps[][7]);

int main (void)
{
	struct Player player[4];
	struct Map map[5][7]; // 세로 5칸, 가로 7 칸
	int currentTurn = 0;
	InitMapAndPlayer(player, map);
	DrawCurrentBoard(player, map, currentTurn);
	system("pause");
	return 0;
}

void InitMapAndPlayer(struct Player Players[], struct Map Maps[][7])
{
	// 플레이어 초기화

	int const NumberOfPlayers = 4;

	for(int i = 0; i < NumberOfPlayers; i++ )
	{
		Players[i].Order = i;
		Players[i].CurrentPlaceX = 4;
		Players[i].CurrentPlaceY = 6;
		Players[i].Money = InitialCapital;
		Players[i].NumberOfDepartment = 0;
		for (int j = 0; j < 5; j++)
		{
			Players[i].Items[j] = 0;
			Players[i].Events[j] = 0;
		}
	}

	// 맵 초기화
	int DepartmentPrice = ((rand() % 10) + 1) * 100;
	
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 7; j++)
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
		}
	}

	srand(time(NULL));

	// 이름, 학과순서, 가격, 이벤트 숫자, 소유주숫자, 장악정도

	strcpy(Maps[0][0].NameOfDepartment, "장학금");
	Maps[0][0].DepartmentOrder = 0;
	Maps[0][0].DepartmentPrice = 0;
	Maps[0][0].EventNumber = Scholarship;
	Maps[0][0].Owner = NULL;
	Maps[0][0].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[0][1].NameOfDepartment, "건축도시설계전공");
	Maps[0][1].DepartmentOrder = 1;
	Maps[0][1].DepartmentPrice = DepartmentPrice;
	Maps[0][1].Owner = NULL;
	Maps[0][1].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[0][2].NameOfDepartment, "건축공학전공");
	Maps[0][2].DepartmentOrder = 2;
	Maps[0][2].DepartmentPrice = DepartmentPrice;
	Maps[0][2].Owner = NULL;
	Maps[0][2].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[0][3].NameOfDepartment, "고분자공학전공");
	Maps[0][3].DepartmentOrder = 3;
	Maps[0][3].DepartmentPrice = DepartmentPrice;
	Maps[0][3].Owner = NULL;
	Maps[0][3].OverWhelmingDegree = NULL;
	
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[0][4].NameOfDepartment, "융합섬유공학전공");
	Maps[0][4].DepartmentOrder = 4;
	Maps[0][4].DepartmentPrice = DepartmentPrice;
	Maps[0][4].Owner = NULL;
	Maps[0][4].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[0][5].NameOfDepartment, "기계공학전공");
	Maps[0][5].DepartmentOrder = 5;
	Maps[0][5].DepartmentPrice = DepartmentPrice;
	Maps[0][5].Owner = NULL;
	Maps[0][5].OverWhelmingDegree = NULL;

	strcpy(Maps[0][6].NameOfDepartment, "MT");
	Maps[0][6].DepartmentOrder = 6;
	Maps[0][6].DepartmentPrice = 0;
	Maps[0][6].EventNumber = MT;
	Maps[0][6].Owner = NULL;
	Maps[0][6].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[1][6].NameOfDepartment, "전자정보통신공학전공");
	Maps[1][6].DepartmentOrder = 7;
	Maps[1][6].DepartmentPrice = DepartmentPrice;
	Maps[1][6].Owner = NULL;
	Maps[1][6].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[2][6].NameOfDepartment, "컴퓨터정보통신공학전공");
	Maps[2][6].DepartmentOrder = 8;
	Maps[2][6].DepartmentPrice = DepartmentPrice;
	Maps[2][6].Owner = NULL;
	Maps[2][6].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[3][6].NameOfDepartment, "소프트웨어공학전공");
	Maps[3][6].DepartmentOrder = 9;
	Maps[3][6].DepartmentPrice = DepartmentPrice;
	Maps[3][6].Owner = NULL;
	Maps[3][6].OverWhelmingDegree = NULL;

	strcpy(Maps[4][6].NameOfDepartment, "스쿨버스");
	Maps[4][6].DepartmentOrder = 10;
	Maps[4][6].DepartmentPrice = 0;
	Maps[4][6].EventNumber = SchoolBus;
	Maps[4][6].Owner = NULL;
	Maps[4][6].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[4][5].NameOfDepartment, "환경에너지공학과");
	Maps[4][5].DepartmentOrder = 11;
	Maps[4][5].DepartmentPrice = DepartmentPrice;
	Maps[4][5].Owner = NULL;
	Maps[4][5].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[4][4].NameOfDepartment, "생물공학과");
	Maps[4][4].DepartmentOrder = 12;
	Maps[4][4].DepartmentPrice = DepartmentPrice;
	Maps[4][4].Owner = NULL;
	Maps[4][4].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[4][3].NameOfDepartment, "금속재료공학전공");
	Maps[4][3].DepartmentOrder = 13;
	Maps[4][3].DepartmentPrice = DepartmentPrice;
	Maps[4][3].Owner = NULL;
	Maps[4][3].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[4][2].NameOfDepartment, "세라믹재료공학전공");
	Maps[4][2].DepartmentOrder = 14;
	Maps[4][2].DepartmentPrice = DepartmentPrice;
	Maps[4][2].Owner = NULL;
	Maps[4][2].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[4][1].NameOfDepartment, "광.전자재료전공");
	Maps[4][1].DepartmentOrder = 15;
	Maps[4][1].DepartmentPrice = DepartmentPrice;
	Maps[4][1].Owner = NULL;
	Maps[4][1].OverWhelmingDegree = NULL;

	strcpy(Maps[4][0].NameOfDepartment, "족보");
	Maps[4][0].DepartmentOrder = 16;
	Maps[4][0].DepartmentPrice = DepartmentPrice;
	Maps[4][0].EventNumber = Previous_Exam_Paper;
	Maps[4][0].Owner = NULL;
	Maps[4][0].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[3][0].NameOfDepartment, "화공소재전공");
	Maps[3][0].DepartmentOrder = 17;
	Maps[3][0].DepartmentPrice = DepartmentPrice;
	Maps[3][0].Owner = NULL;
	Maps[3][0].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[2][0].NameOfDepartment, "전기공학과");
	Maps[2][0].DepartmentOrder = 18;
	Maps[2][0].DepartmentPrice = DepartmentPrice;
	Maps[2][0].Owner = NULL;
	Maps[2][0].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[1][0].NameOfDepartment, "토목공학과");
	Maps[1][0].DepartmentOrder = 19;
	Maps[1][0].DepartmentPrice = DepartmentPrice;
	Maps[1][0].Owner = NULL;
	Maps[1][0].OverWhelmingDegree = NULL;
	

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
	int i, j;
	system("cls");
	system("mode con: cols=138 lines=48");

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

	//플레이어들 스탯 표현 -> 함수화

	char buffer[50] = "";
	char tmp1[50] = "";
	char tmp2[50] = "";

	gotoxyAndPrint(22, 9, "[ 플레이어 : 건물수 / 재산 ]");

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

	// 현 플레이어가 가지고 있는 아이템 -> 함수화

	// char buffer[50] = "";
	// char tmp1[50] = "";

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

	// 플레이어가 위치한 장소의 정보 -> 함수화 할 것

	// char buffer[50] = "";
	// char tmp1[50] = "";

	gotoxyAndPrint(22, 20, "[현재 플레이어가 위치한 장소의 정보]");

	if (Maps[Players[currentTurn].CurrentPlaceX][Players[currentTurn].CurrentPlaceY].EventNumber == NONE)
	{
		itoa(Maps[Players[currentTurn].CurrentPlaceX][Players[currentTurn].CurrentPlaceY].DepartmentPrice, tmp1, 10);
		sprintf(buffer, "기본 가격 : %s", tmp1);
		gotoxyAndPrint(22, 21, buffer);

		itoa(Maps[Players[currentTurn].CurrentPlaceX][Players[currentTurn].CurrentPlaceY].OverWhelmingDegree, tmp1, 10);
		sprintf(buffer, "장악 정도 : %s", tmp1);
		gotoxyAndPrint(22, 22, buffer);
	}
	else
	{
		gotoxyAndPrint(22, 21, Maps[Players[currentTurn].CurrentPlaceX][Players[currentTurn].CurrentPlaceY].NameOfDepartment);
	}

	// 주사위 추가

	// 플레이어 위치 표현
	itoa(currentTurn + 1, tmp1, 10);
	sprintf(buffer, "Player %s", tmp1);
	gotoxyAndPrint(Players[currentTurn].CurrentPlaceX, Players[currentTurn].CurrentPlaceY, buffer);
	

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
					gotoxyAndPrint(startposx, startposy + 1, "주인 : 없음");
					break;
				case 1:
					gotoxyAndPrint(startposx, startposy + 1, "주인 : Player1");
					break;
				case 2:
					gotoxyAndPrint(startposx, startposy + 1, "주인 : Player2");
					break;
				case 3:
					gotoxyAndPrint(startposx, startposy + 1, "주인 : Player3");
					break;
				case 4:
					gotoxyAndPrint(startposx, startposy + 1, "주인 : Player4");
					break;
				}
	
				switch (Maps[indexX][indexY].OverWhelmingDegree)
				{
				case 0:
					gotoxyAndPrint(startposx, startposy + 2, "장악력 : 없음");
					break;
				case 1:
					gotoxyAndPrint(startposx, startposy + 2, "장악력 : 25%");
					break;
				case 2:
					gotoxyAndPrint(startposx, startposy + 2, "장악력 : 50%");
					break;
				case 3:
					gotoxyAndPrint(startposx, startposy + 2, "장악력 : 75%");
					break;
				case 4:
					gotoxyAndPrint(startposx, startposy + 2, "장악력 : 100%");
					break;
			}
		}
}

