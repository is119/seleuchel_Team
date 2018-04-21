/*
게임플레이 관련 함수목록
*/

#include "bluemarble.h"

void Game_Init()
{
	int i, j;

	//pl[0].MONEY = 1600;
//	pl[1].MONEY = 850;

	for (i = 0; i<players; i++)
	{
		pl[i].MONEY=PL_STARTMONEY;
	
		pl[i].Mybuilding = 0;
		pl[i].stat = 0;
		pl[i].round = 1;

		pl[i].mypos = 0;
		pl[i].Mybuilding = 0;

		for (j=0; j<2; j++)
			pl[i].Item[j] = 0;

		if (gamemode == 0)
		{
			pl[i].x = mal_postion[0][0] + (i * 2);
			pl[i].y = mal_postion[0][1];
			setcolor(p_color[i], 0);
			gotoprint(pl[i].x, pl[i].y, player_img);
			setcolor(0, 15);
		}
	}

	for (i = 0; i<boardNum; i++)
	{
		if (i == 0) //버스
			bp[i].order = -2;
		else if (i == 10) // 이벤트
			bp[i].order = -4;
		else if (i == 16) // MT (돈내고 휴식)
			bp[i].order = -5;
		else
			bp[i].order = -1;
		bp[i].price = building_Price[i];
		bp[i].noslevel = 0;
	}
}

void random_turn()
{
	int rn;
	int i;

	for (i = 0; i < players; i++)
	{
		do{
			rn = rand() % players;
		} while (od[rn] != 0);
			od[rn] = i;
	}
	
}

int victory() // 플레이어수가 1일때만승리등록되있으나 나중에 지정된 턴이 지나면 남아있는 돈으로 승자를 가리는 것을 추가시켜야됨
{
	int i;
	int c = 0;
	// 플레이어수가 1명일때 승
	if (players == 1)
	{
		for (i = 0; i<MAX_USER; i++)
		{
			if (pl[i].stat != -1)
			{
				setcolor(10, 0);
				gotoxy(38, 16);
				printf("             %8s님이  이겼습니다!                     ", pl[i].name);
				setcolor(0, 15);
				return 1;
			}
		}
	}

	// 과를 모두 지배했을 떄 승 
	for (i = 0; i < boardNum; i++)
	{
		if (bp[i].order != order)
			if (bp[i].base == 0)
				c = -1;
	}

	if (c != -1)
	{
		setcolor(10, 0);
		gotoxy(38, 16);
		printf("             %8s님이  이겼습니다!             ", pl[order].name);
		setcolor(0, 15);
		return 1;
	}

	return 0;
}


