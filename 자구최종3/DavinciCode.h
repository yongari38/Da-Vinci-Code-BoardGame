#ifndef __DAVINCI_CODE_H__
#define __DAVINCI_CODE_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define USER			1
#define COM				-1

#define TRUE			1
#define FALSE			0

#define BLACK			0      
#define WHITE			1
#define JOKER			12
#define BLOCK_LEN	    13
#define INIT_BLOCK		4			// ó���� �� �÷��̾ �������� ����� ��

extern int MAX_QUEUE_SIZE;		// ���̵��� ���� ũ�� ����

extern int num_white;
extern int num_black;
extern int TURN;
extern int TURN_num;

typedef struct _block {            // �� ����ü ��� ����(���߿��Ḯ��Ʈ)
	int color;                  // ���� �� (0: BLACK, 1: WHITE)
	int number;                  // ���� ���� (0 ~ 11, 12(JOKER))
	int get_turn;               // ��ο�� ��
	int revealed;               // ���� ���� ��������, ����:1, �����:0
	struct _block * llink, *rlink;
	int score[26];               // �� �� �̾����� �����.
								 // ó�� ��ο� ���� score[24] = {50,}. �ʱ����� 50.(�ʱ������� ���߿� ����.)
								 // �� ĭ���� �� ĭ�� �ش��ϴ� ���� ����ġ��.
								 // USER�� draw�� ���� ������ ���� ������ ������ ���                  
} Block;

typedef struct _deque {            // ���� �̾ƿ� Deck�� ���� Deque ����ü
	Block * head, *tail;
} Deque;

extern Deque BlockDeck;   // �÷��̾ ���� �̾ƿ� ����(Deck)
extern Block p_Block;   // USER�� �����ϰ� �ִ� �� head
extern Block c_Block;   // COM�� �����ϰ� �ִ� �� head

#endif

