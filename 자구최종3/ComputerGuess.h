extern int user_reliability;
// ���� ���ν����� �� user_reliability�� �ʱ�ȭ���� �ʰ� �״�� ������

extern int LEAST_SCORE_TO_GUESS;                  // guess �ѹ� �� �ϱ����� �ּ� ����ġ
extern int known_block[26];                  // �˷����� ���� ��
													 // 0: �˷���, 1: �˷����� �ʴ�.
													 // �� �� ĭ�� {0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,J,J}�� �ش��Ѵ�.

													 //int USER_guess[13][13] = { { -1,-1 }, };         // USER�� �� guess ���, �ŷڵ������� �����س��°���
													 // [guess_turn][�� �Ͽ� guess�� ����]
													 // �̷��� ���� ���� ���� ť�� ��������.
													 //   -> ������ ���ſ� �� guess�� �����ؾ� �ϹǷ� FIFO�� ����

typedef struct {
	int guess_turn;
	int guess_number;         // ���Ͽ� 3���� guess�ߴٸ� ���� ��� ����
} element;

typedef struct {
	element * queue;
	int front, rear;
} QueueType;

extern QueueType USER_guess;

void init(QueueType *q);
void enqueue(QueueType *q, element item);

//=====================���� ť ��==============================//

void add_to_known(Block* b);
void insert_USER_guess(int guess_num);
void weight_init(Block * OpponentBlock_head);
void weight_add(Block* OpponentBlock_head);
int * weight_getMax(Block* OpponentBlock_head);
void after_guess(Block* OpponentBlock_head, int guess[2]);
int* guess(Block* OpponentBlock_head);
void init_score(Block* b, Block* OpponentBlock_head);
void did_USER_lie(Block* revealed);