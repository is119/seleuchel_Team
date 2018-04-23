#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define InitialCapital 5000

#pragma warning ( disable : 4996 )
#define _CRT_SECURE_NO_WARNINGS

// �̺�Ʈ �迭 ���� -> �״�� ���

#define NONE 0
#define MT 1
#define SchoolBus 2
#define Previous_Exam_Paper 3
#define Scholarship 4

// ����(������) �迭 ���� -> -5 �ؼ� ���

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
	struct Map map[5][7]; // ���� 5ĭ, ���� 7 ĭ
	int currentTurn = 0;
	InitMapAndPlayer(player, map);
	DrawCurrentBoard(player, map, currentTurn);
	system("pause");
	return 0;
}

void InitMapAndPlayer(struct Player Players[], struct Map Maps[][7])
{
	// �÷��̾� �ʱ�ȭ

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
	
	// �� �ʱ�ȭ

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

		// �̸�, �а�����, ����, �̺�Ʈ ����, �����ּ���, �������

		strcpy(Maps[0][0].NameOfDepartment, "���б�");
		Maps[0][0].DepartmentOrder = 0;
		Maps[0][0].DepartmentPrice = 0;
		Maps[0][0].EventNumber = Scholarship;
		Maps[0][0].Owner = NONE;
		Maps[0][0].OverWhelmingDegree = NONE;
		Maps[0][0].pos.X = 6;
		Maps[0][0].pos.Y = 4;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[0][1].NameOfDepartment, "���൵�ü�������");
		Maps[0][1].DepartmentOrder = 1;
		Maps[0][1].DepartmentPrice = DepartmentPrice;
		Maps[0][1].Owner = NONE;
		Maps[0][1].OverWhelmingDegree = NONE;
		Maps[0][1].pos.X = 22;
		Maps[0][1].pos.Y = 4;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[0][2].NameOfDepartment, "�����������");
		Maps[0][2].DepartmentOrder = 2;
		Maps[0][2].DepartmentPrice = DepartmentPrice;
		Maps[0][2].Owner = NONE;
		Maps[0][2].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[0][3].NameOfDepartment, "����ڰ�������");
		Maps[0][3].DepartmentOrder = 3;
		Maps[0][3].DepartmentPrice = DepartmentPrice;
		Maps[0][3].Owner = NONE;
		Maps[0][3].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[0][4].NameOfDepartment, "���ռ�����������");
		Maps[0][4].DepartmentOrder = 4;
		Maps[0][4].DepartmentPrice = DepartmentPrice;
		Maps[0][4].Owner = NONE;
		Maps[0][4].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[0][5].NameOfDepartment, "����������");
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
		strcpy(Maps[1][6].NameOfDepartment, "����������Ű�������");
		Maps[1][6].DepartmentOrder = 7;
		Maps[1][6].DepartmentPrice = DepartmentPrice;
		Maps[1][6].Owner = NONE;
		Maps[1][6].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[2][6].NameOfDepartment, "��ǻ��������Ű�������");
		Maps[2][6].DepartmentOrder = 8;
		Maps[2][6].DepartmentPrice = DepartmentPrice;
		Maps[2][6].Owner = NONE;
		Maps[2][6].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[3][6].NameOfDepartment, "����Ʈ�����������");
		Maps[3][6].DepartmentOrder = 9;
		Maps[3][6].DepartmentPrice = DepartmentPrice;
		Maps[3][6].Owner = NONE;
		Maps[3][6].OverWhelmingDegree = NONE;

		strcpy(Maps[4][6].NameOfDepartment, "�������");
		Maps[4][6].DepartmentOrder = 10;
		Maps[4][6].DepartmentPrice = 0;
		Maps[4][6].EventNumber = SchoolBus;
		Maps[4][6].Owner = NONE;
		Maps[4][6].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[4][5].NameOfDepartment, "ȯ�濡�������а�");
		Maps[4][5].DepartmentOrder = 11;
		Maps[4][5].DepartmentPrice = DepartmentPrice;
		Maps[4][5].Owner = NONE;
		Maps[4][5].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[4][4].NameOfDepartment, "�������а�");
		Maps[4][4].DepartmentOrder = 12;
		Maps[4][4].DepartmentPrice = DepartmentPrice;
		Maps[4][4].Owner = NONE;
		Maps[4][4].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[4][3].NameOfDepartment, "�ݼ�����������");
		Maps[4][3].DepartmentOrder = 13;
		Maps[4][3].DepartmentPrice = DepartmentPrice;
		Maps[4][3].Owner = NONE;
		Maps[4][3].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[4][2].NameOfDepartment, "���������������");
		Maps[4][2].DepartmentOrder = 14;
		Maps[4][2].DepartmentPrice = DepartmentPrice;
		Maps[4][2].Owner = NONE;
		Maps[4][2].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[4][1].NameOfDepartment, "��.�����������");
		Maps[4][1].DepartmentOrder = 15;
		Maps[4][1].DepartmentPrice = DepartmentPrice;
		Maps[4][1].Owner = NONE;
		Maps[4][1].OverWhelmingDegree = NONE;

		strcpy(Maps[4][0].NameOfDepartment, "����");
		Maps[4][0].DepartmentOrder = 16;
		Maps[4][0].DepartmentPrice = DepartmentPrice;
		Maps[4][0].EventNumber = Previous_Exam_Paper;
		Maps[4][0].Owner = NONE;
		Maps[4][0].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[3][0].NameOfDepartment, "ȭ����������");
		Maps[3][0].DepartmentOrder = 17;
		Maps[3][0].DepartmentPrice = DepartmentPrice;
		Maps[3][0].Owner = NONE;
		Maps[3][0].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[2][0].NameOfDepartment, "������а�");
		Maps[2][0].DepartmentOrder = 18;
		Maps[2][0].DepartmentPrice = DepartmentPrice;
		Maps[2][0].Owner = NONE;
		Maps[2][0].OverWhelmingDegree = NONE;

		DepartmentPrice = ((rand() % 10) + 1) * 100;
		strcpy(Maps[1][0].NameOfDepartment, "�����а�");
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

	// ���� ��ü���� ���� �����

	DrawMapEdge(i, j);

	// ������ ǥ��

	DrawContents(Maps);

	
	char buffer[50] = "";
	char tmp1[50] = "";
	char tmp2[50] = "";

	//�÷��̾�� ����, �� ��ġ ǥ��
	
	PlayersInfo(Players, tmp1, tmp2, buffer, Maps);

	// �� �÷��̾��� ����( ������, ��ġ�� ��� )ǥ��

	CurrentPlayerInfo(Players, currentTurn, tmp1, buffer, Maps);

	// �ֻ��� �߰� �� ��!!!

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
					gotoxyAndPrint(startposx, startposy + 1, "���� : ����");
					break;
				case 1:
					gotoxyAndPrint(startposx, startposy + 1, "���� : Player1");
					break;
				case 2:
					gotoxyAndPrint(startposx, startposy + 1, "���� : Player2");
					break;
				case 3:
					gotoxyAndPrint(startposx, startposy + 1, "���� : Player3");
					break;
				case 4:
					gotoxyAndPrint(startposx, startposy + 1, "���� : Player4");
					break;
				}
	
				switch (Maps[indexX][indexY].OverWhelmingDegree)
				{
				case 0:
					gotoxyAndPrint(startposx, startposy + 2, "��Ƿ� : ����");
					break;
				case 1:
					gotoxyAndPrint(startposx, startposy + 2, "��Ƿ� : 25%");
					break;
				case 2:
					gotoxyAndPrint(startposx, startposy + 2, "��Ƿ� : 50%");
					break;
				case 3:
					gotoxyAndPrint(startposx, startposy + 2, "��Ƿ� : 75%");
					break;
				case 4:
					gotoxyAndPrint(startposx, startposy + 2, "��Ƿ� : 100%");
					break;
			}
		}
}

