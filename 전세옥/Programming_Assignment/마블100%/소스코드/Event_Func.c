/*
�ʼ� �Լ� ���
*/

#include "bluemarble.h"

void DrunkParty()
{
	int rn, rn2;
	rn = rand() % 3;

	if (rn == 0) //����
	{
		rn2 = (rand() % 5) + 1;
		gotoxy(2, 37);
		setcolor(0, 12);
		printf("�ڷ� %dĭ ���ϴ�.", rn2);
		setcolor(0, 15);
		Move_Pieces(-rn2, 200);
	}
	else if (rn == 1) //����
	{
		rn2 = (rand() % 5) + 1;

		gotoxy(2, 37);
		setcolor(0, 10);
		printf("������ %dĭ ���ϴ�.", rn2);
		setcolor(0, 15);
		Move_Pieces(rn2, 200);
	}
	else
	{
		setcolor(15, 0);
		gotoprint(2, 37, "�ҿ��� ������ ������  �ƹ� �� �� �������ϴ� ��");
		setcolor(0, 15);
	}
}

void gameble()
{
	int money;
	int rn;
	char str[200];
	gotoxy(2, 36);
	printf("�󸶸� �Žðڽ��ϱ�? ");
	setcolor(0, 14);
	printf("���� ���� �ι�");
	setcolor(0, 15);
	printf("�� ���� �� �ֽ��ϴ�.");
	gotoprint(2, 37, "�Է�(0�̻�) : ");
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
			gotoprint(16, 37, "�ٽ� �Է����ּ���");
			Sleep(1000);
			gotoprint(16, 37, "                                                                                                      ");
		}
	}
	PlaySound(TEXT("coinflip.wav"), NULL, SND_ASYNC);
	gotoprint(2, 38, "����");
	Sleep(300);
	gotoprint(8, 38, "����");
	Sleep(300);
	gotoprint(14, 38, "����");
	Sleep(300);
	rn = rand() % 2;

	if (rn == 0)
	{
		gotoxy(2, 39);
		setcolor(0, 10);
		printf("����! $%d���� �������� ������ϴ�!", money * 2);
		setcolor(0, 15);
		pl[order].MONEY += money * 2;
		PlaySound(TEXT("win1.wav"), NULL, SND_ASYNC);
	}
	else
	{
		gotoxy(2, 39);
		setcolor(0, 12);
		printf("����.. $%d���� �������� �Ҿ����ϴ�..", money);
		setcolor(0, 15);
		pl[order].MONEY -= money;
		PlaySound(TEXT("lose1.wav"), NULL, SND_ASYNC);
	}
}

void bus_card()
{
	gotoprint(2, 36, "���� �ٷ� �������������� ���ϴ�.");
	gotoprint(2, 37, "���� �Ͽ� ������ �̿��� �� �ֽ��ϴ�.");
	while (pl[order].mypos != 0)
		Move_Pieces(1, 200);
	pl[order].stat = 2;
}


void md_func()
{
	int i;

	char str[100];
	gotoxy(2, 36);
	printf("��Ƿ��� �ø� ���� �Է��ϼ��� ������ ");
	setcolor(15, 0);
	printf("'����'");
	setcolor(0, 15);
	printf("�� �Է����ּ���");
	gotoprint(2, 37, "�Է� : ");
	while (1)
	{
		CursorView(1);
		do{
			gotoprint(9, 37, "                                                                                                                          ");
			gotoxy(9, 37);
			gets_s(str, sizeof(str));
		} while (strcmp(str, "") == 0);
		CursorView(0);
		

		if (strcmp(str, "����") == 0)
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

			gotoprint(9, 37, "�ٽ� �Է����ּ���.");
			Sleep(1000);
			gotoprint(9, 37, "                    ");
	}
}


void steal_func()
{
	int i;
	char str[200];
	gotoprint(2, 36, "���� ���ϴ� ������ �Է��ϼ���");
	gotoprint(2, 37, "�Է� : ");
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
					printf("���� �� ");
					setcolor(15, p_color[i]);
					printf("$%d", STEAL_MONEY);
					setcolor(0, 15);
					printf("�� �����ϴ�");
					setcolor(0, 10);
					printf("$%d(���絷)+$%d(�������)", pl[order].MONEY, STEAL_MONEY);
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
					printf("���� ������ ����� ���� �����ϴ�..");
					return;
				}
			}
		}
		gotoprint(9, 37, "�ٽ� �Է����ּ���.");
		Sleep(1000);
		gotoprint(9, 37, "                     ");
	}

}

void domination()
{
	int i;
	char str[200];
	gotoprint(2, 36, "����ϱ� ���ϴ� ���� �Է��ϼ���");
	gotoprint(2, 37, "�Է� : ");
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
					printf("�ǹ��� ������ ");
					setcolor(15, p_color[order]);
					printf("%s", pl[order].name);
					setcolor(0, 15);
					printf("���Դϴ�");

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
		gotoprint(9, 37, "�ٽ� �Է����ּ���.");
		Sleep(1000);
		gotoprint(9, 37, "                     ");
	}

}

