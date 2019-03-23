#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include "DavinciCode.h"


#define LENGTH 140
#define LINES 9000
#define LENGTH_MAX 80   // 2ĭ ���� ��½�
#define LINES_MAX 50   // 2ĭ ���� ��½�
#define PAUSE() system("pause")
#define CLEAR() system("cls")

#define LEFT	75
#define RIGHT	77
#define UP		72
#define DOWN	80
#define ENTER	13

#define LEFT_CHOSEN		0
#define RIGHT_CHOSEN	1
#define UP_CHOSEN		2
#define DOWN_CHOSEN		3

#define EASY     5		// ���� ���̵��� QUEUE SIZE
#define HARD     20	// ����� ���̵��� QUEUE SIZE

#define GREEN 0
#define WHITE 1

#define BLOCK_WIDTH 8	// �� �ϳ��� ���� ����


void gotoP(int x, int y);

void showEdge();
void showChat();
void clearChat();

int showLevel();
int showOrder();

void showMain();
void SetCursorInvisible();

int whereJoker(Block*head);
int whereWithJoker(int count, int x, int row);
void whereJoker_bar(int x, int y);
void whereJoker_unbar(int x, int y);
int choose_guessNumber();

void printBlock(Block* b, int x, int y);
void printHand(Block* head);

Block* selectBlock(Block*head);
void BlockBoxing(int x, int y);
void BlockUnboxing(int x, int y);

enum ConsolColor {
	CC_BLACK,
	CC_DARKBLUE,
	CC_DARKGREEN,
	CC_DARKCYAN,
	CC_DARKRED,
	CC_DARKMAGENTA,
	CC_DARKYELLOW,
	CC_GRAY,
	CC_DARKGRAY,
	CC_BLUE,
	CC_GREEN,
	CC_CYAN,
	CC_RED,
	CC_MAGENTA,
	CC_YELLOW,
	CC_WHITE,
	CC_LIGHTGRAY = 7,
	CC_ORIGINAL = 7,
	CC_ORIGINALFONT = 7,
	CC_ORIGINALBG = 0
};

//�ؽ�Ʈ, ���� ��� ���� �Լ�
void setColor(int color, int bgcolor);
//�ؽ�Ʈ ���� ���� �Լ�
void setFontColor(int color);
//��� ���� ���� �Լ�
void setBgColor(int bgcolor);
//�ؽ�Ʈ ���� ȹ�� �Լ�
int getFontColor();
//��� ���� ȹ�� �Լ�
int getBgColor();
//�ؽ�Ʈ �÷� �⺻�� 
__inline void resetFontColor();
//���� �⺻��
__inline void resetBgColor();
//�ؽ�Ʈ, ���� �⺻��
__inline void resetColor();