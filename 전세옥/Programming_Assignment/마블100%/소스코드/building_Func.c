/*
�����÷��� ���� �Լ����
*/

#include "bluemarble.h"

void Sell_building(int cost) // �� ��� ����ϱ� 
{
	int i, j;
	int select;
	int sell;
	int temp_arry[boardNum] = { 0, };
	char str[200];
	sell = pl[order].MONEY;

	

	gotoprint(1, 42, "�Է� : ");

	while (cost > sell)
	{
		gotoprint(1, 43, "                                                                                                              ");
		setcolor(0, 14);
		gotoxy(2, 36);
		printf("��� �ǹ��� �Ľðڽ��ϱ�? ($%-4d(���絷) - $%-4d(������) = $%-4d)", sell, cost, sell - cost);
		setcolor(0, 15);
		for (j = 0, i = 0; j < boardNum; j++)
		{

			if (bp[j].order == order && bp[j].base != 1)
			{
				if (i == 0)
					gotoxy(1, 37);
				else if (i == 4)
					gotoxy(1, 38);
				else if (i == 8)
					gotoxy(1, 39);
				else if (i == 12)
					gotoxy(1, 40);
				else if (i == 16)
					gotoxy(1, 41);
				setcolor(0, 14);
				printf("[%2d]", i+1);
				setcolor(0, 15);
				printf("%-16s $%-5d", building_Name[j], bp[j].price);
				temp_arry[i++] = j;
			}

		}

		CursorView(1);
		do{
			gotoprint(9, 42, "                                                                                                                          ");
			gotoxy(9, 42);
			gets(str);
		} while (strcmp(str, "") == 0 || str[0] == ' ');
		CursorView(0);
		select = atoi(str);

		if (select > 0 && select < i+1)
		{
			sell += bp[temp_arry[select-1]].price;
			bp[temp_arry[select - 1]].noslevel = 0;
			bp[temp_arry[select - 1]].order = -1;
			pl[order].Mybuilding--;
			bp[temp_arry[select - 1]].price = building_Price[temp_arry[select - 1]];
			draw_stat();
			gotoxy(28, 36);
			printf("                    ");
			gotoxy(2, 36);

			gotoxy(1, 43);
			setcolor(0, 10);
			printf("%s��(��) �Ⱦҽ��ϴ� ( $%d(���絷) - $%d(������) = $%d )", building_Name[temp_arry[select - 1]], sell, cost, sell - cost);

			setcolor(0, 14);
			gotoxy(2, 36);
			printf("��� �ǹ��� �Ľðڽ��ϱ�? ($%-4d(���絷) - $%-4d(������) = $%-4d)", sell, cost, sell - cost);
			setcolor(0, 15);

			Sleep(1200);
			setcolor(0, 15);
		}
		else
		{
			gotoprint(9, 42, "���� ���� ������ �Է��Ͻñ� �ٶ��ϴ�                                                                                     ");
			Sleep(1000);
			gotoprint(9, 42, "                                     ");
		}

		gotoprint(1, 37, "                                                                                                              ");
		gotoprint(1, 38, "                                                                                                              ");
		gotoprint(1, 39, "                                                                                                              ");
		gotoprint(1, 40, "                                                                                                              ");
		gotoprint(1, 41, "                                                                                                              ");
	}
	pl[order].MONEY = sell - cost;
	pl[bp[pl[order].mypos].order].MONEY += cost;
	setcolor(15, 0);
	gotoprint(1, 44, "������ �Ⱦ� �Ļ��� �������κ��� ������ϴ�.");
	setcolor(0, 15);
	Sleep(2000);
}