void birth_day()
{
	int i;
	gotoxy(2, 36);
	printf("������ ����� �ص� ");
	setcolor(15, p_color[order]);
	printf("%s", pl[order].name);
	setcolor(0, 15);
	printf("���� �����Դϴ�");
	gotoxy(2, 37);
	printf("��� �÷��̾���� ������ ��($%d)�� �����ݴϴ�", BIRTH_MONEY);
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
				printf("���� ���� �ݴϴ�");
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
				printf("���� ������ �ٵ��� �����ϴ�..");
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
		gotoprint(2, 36, "MTȸ�Ǳ��� ȹ���Ͽ����ϴ�");
		gotoprint(2, 37, "MTȸ�Ǳ����� MT�� �Ȱ� �� �ֽ��ϴ�");
	}
	else if (ir == 1)
	{
		gotoprint(2, 36, "���� ȹ���Ͽ����ϴ�");
		gotoprint(2, 37,"���� �̿��ϸ� ��� ���� ��¥�� ������ �� �ֽ��ϴ�");
	}
	setcolor(0, 15);
	pl[order].Item[ir]++;
	PlaySound(TEXT("getitem.wav"), NULL, SND_ASYNC);
}

void Event_System()
{
	int r; // �����̺�Ʈ
	r = rand() % 8;

	//r = 2;
	switch (r)
	{
	case 0:
		setcolor(0, 14);
		gotoprint(2, 35, "�Ҹ���Ƽ�� �����Ͽ����ϴ�");
		setcolor(0, 15);
		Sleep(1000);
		gotoprint(2, 36, "�ʹ� ���ż� ���Ͽ� ");
		Sleep(1000);
		DrunkParty();
		break;
	case 1:
		setcolor(0, 14);
		gotoprint(2, 35, "���԰� ���Դ� ����!");
		setcolor(0, 15);
		gameble();
		break;
	case 2:
		setcolor(0, 14);
		gotoprint(2, 35, "��ȸ�� ����ī�带 �־����ϴ�!");
		setcolor(0, 15);
		bus_card();
		break;
	case 4:
		setcolor(0, 14);
		gotoxy(2, 35);
		printf("�б�� ���ϴ� ������ ���� ����� �� �ֽ��ϴ�");
		setcolor(0, 15); printf(" ");
		setcolor(0, 14);
		printf("���µ� : $%d", STEAL_MONEY);
		setcolor(0, 15);
		steal_func();
		break;
	case 3:
		if (pl[order].round > 1)
		{
			setcolor(0, 14);
			gotoprint(2, 35, "���ϴ� ���� ������� ���� ��Ƿ��� �ø� �� �ֽ��ϴ�.");
			setcolor(0, 15);
			md_func();
			break;
		}
	case 5:
		setcolor(0, 14);
		gotoprint(2, 35, "���ϴ� ���� ����� �� �ֽ��ϴ�!");
		setcolor(0, 15);
		domination();
		break;
	case 6:
		setcolor(0, 14);
		gotoprint(2, 35, "��������!");
		setcolor(0, 15);
		birth_day();
		break;
	default:
		setcolor(0, 14);
		gotoprint(2, 35, "������ ȹ�氡��!");
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
	gotoprint(2, 35, "��������� ž���Ͽ����ϴ�. ���� ���ðڽ��ϱ�?");
	setcolor(0, 15);
	gotoprint(2, 36, "�� ���� �̸� �Է� : ");
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
			gotoprint(24, 36, "�ٽ� �Է����ּ���.");
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
		printf("MTȸ�Ǳ��� �ֽ��ϴ�. ���ðڽ��ϱ�?");
		setcolor(0, 14); printf("[1]"); setcolor(0, 15);  printf("��, ");
		setcolor(0, 14); printf("[2]"); setcolor(0, 15);  printf("�ƴϿ�");

		gotoprint(2, 36, "�Է� : ");
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
				printf("MTȸ�Ǳ��� �̿��Ͽ� MT�� �Ȱ��ϴ�");
				pl[order].Item[0]--;
				return;
			case 2:
				noi = 1;
				break;
			default:
				gotoprint(8,36,"�ٽ� �Է����ּ���");
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
		printf("MT��($%d)�� ���� MT�� ���ϴ� ", MT_PAY);
		printf("%d�� ���� ���ϴ�", REST_NUM);
		setcolor(0, 15);
		Sleep(1000);
		draw_stat();
	}
	else
	{
		setcolor(15, 0);
		gotoxy(2, 35);
		printf("MT��($%d)�� �� ���� �����ϴ� ", MT_PAY);
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
			printf("MT��($%d)�� ���� MT�� ���ϴ� ", MT_PAY);
			printf("%d�� ���� ���ϴ�", REST_NUM);
			setcolor(0, 15);
			Sleep(1000);
			draw_stat();
		}
	}
}

