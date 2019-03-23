#include "DavinciCode.h"
#include "DoubleLinkedList.h"
#include "DoubleEndedQueue.h"
#include "ComputerGuess.h"
#include "gameUI.h"

Deque BlockDeck;   // �÷��̾ ���� �̾ƿ� ����(Deck)
Block p_Block;   // USER�� �����ϰ� �ִ� �� head
Block c_Block;   // COM�� �����ϰ� �ִ� �� head

int num_white = BLOCK_LEN;
int num_black = BLOCK_LEN;
int TURN = COM;
int TURN_num = 0;

/*
-------------------
@���� ���� ���� �Լ�
-------------------
*/

void makeArrayRandom(int * arr) {   // �Ű������� ���޹��� �迭�� ������ �����ϰ� ����� �Լ�
	int len = BLOCK_LEN;
	int rs[BLOCK_LEN];
	int n = 0;

	while (len != 0) {
		int idx = rand() % len;
		rs[n++] = arr[idx];

		for (int i = idx; i < len - 1; i++)
			arr[i] = arr[i + 1];

		len--;
	}

	for (int i = 0; i < BLOCK_LEN; i++) {
		arr[i] = rs[i];
	}
}
void initDeck() {   // BlockDeck�� �ʱ�ȭ
	int arr[BLOCK_LEN] = { 0,1,2,3,4,5,6,7,8,9,10,11,JOKER };

	for (int j = 0; j <= WHITE; j++) {
		makeArrayRandom(arr);

		for (int i = 0; i < BLOCK_LEN; i++) {
			//printf("%d ", arr[i]);
			Block * bnode = (Block*)malloc(sizeof(Block));
			bnode->revealed = FALSE;
			bnode->color = j;
			bnode->number = arr[i];
			bnode->rlink = NULL;
			bnode->llink = NULL;

			for (int k = 0; k < 26; k++)
				bnode->score[k] = 50;

			if (j == 0)
				dq_addFront(&BlockDeck, bnode);
			else
				dq_addRear(&BlockDeck, bnode);
		}
		printf("\n");
	}
}

void InsertAndSort(Block * PlayerBlock, Block * newBlock, int Player) {   // newBlock�� PlayerBlock����Ʈ�� ������ ��ġ�� ����
	Block * before;
	int n = -1; // JOKER�� �ִ� ��� ���� ��ġ ���� ����
	int count;
	int x = LENGTH / 2 - (BLOCK_WIDTH / 2);
	int row = 17;

	if (Player == COM)
		add_to_known(newBlock);

	if (newBlock->number == JOKER) { // �������� ���� ��Ŀ�� ���
		Block * p = PlayerBlock;
		int i = 0;

		if (Player == USER) {
			gotoP(50, 18);   printf("��Ŀ�� ������ ��ġ�� ������");
			n = whereJoker(&p_Block);
		}
		else if (Player == COM) { // Computer�� ���
			for (p = PlayerBlock->rlink; p != PlayerBlock; p = p->rlink, i++);
			n = rand() % (i + 1);
		}

		p = PlayerBlock;
		for (i = 0; i < n; i++) {
			p = p->rlink;
		}

		before = p;
	}

	else {   // �������� ����� ��Ŀ�� �ƴ� ���

		n = -1; // JOKER�� �ִ� ��� ���� ��ġ ���� ���� �ʱ�ȭ
		before = dll_find_index(PlayerBlock, newBlock);      // ������ ��ġ �� ���
															 //printf("<%d>", before->block.number);
		clearChat();
		if (before->number == JOKER && before->rlink->number == JOKER) {  // ��Ŀ�� ���޾� 2�� �ִ� ���

			count = 2;

			if (Player == USER) {

				gotoP(x - 15, row);
				printf("��� ���� ���� ��� �����ðڽ��ϱ�?\n");
				printBlock(newBlock, x, row + 2);

				printBlock(before, x, row + 12);
				printBlock(before->rlink, x + 10, row + 11);
				n = whereWithJoker(count, x, row + 8);
			}
			else if (Player == COM) {
				n = rand() % 3;
			}
		}
		else if (before->number == JOKER) {      // ������ ��ġ �տ� JOKER�� 1�� �ִ� ���

			count = 1;

			if (Player == USER) {

				gotoP(x - 15, row);
				printf("��� ���� ���� ��� �����ðڽ��ϱ�?\n");
				printBlock(newBlock, x, row + 2);

				printBlock(before, x, row + 11);
				n = whereWithJoker(count, x, row + 8);
			}
			else if (Player == COM) {
				n = rand() % 2;
			}
		}

		if (n == 0) {
			before = before->llink;
		}
		else if (n == 2) {
			before = before->rlink;
		}
	}
	dll_insert(before, newBlock);
}

