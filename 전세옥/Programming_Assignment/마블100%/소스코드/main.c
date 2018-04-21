/*
���� �Լ�
*/
#include "bluemarble.h"

int addmoney;

MCI_OPEN_PARMS m_mciOpenParms;
MCI_PLAY_PARMS m_mciPlayParms;

DWORD m_dwDeviceID;
MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;

int dwID;

// ���� �̸�

char * const building_Name[boardNum] =
{
	"�������",
	"�����а�", "��ǰ���а�", "�������ڰ��а�", "��ǻ�Ͱ��а�", "������а�",
	"�ؾ�ý��۰��а�",
	"������а�", "�����а�", "ȯ����а�",
	"�̺�Ʈ",
	"�ż�����а�", "��Ƽ�̵����а�", "�����а�", "������ȣ�а�", "�����а�",
	"MT",
	"������Ű��а�", "����κ����а�", "�������а�"
};
// �����ü�  
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


//�ֻ�����ȣ ������ 
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


// ���� �ǿ� ������ ��ġ����
const int mal_postion[boardNum][2] = {
	{ 112, 30 }, { 94, 30 }, { 76, 30 }, { 58, 30 }, { 40, 30 }, { 22, 30 },
	{ 4, 30 }, { 4, 24 }, { 4, 18 }, { 4, 12 },
	{ 4, 6 }, { 22, 6 }, { 40, 6 }, { 58, 6 }, { 76, 6 }, { 94, 6 },
	{ 112, 6 }, { 112, 12 }, { 112, 18 }, { 112, 24 }
};

const int p_color[MAX_USER] = { 12, 9, 13, 2 }; // �� ���� 1 : ���� 2 : �Ķ� 3 : ���� 4 : �ʷ�
char * const player_img = "��"; //���׸� 
int od[4]; //�÷��̾� ���� 

int gamemode; // ���Ӹ�� ( �⺻ = 0, ��������= 1 )

int players; // �÷��̾��
int order; // ��������
int dice; // �ֻ���
int maxplayers; // �÷��̾��(�����)

struct BUILDING_PRESENT bp[boardNum]; // ���� ����
struct PLAYER pl[MAX_USER]; // �÷��̾�


int main()
{
	int i;
	int c;
	int select;
	char str[200];
	int re=0;
	// ȭ�� ��
	system("title ������ ����");
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

		MainMenu(); // ���Ӹ޴� ����

		mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);

		mciOpen.lpstrElementName = "gameplaybgm.mp3";
		mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);
		mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&m_mciPlayParms);
		//mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);

		Game_Init(); //���� �ʱ�ȭ
		draw_stat(); //���� ���
	
		// ������� �� ���� ����
		if (gamemode == 1) 
		{
			choice_base(); 
			deleteprint();
		}

		random_turn(); // ���ۼ��� ���ϱ�

		while (1)
		{
			for (i = 0; i < maxplayers; i++)
			{
				draw_digital_dice(0);
				gotoxy(0, 0);
				order = pl[od[i]].ID; // ���� �÷��̾� ID

				draw_stat();

				gotoxy(2, 32);
				setcolor(15, p_color[order]);
				printf("%s���� �����Դϴ�", pl[order].name);
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
						printf("%s���� ���� MT�� ���ִ� ����. [%d]�� ���ҽ��ϴ�.", pl[order].name, pl[order].rest_turn);
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
					printf("�ֻ����� �����÷��� ");
					setcolor(15, 0);
					printf("�����̽��ٸ� �� �����ð� ���ʽÿ�");
					setcolor(0, 15);

					while (1)
					{
						c = _getch();

						if (c == 32)
						{
							dice = throwing_dice(); // �ֻ��� ������
							//dice = 5;

							break;
						}
					}

					gotoxy(2, 34);
					setcolor(0, 14);
					printf("%d", dice);
					setcolor(0, 15);
					printf("��(��) ���Խ��ϴ�! ");
					setcolor(0, 14);
					printf("%dĭ �̵�",dice);
					setcolor(0, 15);
					printf("�մϴ�.");
		
					Move_Pieces(dice, 350); // ���̵�
					//	draw_stat();
					building_system(); // ����
					break;
				}


				draw_stat();

				if (victory() == 1)
					break;

				gotoprint(2, 45, "[ ���� �ѱ�÷��� �����̽��ٸ� �����ʽÿ� ]");
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
				//gotoprint(38, 16,"        !!!!!!!!!!!!!!!!!�̰���ϴ�!!!!!!!!!!!!!!!!!!       ");
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
		gotoprint(38, 21, "  [1]��������  [2]�����ϱ�                                     ");
		gotoprint(38, 22, "  �Է� :                                                       ");

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
				gotoprint(46, 22, "���� ���� ������ �Է��Ͻñ� �ٶ��ϴ�");
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

