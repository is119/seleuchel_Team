#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 아이템 인덱스 숫자
#define 프리패스 0
#define MT회피권 1
#define 버스카드 2
#define 무료장악 3
#define 기부 4

// 이벤트 인덱스 숫자

// 초기 자본
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
	struct Map map[5][7]; // 세로 5칸, 가로 7 칸
	InitMapAndPlayer(&player[0], &map[0][0]);
	Play(&player[0], &map[0][0]);

	return 0;
}

void InitMapAndPlayer(Player* Players, Map* Maps)
{
	srand(time(NULL));
	// 플레이어 초기화

	int const NumberOfPlayers = 4;
	for(int i = 0; i < NumberOfPlayers; i++ )
	{
		Players[i] = { i, 0, InitialCapital, 0, {0, }, {0, } };
	}

	// 맵 초기화
	int DepartmentPrice = ((rand() % 10) + 1) * 100;
	
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 7; j++)
		{
			Maps[i][j] = NULL;
		}
	}
	// 이름, 학과순서, 가격, 이벤트 숫자, 소유주숫자, 장악정도
	Maps[0][0] = {"장학금", 0, 0, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[0][1] = {"건축도시설계전공", 1, DepartmentPrice, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[0][3] = {"건축공학전공", 2, DepartmentPrice, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[0][3] = {"고분자공학전공", 3, DepartmentPrice, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[0][4] = {"융합섬유공학전공", 4, DepartmentPrice, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[0][5] = {"기계공학전공", 5, DepartmentPrice, 4, NULL, NULL};
	Maps[0][6] = {"MT", 6, 0, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[1][6] = {"전자정보통신공학전공", 7, DepartmentPrice, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[2][6] = {"컴퓨터정보통신공학전공", 8, DepartmentPrice, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[3][6] = {"소프트웨어공학전공", 9, DepartmentPrice, 4, NULL, NULL};
	Maps[4][6] = {"스쿨버스", 10, 0, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[4][5] = {"환경에너지공학과", 11, DepartmentPrice, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[4][4] = {"생물공학과", 12, DepartmentPrice, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[4][3] = {"금속재료공학전공", 13, DepartmentPrice, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[4][2] = {"세라믹재료공학전공", 14, DepartmentPrice, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[4][1] = {"광.전자재료전공", 15, DepartmentPrice, 4, NULL, NULL};
	Maps[4][0] = {"족보", 16, 0, 4, NULL, NULL};
	DepartmentPrice = ((rand() % 10) + 1) * 100;
	Maps[3][0] = {"화공소재전공", 17, DepartmentPrice, 4, NULL, NULL};
	Maps[2][0] = {"전기공학과", 18, DepartmentPrice, 4, NULL, NULL};
	Maps[1][0] = {"토목공학과", 19, DepartmentPrice, 4, NULL, NULL};

}

void PlayTurn()
{

}

void Play (Player* Players, Map* Maps)
{
	int turn = 1;
	PlayTurn(Players[turn - 1]);

}