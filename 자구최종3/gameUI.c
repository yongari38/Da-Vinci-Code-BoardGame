#include "gameUI.h"
#include "DoubleLinkedList.h"

int TURN;
int TURN_num;
int MAX_QUEUE_SIZE;
//=======������� �Լ�==============================================
//�ؽ�Ʈ, ���� ��� ���� �Լ�
void setColor(int color, int bgcolor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((bgcolor & 0xf) << 4) | (color & 0xf));
}
//�ؽ�Ʈ ���� ���� �Լ�
void setFontColor(int color) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (info.wAttributes & 0xf0) | (color & 0xf));
}
//��� ���� ���� �Լ�
void setBgColor(int bgcolor) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((bgcolor & 0xf) << 4) | (info.wAttributes & 0xf));
}
//�ؽ�Ʈ ���� ȹ�� �Լ�
int getFontColor() {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	return info.wAttributes & 0xf;
}
//��� ���� ȹ�� �Լ�
int getBgColor() {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	return (info.wAttributes & 0xf0) >> 4;
}
//�ؽ�Ʈ �÷� �⺻�� 
__inline void resetFontColor() {
	setFontColor(7);
}
//���� �⺻��
__inline void resetBgColor() {
	setBgColor(0);
}
//�ؽ�Ʈ, ���� �⺻��
__inline void resetColor() {
	setColor(7, 0);
}
//======================================================================
void gotoP(int x, int y) {   // ���� ��ǥ, ���� ��ǥ
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void showEdge() {
	gotoP(0, 0);
	if (MAX_QUEUE_SIZE == HARD)
		setColor(0, 12);
	else if (MAX_QUEUE_SIZE == EASY)
		setColor(0, 14);

	for (int i = 0; i < LENGTH / 2; i++) {
		printf("��");
	}
	for (int i = 1; i < LINES_MAX; i++) {
		gotoP(0, i); printf("��");
		gotoP(LENGTH - 2, i); printf("��");
		//Sleep(1);	�۾Ƴ��� ȿ��
	}
	for (int i = 0; i < LENGTH / 2; i++) {
		printf("��");
	}
	resetColor();
}

void showChat() {

	gotoP(35, 13);
	for (int i = 0; i < 35; i++) {
		printf("��");
	}

	for (int i = 14; i < 38; i++) {
		gotoP(35, i); printf("��");
		gotoP(103, i); printf("��");
	}

	gotoP(35, 38);
	for (int i = 0; i < 35; i++) {
		printf("��");
	}
	// ����� tip
	gotoP(6, 17); printf("������������������������������������������������");
	for (int i = 0; i < 7; i++) {
		gotoP(6, 18 + i); printf("��");   gotoP(6 + 23, 18 + i); printf("��");
	}
	gotoP(8, 19); printf("��: ���� ������ ��");
	gotoP(8, 20); printf("��: ��� ������ ��");

	gotoP(8, 22); printf("���� ��� �����Ǹ�");
	gotoP(8, 23); printf("\t  �й��մϴ�");
	gotoP(6, 24); printf("������������������������������������������������");

	int line = 12;
	gotoP(6, 14 + line); printf("������������������������������������������������");
	for (int i = 0; i < 5; i++) {
		gotoP(6, 15 + line + i); printf("��"); gotoP(6 + 23, 15 + line + i); printf("��");
	}
	gotoP(8, 16 + line); printf("  ���� ��� �����Ǹ�");
	gotoP(8, 17 + line); printf("\t���º��Դϴ�");
	gotoP(8, 18 + line); printf("   ������ �����մϴ�");
	gotoP(6, 20 + line); printf("������������������������������������������������");

	gotoP(LENGTH - 30, 15); printf("������������������������������������������������");
	for (int i = 0; i < 19; i++) {
		gotoP(LENGTH - 30, 16 + i); printf("��");   gotoP(LENGTH - 7, 16 + i); printf("��");
	}
	gotoP(LENGTH - 28, 17); printf("    �ڷᱸ�� 20��");
	gotoP(LENGTH - 28, 18); printf("     Term Project");

	gotoP(LENGTH - 28, 20); printf("  Board Game,");
	gotoP(LENGTH - 28, 21); printf("      'DA VINCI-CODE'");

	gotoP(LENGTH - 28, 23); printf("    <���� �д�>");

	gotoP(LENGTH - 28, 25); printf("��ü ���� �ڵ� ����:");
	gotoP(LENGTH - 28, 26); printf("    2014140419 ������");
	gotoP(LENGTH - 28, 27); printf("    2017320132 �忬��");
	gotoP(LENGTH - 28, 29); printf("��ǻ�� �ǻ���� ����:");
	gotoP(LENGTH - 28, 30); printf("    2017320243 ��ȣ��");
	gotoP(LENGTH - 28, 32); printf("�߰�,�⸻����,��ǥ:");
	gotoP(LENGTH - 28, 33); printf("    2016250053 ����ä");

	gotoP(LENGTH - 30, 35); printf("������������������������������������������������");
}

void clearChat() {
	for (int i = 14; i < 38; i++) {
		for (int j = 37; j < 102; j++) {
			gotoP(j, i); printf(" ");
		}
	}
	//gotoP(14, 38);	// ���� �Է��� ������ �κ����� Ŀ�� �̵�.
}

int showLevel() {
	CLEAR();
	showEdge();

	int i = 5;

	gotoP(LENGTH / 2 - 40, 1 + i); printf("            '##:::::::'########:'##::::'##:'########:'##:::::::        \n");
	gotoP(LENGTH / 2 - 40, 2 + i); printf("             ##::::::: ##.....:: ##:::: ##: ##.....:: ##:::::::        \n");
	gotoP(LENGTH / 2 - 40, 3 + i); printf("             ##::::::: ##::::::: ##:::: ##: ##::::::: ##:::::::        \n");
	gotoP(LENGTH / 2 - 40, 4 + i); printf("             ##::::::: ######::: ##:::: ##: ######::: ##:::::::        \n");
	gotoP(LENGTH / 2 - 40, 5 + i); printf("             ##::::::: ##...::::. ##:: ##:: ##...:::: ##:::::::        \n");
	gotoP(LENGTH / 2 - 40, 6 + i); printf("             ##::::::: ##::::::::. ## ##::: ##::::::: ##:::::::        \n");
	gotoP(LENGTH / 2 - 40, 7 + i); printf("             ########: ########:::. ###:::: ########: ########:        \n");
	gotoP(LENGTH / 2 - 40, 8 + i); printf("            ........::........:::::...:::::........::........::        \n");

	setColor(14, 0);
	gotoP(LENGTH / 2 - 40, 14 + i); printf("                    ������������������������������������������������������������������                \n");
	gotoP(LENGTH / 2 - 40, 15 + i); printf("                    ��                               ��                \n");
	gotoP(LENGTH / 2 - 40, 16 + i); printf("                    ��   .-----.---.-.-----.--.--.   ��                \n");
	gotoP(LENGTH / 2 - 40, 17 + i); printf("                    ��   |  -__|  _  |__ --|  |  |   ��                \n");
	gotoP(LENGTH / 2 - 40, 18 + i); printf("                    ��   |_____|___._|_____|___  |   ��                \n");
	gotoP(LENGTH / 2 - 40, 19 + i); printf("                    ��                     |_____|   ��                \n");
	gotoP(LENGTH / 2 - 40, 20 + i); printf("                    ��                               ��                \n");
	gotoP(LENGTH / 2 - 40, 21 + i); printf("                    ������������������������������������������������������������������                \n");
	setColor(12, 0);
	gotoP(LENGTH / 2 - 40, 24 + i); printf("                                                                      \n");
	gotoP(LENGTH / 2 - 40, 25 + i); printf("                         __                  __                       \n");
	gotoP(LENGTH / 2 - 40, 26 + i); printf("                        |  |--.---.-.----.--|  |                      \n");
	gotoP(LENGTH / 2 - 40, 27 + i); printf("                        |     |  _  |   _|  _  |                      \n");
	gotoP(LENGTH / 2 - 40, 28 + i); printf("                        |__|__|___._|__| |_____|                      \n");
	gotoP(LENGTH / 2 - 40, 29 + i); printf("                                                                      \n");
	gotoP(LENGTH / 2 - 40, 30 + i); printf("                                                                      \n");
	resetColor();
	gotoP(LENGTH / 2 - 40, 35 + i); printf("               ����Ű�� ���� �� Enter �Ǵ� SpaceŰ�� ��������.              \n");

	//while (getch() != 0) getch();	// ��� �Է¹��� ����

	int selectLevel; // ����Ű �޴� ����
	int UD = UP_CHOSEN;         // ����ڰ� ����, �Ʒ��� ���� ���� ����

	while (TRUE) {
		selectLevel = getch();
		if (selectLevel == ENTER || selectLevel == ' ') {
			if (UD == UP_CHOSEN)
				return EASY;
			else if (UD == DOWN_CHOSEN)
				return HARD;
		}
		if (selectLevel == 0 || selectLevel == 0xe0) {
			selectLevel = getch();
			if (selectLevel == UP) { // ���� ����Ű

				UD = UP_CHOSEN;	

				setColor(14,0);
				gotoP(LENGTH / 2 - 40, 14 + i); printf("                    ������������������������������������������������������������������                \n");
				gotoP(LENGTH / 2 - 40, 15 + i); printf("                    ��                               ��                \n");
				gotoP(LENGTH / 2 - 40, 16 + i); printf("                    ��   .-----.---.-.-----.--.--.   ��                \n");
				gotoP(LENGTH / 2 - 40, 17 + i); printf("                    ��   |  -__|  _  |__ --|  |  |   ��                \n");
				gotoP(LENGTH / 2 - 40, 18 + i); printf("                    ��   |_____|___._|_____|___  |   ��                \n");
				gotoP(LENGTH / 2 - 40, 19 + i); printf("                    ��                     |_____|   ��                \n");
				gotoP(LENGTH / 2 - 40, 20 + i); printf("                    ��                               ��                \n");
				gotoP(LENGTH / 2 - 40, 21 + i); printf("                    ������������������������������������������������������������������                \n");
				setColor(12, 0);
				gotoP(LENGTH / 2 - 40, 24 + i); printf("                                                                      \n");
				gotoP(LENGTH / 2 - 40, 25 + i); printf("                         __                  __                       \n");
				gotoP(LENGTH / 2 - 40, 26 + i); printf("                        |  |--.---.-.----.--|  |                      \n");
				gotoP(LENGTH / 2 - 40, 27 + i); printf("                        |     |  _  |   _|  _  |                      \n");
				gotoP(LENGTH / 2 - 40, 28 + i); printf("                        |__|__|___._|__| |_____|                      \n");
				gotoP(LENGTH / 2 - 40, 29 + i); printf("                                                                      \n");
				gotoP(LENGTH / 2 - 40, 30 + i); printf("                                                                      \n");
				resetColor();
				MAX_QUEUE_SIZE = EASY;
				showEdge();
			}
			else if (selectLevel == DOWN) { // �Ʒ��� ����Ű

				UD = DOWN_CHOSEN;
				setColor(14, 0);
				gotoP(LENGTH / 2 - 40, 14 + i); printf("                                                                      \n");
				gotoP(LENGTH / 2 - 40, 15 + i); printf("                                                                      \n");
				gotoP(LENGTH / 2 - 40, 16 + i); printf("                        .-----.---.-.-----.--.--.                     \n");
				gotoP(LENGTH / 2 - 40, 17 + i); printf("                        |  -__|  _  |__ --|  |  |                     \n");
				gotoP(LENGTH / 2 - 40, 18 + i); printf("                        |_____|___._|_____|___  |                     \n");
				gotoP(LENGTH / 2 - 40, 19 + i); printf("                                          |_____|                     \n");
				gotoP(LENGTH / 2 - 40, 20 + i); printf("                                                                      \n");
				gotoP(LENGTH / 2 - 40, 21 + i); printf("                                                                      \n");
				setColor(12, 0);
				gotoP(LENGTH / 2 - 40, 24 + i); printf("                    ������������������������������������������������������������������                \n");
				gotoP(LENGTH / 2 - 40, 25 + i); printf("                    ��    __                  __     ��                  \n");
				gotoP(LENGTH / 2 - 40, 26 + i); printf("                    ��   |  |--.---.-.----.--|  |    ��                 \n");
				gotoP(LENGTH / 2 - 40, 27 + i); printf("                    ��   |     |  _  |   _|  _  |    ��                 \n");
				gotoP(LENGTH / 2 - 40, 28 + i); printf("                    ��   |__|__|___._|__| |_____|    ��                 \n");
				gotoP(LENGTH / 2 - 40, 29 + i); printf("                    ��                               ��                 \n");
				gotoP(LENGTH / 2 - 40, 30 + i); printf("                    ������������������������������������������������������������������                \n");
				resetColor();
				MAX_QUEUE_SIZE = HARD;
				showEdge();
			}
		}
	}
}

int showOrder()
{
	CLEAR();
	showEdge();

	int select;       // ����Ű, ���� ���� ����


	//srand((int)time(NULL));
	int firstLR = rand() % 2;         // ����, ������ �����ϴ� ����� ī�� ���� ����

	int i = 5;


	gotoP(LENGTH / 2 - 40, 1 + i); printf("           :'#######::'########::'########::'########:'########::  \n");
	gotoP(LENGTH / 2 - 40, 2 + i); printf("           '##.... ##: ##.... ##: ##.... ##: ##.....:: ##.... ##:  \n");
	gotoP(LENGTH / 2 - 40, 3 + i); printf("            ##:::: ##: ##:::: ##: ##:::: ##: ##::::::: ##:::: ##:  \n");
	gotoP(LENGTH / 2 - 40, 4 + i); printf("            ##:::: ##: ########:: ##:::: ##: ######::: ########::  \n");
	gotoP(LENGTH / 2 - 40, 5 + i); printf("            ##:::: ##: ##.. ##::: ##:::: ##: ##...:::: ##.. ##:::  \n");
	gotoP(LENGTH / 2 - 40, 6 + i); printf("            ##:::: ##: ##::. ##:: ##:::: ##: ##::::::: ##::. ##::  \n");
	gotoP(LENGTH / 2 - 40, 7 + i); printf("           . #######:: ##::: .##: ########:: ########: ##::: .##:   \n");
	gotoP(LENGTH / 2 - 40, 8 + i); printf("           : .......:: : ..:::: : ..::........:: : ........::..::  \n");

	gotoP(LENGTH / 2 - 40, 14 + i); printf("          ������������������������������������������������   \t ������������������������������������������������   \n");
	gotoP(LENGTH / 2 - 40, 15 + i); printf("          �� /////////////////////��   \t �� /////////////////////��   \n");
	gotoP(LENGTH / 2 - 40, 16 + i); printf("          �� /////////////////////��   \t �� /////////////////////��   \n");
	gotoP(LENGTH / 2 - 40, 17 + i); printf("          �� /////////////////////��   \t �� /////////////////////��   \n");
	gotoP(LENGTH / 2 - 40, 18 + i); printf("          �� /////////////////////��   \t �� /////////////////////��   \n");
	gotoP(LENGTH / 2 - 40, 19 + i); printf("          �� /////////////////////��   \t �� /////////////////////��   \n");
	gotoP(LENGTH / 2 - 40, 20 + i); printf("          �� /////////////////////��   \t �� /////////////////////��   \n");
	gotoP(LENGTH / 2 - 40, 21 + i); printf("          �� /////////////////////��   \t �� /////////////////////��   \n");
	gotoP(LENGTH / 2 - 40, 22 + i); printf("          �� /////////////////////��   \t �� /////////////////////��   \n");
	gotoP(LENGTH / 2 - 40, 23 + i); printf("          �� /////////////////////��   \t �� /////////////////////��   \n");
	gotoP(LENGTH / 2 - 40, 24 + i); printf("          �� /////////////////////��   \t �� /////////////////////��   \n");
	gotoP(LENGTH / 2 - 40, 25 + i); printf("          �� /////////////////////��   \t �� /////////////////////��   \n");
	gotoP(LENGTH / 2 - 40, 26 + i); printf("          �� /////////////////////��   \t �� /////////////////////��   \n");
	gotoP(LENGTH / 2 - 40, 27 + i); printf("          �� /////////////////////��   \t �� /////////////////////��   \n");
	gotoP(LENGTH / 2 - 40, 28 + i); printf("          ������������������������������������������������   \t ������������������������������������������������   \n");

	gotoP(LENGTH / 2 - 40, 31 + i); printf("                      ��             \t                           \n");
	gotoP(LENGTH / 2 - 40, 32 + i); printf("                     ���             \t                           \n");
	gotoP(LENGTH / 2 - 40, 33 + i); printf("                    ����             \t                           \n");

	gotoP(LENGTH / 2 - 40, 36 + i); printf("                 ����Ű�� ���� �� Enter �Ǵ� SpaceŰ�� ��������.         \n");

	//while (getch() != 0) getch();   // ��� �Է¹��� ����

	int LR = LEFT_CHOSEN;         // ����ڰ� ����, ������ ���� ���� ����

	while (TRUE) {
		select = getch();
		if (select == ENTER || select == ' ') {
			if (firstLR == LEFT_CHOSEN) {
				gotoP(LENGTH / 2 - 40, 14 + i); printf("          ������������������������������������������������   \t ������������������������������������������������   \n");
				gotoP(LENGTH / 2 - 40, 15 + i); printf("          ��                      ��   \t ��                      ��   \n");
				gotoP(LENGTH / 2 - 40, 16 + i); printf("          ��                      ��   \t ��                      ��   \n");
				gotoP(LENGTH / 2 - 40, 17 + i); printf("          ��                      ��   \t ��                      ��   \n");
				gotoP(LENGTH / 2 - 40, 18 + i); printf("          ��    #                 ��   \t ��  ####                ��   \n");
				gotoP(LENGTH / 2 - 40, 19 + i); printf("          ��   ##    ####  #####  ��   \t �� #    # #    # #####  ��   \n");
				gotoP(LENGTH / 2 - 40, 20 + i); printf("          ��  # #   #        #    ��   \t ��      # ##   # #    # ��   \n");
				gotoP(LENGTH / 2 - 40, 21 + i); printf("          ��    #    ####    #    ��   \t ��  ####  # #  # #    # ��   \n");
				gotoP(LENGTH / 2 - 40, 22 + i); printf("          ��    #        #   #    ��   \t �� #      #  # # #    # ��   \n");
				gotoP(LENGTH / 2 - 40, 23 + i); printf("          ��    #   #    #   #    ��   \t �� #      #   ## #    # ��   \n");
				gotoP(LENGTH / 2 - 40, 24 + i); printf("          ��  #####  ####    #    ��   \t �� ###### #    # #####  ��   \n");
				gotoP(LENGTH / 2 - 40, 25 + i); printf("          ��                      ��   \t ��                      ��   \n");
				gotoP(LENGTH / 2 - 40, 26 + i); printf("          ��                      ��   \t ��                      ��   \n");
				gotoP(LENGTH / 2 - 40, 27 + i); printf("          ��                      ��   \t ��                      ��   \n");
				gotoP(LENGTH / 2 - 40, 28 + i); printf("          ��                      ��   \t ��                      ��   \n");
				gotoP(LENGTH / 2 - 40, 29 + i); printf("          ������������������������������������������������   \t ������������������������������������������������   \n");
			}
			else if (firstLR == RIGHT_CHOSEN) {
				gotoP(LENGTH / 2 - 40, 14 + i); printf("          ������������������������������������������������   \t ������������������������������������������������   \n");
				gotoP(LENGTH / 2 - 40, 15 + i); printf("          ��                      ��   \t ��                      ��   \n");
				gotoP(LENGTH / 2 - 40, 16 + i); printf("          ��                      ��   \t ��                      ��   \n");
				gotoP(LENGTH / 2 - 40, 17 + i); printf("          ��                      ��   \t ��                      ��   \n");
				gotoP(LENGTH / 2 - 40, 18 + i); printf("          ��  ####                ��   \t ��    #                 ��   \n");
				gotoP(LENGTH / 2 - 40, 19 + i); printf("          �� #    # #    # #####  ��   \t ��   ##    ####  #####  ��   \n");
				gotoP(LENGTH / 2 - 40, 20 + i); printf("          ��      # ##   # #    # ��   \t ��  # #   #        #    ��   \n");
				gotoP(LENGTH / 2 - 40, 21 + i); printf("          ��  ####  # #  # #    # ��   \t ��    #    ####    #    ��   \n");
				gotoP(LENGTH / 2 - 40, 22 + i); printf("          �� #      #  # # #    # ��   \t ��    #        #   #    ��   \n");
				gotoP(LENGTH / 2 - 40, 23 + i); printf("          �� #      #   ## #    # ��   \t ��    #   #    #   #    ��   \n");
				gotoP(LENGTH / 2 - 40, 24 + i); printf("          �� ###### #    # #####  ��   \t ��  #####  ####    #    ��   \n");
				gotoP(LENGTH / 2 - 40, 25 + i); printf("          ��                      ��   \t ��                      ��   \n");
				gotoP(LENGTH / 2 - 40, 26 + i); printf("          ��                      ��   \t ��                      ��   \n");
				gotoP(LENGTH / 2 - 40, 27 + i); printf("          ��                      ��   \t ��                      ��   \n");
				gotoP(LENGTH / 2 - 40, 28 + i); printf("          ��                      ��   \t ��                      ��   \n");
				gotoP(LENGTH / 2 - 40, 29 + i); printf("          ������������������������������������������������   \t ������������������������������������������������   \n");
			}

			if (firstLR == LR) {
				gotoP(LENGTH / 2 - 40, 36 + i); printf("   db    db  .d88b.  db    db        d88888b d888888b d8888b. .d8888. d888888b   \n");
				gotoP(LENGTH / 2 - 40, 37 + i); printf("   `8b  d8' .8P  Y8. 88    88        88'       `88'   88  `8D 88'  YP `~~88~~'   \n");
				gotoP(LENGTH / 2 - 40, 38 + i); printf("    `8bd8'  88    88 88    88        88ooo      88    88oobY' `8bo.      88      \n");
				gotoP(LENGTH / 2 - 40, 39 + i); printf("      88    88    88 88    88        88~~~      88    88`8b     `Y8b.    88      \n");
				gotoP(LENGTH / 2 - 40, 40 + i); printf("      88    `8b  d8' 88b  d88        88        .88.   88 `88. db   8D    88      \n");
				gotoP(LENGTH / 2 - 40, 41 + i); printf("      YP     `Y88P'  ~Y8888P'        YP      Y888888P 88   YD `8888Y'    YP      \n");

				//gotoP(LENGTH / 2 - 40, 38 + i); printf("                             PRESS ANY KEY");
				//getch();

				return USER;
			}
			else {
				gotoP(LENGTH / 2 - 40, 36 + i); printf("    .o88b.  .d88b.  .88b  d88.        d88888b d888888b d8888b. .d8888. d888888b  \n");
				gotoP(LENGTH / 2 - 40, 37 + i); printf("   d8P  Y8 .8P  Y8. 88'YbdP`88        88'       `88'   88  `8D 88'  YP `~~88~~'  \n");
				gotoP(LENGTH / 2 - 40, 38 + i); printf("   8P      88    88 88  88  88        88ooo      88    88oobY' `8bo.      88     \n");
				gotoP(LENGTH / 2 - 40, 39 + i); printf("   8b      88    88 88  88  88        88~~~      88    88`8b     `Y8b.    88     \n");
				gotoP(LENGTH / 2 - 40, 40 + i); printf("   Y8b  d8 `8b  d8' 88  88  88        88        .88.   88 `88. db   8D    88     \n");
				gotoP(LENGTH / 2 - 40, 41 + i); printf("    `Y88P'  `Y88P'  YP  YP  YP        YP      Y888888P 88   YD `8888Y'    YP     \n");

				//gotoP(LENGTH / 2 - 40, 38 + i); printf("                             PRESS ANY KEY");
				//getch();

				return COM;
			}
		}
		if (select == 0 || select == 0xe0) {
			select = getch();
			if (select == LEFT) { // ���� ����Ű

				LR = LEFT_CHOSEN;

				gotoP(LENGTH / 2 - 40, 31 + i); printf("                      ��             \t                           \n");
				gotoP(LENGTH / 2 - 40, 32 + i); printf("                     ���             \t                           \n");
				gotoP(LENGTH / 2 - 40, 33 + i); printf("                    ����             \t                           \n");

				//gotoP(LENGTH / 2 - 40, 36 + i); printf("                 ����Ű�� ���� �� Enter �Ǵ� SpaceŰ�� ��������.         \n");
			}
			else if (select == RIGHT) { // ������ ����Ű

				LR = RIGHT_CHOSEN;

				gotoP(LENGTH / 2 - 40, 31 + i); printf("                                     \t             ��            \n");
				gotoP(LENGTH / 2 - 40, 32 + i); printf("                                     \t            ���            \n");
				gotoP(LENGTH / 2 - 40, 33 + i); printf("                                     \t           ����            \n");

				//gotoP(LENGTH / 2 - 40, 36 + i); printf("                 ����Ű�� ���� �� Enter �Ǵ� SpaceŰ�� ��������.         \n");
			}
		}
	}
}

void showMain() {

	int select;
	int whoIsFirst = 0;

	int i = 5;
	gotoP(LENGTH / 2 - 40, 1 + i); printf("      "); printf(":::::::-.    :::.    :::      .::.::::::.    :::.  .,-:::::  ::: \n");
	gotoP(LENGTH / 2 - 40, 2 + i); printf("      "); printf(" ;;,   `';,  ;;`;;   ';;,   ,;;;' ;;;`;;;;,  `;;;,;;;'````'  ;;; \n");
	gotoP(LENGTH / 2 - 40, 3 + i); printf("      "); printf(" `[[     [[ ,[[ '[[,  \\[[  .[[/   [[[  [[[[[. '[[[[[         [[[ \n");
	gotoP(LENGTH / 2 - 40, 4 + i); printf("      "); printf("  $$,    $$c$$$cc$$$c  Y$c.$$\"    $$$  $$$ \"Y$c$$$$$         $$$ \n");
	gotoP(LENGTH / 2 - 40, 5 + i); printf("      "); printf("  888_,o8P' 888   888,  Y88P      888  888    Y88`88bo,__,o, 888 \n");
	gotoP(LENGTH / 2 - 40, 6 + i); printf("      "); printf("  MMMMP\"`   YMM   \"\"`    MP       MMM  MMM     YM  \"YUMMMMMP\"MMM \n");


	gotoP(LENGTH / 2 - 40, 10 + i); printf("                 "); printf("  .,-:::::     ...    :::::::-.  .,::::::  \n");
	gotoP(LENGTH / 2 - 40, 11 + i); printf("                 "); printf(",;;;'````'  .;;;;;;;.  ;;,   `';,;;;;''''  \n");
	gotoP(LENGTH / 2 - 40, 12 + i); printf("                 "); printf("[[[        ,[[     \\[[,`[[     [[ [[cccc   \n");
	gotoP(LENGTH / 2 - 40, 13 + i); printf("                 "); printf("$$$        $$$,     $$$ $$,    $$ $$\"\"\"\"   \n");
	gotoP(LENGTH / 2 - 40, 14 + i); printf("                 "); printf("`88bo,__,o,\"888,_ _,88P 888_,o8P' 888oo,__ \n");
	gotoP(LENGTH / 2 - 40, 15 + i); printf("                 "); printf("  \"YUMMMMMP\" \"YMMMMMP\"  MMMMP\"`   \"\"\"\"YUMMM ");

	setColor(0, 15);
	gotoP(LENGTH / 2 - 6, 30); printf("  ���� ����  ");
	gotoP(LENGTH / 2 - 6, 33); printf("  ���� ����  ");
	resetColor();

	gotoP(LENGTH / 2 - 9, 30); printf("��");
	gotoP(LENGTH / 2 - 9, 33); printf("  ");

	int chosen = TRUE;

	while (TRUE) {
		select = getch();
		if (select == ENTER || select == ' ') {
			if (chosen == TRUE) {
				MAX_QUEUE_SIZE = showLevel();
				TURN = showOrder();
				// ���� ����
				return;
			}
			else if (chosen == FALSE)
				exit(0);
		}
		if (select == 0 || select == 0xe0) {
			select = getch();
			if (select == UP) { // ���� ����Ű
				chosen = TRUE;
				gotoP(LENGTH / 2 - 9, 30); printf("��");
				gotoP(LENGTH / 2 - 9, 33); printf("  ");
				gotoP(LENGTH, 50);
			}
			else if (select == DOWN) { // �Ʒ��� ����Ű
				chosen = FALSE;
				gotoP(LENGTH / 2 - 9, 30); printf("  ");
				gotoP(LENGTH / 2 - 9, 33); printf("��");
				gotoP(LENGTH, 50);
			}
		}
	}
}

void SetCursorInvisible() {	// Ŀ���� �����ϰ� ����� �Լ�
	HANDLE HCursor = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(HCursor, &info);
}

void printBlock(Block* b, int x, int y) {
	char joker = 'J';
	if (b->color == GREEN)		setColor(0, 10);
	else if (b->color == WHITE)	setColor(0, 15);
	else						setColor(12, 12);	// print red box if wrong color
	gotoP(x, y + 0);		printf("        ");
	gotoP(x, y + 1);
	if (b->number == 12)		printf("    %-4c",  'J');
	else						printf("   %2d   ", b->number);
	gotoP(x, y + 2);		printf("        ");
	gotoP(x, y + 3);
	if (b->revealed == TRUE)	printf("   ��   ");	// ������ ��
	else						printf("        ");
	gotoP(x, y + 4);
	if (b->get_turn == TURN_num)printf("   ��   ");	// �̹��Ͽ� draw�� ��					// �̰� ����� ��� �ȵ�!!!
	else						printf("        ");
	resetColor();
}

void printHand(Block* head) {

	int row;
	if (head == &p_Block) {			// USER �� ���
		row = 40;
		gotoP(LENGTH / 2 - 5, row);	printf("PLAYER HAND");
	}
	else if (head == &c_Block) {	// COM �� ���
		row = 3;
		gotoP(LENGTH / 2 - 5, row);	printf("COMPUTER HAND");
	}
	else {
		printf("printHand�Լ� ����");
	}

	// ���� �� ���� count
	int count = 0;
	for (Block* b = head->rlink; b != head; b = b->rlink) {
		count++;
	}
	// ��� ����.
	int x = LENGTH / 2 - (BLOCK_WIDTH + 2) * (count / 2);		// �Ѻ� �Ҵ�ũ��: (BLOCK_WIDTH + 2), �÷����ϳ�? �Ƹ� �÷����ҵ�.
	int y = 3 + row;
	for (Block *b = head->rlink; b != head; b = b->rlink) {
		if(head==&p_Block||b->revealed==1)	// USER�� �� or COM�� ������ ��
			printBlock(b, x, y);
		else {	// COM�� ����� ��
			if (b->color == GREEN)			setColor(0, 10);
			else if (b->color == WHITE)		setColor(0, 15);
			else							setColor(12, 12);	// print red box if wrong color
			for (int i = 0; i < 5; i++) {
				gotoP(x, y + i);	printf("        ");
			}
			resetColor();
		}

		x += (BLOCK_WIDTH + 2);
	}
}

int whereJoker(Block*head) {
	int count = dll_count(head);
	if (count == 0)
		return 0;
	int index = 0, select;

	int row = 40;

	int x = LENGTH / 2 - (BLOCK_WIDTH + 2) * (count / 2);

	whereJoker_bar(x + (BLOCK_WIDTH + 2)*index, 3 + row);

	while (TRUE) {
		select = getch();


		if (select == 0 || select == 0xe0) {
			select = getch();
			if (select == RIGHT && index < count) { // ������ ����Ű && �����ʳ�
				whereJoker_unbar(x + (BLOCK_WIDTH + 2)*index, 3 + row);	// ������ �����
				index++;
				whereJoker_bar(x + (BLOCK_WIDTH + 2)*index, 3 + row);		// ���� �����
			}
			else if (select == LEFT && index > 0) { // ���� ����Ű && ���ʳ�
				whereJoker_unbar(x + (BLOCK_WIDTH + 2)*index, 3 + row);
				index--;
				whereJoker_bar(x + (BLOCK_WIDTH + 2)*index, 3 + row);
			}
		}
		else if (select == ENTER || select == ' ') {
			whereJoker_unbar(x + (BLOCK_WIDTH + 2)*index, 3 + row); // ������ �����
			return index;
		}
	}

	printf("selectHand�Լ� ����_2\n");
	return NULL;	// �����߻�.
}


int whereWithJoker(int count, int x, int row) {
	if (count == 0)
		return 0;

	int index = 0, select;

	whereJoker_bar(x + (BLOCK_WIDTH + 2)*index, 3 + row);

	while (TRUE) {
		select = getch();

		if (select == 0 || select == 0xe0) {
			select = getch();
			if (select == RIGHT && index < count) { // ������ ����Ű && �����ʳ�
				whereJoker_unbar(x + (BLOCK_WIDTH + 2)*index, 3 + row);   // ������ �����
				index++;
				whereJoker_bar(x + (BLOCK_WIDTH + 2)*index, 3 + row);      // ���� �����
			}
			else if (select == LEFT && index > 0) { // ���� ����Ű && ���ʳ�
				whereJoker_unbar(x + (BLOCK_WIDTH + 2)*index, 3 + row);
				index--;
				whereJoker_bar(x + (BLOCK_WIDTH + 2)*index, 3 + row);
			}
		}
		else if (select == ENTER || select == ' ') {
			whereJoker_unbar(x + (BLOCK_WIDTH + 2)*index, 3 + row); // ������ �����
			return index;
		}
	}
}
void whereJoker_bar(int x, int y) {
	setColor(9,9);
	for (int i = -1; i < 6; i++) {
		gotoP(x - 1 - 1, y +i);	printf("��");
	}
	resetColor();
}
void whereJoker_unbar(int x, int y) {
	for (int i = -1; i < 6; i++) {
		gotoP(x - 1 - 1, y +i);	printf(" ");
	}
}

void BlockBoxing(int x, int y) {
	gotoP(x - 1-1, y - 1);	printf("����������������������");
	// ���̷����ϸ� ��� ��������ϱ�
	//gotoP(x - 1, y + 0);	printf("#       #");
	//gotoP(x - 1, y + 1);	printf("#       #");
	//gotoP(x - 1, y + 2);	printf("#       #");
	//gotoP(x - 1, y + 3);	printf("#       #");
	//gotoP(x - 1, y + 4);	printf("#       #");
	// ���̷��� �Ѵ�
	for (int i = 0; i < 5; i++) {
		gotoP(x - 1-1, y + i);	printf("��");
		gotoP(x + BLOCK_WIDTH, y + i);	printf("��");
	}
	gotoP(x - 1-1, y + 5);	printf("����������������������");
}
void BlockUnboxing(int x, int y) {
	gotoP(x - 1-1, y - 1);	printf("           ");
	for (int i = 0; i < 5; i++) {
		gotoP(x - 1-1, y + i);	printf(" ");
		gotoP(x + BLOCK_WIDTH, y + i);	printf(" ");
	}
	gotoP(x - 1-1, y + 5);	printf("           ");
}

Block* selectBlock(Block*head) {	// output: ���� �� index
	int row;
	if (head == &p_Block) {			// USER �� ���
		row = 40;
	}
	else if (head == &c_Block) {	// COM �� ���
		row = 3;
	}
	else {
		printf("selectHand�Լ� ����");
	}

	// ���� �� ���� count
	int count = dll_count(head);

	int x = LENGTH / 2 - (BLOCK_WIDTH + 2) * (count / 2);

	int index = 0;
	int select;

	BlockBoxing(x + (BLOCK_WIDTH + 2)*index, 3 + row);
	while (TRUE) {
		select = getch();

		
		if (select == 0 || select == 0xe0) {
			select = getch();
			if (select == RIGHT && index < count - 1) { // ������ ����Ű && �����ʳ��� �ƴҶ�
				BlockUnboxing(x + (BLOCK_WIDTH + 2)*index, 3 + row);	// ������ �����
				index++;
				BlockBoxing(x + (BLOCK_WIDTH + 2)*index, 3 + row);		// ���� �����
			}
			else if (select == LEFT && index > 0) { // ���� ����Ű && ���ʳ��� �ƴҶ�
				BlockUnboxing(x + (BLOCK_WIDTH + 2)*index, 3 + row);
				index--;
				BlockBoxing(x + (BLOCK_WIDTH + 2)*index, 3 + row);
			}
		}
		else if (select == ENTER || select == ' ') {
			//BlockUnboxing(x + (BLOCK_WIDTH + 2)*index, 3 + row); // ������ �����
			break;
		}
	}
	

	int find = 0;
	for (Block* b = head->rlink; b != head; b = b->rlink, find++) {
		if (find == index) {
			gotoP(LENGTH / 2 - 10, 13);
			printf("block[%d] ������ �Ϸ�", index);	// ������� �Ϸ����� �˱����� ���
			return b;
		}	
	}

	printf("selectHand�Լ� ����_2\n");
	return NULL;	// �����߻�.
}

int choose_guessNumber() {
	int count = dll_count(&p_Block);
	//BlockBoxing(LENGTH / 2 - (BLOCK_WIDTH + 2) * (count / 2) + (BLOCK_WIDTH + 2)*block_index, 3 + 3);	// ���� ���������� ģ���ϰ� ǥ��.


	int choice = 0;

	gotoP(LENGTH / 2 - 20, 20);
	setColor(0,15);
	printf("0");	// ó�� ���� �Ͼ������ ���. ó�� enter������ �̰� ���õǴϱ�.
	resetColor();
	printf("  1  2  3  4  5  6  7  8  9  10  11  J");
	
	int select;
	//int select = getch();

	while (TRUE) {
		select = getch();
		if (select == 0 || select == 0xe0) {
			select = getch();
			if (select == RIGHT && choice < 12) {		// ������ ����Ű && �����ʳ�
				choice++;
			}
			else if (select == LEFT && choice > 0) {	// ���� ����Ű && ���ʳ�
				choice--;
			}
		}
		else if (select == ENTER || select == ' ') {
			//BlockUnboxing(LENGTH / 2 - (BLOCK_WIDTH + 2) * (count / 2) + (BLOCK_WIDTH + 2)*block_index, 3 + 40);
			return choice;
		}
		gotoP(LENGTH / 2 - 20, 20);

		for (int i = 0; i < 13; i++) {
			if (i == choice) {
				setColor(0, 15);
				if (i == 12)
					printf("J");
				else
					printf("%d", i);
				resetColor();
				printf("  ");
			}
			else {
				if(i == 12)
					printf("J");
				else
					printf("%d  ", i);
			}
		}
	}
}

