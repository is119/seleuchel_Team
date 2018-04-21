/*
필수 함수 목록
*/

#include "bluemarble.h"

void DrunkParty()
{
	int rn, rn2;
	rn = rand() % 3;

	if (rn == 0) //취함
	{
		rn2 = (rand() % 5) + 1;
		gotoxy(2, 37);
		setcolor(0, 12);
		printf("뒤로 %d칸 갑니다.", rn2);
		setcolor(0, 15);
		Move_Pieces(-rn2, 200);
	}
	else if (rn == 1) //취함
	{
		rn2 = (rand() % 5) + 1;

		gotoxy(2, 37);
		setcolor(0, 10);
		printf("앞으로 %d칸 갑니다.", rn2);
		setcolor(0, 15);
		Move_Pieces(rn2, 200);
	}
	else
	{
		setcolor(15, 0);
		gotoprint(2, 37, "불운이 있을법 했지만  아무 일 도 없었습니다 ㅎ");
		setcolor(0, 15);
	}
}

void gameble()
{
	int money;
	int rn;
	char str[200];
	gotoxy(2, 36);
	printf("얼마를 거시겠습니까? ");
	setcolor(0, 14);
	printf("걸은 수의 두배");
	setcolor(0, 15);
	printf("를 얻을 수 있습니다.");
	gotoprint(2, 37, "입력(0이상) : ");
	while (1)
	{
		CursorView(1);
		do{
			gotoprint(16, 37, "                                                                                                                ");
			gotoxy(16, 37);
			gets(str);
		} while (strcmp(str, "") == 0 || str[0] == ' ');
		CursorView(0);
		money = atoi(str);
	
		if (money > 0 && pl[order].MONEY > money)
			break;
		else
		{
			gotoprint(16, 37, "다시 입력해주세요");
			Sleep(1000);
			gotoprint(16, 37, "                                                                                                      ");
		}
	}
	PlaySound(TEXT("coinflip.wav"), NULL, SND_ASYNC);
	gotoprint(2, 38, "■■■");
	Sleep(300);
	gotoprint(8, 38, "■■■");
	Sleep(300);
	gotoprint(14, 38, "■■■");
	Sleep(300);
	rn = rand() % 2;

	if (rn == 0)
	{
		gotoxy(2, 39);
		setcolor(0, 10);
		printf("성공! $%d원을 도박으로 얻었습니다!", money * 2);
		setcolor(0, 15);
		pl[order].MONEY += money * 2;
		PlaySound(TEXT("win1.wav"), NULL, SND_ASYNC);
	}
	else
	{
		gotoxy(2, 39);
		setcolor(0, 12);
		printf("실패.. $%d원을 도박으로 잃었습니다..", money);
		setcolor(0, 15);
		pl[order].MONEY -= money;
		PlaySound(TEXT("lose1.wav"), NULL, SND_ASYNC);
	}
}

void bus_card()
{
	gotoprint(2, 36, "지금 바로 버스정류장으로 갑니다.");
	gotoprint(2, 37, "다음 턴에 버스를 이용할 수 있습니다.");
	while (pl[order].mypos != 0)
		Move_Pieces(1, 200);
	pl[order].stat = 2;
}


void md_func()
{
	int i;

	char str[100];
	gotoxy(2, 36);
	printf("장악력을 올릴 과를 입력하세요 없으면 ");
	setcolor(15, 0);
	printf("'없음'");
	setcolor(0, 15);
	printf("을 입력해주세요");
	gotoprint(2, 37, "입력 : ");
	while (1)
	{
		CursorView(1);
		do{
			gotoprint(9, 37, "                                                                                                                          ");
			gotoxy(9, 37);
			gets_s(str, sizeof(str));
		} while (strcmp(str, "") == 0);
		CursorView(0);
		

		if (strcmp(str, "없음") == 0)
		{
			break;
		}
		for (i = 0; i < boardNum; i++)
		{
			if (strcmp(str, building_Name[i]) == 0)
			{
				if (bp[i].order == order)
				{
					choice_dominate(pl[order].round, i);
					draw_stat();
					return;
				}
				
			}
		}

			gotoprint(9, 37, "다시 입력해주세요.");
			Sleep(1000);
			gotoprint(9, 37, "                    ");
	}
}