void DrawMapEdge(int i, int j)
{
	// �ܺ��׵θ�
	gotoxyAndPrint(2, 1, "��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
	for (i = 2; i<31; i++)
		gotoxyAndPrint(2, i, "��                                                                                                                                   ��");
	gotoxyAndPrint(2, i, "��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");

	// �����׵θ�
	gotoxyAndPrint(20, 7, "������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
	for (i = 8; i<25; i++)
		gotoxyAndPrint(20, i, "��                                                                                         ��");
	gotoxyAndPrint(20, i, "������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");

	// ������
	for (j = 0; j<6; j++)
	{
		int l = 0;
		if (l == 0)
			l = 20;
		gotoxyAndPrint(l + 20 * j - j * 2, 1, "��");
		for (i = 2; i<7; i++)
			gotoxyAndPrint(l + 20 * j - j * 2, i, "��");
		if (j == 0)
			gotoxyAndPrint(l + 20 * j - j * 2, i, "��");
		else
			gotoxyAndPrint(l + 20 * j - j * 2, i, "��");

	}

	// �Ʒ�����
	for (j = 0; j<6; j++)
	{
		int l = 0;
		if (l == 0)
			l = 20;
		if (j == 0)
			gotoxyAndPrint(l + 20 * j - j * 2, 25, "��");
		else
			gotoxyAndPrint(l + 20 * j - j * 2, 25, "��");
		for (i = 26; i<31; i++)
			gotoxyAndPrint(l + 20 * j - j * 2, i, "��");
		gotoxyAndPrint(l + 20 * j - j * 2, i, "��");
	}

	// ������
	gotoxyAndPrint(2, 7, "����������������������������������");
	gotoxyAndPrint(2, 13, "��������������������������������������");
	gotoxyAndPrint(2, 19, "��������������������������������������");
	gotoxyAndPrint(2, 25, "����������������������������������");

	// ��������
	gotoxyAndPrint(110, 7, "��������������������������������������������������");
	gotoxyAndPrint(110, 13, "��������������������������������������������������");
	gotoxyAndPrint(110, 19, "��������������������������������������������������");
	gotoxyAndPrint(110, 25, "��������������������������������������������������");

	gotoxyAndPrint(109, 7, "��");
	gotoxyAndPrint(109, 25, "��");
}

void DrawContents(struct Map Maps[][7])
{
	// ������ ����

	int indexy = 0;
	for (int startposx = 4; startposx <= 112; startposx += 18)
	{
		int const startposy = 2;
		PrintMapInfo(0, indexy, startposx, startposy, Maps);
		indexy++;
	}

	// ������ �Ʒ���
	indexy = 0;
	for (int startposx = 4; startposx <= 112; startposx += 18)
	{
		int const startposy = 26;
		PrintMapInfo(4, indexy, startposx, startposy, Maps);
		indexy++;
	}

	// ������ ����
	PrintMapInfo(1, 0, 4, 8, Maps);
	PrintMapInfo(2, 0, 4, 14, Maps);
	PrintMapInfo(3, 0, 4, 20, Maps);

	// ������ ������
	PrintMapInfo(1, 6, 112, 8, Maps);
	PrintMapInfo(2, 6, 112, 14, Maps);
	PrintMapInfo(3, 6, 112, 20, Maps);
}

void PlayersInfo(struct Player Players[], char tmp1[], char tmp2[], char buffer[], struct Map Maps[][7])
{
	// �ǹ� ���� ���

	gotoxyAndPrint(22, 9, "[ �÷��̾� : �ǹ��� / ��� ]");

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

	// �÷��̾�� �ʻ� ��ġ ǥ��

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
	// �� �÷��̾ ������ �ִ� ������

	gotoxyAndPrint(80, 9, "[ �� �÷��̾��� ������ ��� ]");

	itoa(Players[currentTurn].Items[FreePass - 5], tmp1, 10);
	sprintf(buffer, "�����н� : %s", tmp1);
	gotoxyAndPrint(80, 10, buffer);

	itoa(Players[currentTurn].Items[AvoidMT - 5], tmp1, 10);
	sprintf(buffer, "MTȸ�Ǳ� : %s", tmp1);
	gotoxyAndPrint(80, 11, buffer);

	itoa(Players[currentTurn].Items[BusCard - 5], tmp1, 10);
	sprintf(buffer, "����ī�� : %s", tmp1);
	gotoxyAndPrint(80, 12, buffer);

	itoa(Players[currentTurn].Items[FreeOverWhelming - 5], tmp1, 10);
	sprintf(buffer, "������� : %s", tmp1);
	gotoxyAndPrint(80, 13, buffer);

	itoa(Players[currentTurn].Items[Donation - 5], tmp1, 10);
	sprintf(buffer, "���     : %s", tmp1);
	gotoxyAndPrint(80, 14, buffer);

	// �� ��ġ�� ���� ���� ǥ��

	gotoxyAndPrint(22, 20, "[���� �÷��̾ ��ġ�� ����� ����]");

	if (Maps[Players[currentTurn].CurrentPlaceX][Players[currentTurn].CurrentPlaceY].EventNumber == NONE)
	{
		itoa(Maps[Players[currentTurn].CurrentPlaceX][Players[currentTurn].CurrentPlaceY].DepartmentPrice, tmp1, 10);
		sprintf(buffer, "�⺻ ���� : %s", tmp1);
		gotoxyAndPrint(22, 21, buffer);

		itoa(Maps[Players[currentTurn].CurrentPlaceX][Players[currentTurn].CurrentPlaceY].OverWhelmingDegree, tmp1, 10);
		sprintf(buffer, "��� ���� : %s", tmp1);
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