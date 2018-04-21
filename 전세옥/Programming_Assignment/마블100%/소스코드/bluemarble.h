/*
���� : ������ ���� 
������ : Foza
�÷��̾� : 2~ 4��
��üĭ�� : 20ĭ
���丮 : �������� ��� ���� �����϶�

�ǹ���Ǻ��
[25%]�⺻����
[50%]�⺻����*2
[75%]�⺻����*3
[100%]�⺻����*4  

�ǹ� ����� 
�ǹ������� �� 

���ӷ�
- �����غ�
�������� ������ ��������. �������ø���� ��� ����(base)�� �����ϰ� �װ����� ����.

- �ֻ���
�ֻ����� ���� ���¸�ŭ ����

- �� ����
������ ���� ������ ���ٸ� ���� �ְ� ������ �� �� �ִ�
������ ���� ������ �ִٸ� ���� �����ؾ� �Ѵ�.
�ѹ����� ������ �� ���� ���� ����� �� �ִ�.
��Ƿ��� 100�۰� �ƴ� ���� ���� ���� �� ���� �ִ�. 
base(����)�� ���� �� �� �����ϴ�.

- ���б�
�ѹ����� ���� ���б��� �޴´� (�������ø���� ��� �� �����κ��� �ѹ���)

- ������ ���� ���� ���
�ڽ��� ����ϰ� �ִ� ���� �Ⱦ� ���� ������ �� �ִ�.
���� �������� ���ϸ� �Ļ�ȴ�.

- �Ļ��
������ �ִ� ������ ��� �ȸ��� ���� ��� ��뿡�� ����Ѵ�.

- MT
MT�� �������� MT�� �����ϰ� 2���� ����.

-�������
������ Ÿ�� ������ĭ���� ������ĭ ���� ������ �ƹ����̳� �� �� �ִ�.


- �̺�Ʈ
�̺�Ʈĭ�� ���� Ư���� ���� �������⵵ �ϰ� Ư���� �������� �־����⵵ �Ѵ�.
�÷��̾�� ���� �ݵ�� �����ؾ� �Ѵ�.


- ���� ��
�ڽ��� ������ ��θ� �Ļ��Ű�� �̱��.

[�̺�Ʈ ����] 
�Ҹ���Ƽ           : Ȯ�������� ���ϸ� �ڷ� ���ų� ������ ���ϴ� (�ִ� 5ĭ)
����                 : ������ �̸��� ���� �ɾ� �̱�� ���� ������ �ι踦 ���� �� �ֽ��ϴ�
����ī��ȹ��     : ����ĭ���� �̵��մϴ�. �����Ͽ� ������ Ż �� �ֽ��ϴ�.
����              : ���ϴ� �÷��̾��� ���� ����� �� �ֽ��ϴ� ��, ������ ���� ���൵ �˴ϴ�. (1000��)
�������           : �ڱ� ���� �� ��ǽ�ų �� �ֽ��ϴ�
���                 : ����ִ� ĭ���� ���ϴ� ���� ��� �� �� �ֽ��ϴ� 
��������           : �÷��̾��� �����̹Ƿ� �÷��̾ ������ �÷��̾���� ���� ��Ĩ�ϴ�. ��, ������ ���� ���൵ �˴ϴ�. (1500��)
 
[������ ����]
MTȸ�Ǳ�         : MT�� ȸ���� �� �ֽ��ϴ�
��                   : ���� �̿��� ������ ����� ���� ����� ������ �� �ֽ��ϴ�
*/

#ifndef __MARBLE_H__

#define __MARBLE_H__


// ------------------------------------------
// �ش����
// ------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <MMSystem.h> // ���� ����
#include "Digitalv.h" // ���� ����

#pragma comment(lib,"winmm.lib") // ��������
#pragma warning (disable:4996)