int bankruptcy(int cost)
{
	int i, j;
	int select;
	int money;
	char str[200];

	money = pl[order].MONEY;
	for (i = 0; i < boardNum; i++)
		if (bp[i].order == order && bp[i].base != 1)
			money += bp[i].price;
	addmoney = money;

	
	gotoxy(2, 36);
	printf("�Ļ� �Ͻðڽ��ϱ�?");
	setcolor(0, 14); printf("[1]"); setcolor(0, 15); printf("��, ");
	setcolor(0, 14); printf("[2]"); setcolor(0, 15); printf("�� �ǹ��ȱ�");
//	setcolor(0, 10); printf(" : %d", addmoney);
	setcolor(0, 15);

	gotoprint(2, 37, "�Է� : ");

	while (1)
	{
		CursorView(1);
		do{
			gotoprint(9, 37, "                                                                                                                          ");
			gotoxy(9, 37);
			gets(str);
		} while (strcmp(str, "") == 0 || str[0] == ' ');
		CursorView(0);
		select = atoi(str);
		switch (select)
		{
		case 1:
			gotoxy(2, 38);
			setcolor(15, 0);
			printf("%s���� �Ļ��Ͽ����ϴ� �̤�", pl[order].name);
			setcolor(0, 15);
			Sleep(2000);
			players--;
			pl[order].stat = -1;
			for (j = 0; j < boardNum; j++)
			{
				if (bp[j].order == order)
				{
					bp[j].order = -1;
					bp[j].price = building_Price[j];
					bp[j].noslevel = 0;
					pl[order].Mybuilding -= 1;
				}
			}
			setcolor(0, 15);
			gotoprint(pl[order].x, pl[order].y, "  ");
			return YES;
		case 2:
			if (pl[order].Mybuilding > 0)
			{
				if (money > cost)
				{

					gotoprint(2, 36, "                                              ");
					gotoprint(2, 37, "          ");
					// �ǹ� �Ǹ��Լ� ���
					Sell_building(cost);
					return NO;
				}
				else
				{
					gotoxy(2, 38);
					setcolor(15, 0);
					printf("�ǹ��� ��� �Ǵ��ص� ������ ���������� %s���� �Ļ��Ͽ����ϴ� �̤�", pl[order].name);
					setcolor(0, 15);
					Sleep(2000);
					players--;
					pl[order].stat = -1;
					for (j = 0; j < boardNum; j++)
					{
						if (bp[j].order == order)
						{
							bp[j].order = -1;
							bp[j].price = building_Price[j];
							bp[j].noslevel = 0;
							pl[order].Mybuilding -= 1;
						}
					}
					setcolor(0, 15);
					gotoprint(pl[order].x, pl[order].y, "  ");
				}
			}
			else
			{
				gotoxy(2, 39);
				setcolor(15, 0);
				printf("%s���� �ǹ������� ��� �Ļ���Ͽ����ϴ� �̤�", pl[order].name);
				setcolor(0, 15);
				Sleep(2000);
				players--;
				pl[order].stat = -1;
				for (j = 0; j < boardNum; j++)
				{
					if (bp[j].order == order)
					{
						bp[j].order = -1;
						bp[j].price = building_Price[j];
						bp[j].noslevel = 0;
						pl[order].Mybuilding -= 1;
					}
				}
				setcolor(0, 15);
				gotoprint(pl[order].x, pl[order].y, "  ");
			}
			return YES;
		default:

			gotoprint(8, 37, "�ٽ� �Է����ּ���.                                                                                                    ");
			Sleep(1000);
			gotoprint(8, 37, "                   ");
			break;
		}
	}
	return NO;
}

void choice_base()
{
	int cham;
	int i, j;
	char str[255];

	for (j = 0; j < maxplayers; j++)
	{
		gotoxy(0, 0);
		gotoxy(2, 32);
		setcolor(15, p_color[j]);
		printf("%8s", pl[j].name);
		setcolor(0, 15);
		printf("���� ���ϴ� ");
		setcolor(15,0);
		printf("���� �̸��� �Է�");
		setcolor(0, 15);
		printf("�ϼ���");
		
		gotoprint(2, 33, "�Է� : ");
		while (1)
		{
			CursorView(1);
			do{
				gotoprint(9, 33, "                                      ");
				gotoxy(9, 33);
				gets_s(str, sizeof(str));
			} while (strcmp(str, "") == 0 || str[0] == ' ');
			CursorView(0);

			for (i = 0, cham = 0; i<boardNum; i++)
			{
				if (strcmp(str, building_Name[i]) == 0)
				{
					if (bp[i].base == 0 && bp[i].order == -1)
						cham = 1;
					break;
				}
			}
			if (cham == 1)
			{
				bp[i].order = j;
				bp[i].noslevel = 25;
				bp[i].price = building_Price[i] * 2;
				bp[i].base = 1;
				pl[j].x = mal_postion[i][0] + (j * 2);
				pl[j].y = mal_postion[i][1];
				pl[j].mypos = i;
				pl[j].Mybuilding = 1;

				setcolor(p_color[j], 0);
				gotoprint(pl[j].x, pl[j].y, player_img);
				setcolor(0, 15);

				gotoxy(2, 34);
				setcolor(15, 8);
				printf("%s", building_Name[i]);
				setcolor(0, 15);
				printf("�ǹ��� ");
				setcolor(15, p_color[j]);
				printf("%s���� ����", pl[j].name);
				setcolor(0, 15);
				printf("�� �Ǿ����ϴ�");
				

				draw_stat();

				Sleep(2000);
				deleteprint();
				break;
			}
			else
			{
				gotoprint(9, 33, "�ٽ� �Է����ּ���.                     ");
				Sleep(1000);
				gotoprint(9, 33, "                                      ");
			}
		}
	}
}

