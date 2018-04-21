/*
제목 : 공과대 마블 
제작자 : Foza
플레이어 : 2~ 4인
전체칸수 : 20칸
스토리 : 공과대의 모든 과를 점령하라

건물장악비용
[25%]기본가격
[50%]기본가격*2
[75%]기본가격*3
[100%]기본가격*4  

건물 통행비 
건물가격의 반 

게임룰
- 게임준비
랜덤으로 순서가 정해진다. 기지선택모드의 경우 기지(base)를 선택하고 그곳에서 시작.

- 주사위
주사위를 굴려 나온만큼 전진

- 과 구입
도착한 과가 주인이 없다면 돈을 주고 주인이 될 수 있다
도착한 과가 주인이 있다면 돈을 지불해야 한다.
한바퀴를 돌수록 더 많이 과를 장악할 수 있다.
장악력이 100퍼가 아닌 과는 돈을 내고 살 수가 있다. 
base(기지)인 과는 살 수 없습니다.

- 장학금
한바퀴를 돌면 장학금을 받는다 (기지선택모드의 경우 그 기지로부터 한바퀴)

- 지불할 돈이 없을 경우
자신이 장악하고 있는 과를 팔아 돈을 마련할 수 있다.
돈을 지불하지 못하면 파산된다.

- 파산시
가지고 있는 과들이 모두 팔리고 돈을 모두 상대에게 줘야한다.

- MT
MT에 가기위해 MT비를 지불하고 2턴을 쉰다.

-스쿨버스
버스에 타면 버스앞칸부터 버스뒤칸 범위 내에서 아무곳이나 갈 수 있다.


- 이벤트
이벤트칸에 들어가면 특별한 일이 벌어지기도 하고 특별한 아이템이 주어지기도 한다.
플레이어는 일을 반드시 수행해야 한다.


- 게임 승
자신을 제외한 모두를 파산시키면 이긴다.

[이벤트 종류] 
소맥파티           : 확률적으로 취하면 뒤로 가거나 앞으로 갑니다 (최대 5칸)
도박                 : 소지금 미만의 돈을 걸어 이기면 걸은 가격의 두배를 얻을 수 있습니다
버스카드획득     : 버스칸으로 이동합니다. 다음턴에 버스를 탈 수 있습니다.
삥뜯기              : 원하는 플레이어의 돈을 삥뜯을 수 있습니다 단, 거지는 돈을 안줘도 됩니다. (1000원)
군기잡기           : 자기 과를 더 장악시킬 수 있습니다
장악                 : 비어있는 칸에서 원하는 과를 장악 할 수 있습니다 
생일축제           : 플레이어의 생일이므로 플레이어를 제외한 플레이어들은 돈을 받칩니다. 단, 거지는 돈을 안줘도 됩니다. (1500원)
 
[아이템 종류]
MT회피권         : MT를 회피할 수 있습니다
빽                   : 빽을 이용해 상대방이 장악한 과를 무료로 지나갈 수 있습니다
*/

#ifndef __MARBLE_H__

#define __MARBLE_H__


// ------------------------------------------
// 해더목록
// ------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <MMSystem.h> // 음악 파일
#include "Digitalv.h" // 음악 파일

#pragma comment(lib,"winmm.lib") // 음악파일
#pragma warning (disable:4996)

// ------------------------------------------
// 매크로
// ------------------------------------------
#define boardNum 20 // 보드칸 수(고정)
#define MAX_USER 4 // 최대 유저수(고정)
#define PL_STARTMONEY 30000 // 플레이어 처음 재산
#define MONTH_PAY 1000 // 장학금
#define REST_NUM 2 // 쉬는턴
#define MT_PAY 2000
#define STEAL_MONEY 1000 // 삥뜯는돈
#define BIRTH_MONEY 1500 // 생일돈
#define YES 1
#define NO 0


// ------------------------------------------
// 구조체
// ------------------------------------------
struct BUILDING_PRESENT{
	int order; // 현재 주인  -1 = 없음, -2 = 버스, -3 = 휴학(턴쉼), -4 = 이벤트, -5 = 입학금 (돈내기), 0 ~ 3 = 자기땅[user_ID로 빌딩주인체크]
	int price; // 현재 가격
	int noslevel; // 현재 층수 1 : 일층, 2 : 이층, 3 : 삼층(최대)
	int base; // 기지인지 아닌지
};

struct PLAYER{

	char name[10]; // 닉네임
	int ID; // ID
	int MONEY; // 재산
	int Mybuilding; // 빌딩수
	int stat; // 상태  0= 기본, 1 = MT, -1 = 죽음, 2 = 버스카드
	int rest_turn; // 쉬는턴 (MT 등)
	int x, y; // 말 좌표
	int mypos; // 밟고잇는 칸번호
	int round; // 라운드 당 살수있는 층수가 많아짐 (1라=1층, 2라=2층, 3라=3층(최대))
	int Item[2]; // 아이템 0=MT회피권, 1=빽
};

// ------------------------------------------
// 외부변수
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
// 함수목록
// ------------------------------------------
void CursorView(char show);//커서숨기기
void setcolor(int color, int bgcolor); // 컬러 (색입히기)
void gotoxy(int x, int y); // 커서좌표이동
void gotoprint(int x, int y, char *m); // 커서좌표이동 및 출력
void deleteprint(); // 상태출력화면 지우기
void Move_Pieces(int num, int delay); // 말 움직이기


void MainMenu(); // 메인메뉴
void Game_Help(); // 게임설명
void Game_player(); // 게임인원 설정 (2인~4인 설정)
void Game_Mode(); // 게임모드 설정 (기본모드 , 기지선택모드)
void Input_Name(); // 플레이어 닉네임입력


void Game_Init(); // 게임초기화 
void random_turn(); // 시작순서 정하기

void draw_digital_dice(int who); // 디지털주사위 출력
void Draw_Board(); // 보드판 출력 
void draw_stat(); // 유저 상태출력

void choice_base(); // 기지 설정

int throwing_dice(); // 주사위던지기


int victory(); // 승자 가리기
int bankruptcy(int cost); // 파산기능

void MT_System(); // MT기능
void bus_System(); // 버스기능
void DrunkParty(); // 소맥파티
void gameble(); // 도박
void bus_card(); // 버스 카드
void md_func(); // 군기잡기
void steal_func(); // 삥뜯기
void domination(); // 장악
void birth_day(); // 생일축제
void additem(); //아이템획득
void Event_System(); // 이벤트기능
void Sell_building(int cost); // 빌딩팔기
void choice_dominate(int r, int pos); // 건물 장악력 발전

void building_system(); // 건물기능


#endif