Block * choiceColor(Deque * pd) {   // ����, �� �� ���� �� ������ �� ��ȯ�ϴ� �Լ�

	int color = BLACK;
	int select;

	Block * newBlock = NULL;

	if (dq_isEmpty(pd)) {
		printf("�� �̻� �̾ƿ� ���� �����ϴ�.");
		printf("���º��Դϴ�.");
		exit(1);
	}
	else
	{
		//while (getchar() != '\n');

		int x = 58, y = 20;
		int i;

		setColor(10, 0);   gotoP(x - 1 - 1, y - 1);   printf("����������������������");
		gotoP(x - 1 + BLOCK_WIDTH / 2 - 3, y + 1); printf("������");
		gotoP(x - 1 + BLOCK_WIDTH / 2, y + 3); printf("%d", num_black);
		setColor(15, 0);   gotoP(x - 1 - 1 + 16, y - 1);   printf("����������������������");
		gotoP(x + 16 - 1 + BLOCK_WIDTH / 2 - 3, y + 1); printf("������");
		gotoP(x + 16 - 1 + BLOCK_WIDTH / 2, y + 3); printf("%d", num_white);

		// ���̷����ϸ� ��� ��������ϱ�
		//gotoP(x - 1, y + 0);   printf("#       #");
		//gotoP(x - 1, y + 1);   printf("#       #");
		//gotoP(x - 1, y + 2);   printf("#       #");
		//gotoP(x - 1, y + 3);   printf("#       #");
		//gotoP(x - 1, y + 4);   printf("#       #");
		// ���̷��� �Ѵ�

		for (i = 0; i < 5; i++) {

			setColor(10, 0);
			gotoP(x - 1 - 1, y + i);   printf("��");
			gotoP(x + BLOCK_WIDTH, y + i);   printf("��");

			setColor(15, 0);
			gotoP(x - 1 - 1 + 16, y + i);   printf("��");
			gotoP(x + BLOCK_WIDTH + 16, y + i);   printf("��");
		}

		setColor(10, 0);   gotoP(x - 1 - 1, y + 5);   printf("����������������������");
		setColor(15, 0);   gotoP(x - 1 - 1 + 16, y + 5);   printf("����������������������");

		resetColor();

		gotoP(x - 1 - 1 + 4, y + 6); printf(" �� ");

		gotoP(x - 1 - 1 - 9, y + 10); printf("����Ű�� ���� �� Enter �Ǵ� SpaceŰ�� ��������.\n");

		while (TRUE) {
			select = getch();
			if (select == ENTER || select == ' ')
				break;

			if (select == 0 || select == 0xe0) {
				select = getch();
				if (select == LEFT) { // ���� ����Ű

					color = BLACK;

					gotoP(x - 1 - 1 + 20, y + 6); printf("   ");
					gotoP(x - 1 - 1 + 4, y + 6); printf(" ��");
				}
				else if (select == RIGHT) { // ������ ����Ű

					color = WHITE;

					gotoP(x - 1 - 1 + 4, y + 6); printf("   ");
					gotoP(x - 1 - 1 + 20, y + 6); printf(" ��");
				}
			}
		}

		//getchar();

		//gotoP(40, 20);

		switch (color) {
		case BLACK:
			newBlock = dq_deleteFront(pd);
			if (newBlock == NULL) {
				color = -1;
				break;
			}
			/*if (newBlock->number == JOKER) {
			printf("���� �� : ������ ��Ŀ                                     \n");
			printf("                                                            ", newBlock->number);
			}
			else {
			printf("���� �� : ������ %d                                      \n", newBlock->number);
			printf("                                                            ", newBlock->number);
			}*/

			break;
		case WHITE:
			newBlock = dq_deleteRear(pd);
			if (newBlock == NULL) {
				color = -1;
				break;
			}
			/*if (newBlock->number == JOKER){
			printf("���� �� : ��� ��Ŀ                                       \n");
			printf("                                                            ", newBlock->number);
			}
			else {
			printf("���� �� : ��� %d                                        \n");
			printf("                                                            ", newBlock->number);
			}*/

			break;
		}

		gotoP(x - 1 - 1 - 9, y + 14);

	}
	return newBlock;
}
Block * choiceColor_COM(Deque * pd) {   // COM�� ����, �� �� ���� �� ������ �� ��ȯ�ϴ� �Լ�
	int color = -1;
	Block * newBlock = NULL;

	if (dq_isEmpty(&BlockDeck)) {
		printf("�� �̻� �̾ƿ� ���� �����ϴ�.");
		printf("���º��Դϴ�.");
		exit(1);
	}
	else
	{
		while (color != BLACK && color != WHITE)
		{
			if (dq_isEmpty(pd))               // ���� �������
				printf("���� ��� �����Ǿ����ϴ�. ������ �����մϴ�.\n");
			else if (dq_isFrontEmpty(pd))      // ������ �������
				color = WHITE;
			else if (dq_isRearEmpty(pd))      // �Ͼ��� ����� ��
				color = BLACK;
			else {
				Block* b;
				Block* tmp;
				tmp = &c_Block;

				int B_count = 0, W_count = 0;
				for (b = tmp->rlink; b != tmp; b = b->rlink) {
					if (b->color == BLACK)
						B_count++;
					else if (b->color == WHITE)
						W_count++;
				}
				// BLACK ������ WHITE �̰� WHITE ������ BLACK�̴´�
				// ������ WHITE �̴´�
				color = (B_count >= W_count ? WHITE : BLACK);
			}

			switch (color) {
			case BLACK:
				newBlock = dq_deleteFront(pd);
				if (newBlock == NULL) {
					color = -1;
					break;
				}
				break;
			case WHITE:
				newBlock = dq_deleteRear(pd);
				if (newBlock == NULL) {
					color = -1;
					break;
				}
				break;
			}
		}
	}
	return newBlock;
}