void choice_dominate(int r, int pos) // ������������ �����
{
	int select;
	char str[200];

	gotoprint(2, 39, "�󸶸�ŭ ����Ͻǰ̴ϱ�? ");
	
	gotoxy(26, 39);
	setcolor(0, 14); printf("[2]"); setcolor(0, 15); printf("50%%($%d), ", building_Price[pos] * 2);
	setcolor(0, 14); printf("[3]"); setcolor(0, 15); printf("75%%($%d), ", building_Price[pos] * 3);
	setcolor(0, 14); printf("[4]"); setcolor(0, 15); printf("100%%($%d), ", building_Price[pos] * 4);
	setcolor(0, 14); printf("[5]"); setcolor(0, 15); printf("���");

	gotoprint(2, 40, "�Է� : ");

	while (1)
	{
		CursorView(1);
		do{
			gotoprint(9, 40, "                                                                                                                          ");
			gotoxy(9, 40);
			gets(str);
		} while (strcmp(str, "") == 0 || str[0] == ' ');
		CursorView(0);
		select = atoi(str);

		switch (select)
		{
		case 2:
			if (bp[pos].noslevel == 25)
			{
				if (pl[order].MONEY >= building_Price[pos] * 2)
				{
					gotoxy(2, 41);
					setcolor(15, p_color[order]);
					printf("%s", building_Name[pos]);
					setcolor(0, 15);
					printf("�ǹ��� ");
					setcolor(0, 10);
					printf("50%% ���");
					setcolor(0, 15);
					printf("�Ǿ����ϴ�.");
					setcolor(12, 15);
					printf("$%d(���絷)-$%d(��������)", pl[order].MONEY, building_Price[pos] * 2);
					setcolor(0, 15);

					pl[order].MONEY -= building_Price[pos] * 2;
					bp[pos].noslevel = 50;
					bp[pos].price = building_Price[pos] * 3;


					Sleep(2000);
				}
				else
				{
					gotoxy(2, 41);
					printf("���� ��� ���׷��̵带 �� �� �����ϴ� [$%d(���絷)/$%d(����)]", pl[order].MONEY, building_Price[pos] * 2);
					Sleep(2000);
				}
				return;
			}
			else
			{
				gotoprint(9, 40, "25% ���¿����� �����մϴ�.                                                                                                ");
				Sleep(2000);
				gotoprint(9, 40, "                                 ");
				continue;
			}
			break;
		case 3:
			if (bp[pos].noslevel == 50)
			{
				if (pl[order].MONEY >= building_Price[pos] * 3)
				{
					gotoxy(2, 41);
					setcolor(15, p_color[order]);
					printf("%s", building_Name[pos]);
					setcolor(0, 15);
					printf("�ǹ��� ");
					setcolor(0, 10);
					printf("75%% ���");
					setcolor(0, 15);
					printf("�Ǿ����ϴ�.");
					setcolor(12, 15);
					printf("$%d(���絷)-$%d(��������)", pl[order].MONEY, building_Price[pos] * 3);
					setcolor(0, 15);

					pl[order].MONEY -= building_Price[pos] * 3;
					bp[pos].noslevel = 75;
					bp[pos].price = building_Price[pos] * 4;


					Sleep(2000);
				}
				else
				{
					gotoxy(2, 41);
					printf("���� ��� ���׷��̵带 �� �� �����ϴ� [$%d(���絷)/$%d(����)]", pl[order].MONEY, building_Price[pos] * 3);
					Sleep(2000);
				}
				return;
			}
			else
			{
				gotoprint(9, 40, "50% ���¿����� �����մϴ�.                                                                                                ");
				Sleep(2000);
				gotoprint(9, 40, "                                   ");
				continue;
			}
			break;
		case 4:
			if (bp[pos].noslevel == 75)
			{
				if (pl[order].MONEY > building_Price[pos] * 4)
				{
					gotoxy(2, 41);
					setcolor(15, p_color[order]);
					printf("%s");
					setcolor(0, 15);
					printf("�ǹ��� ");
					setcolor(0, 10);
					printf("100%% ����");
					setcolor(0, 15);
					printf("�Ǿ����ϴ�");
					setcolor(12, 15);
					printf("$%d(���絷)-$%d(��������)", pl[order].MONEY, building_Price[pos] * 4);
					setcolor(0, 15);

					pl[order].MONEY -= building_Price[pos] * 4;
					bp[pos].noslevel = 100;
					bp[pos].price = building_Price[pos] * 4;

					Sleep(2000);
				}
				else
				{
					gotoxy(2, 41);
					printf("���� ��� ���� ���׷��̵带 �� �� �����ϴ� [$%d(���絷)/$%d(����)]", pl[order].MONEY, building_Price[pos] * 4);
					Sleep(2000);
				}
				return;
			}
			else
			{
				gotoprint(9, 40, "75% ���¿����� �����մϴ�.                                                                                                ");
				Sleep(2000);
				gotoprint(9, 40, "                                        ");
				continue;
			}
			break;
		case 5:
			return;
		}

		gotoprint(9, 40, "�ٽ� �Է����ּ���.                                                                                                        ");
		Sleep(1000);
		gotoprint(9, 40, "                     ");

	}

}