void steal_func()
{
	int i;
	char str[200];
	gotoprint(2, 36, "삥뜯길 원하는 유저를 입력하세요");
	gotoprint(2, 37, "입력 : ");
	CursorView(1);

	while (1)
	{
		do{
			gotoprint(9, 37, "                                                                                                                          ");
			gotoxy(9, 37);
			gets_s(str, sizeof(str));
		} while (strcmp(str, "") == 0 || str[0] == ' ');
		CursorView(0);

		for (i = 0; i < maxplayers; i++)
		{
			if (pl[i].ID!=order && pl[i].stat != -1 && strcmp(pl[i].name, str) == 0)
			{
				if (pl[i].MONEY > STEAL_MONEY)
				{
					gotoxy(2, 38);
					setcolor(15, p_color[i]);
					printf("%s", pl[i].name);
					setcolor(0, 15);
					printf("님의 돈 ");
					setcolor(15, p_color[i]);
					printf("$%d", STEAL_MONEY);
					setcolor(0, 15);
					printf("를 삥뜯습니다");
					setcolor(0, 10);
					printf("$%d(현재돈)+$%d(삥뜯은돈)", pl[order].MONEY, STEAL_MONEY);
					setcolor(0, 15);

					pl[i].MONEY -= STEAL_MONEY;
					pl[order].MONEY += STEAL_MONEY;
					return;
				}
				else
				{
					gotoxy(2, 38);
					setcolor(15, p_color[i]);
					printf("%s", pl[i].name);
					setcolor(0, 15);
					printf("님은 거지라 삥뜯을 돈도 없습니다..");
					return;
				}
			}
		}
		gotoprint(9, 37, "다시 입력해주세요.");
		Sleep(1000);
		gotoprint(9, 37, "                     ");
	}

}

void domination()
{
	int i;
	char str[200];
	gotoprint(2, 36, "장악하길 원하는 과를 입력하세요");
	gotoprint(2, 37, "입력 : ");
	CursorView(1);

	while (1)
	{
		do{
			gotoprint(9, 37, "                                                                                                                          ");
			gotoxy(9, 37);
			gets_s(str, sizeof(str));
		} while (strcmp(str, "") == 0 || str[0] == ' ');
		CursorView(0);

		for (i = 0; i < boardNum; i++)
		{
			if (strcmp(building_Name[i], str) == 0)
			{
				if (bp[i].noslevel==0 && bp[i].base==0 && bp[i].order==-1)
				{
					gotoxy(2, 38);
					setcolor(15, 8);
					printf("%s", building_Name[i]);
					setcolor(0, 15);
					printf("건물의 주인은 ");
					setcolor(15, p_color[order]);
					printf("%s", pl[order].name);
					setcolor(0, 15);
					printf("님입니다");

					bp[i].order = pl[order].ID;
					bp[i].noslevel = 25;
					bp[i].price = building_Price[i];
					pl[order].Mybuilding++;

					Sleep(2000);
					draw_stat();

					if (pl[order].round>1)
						choice_dominate(pl[order].round, pl[order].mypos);
					return;
				}
			}
		}
		gotoprint(9, 37, "다시 입력해주세요.");
		Sleep(1000);
		gotoprint(9, 37, "                     ");
	}

}

void birth_day()
{
	int i;
	gotoxy(2, 36);
	printf("오늘은 구라긴 해도 ");
	setcolor(15, p_color[order]);
	printf("%s", pl[order].name);
	setcolor(0, 15);
	printf("님의 생일입니다");
	gotoxy(2, 37);
	printf("모든 플레이어들이 선물로 돈($%d)을 보내줍니다", BIRTH_MONEY);
	CursorView(1);


	for (i = 0; i < maxplayers; i++)
	{
		if (pl[i].stat != -1 && pl[i].ID!=order)
		{
			if (pl[i].MONEY > BIRTH_MONEY)
			{
				gotoxy(2, 38+i);
				setcolor(15, p_color[i]);
				printf("%s", pl[i].name);
				setcolor(0, 15);
				printf("님이 돈을 줍니다");
				setcolor(10, 15);
				printf("+$%d", BIRTH_MONEY);
				setcolor(0, 15);
				pl[i].MONEY -= BIRTH_MONEY;
				pl[order].MONEY += BIRTH_MONEY;
			}
			else
			{
				gotoxy(2, 38+i);
				setcolor(15, p_color[i]);
				printf("%s", pl[i].name);
				setcolor(0, 15);
				printf("님은 거지라 줄돈이 없습니다..");
			}
		}
	}
}

void additem()
{
	int ir;
	ir = rand() % 2;
	setcolor(0, 10);
	if (ir == 0)
	{
		gotoprint(2, 36, "MT회피권을 획득하였습니다");
		gotoprint(2, 37, "MT회피권으로 MT를 안갈 수 있습니다");
	}
	else if (ir == 1)
	{
		gotoprint(2, 36, "빽을 획득하였습니다");
		gotoprint(2, 37,"빽을 이용하면 상대 과를 공짜로 지나갈 수 있습니다");
	}
	setcolor(0, 15);
	pl[order].Item[ir]++;
	PlaySound(TEXT("getitem.wav"), NULL, SND_ASYNC);
}