void currentDeck() {   // ���� �� DECK�� �����ִ� ���, ������ ���� ������ ���
	printf("\n%d���� ���� ���� %d���� �� ���� �����ֽ��ϴ�.\n\n", num_black, num_white);
}
void showBlocks() {
	CLEAR();
	showEdge();
	showChat();

	printHand(&c_Block);
	printHand(&p_Block);
}

char replay = FALSE;	// ������ ������ �� ������ ��� ������ ��
char replay_COM = FALSE;// ��ǻ�Ͱ� ������ �� ������ ��� ������ �� 
Block * newBlock = NULL;

void play() {
	if (TURN == USER) {

		showBlocks();
		showChat();
		gotoP(LENGTH / 2 - 10, 13); printf("����� �����Դϴ�.");
		if (replay == FALSE) {
			gotoP(LENGTH / 2 - 20, 16);  printf("���ο� ���� �����ɴϴ�.");
			newBlock = choiceColor(&BlockDeck);
			TURN_num++;
			init_score(newBlock, &p_Block);
			InsertAndSort(&p_Block, newBlock, USER);
			printHand(&p_Block);

		}
		gotoP(LENGTH / 2 - 25, 16);  printf("                         ");	// "���ο� ���� �����ɴϴ�." �����
		// �ڽ� �׽�Ʈ BlockBoxing(LENGTH / 2 - (BLOCK_WIDTH + 2) * (4 / 2), 3 + 3);


		Block * selected_Block;		// USER�� guess�� ��
		int choiceNumber = -1;	// USER�� guess�� ��


		do {
			clearChat();
			selected_Block = selectBlock(&c_Block);

			if (selected_Block->revealed == TRUE) {
				gotoP(LENGTH / 2 - 30, 18);  printf("�̹� ������ ���Դϴ�. �ٸ� ���� �����ϼ���.");
				gotoP(LENGTH / 2 - 30, 19);	printf("(����Ϸ��� ����)");
				getchar();
			}
			else
				break;

		} while (TRUE);

		clearChat();
		choiceNumber = choose_guessNumber();

		insert_USER_guess(2 * choiceNumber + selected_Block->color);

		if (selected_Block->number == choiceNumber) {
			selected_Block->revealed = TRUE;
			add_to_known(selected_Block);
			while (TRUE) {
				clearChat();

				gotoP(LENGTH / 2 - 25, 16); printf("������ϴ�. ����Ͻðڽ��ϱ�? [Y/N] : ");
				scanf("%c", &replay);
				while (getchar() != '\n');

				if (replay == 'N' || replay == 'n') {
					gotoP(LENGTH / 2 - 25, 18); printf("������� �ʰڴٰ� ����.");
					replay = FALSE;
					TURN = COM;
					gotoP(LENGTH / 2 - 25, 20); printf("�� ���� �������ϴ�.(����Ϸ��� ����)");
					getchar();
					return;
				}

				else if (replay == 'Y' || replay == 'y') {
					gotoP(LENGTH / 2 - 25, 18); printf("����ϰڴٰ� ����.");
					replay = TRUE;
					TURN = USER;
					gotoP(LENGTH / 2 - 25, 20); printf("(����Ϸ��� ����)");
					getchar();
					return;
				}
			}
		}


		else {
			gotoP(LENGTH / 2 - 25, 16); printf("Ʋ�Ƚ��ϴ�. �̹� ���ʿ� ������ ���� �����մϴ�.");
			gotoP(LENGTH / 2 - 25, 17); printf("(����Ϸ��� ����)");
			newBlock->revealed = TRUE;
			add_to_known(newBlock);
			did_USER_lie(newBlock);
			TURN = COM;
			replay = FALSE;
			getchar();
			return;
		}
	}

	else if (TURN == COM) {

		clearChat();
		showBlocks();
		gotoP(LENGTH / 2 - 10, 13); printf("��ǻ���� �����Դϴ�. ");


		if (replay_COM == FALSE) {      // ��ǻ���� ù ������ ��� draw
			gotoP(LENGTH / 2 - 25, 20); printf("���ο� ���� �����ɴϴ�.\n");
			// ��ǻ�Ͱ� draw�ϴ� �Լ�.
			newBlock = choiceColor_COM(&BlockDeck);
			newBlock->get_turn = ++TURN_num;
			InsertAndSort(&c_Block, newBlock, COM);
		}


		gotoP(LENGTH / 2 - 25, 18); printf("Computer is thinking");
		for (int i = 0; i < 6; i++) {
			if (i < 3) {
				printf(".");
				Sleep(200);
			}
			else {
				printf("\b \b");
				Sleep(200);
			}
		}
		printf("..DONE!");

		int *  rs = guess(&p_Block);

		//gotoP(LENGTH / 2 - 25, 20); printf("�Խ� ���: %d %d %d\n", rs[0], rs[1], rs[2]);

		int choicePosition = rs[0];
		int choiceNumber = rs[1] / 2;
		int computerWantsToGo = rs[2];

		Block * p = dll_getNodeAt(&p_Block, choicePosition);

		if (p->number == choiceNumber) {
			p->revealed = TRUE;
			gotoP(LENGTH / 2 - 25, 20); printf("��ǻ�Ͱ� ����� %d�� ���� ���ڸ� ������ϴ�.", choicePosition);
			add_to_known(p);
			did_USER_lie(p);

			if (!computerWantsToGo) {
				gotoP(LENGTH / 2 - 25, 21); printf("��ǻ�Ͱ� ���ʸ� ��ſ��� �Ѱ���ϴ�.");
				gotoP(LENGTH / 2 - 25, 23); printf("�� ���� �������ϴ�.(����Ϸ��� ����)");
				getchar();
				TURN = USER;
				replay_COM = FALSE;
			}

			else {
				gotoP(LENGTH / 2 - 25, 21); printf("��ǻ�Ͱ� ��� �÷��� �ϰڴٰ� �����߽��ϴ�.");
				gotoP(LENGTH / 2 - 25, 23); printf("(����Ϸ��� ����)");
				getchar();
				TURN = COM;
				replay_COM = TRUE;
			}
		}

		else {
			gotoP(LENGTH / 2 - 25, 20); printf("��ǻ�Ͱ� ����� %d�� ���� \"%d\" �̶� ����������,", choicePosition, choiceNumber);
			gotoP(LENGTH / 2 - 25, 21); printf("Ʋ�Ƚ��ϴ�.", choicePosition, choiceNumber);
			gotoP(LENGTH / 2 - 25, 23); printf("�� ���� �������ϴ�.(����Ϸ��� ����)");
			newBlock->revealed = TRUE;
			add_to_known(newBlock);
			getchar();
			TURN = USER;
			replay_COM = FALSE;
		}
	}
}
int isEndUser(Block * p_Block) {   // ������ �������� �Ǻ�
	Block * p;

	for (p = p_Block->rlink; p != p_Block; p = p->rlink) {
		if (p->revealed == FALSE)
			return FALSE;
	}
	return TRUE;
}
int isEndCom(Block * c_Block) {
	Block * p;
	for (p = c_Block->rlink; p != c_Block; p = p->rlink) {
		if (p->revealed == FALSE) {
			return FALSE;
		}
	}
	return TRUE;
}

