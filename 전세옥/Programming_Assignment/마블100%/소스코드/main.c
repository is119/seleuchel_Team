/*
메인 함수
*/
#include "bluemarble.h"

int addmoney;

MCI_OPEN_PARMS m_mciOpenParms;
MCI_PLAY_PARMS m_mciPlayParms;

DWORD m_dwDeviceID;
MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;

int dwID;

// 빌딩 이름

char * const building_Name[boardNum] =
{
	"스쿨버스",
	"기계공학과", "식품공학과", "정보전자공학과", "컴퓨터공학과", "건축공학과",
	"해양시스템공학과",
	"전기공학과", "토목공학과", "환경공학과",
	"이벤트",
	"신소재공학과", "멀티미디어공학과", "조경학과", "정보보호학과", "건축학과",
	"MT",
	"정보통신공학과", "제어로봇공학과", "조선공학과"
};
// 빌딩시세  
const int building_Price[boardNum] =
{
	0,
	500, 550, 600, 650, 700,
	750,
	800, 850, 900,
	0,
	950, 1000, 1050, 1100, 1150,
	0,
	1200, 1250, 1300
};


//주사위번호 디지털 
const int dice_digital[7][7][7] =
{
	{
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 0, 0, 1, 0 },
		{ 0, 1, 0, 0, 0, 1, 0 },
		{ 0, 1, 0, 0, 0, 1, 0 },
		{ 0, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 1, 0 },
		{ 0, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 1, 0 },
		{ 0, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 1, 0 },
		{ 0, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 0, 0, 0, 1, 0 },
		{ 0, 1, 0, 0, 0, 1, 0 },
		{ 0, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 1, 0 },
		{ 0, 0, 0, 0, 0, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 1, 0 },
		{ 0, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 0, 0, 1, 0 },
		{ 0, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	}
};


// 말이 판에 나오는 위치지정
const int mal_postion[boardNum][2] = {
	{ 112, 30 }, { 94, 30 }, { 76, 30 }, { 58, 30 }, { 40, 30 }, { 22, 30 },
	{ 4, 30 }, { 4, 24 }, { 4, 18 }, { 4, 12 },
	{ 4, 6 }, { 22, 6 }, { 40, 6 }, { 58, 6 }, { 76, 6 }, { 94, 6 },
	{ 112, 6 }, { 112, 12 }, { 112, 18 }, { 112, 24 }
};

const int p_color[MAX_USER] = { 12, 9, 13, 2 }; // 말 색깔 1 : 빨강 2 : 파랑 3 : 자주 4 : 초록
char * const player_img = "♀"; //말그림 
int od[4]; //플레이어 순서 

int gamemode; // 게임모드 ( 기본 = 0, 기지선택= 1 )

int players; // 플레이어수
int order; // 현재차례
int dice; // 주사위
int maxplayers; // 플레이어수(저장용)

struct BUILDING_PRESENT bp[boardNum]; // 현재 빌딩
struct PLAYER pl[MAX_USER]; // 플레이어


