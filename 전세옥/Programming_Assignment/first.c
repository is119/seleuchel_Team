#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ������ �ε��� ����
#define �����н� 0
#define MTȸ�Ǳ� 1
#define ����ī�� 2
#define ������� 3
#define ��� 4

// �̺�Ʈ �ε��� ����

// �ʱ� �ں�
#define InitialCapital 5000

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

void InitMapAndPlayer(Player* Players, Map* Maps);
void Play(Player* Players, Map* Maps);
void Play (Player* Players, Map* Maps);

int main (void)
{
	struct Player player[4];
	struct Map map[5][7]; // ���� 5ĭ, ���� 7 ĭ
	InitMapAndPlayer(&player[0], &map[0][0]);
	Play(&player[0], &map[0][0]);

	return 0;
}

void InitMapAndPlayer(Player* Players, Map* Maps)
{
	srand(time(NULL));
	// �÷��̾� �ʱ�ȭ

	int const NumberOfPlayers = 4;
	for(int i = 0; i < NumberOfPlayers; i++ )
	{
		Players[i] = { i, 0, InitialCapital, 0, {0, }, {0, } };
	}

	// �� �ʱ�ȭ
	int DepartmentPrice = ((rand() % 10) + 1) * 100;
	
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 7; j++)
		{
			Maps[i][j] = NULL;
		}
	}
	// �̸�, �а�����, ����, �̺�Ʈ ����, �����ּ���, �������
	Maps[0][0] = {"���б�", 0, 0, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[0][1] = {"���൵�ü�������", 1, DepartmentPrice, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[0][3] = {"�����������", 2, DepartmentPrice, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[0][3] = {"����ڰ�������", 3, DepartmentPrice, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[0][4] = {"���ռ�����������", 4, DepartmentPrice, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[0][5] = {"����������", 5, DepartmentPrice, 4, NULL, NULL};
	Maps[0][6] = {"MT", 6, 0, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[1][6] = {"����������Ű�������", 7, DepartmentPrice, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[2][6] = {"��ǻ��������Ű�������", 8, DepartmentPrice, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[3][6] = {"����Ʈ�����������", 9, DepartmentPrice, 4, NULL, NULL};
	Maps[4][6] = {"�������", 10, 0, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[4][5] = {"ȯ�濡�������а�", 11, DepartmentPrice, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[4][4] = {"�������а�", 12, DepartmentPrice, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[4][3] = {"�ݼ�����������", 13, DepartmentPrice, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[4][2] = {"���������������", 14, DepartmentPrice, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[4][1] = {"��.�����������", 15, DepartmentPrice, 4, NULL, NULL};
	Maps[4][0] = {"����", 16, 0, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[3][0] = {"ȭ����������", 17, DepartmentPrice, 4, NULL, NULL};
	Maps[2][0] = {"������а�", 18, DepartmentPrice, 4, NULL, NULL};
	Maps[1][0] = {"�����а�", 19, DepartmentPrice, 4, NULL, NULL};

}

void PlayTurn()
{

}

void Play (Player* Players, Map* Maps)
{
	int turn = 1;
	PlayTurn(Players[turn - 1]);

}