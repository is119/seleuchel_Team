/*
게임플레이 관련 함수목록
*/

#include "bluemarble.h"


int throwing_dice()
{
	int m;
	int power = -1;
	int updown = 0;

	m = (rand() % 6) + 1;

	_getch();

	Sleep(50);
	while (_kbhit())
	{
		_getch();
		if (updown == 0 && power < 8)
		{
			power++;
			if (power == 8)
				updown = 1;
		}
		else if (updown == 1 && power > 0)
		{
			power--;
			if (power == 0)
				updown = 0;
		}


		if (updown == 0)
		{
			setcolor(4, 4);
			gotoxy(66 + (power * 2), 33);
			printf("  ");
		}
		else
		{
			setcolor(0, 15);
			gotoxy(66 + (power * 2), 33);
			printf("  ");
		}
		setcolor(0, 15);
		Sleep(60);
	}
	//fflush(stdin);
	m += power * 1000;
	m = (m % 6) + 1;
	gotoprint(66, 33, "                ");
	if (m <= 0)
	{
		m = rand() % 6 + 1;
		draw_digital_dice(m);
	}
	else
	{
		draw_digital_dice(m);
	}
	PlaySound(TEXT("throwingDice.wav"), NULL, SND_SYNC);

	return m;
}
