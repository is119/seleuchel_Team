/*
���Ӹ޴�ȭ�� ���� �Լ����
*/

#include "bluemarble.h"

void MainMenu()
{
	int Select;
	int num = 1;
	int truth = 1;
	int check = 0;
	//system("mode con: cols=30 lines=18");
	system("mode con: cols=30 lines=20");
	gotoprint(10, 9, "..Loading...");
	Sleep(1000);
	gotoprint(3, 10, "��");
	while (1)
	{
	
		gotoprint(5, 3, "��������������������");
		gotoprint(5, 4, "     ������ ����      ");
		gotoprint(5, 5, "��������������������");
		
		gotoprint(5, 9, "��������������������");
		gotoprint(5, 10, "��    ���ӽ���    ��");
		gotoprint(5, 11, "��������������������");

		gotoprint(5, 12, "��������������������");
		gotoprint(5, 13, "��    ���ӹ��    ��");
		gotoprint(5, 14, "��������������������");

		gotoprint(1, 16, "MOVE : ��� Click : Enter");

		if (GetKeyState(VK_RETURN) < 0)
			continue;

		Select = _getch();

		switch (Select)
		{
		case 80: // �Ʒ� 
			num = 2;
			gotoprint(3, 10, "  ");
			gotoprint(3, 13, "��");
			break;
		case 72: // ��
			num = 1;
			gotoprint(3, 13, "  ");
			gotoprint(3, 10, "��");
			break;
		case 13: // ���� 
			system("cls");
			PlaySound(TEXT("click.wav"), NULL, SND_ASYNC);
			if (num == 1)
			{
				truth = 0;
				Game_player();
				break;
			}
			else if (num == 2)
			{
				Game_Help();
			}
		}

		if (truth == 0)
			break;
	}
}

void Game_player()
{
	int Select;
	int num = 1;
	int y; // �ӽ�����
	int truth = 1;
	gotoprint(5, 3, "��������������������");
	gotoprint(5, 4, "     �ο��� ����    ");
	gotoprint(5, 5, "��������������������");


	gotoprint(5, 9, "��������������������");
	gotoprint(5, 10, "��    2���÷���   ��");
	gotoprint(5, 11, "��������������������");

	gotoprint(5, 12, "��������������������");
	gotoprint(5, 13, "��    3���÷���   ��");
	gotoprint(5, 14, "��������������������");

	gotoprint(5, 15, "��������������������");
	gotoprint(5, 16, "��    4���÷���   ��");
	gotoprint(5, 17, "��������������������");
	y = 10;
	gotoprint(3, y, "��");
	while (1)
	{
		if (GetKeyState(VK_RETURN)<0)
			continue;
		Select = _getch();
		switch (Select)
		{

		case 80: // �Ʒ�
			if (num<3)
			{
				num++;
				gotoprint(3, y, "  ");
				y += 3;
				gotoprint(3, y, "��");

			}
			break;
		case 72: // ��
			if (num>1)
			{
				num--;
				gotoprint(3, y, "  ");
				y -= 3;
				gotoprint(3, y, "��");

			}
			break;
		case 13: // ���� 
			PlaySound(TEXT("click.wav"), NULL, SND_ASYNC);
			if (num == 1)
				players = 2;
			else if (num == 2)
				players = 3;
			else
				players = 4;
			maxplayers = players;
			system("cls");
			Game_Mode();
			truth = 0;
			break;
		}
		if (truth == 0)
			break;
	}
}