void building_system()
{
	int noi = 0;
	int select;
	int minuscost;  // �ҹ�ħ������ ���� ��
	char str[200];
	if (bp[pl[order].mypos].order == -1)
	{
		
		setcolor(15, 0);
		gotoxy(2, 35);
		printf("�� �ǹ��� ������ �����ϴ�. $%d", building_Price[pl[order].mypos]);
		setcolor(0, 14); printf("[1]"); setcolor(0, 15); printf("���, ");
		setcolor(0, 14); printf("[2]"); setcolor(0, 15); printf("�Ȼ��");
		setcolor(0, 15);

		gotoprint(2, 36, "�Է� : ");


		while (1)
		{
			CursorView(1);
			do{
				gotoprint(9, 36, "                                                                                                                          ");
				gotoxy(9, 36);
				gets(str);
			} while (strcmp(str, "") == 0 || str[0] == ' ');
			CursorView(0);
			select = atoi(str);
			switch (select)
			{
			case 1:
				if (pl[order].MONEY>building_Price[pl[order].mypos])
				{
					gotoxy(2, 37);
					setcolor(15, 8);
					printf("%s", building_Name[pl[order].mypos]);
					setcolor(0, 15);
					printf("�ǹ��� ������ ");
					setcolor(15, p_color[order]);
					printf("%s", pl[order].name);
					setcolor(0, 15);
					printf("���Դϴ�");

					setcolor(0, 10);
					printf("$%d(���絷)-$%d(��������)", pl[order].MONEY, building_Price[pl[order].mypos]);
					setcolor(0, 15);
					pl[order].MONEY -= building_Price[pl[order].mypos];
					bp[pl[order].mypos].order = pl[order].ID;
					bp[pl[order].mypos].noslevel = 25;
					bp[pl[order].mypos].price = building_Price[pl[order].mypos];
					pl[order].Mybuilding++;

					Sleep(2000);
					draw_stat();

					if (pl[order].round>1)
						choice_dominate(pl[order].round, pl[order].mypos);
				}
				else
				{
					gotoprint(2, 37, "���� ��� �� �� �����ϴ�                                                           ");
					Sleep(2000);

				}
				return;
			case 2:
				return;
			default:
				gotoprint(8, 36, "�ٽ� �Է����ּ���.                                                                                                    ");
				Sleep(1000);
				gotoprint(8, 36, "                   ");
				break;
			}
		}
	}
	else if (bp[pl[order].mypos].order == order)
	{
		gotoxy(2, 35);

		printf("�ǹ��� ������ �Ͻðڽ��ϱ�? ");

		setcolor(0, 14); printf("[1]"); setcolor(0, 15); printf("����, ");
		setcolor(0, 14); printf("[2]"); setcolor(0, 15); printf("�ȱ�, ");
		setcolor(0, 14); printf("[3]"); setcolor(0, 15); printf("�ƹ��͵� ����");

		gotoprint(2, 36, "�Է� : ");

		while (1)
		{
			CursorView(1);
			do{
				gotoprint(9, 36, "                                                                                                                          ");
				gotoxy(9, 36);
				gets(str);
			} while (strcmp(str, "") == 0 || str[0] == ' ');
			CursorView(0);
			select = atoi(str);

			switch (select)
			{
			case 3:
				return;
			case 1:
				choice_dominate(pl[order].round, pl[order].mypos);
				draw_stat();
				return;
			case 2:
				if (bp[pl[order].mypos].base != 1)
				{
					pl[order].MONEY += bp[pl[order].mypos].price;
					bp[pl[order].mypos].noslevel = 0;
					bp[pl[order].mypos].order = -1;
					pl[order].Mybuilding--;
					gotoxy(2, 37);
					setcolor(15, 8);
					printf("%s", building_Name[pl[order].mypos]);
					setcolor(0, 15);
					printf("�ǹ��� �Ⱦҽ��ϴ�");
					setcolor(10, 15);
					printf("$%d(���絷)+$%d(��������)", pl[order].MONEY,bp[pl[order].mypos].price);
					setcolor(0, 15);
					bp[pl[order].mypos].price = building_Price[pl[order].mypos];
					Sleep(2000);
				}
				else
				{
					gotoprint(2, 37, "������ �� �� �����ϴ�.");
					Sleep(2000);
				}
				return;
			default:
				gotoprint(8, 36, "�ٽ� �Է����ּ���.                                                                                                    ");
				Sleep(1000);
				gotoprint(8, 36, "                   ");
				break;
			}
		}
	}
	else if (bp[pl[order].mypos].order != order)
	{
		if (bp[pl[order].mypos].order == -2) // ���� 
		{
			bus_System();
			building_system();
			return;
		}
		else if (bp[pl[order].mypos].order == -5) // MT
		{
			MT_System();
			return;
		}
		else if (bp[pl[order].mypos].order == -4) // �̺�Ʈ (�̰���)
		{
			Event_System();
			return;
		}

		if (pl[order].Item[1] > 0)
		{
			gotoxy(2, 35);
			printf("���� �ֽ��ϴ�. ���ðڽ��ϱ�?");
			setcolor(0, 14); printf("[1]"); setcolor(0, 15);  printf("��, ");
			setcolor(0, 14); printf("[2]"); setcolor(0, 15);  printf("�ƴϿ�");

			gotoprint(2, 36, "�Է� : ");
			while (1)
			{
				CursorView(1);
				do{
					gotoprint(8, 36, "                                                                                                                          ");
					gotoxy(8, 36);
					gets_s(str, sizeof(str));
				} while (strcmp(str, "") == 0 || str[0]==' ');
				CursorView(0);

				select = atoi(str);

				switch (select)
				{
				case 1:
					gotoxy(2, 37);
					printf("���� �̿��Ͽ� ����Ḧ �ȳ��ϴ�");
					pl[order].Item[1]--;
					return;
				case 2:
					noi = 1;
					break;
				default:
					gotoprint(8, 36, "�ٽ� �Է����ּ���                                                                                                    ");
					Sleep(1000);
					gotoprint(8, 36, "                       ");
				}
				if (noi == 1)
					break;
			}

			gotoprint(1, 35, "                                                                                                              ");
		}
		minuscost = bp[pl[order].mypos].price / 2; //����

		if (pl[order].MONEY>minuscost)
		{
			gotoxy(2, 35);
			setcolor(15, p_color[bp[pl[order].mypos].order]);
			printf("%s", pl[bp[pl[order].mypos].order].name);
			setcolor(0, 15);
			printf("���� �ǹ��� ");
			setcolor(15, 0);
			printf("�ҹ�ħ��");
			setcolor(0, 15);
			printf("�Ͽ����ϴ� ");
			setcolor(12, 15);
			printf("$%d(���絷)-$%d(����)",pl[order].MONEY, minuscost);
			setcolor(0, 15);
			pl[order].MONEY -= minuscost;
			pl[bp[pl[order].mypos].order].MONEY += minuscost;
		}
		else
		{
			gotoxy(2, 35);
			setcolor(15, p_color[bp[pl[order].mypos].order]);
			printf("%s", pl[bp[pl[order].mypos].order].name);
			setcolor(0, 15);
			printf("���� �ǹ��� ");
			setcolor(15, 0);
			printf("�ҹ�ħ��");
			setcolor(0, 15);
			printf("���� ");
			setcolor(12, 15);
			printf("$%d(����)�� �� ���� �����ϴ�.", minuscost);
			setcolor(0, 15);
			Sleep(1000);
			if (bankruptcy(minuscost) == YES)
			{
				//gotoxy(0, 0);
				//printf("�Ӵ� : %d", addmoney);
				pl[bp[pl[order].mypos].order].MONEY += addmoney;
				//drawstat();
				if (victory() == 1)
					return;
			}
			return;
		}
		Sleep(2000);
		draw_stat();

		if (bp[pl[order].mypos].noslevel != 100 && bp[pl[order].mypos].base != 1)
		{
			gotoxy(2, 36);
			setcolor(0, 10);
			printf("�� �ǹ��� ��ðڽ��ϱ�? $%d", bp[pl[order].mypos].price);
			setcolor(0, 15); printf(" ");
			setcolor(0, 14); printf("[1]"); setcolor(0, 15); printf("��, ");
			setcolor(0, 14); printf("[2]"); setcolor(0, 15); printf("�ƴϿ�");
			
			gotoprint(2, 37, "�Է� : ");

			while (1)
			{
				CursorView(1);
				do{
					gotoprint(9, 37, "                                                                                                                          ");
					gotoxy(9, 37);
					gets(str);
				} while (strcmp(str, "") == 0 || str[0] == ' ');
				CursorView(0);
				select = atoi(str);

				switch (select)
				{
				case 1:
					if (pl[order].MONEY>bp[pl[order].mypos].price)
					{
						gotoxy(2, 38);

						setcolor(15, p_color[bp[pl[order].mypos].order]);
						printf("%s", building_Name[pl[order].mypos]);
						setcolor(0, 15);
						printf("�ǹ��� ������ ");

						setcolor(15, p_color[bp[pl[order].mypos].order]);
						printf("%s", pl[bp[pl[order].mypos].order].name);
						setcolor(0, 15);
						printf("�Կ��� ");
						setcolor(15, p_color[order]);
						printf("%s", pl[order].name);
						setcolor(0, 15);
						printf("������ �ٲ�����ϴ�.");

						setcolor(0, 10);
						printf("$%d(���絷)-$%d(��������)", pl[order].MONEY, bp[pl[order].mypos].price);
						setcolor(0, 15);

						pl[order].MONEY -= bp[pl[order].mypos].price; // �������� ��� �� ����
						pl[bp[pl[order].mypos].order].MONEY += bp[pl[order].mypos].price; // ��뵷���� �����ε� �߰�

						pl[order].Mybuilding++; // ���ǹ��� �ø� 
						pl[bp[pl[order].mypos].order].Mybuilding--;  // ���ǹ��� �پ����  



						bp[pl[order].mypos].order = pl[order].ID; // �ǹ�ĭ�� �����̵� ������� 
						Sleep(2000);

						if (pl[order].round>1)
							choice_dominate(pl[order].round, pl[order].mypos);

						draw_stat();
						/*
						if (bp[pl[order].mypos].noslevel<75)
						{
						if (pl[order].round >= 3)
						{
						choice_dominate(3, pl[order].mypos);
						}
						else if (pl[order].round == 2)
						{
						choice_dominate(2, pl[order].mypos);
						}
						}*/
					}
					else
					{
						gotoprint(2, 38, "���� �����ϴ�                                                                                                    ");
						Sleep(2000);
					}
					return;
				case 2:
					return;
				default:
					gotoprint(8, 37, "�ٽ� �Է����ּ���.                                                                                                    ");
					Sleep(1000);
					gotoprint(8, 37, "                   ");
					break;
				}
			}
		}
	}
}