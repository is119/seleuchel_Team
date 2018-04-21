/*
게임플레이 관련 함수목록
*/

#include "bluemarble.h"

void draw_digital_dice(int who)
{
	int j, k;
	for (j = 0; j<7; j++)
	{
		for (k = 0; k<7; k++)
		{
			gotoxy(96 + (k * 2), 18 + j);
			if (dice_digital[who][j][k] == 0)
			{
				setcolor(0, 0);
				printf("□");
				setcolor(0, 15);

			}
			else
			{
				setcolor(15, 15);
				printf("□");
				setcolor(0, 15);
			}
		}
	}


}
void Draw_Board()
{
	int i, j;
	//system("mode con: cols=132 lines=46"); 
	system("mode con: cols=134 lines=48");
	// 외부테두리
	gotoprint(2, 1, "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	for (i = 2; i<31; i++)
		gotoprint(2, i, "┃                                                                                                                            ┃");
	gotoprint(2, i, "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	// 내부테두리
	gotoprint(20, 7, "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	for (i = 8; i<25; i++)
		gotoprint(20, i, "┃                                                                                        ┃");
	gotoprint(20, i, "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

	// 위쪽줄
	for (j = 0; j<6; j++)
	{
		int l = 0;
		if (l == 0)
			l = 20;
		gotoprint(l + 20 * j - j * 2, 1, "┳");
		for (i = 2; i<7; i++)
			gotoprint(l + 20 * j - j * 2, i, "┃");
		if (j == 0)
			gotoprint(l + 20 * j - j * 2, i, "╋");
		else
			gotoprint(l + 20 * j - j * 2, i, "┻");

	}

	// 아래쪽줄
	for (j = 0; j<6; j++)
	{
		int l = 0;
		if (l == 0)
			l = 20;
		if (j == 0)
			gotoprint(l + 20 * j - j * 2, 25, "╋");
		else
			gotoprint(l + 20 * j - j * 2, 25, "┳");
		for (i = 26; i<31; i++)
			gotoprint(l + 20 * j - j * 2, i, "┃");
		gotoprint(l + 20 * j - j * 2, i, "┻");
	}

	// 왼쪽줄
	gotoprint(2, 7, "┣━━━━━━━━");
	gotoprint(2, 13, "┣━━━━━━━━┫");
	gotoprint(2, 19, "┣━━━━━━━━┫");
	gotoprint(2, 25, "┣━━━━━━━━");
	// 오른쪽줄
	gotoprint(110, 7, "╋━━━━━━━━┫");
	gotoprint(110, 13, "┣━━━━━━━━┫");
	gotoprint(110, 19, "┣━━━━━━━━┫");
	gotoprint(110, 25, "╋━━━━━━━━┫");


	for (j = 0; j<4; j++)
	{
		if (j == 0)
		{
			for (i = 0; i<6; i++)
			{
				int l = 0;
				if (l == 0)
					l = 112;
				setcolor(15, 8);
				gotoprint(l - 20 * i + i * 2, 26, building_Name[i]);
				setcolor(0, 15);
				if (i != 0)
				{
					gotoprint(l - 20 * i + i * 2, 27, "주인  :");
					gotoprint(l - 20 * i + i * 2, 28, "장악력:");
				}
			}
		}
		else if (j == 1)
		{
			for (i = 0; i<4; i++)
			{
				setcolor(15, 8);
				gotoprint(4, 26 - i * 6, building_Name[6 + i]);
				setcolor(0, 15);
				gotoprint(4, 27 - i * 6, "주인  :");
				gotoprint(4, 28 - i * 6, "장악력:");
			}
		}
		else if (j == 2)
		{
			for (i = 0; i<6; i++)
			{
				int l = 0;
				if (l == 0)
					l = 4;
				setcolor(15, 8);
				gotoprint(l + 20 * i - i * 2, 2, building_Name[10 + i]);
				setcolor(0, 15);
				if (i != 0)
				{
					gotoprint(l + 20 * i - i * 2, 3, "주인  :");
					gotoprint(l + 20 * i - i * 2, 4, "장악력:");
				}
			}
		}
		else if (j == 3)
		{
			for (i = 0; i<4; i++)
			{
				setcolor(15, 8);
				gotoprint(112, 2 + i * 6, building_Name[16 + i]);
				setcolor(0, 15);
				if (i != 0)
				{
					gotoprint(112, 3 + i * 6, "주인  :");
					gotoprint(112, 4 + i * 6, "장악력:");
				}
			}
		}
	}


	// 플레이어란
	gotoprint(24, 9, "[  플레이어 건물수/  재산]");
	for (i = 0; i<players; i++)
	{
		setcolor(p_color[i], 15);
		gotoxy(24, 10 + i);
		printf("%8s %s :  ", pl[i].name, player_img);

		//	gotoprint(30,10+i,player_img);
		setcolor(0, 15);
	}

	// 건물상태
	//gotoprint(22,20,"─      건물상태   ─");
	gotoprint(24, 21, "빌딩 가격      : ");
	gotoprint(24, 22, "장악 비용      : ");
	gotoprint(24, 23, "통행료         : ");

	// 주사위
	gotoprint(96, 17, "[   주사위   ]");
	gotoprint(64, 33, "【                  】←던지는힘");

	//아이템
	gotoprint(70, 9, "[     아이템     ]");
	gotoprint(70, 10, "MT회피권 : ");
	gotoprint(70, 11, "빽       : ");
	draw_digital_dice(0);
}


void draw_stat()
{
	int i;
	for (i = 0; i<maxplayers; i++)
	{
		setcolor(p_color[i], 15);
		gotoxy(35, 10 + i);
		printf("                                ");
		gotoxy(35, 10 + i);
		if (pl[i].stat != -1)
		{
			printf(":  %d  %8d ", pl[i].Mybuilding, pl[i].MONEY);
		}
		else
		{
			printf("파산                            ");
		}
	}

	setcolor(0, 15);

	for (i = 0; i < 2; i++)
	{
		gotoxy(82, 10+i);
		printf("%d",pl[order].Item[i]);
	}

	for (i = 0; i<boardNum; i++)
	{
		if (i != 0 && i != 10 && i != 16)
		{
			gotoprint(mal_postion[i][0] + 7, mal_postion[i][1] - 3, "         ");
			//gotoxy(mal_postion[i][0]+7,mal_postion[i][1]-3);
			gotoprint(mal_postion[i][0] + 7, mal_postion[i][1] - 2, "         ");
			//gotoxy(mal_postion[i][0] + 7, mal_postion[i][1] - 2);
			gotoprint(mal_postion[i][0], mal_postion[i][1] - 1, "      ");
			if (bp[i].order == -1)
			{
				gotoxy(mal_postion[i][0] + 7, mal_postion[i][1] - 3);
				printf("없음");

				gotoxy(mal_postion[i][0] + 7, mal_postion[i][1] - 2);
				printf("X");


			}
			else
			{
				gotoxy(mal_postion[i][0] + 7, mal_postion[i][1] - 3);
				setcolor(p_color[bp[i].order], 15);
				printf("%-8s", pl[bp[i].order].name);

				gotoxy(mal_postion[i][0] + 7, mal_postion[i][1] - 2);
				setcolor(p_color[bp[i].order], 15);
				printf("%d%%", bp[i].noslevel);

				if (bp[i].base == 1)
				{
					setcolor(15, p_color[bp[i].order]);
					gotoprint(mal_postion[i][0], mal_postion[i][1] - 1, "[Base]");
					setcolor(0, 15);
				}
			}
			setcolor(0, 15);

			gotoprint(22, 20, "                                   ");


			gotoxy(22, 20);
			printf("[%5s님이 밟고 있는 건물상태]", pl[order].name);
			if (bp[pl[order].mypos].order >= 0)
				setcolor(p_color[bp[pl[order].mypos].order], 15);
			else
				setcolor(0, 15);
			gotoxy(38, 21);
			printf("   %6d     ", bp[pl[order].mypos].price);
			gotoxy(38, 22);
			printf("   %6d     ", bp[pl[order].mypos].price);
			gotoxy(38, 23);
			printf("   %6d     ", bp[pl[order].mypos].price / 2);
			setcolor(0, 15);
		}
	}
}