// ------------------------------------------
// ��ũ��
// ------------------------------------------
#define boardNum 20 // ����ĭ ��(����)
#define MAX_USER 4 // �ִ� ������(����)
#define PL_STARTMONEY 30000 // �÷��̾� ó�� ���
#define MONTH_PAY 1000 // ���б�
#define REST_NUM 2 // ������
#define MT_PAY 2000
#define STEAL_MONEY 1000 // ���µ�
#define BIRTH_MONEY 1500 // ���ϵ�
#define YES 1
#define NO 0


// ------------------------------------------
// ����ü
// ------------------------------------------
struct BUILDING_PRESENT{
	int order; // ���� ����  -1 = ����, -2 = ����, -3 = ����(�Ͻ�), -4 = �̺�Ʈ, -5 = ���б� (������), 0 ~ 3 = �ڱⶥ[user_ID�� ��������üũ]
	int price; // ���� ����
	int noslevel; // ���� ���� 1 : ����, 2 : ����, 3 : ����(�ִ�)
	int base; // �������� �ƴ���
};

struct PLAYER{

	char name[10]; // �г���
	int ID; // ID
	int MONEY; // ���
	int Mybuilding; // ������
	int stat; // ����  0= �⺻, 1 = MT, -1 = ����, 2 = ����ī��
	int rest_turn; // ������ (MT ��)
	int x, y; // �� ��ǥ
	int mypos; // ����մ� ĭ��ȣ
	int round; // ���� �� ����ִ� ������ ������ (1��=1��, 2��=2��, 3��=3��(�ִ�))
	int Item[2]; // ������ 0=MTȸ�Ǳ�, 1=��
};

// ------------------------------------------
// �ܺκ���
// ------------------------------------------

extern MCI_OPEN_PARMS m_mciOpenParms;
extern MCI_PLAY_PARMS m_mciPlayParms;

extern DWORD m_dwDeviceID;
extern MCI_OPEN_PARMS mciOpen;
extern MCI_PLAY_PARMS mciPlay;
extern int dwID;

extern char * const building_Name[boardNum];
extern const int building_Price[boardNum];
extern const int dice_digital[7][7][7];
extern const int mal_postion[boardNum][2];
extern const int p_color[MAX_USER];
extern int gamemode;
extern int players;
extern int maxplayers;
extern int order;
extern int dice;
extern char * const player_img;
extern int od[4];
extern struct BUILDING_PRESENT bp[boardNum];
extern struct PLAYER pl[MAX_USER];

extern int addmoney;

// ------------------------------------------
// �Լ����
// ------------------------------------------
void CursorView(char show);//Ŀ�������
void setcolor(int color, int bgcolor); // �÷� (��������)
void gotoxy(int x, int y); // Ŀ����ǥ�̵�
void gotoprint(int x, int y, char *m); // Ŀ����ǥ�̵� �� ���
void deleteprint(); // �������ȭ�� �����
void Move_Pieces(int num, int delay); // �� �����̱�


void MainMenu(); // ���θ޴�
void Game_Help(); // ���Ӽ���
void Game_player(); // �����ο� ���� (2��~4�� ����)
void Game_Mode(); // ���Ӹ�� ���� (�⺻��� , �������ø��)
void Input_Name(); // �÷��̾� �г����Է�


void Game_Init(); // �����ʱ�ȭ 
void random_turn(); // ���ۼ��� ���ϱ�

void draw_digital_dice(int who); // �������ֻ��� ���
void Draw_Board(); // ������ ��� 
void draw_stat(); // ���� �������

void choice_base(); // ���� ����

int throwing_dice(); // �ֻ���������


int victory(); // ���� ������
int bankruptcy(int cost); // �Ļ���

void MT_System(); // MT���
void bus_System(); // �������
void DrunkParty(); // �Ҹ���Ƽ
void gameble(); // ����
void bus_card(); // ���� ī��
void md_func(); // �������
void steal_func(); // ����
void domination(); // ���
void birth_day(); // ��������
void additem(); //������ȹ��
void Event_System(); // �̺�Ʈ���
void Sell_building(int cost); // �����ȱ�
void choice_dominate(int r, int pos); // �ǹ� ��Ƿ� ����

void building_system(); // �ǹ����


#endif