void Event_System()
{
	int r; // 랜덤이벤트
	r = rand() % 8;

	//r = 2;
	switch (r)
	{
	case 0:
		setcolor(0, 14);
		gotoprint(2, 35, "소맥파티에 참여하였습니다");
		setcolor(0, 15);
		Sleep(1000);
		gotoprint(2, 36, "너무 마셔서 취하여 ");
		Sleep(1000);
		DrunkParty();
		break;
	case 1:
		setcolor(0, 14);
		gotoprint(2, 35, "돈먹고 돈먹는 도박!");
		setcolor(0, 15);
		gameble();
		break;
	case 2:
		setcolor(0, 14);
		gotoprint(2, 35, "일회용 버스카드를 주었습니다!");
		setcolor(0, 15);
		bus_card();
		break;
	case 4:
		setcolor(0, 14);
		gotoxy(2, 35);
		printf("패기로 원하는 유저의 돈을 삥뜯을 수 있습니다");
		setcolor(0, 15); printf(" ");
		setcolor(0, 14);
		printf("삥뜯는돈 : $%d", STEAL_MONEY);
		setcolor(0, 15);
		steal_func();
		break;
	case 3:
		if (pl[order].round > 1)
		{
			setcolor(0, 14);
			gotoprint(2, 35, "원하는 과를 군기잡아 과의 장악력을 올릴 수 있습니다.");
			setcolor(0, 15);
			md_func();
			break;
		}
	case 5:
		setcolor(0, 14);
		gotoprint(2, 35, "원하는 과를 장악할 수 있습니다!");
		setcolor(0, 15);
		domination();
		break;
	case 6:
		setcolor(0, 14);
		gotoprint(2, 35, "생일축제!");
		setcolor(0, 15);
		birth_day();
		break;
	default:
		setcolor(0, 14);
		gotoprint(2, 35, "아이템 획득가능!");
		setcolor(0, 15);

		additem();
		break;
	}
}

void bus_System()
{
	int i;
	int cham;
	char str[255];
				
	setcolor(0, 14);
	gotoprint(2, 35, "스쿨버스에 탑승하였습니다. 어디로 가시겠습니까?");
	setcolor(0, 15);
	gotoprint(2, 36, "갈 곳의 이름 입력 : ");
	while (1)
	{
		CursorView(1);
		do{
			gotoprint(24, 36, "                                                                                                          ");
			gotoxy(24, 36);
			gets_s(str, sizeof(str));
		} while (strcmp(str, "") == 0);
		CursorView(0);

		for (i = 0, cham = 0; i < boardNum; i++)
		{
			if (strcmp(str, building_Name[i]) == 0)
			{
				if (bp[i].order != -2)
					cham = 1;
				break;
			}
		}
		if (cham == 1)
		{
			Move_Pieces(i, 200);
			break;
		}
		else
		{
			gotoprint(24, 36, "다시 입력해주세요.");
			Sleep(1000);
			gotoprint(24, 36, "                    ");
		}
	}
	gotoprint(2, 35, "                                                                            ");
	gotoprint(2, 36, "                                                                            ");
}


void MT_System()
{
	int noi = 0;
	int select;
	char str[200];
	if (pl[order].Item[0] > 0)
	{
		gotoxy(2, 35);
		printf("MT회피권이 있습니다. 쓰시겠습니까?");
		setcolor(0, 14); printf("[1]"); setcolor(0, 15);  printf("예, ");
		setcolor(0, 14); printf("[2]"); setcolor(0, 15);  printf("아니오");

		gotoprint(2, 36, "입력 : ");
		while (1)
		{
			CursorView(1);
			do{
				gotoprint(8, 36, "                                                                                                                         ");
				gotoxy(8, 36);
				gets_s(str, sizeof(str));
			} while (strcmp(str, "") == 0);
			CursorView(0);

			select = atoi(str);

			switch (select)
			{
			case 1:
				gotoxy(2, 37);
				printf("MT회피권을 이용하여 MT를 안갑니다");
				pl[order].Item[0]--;
				return;
			case 2:
				noi = 1;
				break;
			default:
				gotoprint(8,36,"다시 입력해주세요");
				Sleep(1000);
				gotoprint(8, 36, "                       ");
			}
			if (noi == 1)
				break;
		}
		gotoprint(1, 35, "                                                                                                              ");
	}

	if (pl[order].MONEY > MT_PAY)
	{
		pl[order].stat = 1;
		pl[order].rest_turn = REST_NUM;
		pl[order].MONEY -= MT_PAY;
		gotoxy(2, 35);
		setcolor(15, 0);
		printf("MT비($%d)를 내고 MT에 갑니다 ", MT_PAY);
		printf("%d턴 동안 쉽니다", REST_NUM);
		setcolor(0, 15);
		Sleep(1000);
		draw_stat();
	}
	else
	{
		setcolor(15, 0);
		gotoxy(2, 35);
		printf("MT비($%d)를 낼 돈이 없습니다 ", MT_PAY);
		setcolor(0, 15);
		Sleep(1000);
		if (bankruptcy(MT_PAY) == YES)
		{
			if (victory() == YES)
				return;
		}
		else
		{
			pl[order].stat = 1;
			pl[order].rest_turn = REST_NUM;
			pl[order].MONEY -= MT_PAY;
			gotoxy(2, 35);
			setcolor(15, 0);
			printf("MT비($%d)를 내고 MT에 갑니다 ", MT_PAY);
			printf("%d턴 동안 쉽니다", REST_NUM);
			setcolor(0, 15);
			Sleep(1000);
			draw_stat();
		}
	}
}

