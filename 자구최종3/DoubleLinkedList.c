#include "DavinciCode.h"
/*
--------------------------------------------
@(����)���߿��Ḯ��Ʈ(double linked list) �Լ�
--------------------------------------------
*/

void dll_init(Block * phead) {   // DLL �ʱ�ȭ(��� ��� �ʱ�ȭ)
	phead->number = -1;
	phead->llink = phead;
	phead->rlink = phead;
}
Block * dll_find_index(Block * head, Block * newBlock) { // newBlock�� �� ��ġ�� "��" ��� ��ȯ
	Block * cur = head;
	int number = newBlock->number;
	int color = newBlock->color;

	while (cur->rlink != head) {
		cur = cur->rlink;

		if (cur->number != JOKER && number < cur->number) {  // FOR �������� ���� (��Ŀ�� ���ڸ� 12�� ����ϹǷ� JOKER�� �ƴ϶�� ���� �߰�)
			cur = cur->llink;
			break;
		}

		else if (cur->number == number) {   // ���ڰ� ���� ��� �������� �տ� �־����
			if (cur->color == WHITE)
				cur = cur->llink;

			break;
		}
	}

	if (cur->rlink->number == JOKER) {
		cur = cur->rlink;
	}

	if (cur->number == JOKER && cur->llink->number == JOKER) {
		cur = cur->llink;
	}

	//printf("$%d, %d$\n", cur->block.color, cur->block.number);
	return cur;
}
void dll_insert(Block * before, Block * newBlock) {   // before ��� �ڿ� newBlock ��带 �߰���
	newBlock->rlink = before->rlink;
	newBlock->llink = before;

	before->rlink->llink = newBlock;
	before->rlink = newBlock;
}
void dll_display(Block * phead, int n) {   // DLL�� ������ ���
	Block * p;

	switch (n) {
	case USER:
		printf("[USER BLOCK] ");


		for (p = phead->rlink; p != phead; p = p->rlink) {
			printf("(%c: ", p->color == BLACK ? 'B' : 'W');

			if (p->number == JOKER)
				printf("J)");
			else
				printf("%d)", p->number);

			if (p->revealed == TRUE) {   // ��ǻ�Ϳ��� ���ڰ� ������ ���̸�
				printf("��, ");
			}
			else {
				printf(", ");
			}
		}
		printf("\n");
		break;

	case COM:
		printf("[COM  BLOCK] ");

		/*
		for (p = phead->rlink; p != phead; p = p->rlink) {
		//printf("(%c: %c), ", p->block.color == BLACK ? 'B' : 'W', p->revealed == TRUE ? '?' : (p->block.number == JOKER ? 'J' : (p->block.number + '0')));
		printf("(%c: ", p->color == BLACK ? 'B' : 'W');

		if (p->revealed == TRUE) {
		if (p->number == JOKER)
		printf("J), ");
		else
		printf("%d), ", p->number);
		}
		else {
		printf("?), ");
		}
		}
		*/

		for (p = phead->rlink; p != phead; p = p->rlink) {
			printf("(%c: ", p->color == BLACK ? 'B' : 'W');

			if (p->number == JOKER)
				printf("J)");
			else
				printf("%d)", p->number);

			if (p->revealed == TRUE) {   // ��ǻ�Ϳ��� ���ڰ� ������ ���̸�
				printf("��, ");
			}
			else {
				printf(", ");
			}
		}

		printf("\n");

		break;
	}
}
int dll_count(Block * phead) {
	Block * p;
	int cnt = 0;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		cnt++;
	}

	return cnt;
}
Block * dll_getNodeAt(Block * blocks, int pos) {
	int i;
	Block *tmp_node = blocks->rlink;

	if (pos < 0) return NULL;
	for (i = 0; i < pos; i++)
		tmp_node = tmp_node->rlink;

	return tmp_node;
}