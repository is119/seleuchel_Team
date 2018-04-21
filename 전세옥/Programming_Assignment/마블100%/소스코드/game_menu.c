/*
게임메뉴화면 관련 함수목록
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
	gotoprint(3, 10, "☞");
	while (1)
	{
	
		gotoprint(5, 3, "──────────");
		gotoprint(5, 4, "     공과대 마블      ");
		gotoprint(5, 5, "──────────");
		
		gotoprint(5, 9, "┌────────┐");
		gotoprint(5, 10, "│    게임시작    │");
		gotoprint(5, 11, "└────────┘");

		gotoprint(5, 12, "┌────────┐");
		gotoprint(5, 13, "│    게임방법    │");
		gotoprint(5, 14, "└────────┘");

		gotoprint(1, 16, "MOVE : ↑↓ Click : Enter");

		if (GetKeyState(VK_RETURN) < 0)
			continue;

		Select = _getch();

		switch (Select)
		{
		case 80: // 아래 
			num = 2;
			gotoprint(3, 10, "  ");
			gotoprint(3, 13, "☞");
			break;
		case 72: // 위
			num = 1;
			gotoprint(3, 13, "  ");
			gotoprint(3, 10, "☞");
			break;
		case 13: // 엔터 
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
	int y; // 임시저장
	int truth = 1;
	gotoprint(5, 3, "──────────");
	gotoprint(5, 4, "     인원수 설정    ");
	gotoprint(5, 5, "──────────");


	gotoprint(5, 9, "┌────────┐");
	gotoprint(5, 10, "│    2인플레이   │");
	gotoprint(5, 11, "└────────┘");

	gotoprint(5, 12, "┌────────┐");
	gotoprint(5, 13, "│    3인플레이   │");
	gotoprint(5, 14, "└────────┘");

	gotoprint(5, 15, "┌────────┐");
	gotoprint(5, 16, "│    4인플레이   │");
	gotoprint(5, 17, "└────────┘");
	y = 10;
	gotoprint(3, y, "☞");
	while (1)
	{
		if (GetKeyState(VK_RETURN)<0)
			continue;
		Select = _getch();
		switch (Select)
		{

		case 80: // 아래
			if (num<3)
			{
				num++;
				gotoprint(3, y, "  ");
				y += 3;
				gotoprint(3, y, "☞");

			}
			break;
		case 72: // 위
			if (num>1)
			{
				num--;
				gotoprint(3, y, "  ");
				y -= 3;
				gotoprint(3, y, "☞");

			}
			break;
		case 13: // 엔터 
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
	gotoprint(5, 3, "──────────");
	gotoprint(5, 4, "    게임모드설정    ");
	gotoprint(5, 5, "──────────");


	gotoprint(5, 9, "┌────────┐");
	gotoprint(5, 10, "│    기본 모드   │");
	gotoprint(5, 11, "└────────┘");

	gotoprint(5, 12, "┌────────┐");
	gotoprint(5, 13, "│  기지선택모드  │");
	gotoprint(5, 14, "└────────┘");

	gotoprint(3, 10, "☞");
	while (1)
	{
		if (GetKeyState(VK_RETURN)<0)
			continue;
		Select = _getch();
		switch (Select)
		{

		case 80: // 아래
			num = 2;
			gotoprint(3, 10, "  ");
			gotoprint(3, 13, "☞");
			break;
		case 72: // 위
			num = 1;
			gotoprint(3, 13, "  ");
			gotoprint(3, 10, "☞");
			break;
		case 13: // 엔터 
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

	gotoprint(5, 3, "──────────");
	gotoprint(5, 4, "    유저이름 입력    ");
	gotoprint(5, 5, "──────────");

	
	while (1)
	{
		if (GetKeyState(VK_RETURN) < 0)
			continue;
		for (i = 0; i < players; i++)
		{
			gotoxy(3, 8);
			setcolor(15, p_color[i]);
			printf("플레이어%d", i + 1);
			setcolor(0, 15);
			printf("의 닉네임 입력");

			gotoprint(2, 9, "(한글 4자,영문 8자 이내");
			gotoprint(10, 10, "뛰어쓰기X      )");
			gotoprint(2, 11, "입력 : ");
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
	gotoprint(1, 7, "┌────────────┐");
	gotoprint(1, 8, "│                        │");
	gotoprint(1, 9, "│!!곧 게임이 시작됩니다!!│");
	gotoprint(1, 10, "│                        │");
	gotoprint(1, 11, "└────────────┘");
	Sleep(2000);
}

void Game_Help()
{
	int select;
	gotoprint(2, 1, "공과대 마블에 ");
	gotoprint(7, 2, "오신것을 환영합니다.");
	gotoprint(2, 4, "[게임 방법]");
	gotoprint(2, 5, "1.주사윈를 굴린다");
	gotoprint(2, 6, "2.과를 산다");
	gotoprint(2, 7, "3.과를 다사거나");
	gotoprint(9, 8, "혼자만 남는다");
	gotoprint(2, 9, "= 이긴다");
	gotoprint(2, 10, "");
	gotoprint(5, 13, "┌────────┐");
	gotoprint(5, 14, "│ [Space]돌아가기│");
	gotoprint(5, 15, "└────────┘");

	while (1)
	{
		fflush(stdin);
		select = _getch();

		if (select == 32)
		{
			PlaySound(TEXT("click.wav"), NULL, SND_ASYNC);
			system("cls");
			gotoprint(3, 13, "☞");
			break;
		}
	}
}