void Game_Mode()
{
	int Select;
	int num = 1;
	int truth = 1;
	gotoprint(5, 3, "��������������������");
	gotoprint(5, 4, "    ���Ӹ�弳��    ");
	gotoprint(5, 5, "��������������������");


	gotoprint(5, 9, "��������������������");
	gotoprint(5, 10, "��    �⺻ ���   ��");
	gotoprint(5, 11, "��������������������");

	gotoprint(5, 12, "��������������������");
	gotoprint(5, 13, "��  �������ø��  ��");
	gotoprint(5, 14, "��������������������");

	gotoprint(3, 10, "��");
	while (1)
	{
		if (GetKeyState(VK_RETURN)<0)
			continue;
		Select = _getch();
		switch (Select)
		{

		case 80: // �Ʒ�
			num = 2;
			gotoprint(3, 10, "  ");
			gotoprint(3, 13, "��");
			break;
		case 72: // ��
			num = 1;
			gotoprint(3, 13, "  ");
			gotoprint(3, 10, "��");
			break;
		case 13: // ���� 
			PlaySound(TEXT("click.wav"), NULL, SND_ASYNC);
			if (num == 1)
				gamemode = 0;
			else if (num == 2)
				gamemode = 1;
			system("cls");
			Input_Name();
			system("cls");
			Draw_Board();
			truth = 0;
			break;
		}
		if (truth == 0)
			break;
	}
}

void Input_Name()
{
	int i, k;

	gotoprint(5, 3, "��������������������");
	gotoprint(5, 4, "    �����̸� �Է�    ");
	gotoprint(5, 5, "��������������������");

	
	while (1)
	{
		if (GetKeyState(VK_RETURN) < 0)
			continue;
		for (i = 0; i < players; i++)
		{
			gotoxy(3, 8);
			setcolor(15, p_color[i]);
			printf("�÷��̾�%d", i + 1);
			setcolor(0, 15);
			printf("�� �г��� �Է�");

			gotoprint(2, 9, "(�ѱ� 4��,���� 8�� �̳�");
			gotoprint(10, 10, "�پ��X      )");
			gotoprint(2, 11, "�Է� : ");
			CursorView(1);
			do{
				gotoxy(9, 11);
				gets(pl[i].name);
				gotoprint(2, 12, "                           ");
				gotoprint(2, 13, "                           ");
				gotoprint(2, 14, "                           ");
				gotoprint(2, 15, "                           ");
				gotoprint(2, 16, "                           ");
				gotoprint(2, 17, "                           ");
				gotoprint(2, 18, "                           ");
			} while (strcmp(pl[i].name, "") == 0 || pl[i].name[0] == ' ');
			CursorView(0);
			gotoprint(6, 11, "              ");
			pl[i].ID = i;
			for (k = strlen(pl[i].name); pl[i].name[k] != 0; k++)
				pl[i].name[k] = ' ';
			PlaySound(TEXT("click.wav"), NULL, SND_ASYNC);
		}
		break;
	}
	gotoprint(1, 7, "����������������������������");
	gotoprint(1, 8, "��                        ��");
	gotoprint(1, 9, "��!!�� ������ ���۵˴ϴ�!!��");
	gotoprint(1, 10, "��                        ��");
	gotoprint(1, 11, "����������������������������");
	Sleep(2000);
}

void Game_Help()
{
	int select;
	gotoprint(2, 1, "������ ���� ");
	gotoprint(7, 2, "���Ű��� ȯ���մϴ�.");
	gotoprint(2, 4, "[���� ���]");
	gotoprint(2, 5, "1.�ֻ����� ������");
	gotoprint(2, 6, "2.���� ���");
	gotoprint(2, 7, "3.���� �ٻ�ų�");
	gotoprint(9, 8, "ȥ�ڸ� ���´�");
	gotoprint(2, 9, "= �̱��");
	gotoprint(2, 10, "");
	gotoprint(5, 13, "��������������������");
	gotoprint(5, 14, "�� [Space]���ư��⦢");
	gotoprint(5, 15, "��������������������");

	while (1)
	{
		fflush(stdin);
		select = _getch();

		if (select == 32)
		{
			PlaySound(TEXT("click.wav"), NULL, SND_ASYNC);
			system("cls");
			gotoprint(3, 13, "��");
			break;
		}
	}
}