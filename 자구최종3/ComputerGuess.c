#include "DavinciCode.h"
#include "ComputerGuess.h"

int user_reliability = 60;
int LEAST_SCORE_TO_GUESS = 100;
int known_block[26] = { 1, };
QueueType USER_guess;

void init(QueueType *q) {      // �ʱ�ȭ �Լ�
	q->front = 0;
	q->rear = 0;
	q->queue = (element*)malloc(sizeof(element) * MAX_QUEUE_SIZE);
	element dummy = { -1,-1 };
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
		q->queue[i] = dummy;   // �� �����Ⱚ �־��ش�
	}
}

void enqueue(QueueType *q, element item) {   // ���� �Լ�
											 // is_full���� �˻����ʿ䰡 ����. ������ ��á���� ������Ҳ��ϱ�
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

//=====================���� ť ��==============================//


void add_to_known(Block* b) {                  // COM�� draw�ϰų� USER�� �а� �������� �� ȣ��
											   // ������ ī����� 1, �ƴѰ� 0
	known_block[2 * b->number + b->color] = 1;
}
void insert_USER_guess(int guess_num) {      // ���ο� guess�� ť�� ����
											 // input: USER�� guess�� number
	element guess;
	guess.guess_turn = TURN;
	guess.guess_number = guess_num;

	enqueue(&USER_guess, guess);
}

void weight_init(Block * head) {      // input: ����(USER)�� �� head

	for (Block* b = head->rlink; b != head; b = b->rlink) {
		if (b->revealed == TRUE) {			// ���� ���� ���� ����ġ ��� 0
			for (int i = 0; i < 26; i++)
				b->score[i] = 0;
		}
		else if (b->revealed == FALSE) {      // ���� ����� ���¸�~
			for (int i = 0; i < 26; i++)      // �� ���� ����ġ�迭�� �̹� �˷��� ����� ����ġ�� 0���� ������ش�
				if (known_block[i] == TRUE)
					b->score[i] = 0;

			// �ٸ� ���� ����� �� 0���� ������ֱ�
			if (b->color == BLACK) {      // Ȧ�� 0 ������ֱ�
				for (int i = 1; i < 26; i += 2)
					b->score[i] = 0;
			}
			else {
				for (int i = 0; i < 26; i += 2)      // ¦�� 0 ������ֱ�
					b->score[i] = 0;
			}
		}
	}
	// ���� USER ���� ������ ������ �������� �Ұ����� ����� ���� ����ġ�� 0���� ������ش�.
	for (Block* b = head->rlink; b != head; b = b->rlink)
	{
		// b�� ������ ���̶�� && ��Ŀ�� �ƴ϶��
		if (b->revealed == TRUE && b->number != 12)
		{
			// �տ��ִ� ������ ����ġ�� ����
			for (Block* front = head->rlink; front != b; front = front->rlink)
				// b ���� '�ڽź��� ū ����� ��' ����ġ 0�����
				for (int i = 2 * b->number + b->color; i < 24; i++)   // i=24,25�� ��Ŀ�ڸ��̹Ƿ� �ǵ帮�� �ʽ��ϴ�
					front->score[i] = 0;

			// �ڿ��ִ� ������ ����ġ�� ����
			for (Block* back = b->rlink; back != head; back = back->rlink)
				// b ���� '�ڽź��� ���� ����� ��' ����ġ 0�����
				for (int i = 0; i <= 2 * b->number + b->color; i++)
					back->score[i] = 0;
		}
	}
}
void weight_add(Block* OpponentBlock_head) {

	// ���� ������ �� current_block, current_block2 ������ count���� ������ ����ġ ������
	for (Block* current_block = OpponentBlock_head->rlink; current_block != OpponentBlock_head; current_block = current_block->rlink)
	{
		if (current_block->revealed == FALSE)
		{
			int count = 0;
			for (int i = 0; i < 26; i++)
				if (current_block->score[i] != 0) count++;      // final candidatesd���� ����ġ�� ���������� �Ϸ��� �켱 ����� �˾ƾ�

			for (int i = 0; i < 26; i++)
				if (current_block->score[i] != 0)            // ����ġ�� 0�� �ƴϸ�~
				{
					int is_it_recent_guess = 0;      // 1: ��� turn USER�� guess�̴�.
													 // 0: �ƴϴ�.

					int index = USER_guess.rear;
					do {
						if (USER_guess.queue[index].guess_number == current_block->number) {
							is_it_recent_guess = 1;
						}
						index--;
					} while (USER_guess.queue[index].guess_turn == USER_guess.queue[USER_guess.rear].guess_turn);
					// ����� �� guess ���� �˻�
					if (is_it_recent_guess)         // USER�� ��� guess�� number��
						current_block->score[i] += (100 - user_reliability) / count;
					else                     // �ƴϸ�
						current_block->score[i] += (user_reliability) / count;

				}
		}
	}
}

int* weight_getMax(Block* OpponentBlock_head) {      // ����ġ�� ���� ū guess �� ã�� ����

	int * output = (int *)malloc(sizeof(int) * 3);                  // [position][guess_number][score]
	output[0] = output[1] = output[2] = -1;

	int index_of_max = 0;
	for (Block* current_block = OpponentBlock_head->rlink; current_block != OpponentBlock_head; current_block = current_block->rlink) {
		for (int i = 0; i < 26; i++) {
			if (current_block->score[i] > output[2]) {
				output[0] = index_of_max;
				output[1] = i;
				output[2] = current_block->score[i];
			}
		}
		index_of_max++;
	}
	return output;
}


void after_guess(Block* OpponentBlock_head, int guess[2]) {         // guess�� ������ �� ������ �� ����� ���� �����ִ� �Լ�
																	// input: p_head, [index_of_max][guess_number(0~25)]
	Block* block_of_guess;
	int i = 0;
	for (block_of_guess = OpponentBlock_head->rlink; i < guess[0]; i++)
		block_of_guess = block_of_guess->rlink;

	block_of_guess->score[guess[1]] = 0;
}

int* guess(Block* OpponentBlock_head) {            // COM�� ���ʿ� ��ο� ���� ȣ��
												   // input: ������ �� head

	weight_init(OpponentBlock_head);                  // initial candidates
	weight_add(OpponentBlock_head);               // reliability�� ����� ����ġ�� �����ִ� �Լ�
												  // int max[3] = guess_getMax(OpponentBlock_head);   // [position][guess_number][score]
	int* max;                              // [position][guess_number][score]
	max = weight_getMax(OpponentBlock_head);
	int guess1[2] = { max[0] ,max[1] };            // [position][guess_number]
	after_guess(OpponentBlock_head, guess1);      // guess�� ������ �� ������ �� ����� ���� �����ִ� �Լ�

												  // ����ؼ� guess ���� ����
	int * result = (int*)malloc(sizeof(int) * 3);
	result[0] = max[0];
	result[1] = max[1];
	result[2] = 0;                            // [position][guess_number][repeat?]

	weight_init(OpponentBlock_head);
	weight_add(OpponentBlock_head);

	int* max2;                              // [position][guess_number][score]
	max2 = weight_getMax(OpponentBlock_head);

	LEAST_SCORE_TO_GUESS = max[2]+20;
	if (max2[2] >= LEAST_SCORE_TO_GUESS)         // �� ���� ū ����ġ���� LEAST_SCORE_TO_GUESS �̻��� ��츸
		result[2] = 1;  

	return result;
}

void init_score(Block* b, Block* OpponentBlock_head) {   // USER�� ���ο� ����� �̾��� �� ȣ��
													// input: ���� ���� ��
													// USER�� draw�� ���� ������ ���� ������ ������ ���
	int score = 0;
	int count = 0;
	for (Block* current_block = OpponentBlock_head->rlink; current_block != OpponentBlock_head; current_block = current_block->rlink) {
		for (int i = 0; i < 26; i++) {
			if (current_block->score[i] != 0) {
				score += current_block->score[i];
				count++;
			}
		}
	}
	for (int i = 0; i < 26; i++)
		b->score[i] = score / count;               // int���� �Ҽ��� ���������� �������� ��������?
	b->get_turn = TURN_num;
}

void did_USER_lie(Block* revealed) {            // COM�� USER�� �и� ���缭 �ո��� ���� �� ȣ���ؼ� �˻�
												// USER�� guess�ߴµ� Ʋ���� �� �Ͽ� ��ο��� ���� �������� ���� ȣ��????
												// input: �̹��� ���缭 ������ ��
	int index = USER_guess.rear;
	do {
		if (USER_guess.queue[index].guess_number == revealed->number) {      // ���� ������ ���� number�� USER�� guess�� number�߿� �ִٸ�
			if (revealed->get_turn <= USER_guess.queue[index].guess_turn)   // ���� ������ ���� ��ο��� ���Ŀ� guess�� �ѰŶ��
				user_reliability--;                                 // ������� ���ϰ� ������ ����.
			else
				user_reliability++;
		}
		index--;
	} while (USER_guess.queue[index].guess_turn != USER_guess.queue[USER_guess.rear].guess_turn);
	// ����� �� guess ���� �˻�
	// ���� ������ ���� number�� USER�� guess�� number�߿� ���ٸ�, �ƹ��͵� ����
}