int main() {
	//srand((int)time(NULL));
	srand(4);

	SetCursorInvisible();
	system("title Da Vinci Code");
	system("mode con: cols=140 lines=51");
	showEdge();
	showMain();
	init(&USER_guess);

	dq_init(&BlockDeck);
	initDeck();
	dll_init(&p_Block);
	dll_init(&c_Block);

	Sleep(2000);

	CLEAR();
	showEdge();
	showChat();

	for (int i = 0; i < INIT_BLOCK; i++) {   // ó�� �� �����ֱ�(COM)
		int n = rand() % 2;
		if (n == BLACK)
			InsertAndSort(&c_Block, dq_deleteFront(&BlockDeck), COM);
		else if (n == WHITE)
			InsertAndSort(&c_Block, dq_deleteRear(&BlockDeck), COM);
	}
	printHand(&c_Block);


	for (int i = 0; i < INIT_BLOCK; i++) {  // ó�� �� �����ֱ�(USER)
		clearChat();
		gotoP(LENGTH / 2 - 5, 14);	printf("�ʱ� ��ο�");
		InsertAndSort(&p_Block, choiceColor(&BlockDeck), USER);
		printHand(&p_Block);
	}
	printHand(&c_Block);
	// ó�� �� �����ֱ� �Ϸ�

	while (!isEndUser(&p_Block) && !isEndCom(&c_Block)) {
		play();

		if (isEndUser(&p_Block) && isEndCom(&c_Block)) {
			setColor(0, 15);
			clearChat();
			gotoP(LENGTH / 2 - 25, 25);	printf("���º��Դϴ�.");
			gotoP(LENGTH / 2 - 25, 26);
			PAUSE();
			getchar();
			exit(1);
		}
		else if (isEndUser(&p_Block)) {
			setColor(12, 15);
			clearChat();
			gotoP(LENGTH / 2 - 25, 25);	printf("��ǻ�Ͱ� �¸��Ͽ����ϴ�.");
			gotoP(LENGTH / 2 - 25, 26);
			PAUSE();
			getchar();
			exit(1);
		}
		else if (isEndCom(&c_Block)) {
			setColor(9, 15);
			clearChat();
			gotoP(LENGTH / 2 - 25, 25);	printf("����� �¸��Ͽ����ϴ�.");
			gotoP(LENGTH / 2 - 25, 26);
			PAUSE();
			getchar();
			exit(1);
		}

		if (dq_isEmpty(&BlockDeck)) {
			setColor(0, 15);
			clearChat();
			gotoP(LENGTH / 2 - 25, 25);  printf("�� �̻� �̾ƿ� ���� �����ϴ�.");
			gotoP(LENGTH / 2 - 25, 26);  printf("���º��Դϴ�.");
			gotoP(LENGTH / 2 - 25, 27);
			exit(1);
		}
	}
	Sleep(5000);
}