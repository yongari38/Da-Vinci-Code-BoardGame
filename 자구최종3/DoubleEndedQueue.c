#include "DavinciCode.h"
/*
---------------
@��(Deque) �Լ�
---------------
*/

void dq_init(Deque * pd) {   // �� �ʱ�ȭ
	pd->head = NULL;
	pd->tail = NULL;
}
int dq_isEmpty(Deque * pd) {   // ���� ����ִ��� ����
	return (pd->head == NULL);
}
int dq_isFrontEmpty(Deque * pd) {   // ���� ���ʿ��� ���� ���� ����. ���� ���� �����ִ��� ����
	return (pd->head->color == WHITE);
}
int dq_isRearEmpty(Deque * pd) {   // ���� ���ʿ��� �� ���� ����. �� ���� �����ִ��� ����
	return (pd->tail->color == BLACK);
}
void dq_addFront(Deque * pd, Block * newBlock) {   // ���� ���ʿ� ��� �߰�
	if (dq_isEmpty(pd))
		pd->tail = newBlock;
	else {
		pd->head->llink = newBlock;
		newBlock->rlink = pd->head;
	}
	pd->head = newBlock;
}
void dq_addRear(Deque * pd, Block * newBlock) {   // ���� ���ʿ� ����� �߰�
	if (dq_isEmpty(pd))
		pd->head = newBlock;
	else {
		pd->tail->rlink = newBlock;
		newBlock->llink = pd->tail;
	}
	pd->tail = newBlock;
}
Block * dq_deleteFront(Deque * pd) { // ���� �� �� BlockNode�� �޸��������� "�ʰ�" ��ȯ
	Block * removedNode = NULL;

	if (dq_isEmpty(pd)) {
		printf("���� ��� �����Ǿ����ϴ�. ������ �����մϴ�.\n");
		exit(1);
	}

	if (dq_isFrontEmpty(pd)) {
		printf("�� �̻� ���� ���� �����ϴ�. �� ���� �������ּ���.\n");      // ���� �� ��� ����
		return NULL;
	}

	else {
		removedNode = pd->head;
		pd->head = pd->head->rlink;

		if (pd->head == NULL)
			pd->tail = NULL;
		else
			pd->head->llink = NULL;
	}
	num_black--;
	return removedNode;
}
Block * dq_deleteRear(Deque * pd) {   // ���� �� �� BlockNode�� �޸��������� "�ʰ�" ��ȯ
	Block * removedNode = NULL;

	if (dq_isEmpty(pd)) {
		printf("���� ��� �����Ǿ����ϴ�. ������ �����մϴ�.\n");
		exit(1);
	}

	if (dq_isRearEmpty(pd)) {
		printf("�� �̻� �� ���� �����ϴ�. ���� ���� �������ּ���.\n");      // �� �� ��� ����
		return NULL;
	}

	else {
		removedNode = pd->tail;
		pd->tail = pd->tail->llink;

		if (pd->tail == NULL)
			pd->head = NULL;
		else
			pd->tail->rlink = NULL;
	}
	num_white--;
	return removedNode;
}
void dq_display(Deque * pd) { // ���� ���� ���
	Block * p;
	for (p = pd->head; p != NULL; p = p->rlink) {
		printf("(%d: %d), ", p->color, p->color);
	}
	printf("\n");
}