int main()
{
	int i;
	int c;
	int select;
	char str[200];
	int re=0;
	// 화면 색
	system("title 공과대 마블");
	system("color F0");
	srand((unsigned int)time(NULL));


	//char *music[2]={"mainbgm.mp3","gameplaybgm.mp3"};
	for (;;)
	{
		CursorView(0);
		system("cls");
		mciOpen.lpstrElementName = "mainbgm.mp3";
		mciOpen.lpstrDeviceType = "mpegvideo";
		mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);
		dwID = mciOpen.wDeviceID;
		mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&m_mciPlayParms);

		MainMenu(); // 게임메뉴 실행

		mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);

		mciOpen.lpstrElementName = "gameplaybgm.mp3";
		mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);
		mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&m_mciPlayParms);
		//mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);

		Game_Init(); //변수 초기화
		draw_stat(); //상태 출력
	
		// 기지모드 시 기지 설정
		if (gamemode == 1) 
		{
			choice_base(); 
			deleteprint();
		}

		random_turn(); // 시작순서 정하기

		while (1)
		{
			for (i = 0; i < maxplayers; i++)
			{
				draw_digital_dice(0);
				gotoxy(0, 0);
				order = pl[od[i]].ID; // 현재 플레이어 ID

				draw_stat();

				gotoxy(2, 32);
				setcolor(15, p_color[order]);
				printf("%s님의 차례입니다", pl[order].name);
				setcolor(0, 15);

				switch (pl[order].stat)
				{
				case -1:
					continue;
				case 2:

					bus_System();
					pl[order].stat = 0;
					building_system();
					break;
				case 1:
					if (pl[order].rest_turn > 0)
					{

						gotoxy(2, 33);
						setcolor(15, p_color[order]);
						printf("%s님은 지금 MT에 가있는 상태. [%d]턴 남았습니다.", pl[order].name, pl[order].rest_turn);
						setcolor(0, 15);

						pl[order].rest_turn--;
						Sleep(2000);
						break;
					}
					else
					{
						pl[order].stat = 0;
					}
				default:
					gotoxy(2, 33);
					printf("주사위를 던지시려면 ");
					setcolor(15, 0);
					printf("스페이스바를 꾹 누르시고 떼십시오");
					setcolor(0, 15);

					while (1)
					{
						c = _getch();

						if (c == 32)
						{
							dice = throwing_dice(); // 주사위 던지기
							//dice = 5;

							break;
						}
					}

					gotoxy(2, 34);
					setcolor(0, 14);
					printf("%d", dice);
					setcolor(0, 15);
					printf("이(가) 나왔습니다! ");
					setcolor(0, 14);
					printf("%d칸 이동",dice);
					setcolor(0, 15);
					printf("합니다.");
		
					Move_Pieces(dice, 350); // 말이동
					//	draw_stat();
					building_system(); // 빌딩
					break;
				}


				draw_stat();

				if (victory() == 1)
					break;

				gotoprint(2, 45, "[ 턴을 넘기시려면 스페이스바를 누르십시오 ]");
				for (;;)
				{
					select = _getch();

					if (select == 32)
					{
						deleteprint();
						break;
					}
				}
			}
			if (victory() == 1)
			{
				setcolor(10, 0);
				gotoprint(38, 12, "  ===========================================================  ");
				gotoprint(38, 13, "                                                               ");
				gotoprint(38, 14, "                                                               ");
				gotoprint(38, 15, "                                                               ");
				//gotoprint(38, 16,"        !!!!!!!!!!!!!!!!!이겼습니다!!!!!!!!!!!!!!!!!!       ");
				gotoprint(38, 17, "                                                               ");
				gotoprint(38, 18, "                                                               ");
				gotoprint(38, 19, "                                                               ");
				gotoprint(38, 20, "  ===========================================================  ");
				setcolor(0, 15);
				break;
			}
		}

		mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);

		mciOpen.lpstrElementName = "Victory.mp3";
		mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);
		mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&m_mciPlayParms);

		setcolor(10, 0);
		gotoprint(38, 21, "  [1]메인으로  [2]종료하기                                     ");
		gotoprint(38, 22, "  입력 :                                                       ");

		while (1)
		{
			CursorView(1);
			do{
				gotoprint(48, 22, "                                                                                  ");
				gotoxy(48, 22);
				gets(str);
			} while (strcmp(str, "") == 0 || str[0] == ' ');
			CursorView(0);
			select = atoi(str);

			switch (select)
			{
			case 1:
				re = 1;
				break;
			case 2:
				exit(0);
			default:
				gotoprint(46, 22, "위의 숫자 내에서 입력하시길 바랍니다");
				Sleep(1000);
				gotoprint(46, 22, "                                     ");
			}
			if (re == 1)
			{
				re = 0;
				break;
			}
		}
		setcolor(0, 15);
	}
	return 0;
}

