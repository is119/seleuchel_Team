/*
필수 함수 목록
*/

#include "bluemarble.h"

void setcolor(int color, int bgcolor){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((bgcolor & 0xf) << 4) | (color & 0xf));
}

void CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
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


void deleteprint()
{
	gotoxyAndPrint(1, 32, "                                                                                                                                  ");
	gotoxyAndPrint(1, 33, "                                                           ");
	gotoxyAndPrint(1, 34, "                                                                                                                                  ");
	gotoxyAndPrint(1, 35, "                                                                                                                                  ");
	gotoxyAndPrint(1, 36, "                                                                                                                                  ");
	gotoxyAndPrint(1, 37, "                                                                                                                                  ");
	gotoxyAndPrint(1, 38, "                                                                                                                                  ");
	gotoxyAndPrint(1, 39, "                                                                                                                                  ");
	gotoxyAndPrint(1, 40, "                                                                                                                                  ");
	gotoxyAndPrint(1, 41, "                                                                                                                                  ");
	gotoxyAndPrint(1, 42, "                                                                                                                                  ");
	gotoxyAndPrint(1, 43, "                                                                                                                                  ");
	gotoxyAndPrint(1, 44, "                                                                                                                                  ");
}

void Move_Pieces(int num, int delay)
{
	int j;
	int n = num;
	int dinum;
	if (n < 0)
		n *= -1;
	dinum = n;
	for (j = 0; j < n; j++)
	{
		gotoxyAndPrint(pl[order].x, pl[order].y, "  ");
		if (num > 0)
		{
			pl[order].mypos++;
			if (pl[order].mypos > 19)
			{
				pl[order].mypos = 0;
				if (gamemode == 0) // 기본 모드 
				{
					setcolor(0, 10);
					gotoxyAndPrint(70, 35, "한바퀴를 돌았으므로 장학금이 주어집니다");
					setcolor(0, 15);
					draw_stat();
					PlaySound(TEXT("coin+.wav"), NULL, SND_SYNC);
					gotoxyAndPrint(70, 35, "                                         ");
					pl[order].MONEY += MONTH_PAY;
					pl[order].round++;
				}
			}

			if (gamemode == 1) //베이스 모드
			{
				if (bp[pl[order].mypos].order == order && bp[pl[order].mypos].base == 1)
				{
					setcolor(0, 10);
					gotoxyAndPrint(70, 35, "한바퀴를 돌았으므로 장학금이 주어집니다");
					setcolor(0, 15);
					draw_stat();
					PlaySound(TEXT("coin+.wav"), NULL, SND_SYNC);
					gotoxyAndPrint(70, 35, "                                         ");
					pl[order].MONEY += MONTH_PAY;
					pl[order].round++;
				}
			}

		}
		else
		{
			pl[order].mypos--;
			if (pl[order].mypos < 0)
			{
				pl[order].mypos = 19;
			}
		}
		pl[order].x = mal_postion[pl[order].mypos][0] + (order * 2);
		pl[order].y = mal_postion[pl[order].mypos][1];

		setcolor(p_color[order], 0);
		gotoxyAndPrint(pl[order].x, pl[order].y, player_img);
		setcolor(0, 15);
		PlaySound(TEXT("step_wood2.wav"), NULL, SND_ASYNC);

		if (dinum<=6)
		draw_digital_dice(--dinum);
		else
		draw_digital_dice(0);

		draw_stat();
		Sleep(delay);
	}
}
