#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define InitialCapital 5000

#pragma warning ( disable : 4996 )

struct Player 
{   
	int Order;
    int CurrentPlace;
    int Money;
	int NumberOfDice;
	int Items[5];
	int Events[5];
};

struct Map 
{
	char NameOfDepartment[20];
	int DepartmentOrder;
	int DepartmentPrice;
	int EventNumber;
	int Owner;
	int OverWhelmingDegree;
};

void InitMapAndPlayer(struct Player Players[], struct Map Maps[][7]);
void DrawCurrentBoard(struct Player Players[], struct Map Maps[][7]);
void PrintMapInfo(int i, int j, int startposx, int startposy, struct Map Maps[][7]);

int main (void)
{
	struct Player player[4];
	struct Map map[5][7]; // ���� 5ĭ, ���� 7 ĭ
	InitMapAndPlayer(player, map);
	DrawCurrentBoard(player, map);
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
		Players[i].CurrentPlace = 0;
		Players[i].Money = InitialCapital;
		Players[i].NumberOfDice = 0;
		for (int j = 0; j < 5; j++)
		{
			Players[i].Items[j] = 0;
			Players[i].Events[j] = 0;
		}
	}

	// �� �ʱ�ȭ
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
			Maps[i][j].EventNumber = 0;
			Maps[i][j].Owner = 0;
			Maps[i][j].OverWhelmingDegree = 0;
		}
	}

	srand(time(NULL));

	// �̸�, �а�����, ����, �̺�Ʈ ����, �����ּ���, �������

	strcpy(Maps[0][0].NameOfDepartment, "���б�");
	Maps[0][0].DepartmentOrder = 0;
	Maps[0][0].DepartmentPrice = 0;
	Maps[0][0].EventNumber = 4;
	Maps[0][0].Owner = NULL;
	Maps[0][0].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[0][1].NameOfDepartment, "���൵�ü�������");
	Maps[0][1].DepartmentOrder = 1;
	Maps[0][1].DepartmentPrice = DepartmentPrice;
	Maps[0][1].EventNumber = 0;
	Maps[0][1].Owner = NULL;
	Maps[0][1].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[0][2].NameOfDepartment, "�����������");
	Maps[0][2].DepartmentOrder = 2;
	Maps[0][2].DepartmentPrice = DepartmentPrice;
	Maps[0][2].EventNumber = 0;
	Maps[0][2].Owner = NULL;
	Maps[0][2].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[0][3].NameOfDepartment, "����ڰ�������");
	Maps[0][3].DepartmentOrder = 3;
	Maps[0][3].DepartmentPrice = DepartmentPrice;
	Maps[0][3].EventNumber = 0;
	Maps[0][3].Owner = NULL;
	Maps[0][3].OverWhelmingDegree = NULL;
	
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[0][4].NameOfDepartment, "���ռ�����������");
	Maps[0][4].DepartmentOrder = 4;
	Maps[0][4].DepartmentPrice = DepartmentPrice;
	Maps[0][4].EventNumber = 0;
	Maps[0][4].Owner = NULL;
	Maps[0][4].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[0][5].NameOfDepartment, "����������");
	Maps[0][5].DepartmentOrder = 5;
	Maps[0][5].DepartmentPrice = DepartmentPrice;
	Maps[0][5].EventNumber = 0;
	Maps[0][5].Owner = NULL;
	Maps[0][5].OverWhelmingDegree = NULL;

	strcpy(Maps[0][6].NameOfDepartment, "MT");
	Maps[0][6].DepartmentOrder = 6;
	Maps[0][6].DepartmentPrice = 0;
	Maps[0][6].EventNumber = 1;
	Maps[0][6].Owner = NULL;
	Maps[0][6].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[1][6].NameOfDepartment, "����������Ű�������");
	Maps[1][6].DepartmentOrder = 7;
	Maps[1][6].DepartmentPrice = DepartmentPrice;
	Maps[1][6].EventNumber = 0;
	Maps[1][6].Owner = NULL;
	Maps[1][6].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[2][6].NameOfDepartment, "��ǻ��������Ű�������");
	Maps[2][6].DepartmentOrder = 8;
	Maps[2][6].DepartmentPrice = DepartmentPrice;
	Maps[2][6].EventNumber = 0;
	Maps[2][6].Owner = NULL;
	Maps[2][6].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[3][6].NameOfDepartment, "����Ʈ�����������");
	Maps[3][6].DepartmentOrder = 9;
	Maps[3][6].DepartmentPrice = DepartmentPrice;
	Maps[3][6].EventNumber = 0;
	Maps[3][6].Owner = NULL;
	Maps[3][6].OverWhelmingDegree = NULL;

	strcpy(Maps[4][6].NameOfDepartment, "�������");
	Maps[4][6].DepartmentOrder = 10;
	Maps[4][6].DepartmentPrice = 0;
	Maps[4][6].EventNumber = 2;
	Maps[4][6].Owner = NULL;
	Maps[4][6].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[4][5].NameOfDepartment, "ȯ�濡�������а�");
	Maps[4][5].DepartmentOrder = 11;
	Maps[4][5].DepartmentPrice = DepartmentPrice;
	Maps[4][5].EventNumber = 0;
	Maps[4][5].Owner = NULL;
	Maps[4][5].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[4][4].NameOfDepartment, "�������а�");
	Maps[4][4].DepartmentOrder = 12;
	Maps[4][4].DepartmentPrice = DepartmentPrice;
	Maps[4][4].EventNumber = 0;
	Maps[4][4].Owner = NULL;
	Maps[4][4].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[4][3].NameOfDepartment, "�ݼ�����������");
	Maps[4][3].DepartmentOrder = 13;
	Maps[4][3].DepartmentPrice = DepartmentPrice;
	Maps[4][3].EventNumber = 0;
	Maps[4][3].Owner = NULL;
	Maps[4][3].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[4][2].NameOfDepartment, "���������������");
	Maps[4][2].DepartmentOrder = 14;
	Maps[4][2].DepartmentPrice = DepartmentPrice;
	Maps[4][2].EventNumber = 0;
	Maps[4][2].Owner = NULL;
	Maps[4][2].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[4][1].NameOfDepartment, "��.�����������");
	Maps[4][1].DepartmentOrder = 15;
	Maps[4][1].DepartmentPrice = DepartmentPrice;
	Maps[4][1].EventNumber = 0;
	Maps[4][1].Owner = NULL;
	Maps[4][1].OverWhelmingDegree = NULL;

	strcpy(Maps[4][0].NameOfDepartment, "����");
	Maps[4][0].DepartmentOrder = 16;
	Maps[4][0].DepartmentPrice = DepartmentPrice;
	Maps[4][0].EventNumber = 3;
	Maps[4][0].Owner = NULL;
	Maps[4][0].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[3][0].NameOfDepartment, "ȭ����������");
	Maps[3][0].DepartmentOrder = 17;
	Maps[3][0].DepartmentPrice = DepartmentPrice;
	Maps[3][0].EventNumber = 0;
	Maps[3][0].Owner = NULL;
	Maps[3][0].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[2][0].NameOfDepartment, "������а�");
	Maps[2][0].DepartmentOrder = 18;
	Maps[2][0].DepartmentPrice = DepartmentPrice;
	Maps[2][0].EventNumber = 0;
	Maps[2][0].Owner = NULL;
	Maps[2][0].OverWhelmingDegree = NULL;

	DepartmentPrice = ((rand() % 10) + 1) * 100;
	strcpy(Maps[1][0].NameOfDepartment, "�����а�");
	Maps[1][0].DepartmentOrder = 19;
	Maps[1][0].DepartmentPrice = DepartmentPrice;
	Maps[1][0].EventNumber = 0;
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

void DrawCurrentBoard(struct Player Players[], struct Map Maps[][7])
{
	int i, j;
	system("cls");
	system("mode con: cols=134 lines=48");

	// �ܺ��׵θ�
	gotoxyAndPrint(2, 1, "������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
	for (i = 2; i<31; i++)
		gotoxyAndPrint(2, i, "��                                                                                                                            ��");
	gotoxyAndPrint(2, i, "������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");

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
	gotoxyAndPrint(110, 7, "������������������������������������");
	gotoxyAndPrint(110, 13, "������������������������������������");
	gotoxyAndPrint(110, 19, "������������������������������������");
	gotoxyAndPrint(110, 25, "������������������������������������");

	gotoxyAndPrint(109, 7, "��");
	gotoxyAndPrint(109, 25, "��");

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

