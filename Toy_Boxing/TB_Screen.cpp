#include <windows.h>
#include <iostream>
#include <stdio.h>
#include "TB_Head.h"
#include "character.h"
#include <curses.h>

char space[BUFFSIZE] = " ";
char line[BUFFSIZE] = "-";
#define colorBlack 1
#define colorWhite 5

int maxX, maxY;

/*���݂̃J�����g�f�B���N�g���擾*/
void getCurrentDirectory(char* currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}

/*char�ǂݍ���*/
bool readChar(const char* section, const char* keyword, const char* defaultValue, char* returnValue, const char* filePath) {
	if (GetPrivateProfileString(section, keyword, defaultValue, returnValue, CHARBUFF, filePath) != 0) {
		return true;
	}
	else {
		return false;
	}
}

/*CSV�ǂݍ���*/
void readCSV(charaInf* player1, charaInf* player2) {
	FILE* fp;
	char s[BUFFSIZE];
	errno_t error;
	char currentDirectory[CHARBUFF];
	getCurrentDirectory(currentDirectory);
	char iniFile[CHARBUFF];
	sprintf_s(iniFile, "input");
	char filename[CHARBUFF];
	sprintf_s(filename, "filename");
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\setting.ini", currentDirectory);
	char keyValue[CHARBUFF];
	if (readChar(iniFile, filename, "none", keyValue, settingFile) == false) {
		fprintf_s(stderr, "failed to open");
	}
	error = fopen_s(&fp, keyValue, "r");
	/*�f�[�^�̓ǂݍ���*/
	int line = 1;
	if (error != 0) {
		fprintf_s(stderr, "failed to open");
	}
	else {
		while (fgets(s, BUFFSIZE, fp) != NULL) {
			char delim[] = ",";
			if (line == 1) {
				line = line + 1;
			}
			else if (line == 2) {
				char* ctx;
				char* p1;
				p1 = strtok_s(s, delim, &ctx);
				p1 = strtok_s(NULL, delim, &ctx);
				player1->playerNum = atoi(p1);
				p1 = strtok_s(NULL, delim, &ctx);
				player1->punchingL = atoi(p1);
				p1 = strtok_s(NULL, delim, &ctx);
				player1->punchingR = atoi(p1);
				p1 = strtok_s(NULL, delim, &ctx);
				player1->colorNum = atoi(p1);
				p1 = strtok_s(NULL, delim, &ctx);
				player1->punchL1 = atoi(p1);
				p1 = strtok_s(NULL, delim, &ctx);
				player1->punchL2 = atoi(p1);
				p1 = strtok_s(NULL, delim, &ctx);
				player1->punchR1 = atoi(p1);
				p1 = strtok_s(NULL, delim, &ctx);
				player1->punchR2 = atoi(p1);
				p1 = strtok_s(NULL, delim, &ctx);
				player1->winTime = atoi(p1);
				line = line + 1;
			}
			else if (line == 3) {
				char* ctx;
				char* p1;
				p1 = strtok_s(s, delim, &ctx);
				p1 = strtok_s(NULL, delim, &ctx);
				player2->playerNum = atoi(p1);
				p1 = strtok_s(NULL, delim, &ctx);
				player2->punchingL = atoi(p1);
				p1 = strtok_s(NULL, delim, &ctx);
				player2->punchingR = atoi(p1);
				p1 = strtok_s(NULL, delim, &ctx);
				player2->colorNum = atoi(p1);
				p1 = strtok_s(NULL, delim, &ctx);
				player2->punchL1 = atoi(p1);
				p1 = strtok_s(NULL, delim, &ctx);
				player2->punchL2 = atoi(p1);
				p1 = strtok_s(NULL, delim, &ctx);
				player2->punchR1 = atoi(p1);
				p1 = strtok_s(NULL, delim, &ctx);
				player2->punchR2 = atoi(p1);
				p1 = strtok_s(NULL, delim, &ctx);
				player2->winTime = atoi(p1);
				line = line + 1;
			}
		}
		fclose(fp);
	}
}

/*�Q�[�����ʏo��*/
void printGameResult(charaInf* player1, charaInf* player2) {
	FILE* fp;
	errno_t error;
	char currentDirectory[CHARBUFF];
	getCurrentDirectory(currentDirectory);
	char iniFile[CHARBUFF];
	sprintf_s(iniFile, "output");
	char filename[CHARBUFF];
	sprintf_s(filename, "filename");
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\setting.ini", currentDirectory);
	char keyValue[CHARBUFF];
	if (readChar(iniFile, filename, "none", keyValue, settingFile) == false) {
		fprintf_s(stderr, "failed to open");
	}
	error = fopen_s(&fp, keyValue, "w");
	if (error != 0) {
		fprintf_s(stderr, "failed to open");
	}
	else {
		int player1PunchNum = player1->punchL1 + player1->punchL2 + player1->punchR1 + player1->punchR2;
		int player2PunchNum = player2->punchL1 + player2->punchL2 + player2->punchR1 + player2->punchR2;
		fprintf(fp, "�v���C���[���,���p���`��,���p���`��,�E�p���`��,�E�p���`��,�p���`���v,������\n");
		fprintf(fp, "player1,%d,%d,%d,%d,%d,%d\n", player1->punchL1, player1->punchL2,
			player1->punchR1, player1->punchR2, player1PunchNum, player1->winTime);
		fprintf(fp, "player2,%d,%d,%d,%d,%d,%d\n", player2->punchL1, player2->punchL2,
			player2->punchR1, player2->punchR2, player2PunchNum, player2->winTime);
		fclose(fp);
	}
}

/*�A���t�@�x�b�g���w�肳�ꂽ�F�ŕ\���@*/
void print_alph(int x, int y, int colorNum, int alphNum) {
	unsigned char cbit;	/*����r�b�g*/
	int tx, ty;
	for (ty = 0; ty < 8; ty++) {
		cbit = 0x80;	/*����r�b�g��8�r�b�g�̍ŏ��*/
		for (tx = 0; tx < 8; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((alphabet[alphNum][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				draw_point((x * 8 + tx), (y * 8 + ty), colorNum);	/*�w�肳�ꂽ�F�ŕ`��*/
			}
			else {	/*0�̏ꍇ*/
				draw_point((x * 8 + tx), (y * 8 + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
}

/*�������w�肳�ꂽ�F�ŕ\��*/
void print_number(int x, int y, int colorNum, int numberNum) {
	unsigned char cbit;	/*����r�b�g*/
	int tx, ty;
	for (ty = 0; ty < 8; ty++) {
		cbit = 0x80;	/*����r�b�g��8�r�b�g�̍ŏ��*/
		for (tx = 0; tx < 8; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((number[numberNum][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				draw_point((x * 8 + tx), (y * 8 + ty), colorNum);	/*�w�肳�ꂽ�F�ŕ`��*/
			}
			else {	/*0�̏ꍇ*/
				draw_point((x * 8 + tx), (y * 8 + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
}

/*�w�肵�����W�Ɏw�肳�ꂽ�F�ŕ`��*/
void draw_point(int x, int y, int color) {
	attrset(COLOR_PAIR(color));
	mvaddstr(y, x, space);	/*(x, y)��color�ŕ`��*/
}


/*A�_��*/
void Aflashing() {
	char A[BUFFSIZE] = "A";
	for (int i = 0; i < 4; i++) {
		attrset(COLOR_PAIR(2));
		for (int i = 0; i < 3; i++) {
			mvaddstr(20, 30 + i, space);
		}
		mvaddstr(21, 30, space);
		mvaddstr(21, 31, A);
		mvaddstr(21, 32, space);
		for (int i = 0; i < 3; i++) {
			mvaddstr(22, 30 + i, space);
		}
		refresh();
		Sleep(100);
		attrset(COLOR_PAIR(5));
		for (int i = 0; i < 3; i++) {
			mvaddstr(20, 30 + i, space);
		}
		mvaddstr(21, 30, space);
		mvaddstr(21, 31, A);
		mvaddstr(21, 32, space);
		for (int i = 0; i < 3; i++) {
			mvaddstr(22, 30 + i, space);
		}
		refresh();
		Sleep(100);
	}
}

/*�J�E���g�_�E��*/
void countdown() {
	erase();
	print_number(7, 1, 2, 2);
	refresh();
	Sleep(1000);
	erase();
	print_number(7, 1, 2, 1);
	refresh();
	Sleep(1000);
	erase();
	print_number(7, 1, 2, 0);
	refresh();
	Sleep(1000);
	erase();
	print_alph(5, 1, 2, 5);
	print_alph(6, 1, 2, 8);
	print_alph(7, 1, 2, 6);
	print_alph(8, 1, 2, 7);
	print_alph(9, 1, 2, 19);
	refresh();
	Sleep(500);
}

/*1P���w�肳�ꂽ�F�ŕ\��*/
void print_char1P(charaInf* player1) {
	unsigned char cbit;	/*����r�b�g*/
	int tx, ty;
	/*��*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((charPart1P[0][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				draw_point((player1->X + tx), (player1->Y + ty), player1->colorNum);	/*�w�肳�ꂽ�F�ŕ`��*/
			}
			else {	/*0�̏ꍇ*/
				draw_point((player1->X + tx), (player1->Y + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
	/*�E��*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((charPart1P[1][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				if (player1->punchingR == 1) {
					draw_point((player1->X + 7 + tx), (player1->Y - 4 + ty), player1->colorNum);	/*�w�肳�ꂽ�F�ŕ`��*/
				}
				else {
					draw_point((player1->X + 7 + tx), (player1->Y - 4 + ty), colorWhite);	/*�w�肳�ꂽ�F�ŕ`��*/
				}
			}
			else {	/*0�̏ꍇ*/
				draw_point((player1->X + 7 + tx), (player1->Y - 4 + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
	/*����*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((charPart1P[2][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				if (player1->punchingL == 1) {
					draw_point((player1->X - 7 + tx), (player1->Y - 4 + ty), player1->colorNum);	/*�w�肳�ꂽ�F�ŕ`��*/
				}
				else {
					draw_point((player1->X - 7 + tx), (player1->Y - 4 + ty), colorWhite);	/*���F�ŕ`��*/
				}
			}
			else {	/*0�̏ꍇ*/
				draw_point((player1->X - 7 + tx), (player1->Y - 4 + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
}

/*2P���w�肳�ꂽ�F�ŕ\��*/
void print_char2P(charaInf* player2) {
	unsigned char cbit;	/*����r�b�g*/
	int tx, ty;
	/*��*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((charPart2P[0][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				draw_point((player2->X + tx), (player2->Y + ty), player2->colorNum);	/*�w�肳�ꂽ�F�ŕ`��*/
			}
			else {	/*0�̏ꍇ*/
				draw_point((player2->X + tx), (player2->Y + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
	/*�E��*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((charPart2P[1][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				if (player2->punchingR == 1) {
					draw_point((player2->X + 7 + tx), (player2->Y + 4 + ty), player2->colorNum);	/*�w�肳�ꂽ�F�ŕ`��*/
				}
				else {
					draw_point((player2->X + 7 + tx), (player2->Y + 4 + ty), colorWhite);	/*���F�ŕ`��*/
				}
			}
			else {	/*0�̏ꍇ*/
				draw_point((player2->X + 7 + tx), (player2->Y + 4 + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
	/*����*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((charPart2P[2][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				if (player2->punchingL == 1) {
					draw_point((player2->X - 7 + tx), (player2->Y + 4 + ty), player2->colorNum);	/*�w�肳�ꂽ�F�ŕ`��*/
				}
				else {
					draw_point((player2->X - 7 + tx), (player2->Y + 4 + ty), colorWhite);	/*���F�ŕ`��*/
				}
			}
			else {	/*0�̏ꍇ*/
				draw_point((player2->X - 7 + tx), (player2->Y + 4 + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
}

/*1P���p���`�@����*/
void player1PunchL1(charaInf* player1) {
	int tx, ty;
	unsigned char cbit;	/*����r�b�g*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((charPart1P[2][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				draw_point((player1->X - 7 + tx), (player1->Y - 4 + ty), colorBlack);	/*���F�ŕ`��*/
			}
			else {	/*0�̏ꍇ*/
				draw_point((player1->X - 7 + tx), (player1->Y - 4 + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((charPart1P[2][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				draw_point((player1->X - 7 + tx), (player1->Y - 9 + ty), player1->colorNum);	/*�w�肳�ꂽ�F�ŕ`��*/
			}
			else {	/*0�̏ꍇ*/
				draw_point((player1->X - 7 + tx), (player1->Y - 9 + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
	refresh();
	Sleep(100);
}

/*1P���p���`�@���*/
void player1PunchL2(charaInf* player1) {
	int tx, ty;
	unsigned char cbit;	/*����r�b�g*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((charPart1P[2][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				draw_point((player1->X - 7 + tx), (player1->Y - 4 + ty), colorBlack);	/*���F�ŕ`��*/
			}
			else {	/*0�̏ꍇ*/
				draw_point((player1->X - 7 + tx), (player1->Y - 4 + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((charPart1P[2][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				draw_point((player1->X - 7 + tx), (player1->Y - 5 + ty), player1->colorNum);	/*�w�肳�ꂽ�F�ŕ`��*/
			}
			else {	/*0�̏ꍇ*/
				draw_point((player1->X - 7 + tx), (player1->Y - 5 + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
	refresh();
	Sleep(100);
}

/*1P�E�p���`�@����*/
void player1PunchR1(charaInf* player1) {
	int tx, ty;
	unsigned char cbit;	/*����r�b�g*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((charPart1P[1][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				draw_point((player1->X + 7 + tx), (player1->Y - 4 + ty), colorBlack);	/*���F�ŕ`��*/
			}
			else {	/*0�̏ꍇ*/
				draw_point((player1->X + 7 + tx), (player1->Y - 4 + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((charPart1P[1][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				draw_point((player1->X + 7 + tx), (player1->Y - 9 + ty), player1->colorNum);	/*�w�肳�ꂽ�F�ŕ`��*/
			}
			else {	/*0�̏ꍇ*/
				draw_point((player1->X + 7 + tx), (player1->Y - 9 + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
	refresh();
	Sleep(100);
}

/*1P�E�p���`�@���*/
void player1PunchR2(charaInf* player1) {
	int tx, ty;
	unsigned char cbit;	/*����r�b�g*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((charPart1P[1][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				draw_point((player1->X + 7 + tx), (player1->Y - 4 + ty), colorBlack);	/*���F�ŕ`��*/
			}
			else {	/*0�̏ꍇ*/
				draw_point((player1->X + 7 + tx), (player1->Y - 4 + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((charPart1P[1][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				draw_point((player1->X + 7 + tx), (player1->Y - 5 + ty), player1->colorNum);	/*�w�肳�ꂽ�F�ŕ`��*/
			}
			else {	/*0�̏ꍇ*/
				draw_point((player1->X + 7 + tx), (player1->Y - 5 + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
	refresh();
	Sleep(100);
}

/*2P���p���`�@����*/
void player2PunchL1(charaInf* player2) {
	int tx, ty;
	unsigned char cbit;	/*����r�b�g*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((charPart2P[2][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				draw_point((player2->X - 7 + tx), (player2->Y + 4 + ty), colorBlack);	/*���F�ŕ`��*/
			}
			else {	/*0�̏ꍇ*/
				draw_point((player2->X - 7 + tx), (player2->Y + 4 + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((charPart2P[2][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				draw_point((player2->X - 7 + tx), (player2->Y + 9 + ty), player2->colorNum);	/*�w�肳�ꂽ�F�ŕ`��*/
			}
			else {	/*0�̏ꍇ*/
				draw_point((player2->X - 7 + tx), (player2->Y + 9 + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
	refresh();
	Sleep(100);
}

/*2P���p���`�@���*/
void player2PunchL2(charaInf* player2) {
	int tx, ty;
	unsigned char cbit;	/*����r�b�g*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((charPart2P[2][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				draw_point((player2->X - 7 + tx), (player2->Y + 4 + ty), colorBlack);	/*���F�ŕ`��*/
			}
			else {	/*0�̏ꍇ*/
				draw_point((player2->X - 7 + tx), (player2->Y + 4 + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((charPart2P[2][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				draw_point((player2->X - 7 + tx), (player2->Y + 5 + ty), player2->colorNum);	/*�w�肳�ꂽ�F�ŕ`��*/
			}
			else {	/*0�̏ꍇ*/
				draw_point((player2->X - 7 + tx), (player2->Y + 5 + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
	refresh();
	Sleep(100);
}

/*2P�E�p���`�@����*/
void player2PunchR1(charaInf* player2) {
	int tx, ty;
	unsigned char cbit;	/*����r�b�g*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((charPart2P[1][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				draw_point((player2->X + 7 + tx), (player2->Y + 4 + ty), colorBlack);	/*���F�ŕ`��*/
			}
			else {	/*0�̏ꍇ*/
				draw_point((player2->X + 7 + tx), (player2->Y + 4 + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((charPart2P[1][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				draw_point((player2->X + 7 + tx), (player2->Y + 9 + ty), player2->colorNum);	/*�w�肳�ꂽ�F�ŕ`��*/
			}
			else {	/*0�̏ꍇ*/
				draw_point((player2->X + 7 + tx), (player2->Y + 9 + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
	refresh();
	Sleep(100);
}

/*2P�E�p���`�@���*/
void player2PunchR2(charaInf* player2) {
	int tx, ty;
	unsigned char cbit;	/*����r�b�g*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((charPart2P[1][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				draw_point((player2->X + 7 + tx), (player2->Y + 4 + ty), colorBlack);	/*���F�ŕ`��*/
			}
			else {	/*0�̏ꍇ*/
				draw_point((player2->X + 7 + tx), (player2->Y + 4 + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*�r�b�g�ʒu�̔���*/
			if ((charPart2P[1][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
				draw_point((player2->X + 7 + tx), (player2->Y + 5 + ty), player2->colorNum);	/*�w�肳�ꂽ�F�ŕ`��*/
			}
			else {	/*0�̏ꍇ*/
				draw_point((player2->X + 7 + tx), (player2->Y + 5 + ty), colorBlack);	/*���ŕ`��*/
			}
			cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
		}
	}
	refresh();
	Sleep(100);
}

/*1P�p���C���\��*/
void printLine1P(int colorNum) {
	int lx;
	attrset(COLOR_PAIR(colorNum));
	for (lx = 0; lx < maxX; lx++) {
		mvaddstr(maxY-1, lx, line);
	}
}

/*2P�p���C���\��*/
void printLine2P(int colorNum) {
	int lx;
	attrset(COLOR_PAIR(colorNum));
	for (lx = 0; lx < maxX; lx++) {
		mvaddstr(0, lx, line);
	}
}

/*1P�p���C���_��*/
void line1Pflashing() {
	for (int i = 0; i < 4; i++) {
		printLine1P(7);
		refresh();
		Sleep(100);
		printLine1P(4);
		refresh();
		Sleep(100);
	}
}

/*2P�p���C���_��*/
void line2Pflashing() {
	for (int i = 0; i < 4; i++) {
		printLine2P(6);
		refresh();
		Sleep(100);
		printLine2P(4);
		refresh();
		Sleep(100);
	}
}

/*�����ݒ�*/
void standby(charaInf* player1, charaInf* player2) {
	getmaxyx(stdscr, maxY, maxX);
	colorMake();
	player1->X = int(maxX / 2) - 3;
	player1->Y = int(maxY / 2) + 5;
	player2->X = int(maxX / 2) - 3;
	player2->Y = int(maxY / 2) - 8;
	readCSV(player1, player2);
}

/*�\������F�ݒ�*/
void colorMake() {
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_RED);
	init_pair(3, COLOR_BLACK, COLOR_BLUE);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);
	init_pair(6, COLOR_RED, COLOR_BLACK);
	init_pair(7, COLOR_BLUE, COLOR_BLACK);
}

/*�Q�[�����[�h*/
void gameMode(charaInf* player1, charaInf* player2) {
	while (true) {
		int key;
		noecho();
		cbreak();
		keypad(stdscr, TRUE);
		key = getch();
		if ((player1->Y <= maxY - 4) && (player2->Y >= 1)) {
			/*1P���p���`*/
			if (key == 'a') {
				player1->punchingL = 1;
				player1->punchingR = 0;
				if (player2->punchingL == 0) {
					/*���p���`�@��*/
					player1PunchL1(player1);
					player2->Y = player2->Y - 2;
					player1->Y = player1->Y - 2;
					player1->punchL1 = player1->punchL1 + 1;
				}
				else {
					/*���p���`�@��*/
					player1PunchL2(player1);
					player2->Y = player2->Y - 1;
					player1->Y = player1->Y - 1;
					player1->punchL2 = player1->punchL2 + 1;
				}
			}
			/*1P�E�p���`*/
			else if (key == 's') {
				player1->punchingR = 1;
				player1->punchingL = 0;
				if (player2->punchingR == 0) {
					/*�E�p���`�@��*/
					player1PunchR1(player1);
					player2->Y = player2->Y - 2;
					player1->Y = player1->Y - 2;
					player1->punchR1 = player1->punchR1 + 1;
				}
				else {
					/*�E�p���`�@��*/
					player1PunchR2(player1);
					player2->Y = player2->Y - 1;
					player1->Y = player1->Y - 1;
					player1->punchR2 = player1->punchR2 + 1;
				}
			}
			/*2P���p���`*/
			else if (key == 'k') {
				player2->punchingL = 1;
				player2->punchingR = 0;
				if (player1->punchingL == 0) {
					/*���p���`�@��*/
					player2PunchL1(player2);
					player1->Y = player1->Y + 2;
					player2->Y = player2->Y + 2;
					player2->punchL1 = player2->punchL1 + 1;
				}
				else {
					/*���p���`�@��*/
					player2PunchL2(player2);
					player1->Y = player1->Y + 1;
					player2->Y = player2->Y + 1;
					player2->punchL2 = player2->punchL2 + 1;
				}
			}
			/*2P�E�p���`*/
			else if (key == 'l') {
				player2->punchingR = 1;
				player2->punchingL = 0;
				if (player1->punchingR == 0) {
					/*�E�p���`�@��*/
					player2PunchR1(player2);
					player1->Y = player1->Y + 2;
					player2->Y = player2->Y + 2;
					player2->punchR1 = player2->punchR1 + 1;
				}
				else {
					/*�E�p���`�@��*/
					player2PunchR2(player2);
					player1->Y = player1->Y + 1;
					player2->Y = player2->Y + 1;
					player2->punchR2 = player2->punchR2 + 1;
				}
			}
		}
		screen2(player1, player2);
		/*�ǂ��炩�����C�����z����*/
		/*2P����*/
		if (player1->Y > maxY - 4) {
			line1Pflashing();
			player2->winTime = player2->winTime + 1;
			break;  /*�Q�[���I��*/
		}
		/*1P����*/
		else if (player2->Y < 1) {
			line2Pflashing();
			player1->winTime = player1->winTime + 1;
			break;  /*�Q�[���I��*/
		}
	}
}

/*��ʂP�@�J�n���*/
void screen1() {
	erase();
	/*TOY BOXING�\��*/
	print_alph(2, 1, 2, 19);
	print_alph(3, 1, 2, 14);
	print_alph(4, 1, 2, 24);
	print_alph(5, 1, 2, 26);
	print_alph(6, 1, 2, 1);
	print_alph(7, 1, 2, 14);
	print_alph(8, 1, 2, 23);
	print_alph(9, 1, 2, 8);
	print_alph(10, 1, 2, 13);
	print_alph(11, 1, 2, 6);

	attrset(COLOR_PAIR(5));
	for (int i = 0; i < 3; i++) {
		mvaddstr(20, 30+i, space);
	}
	char A[BUFFSIZE] = "A";
	mvaddstr(21, 30, space);
	mvaddstr(21, 31, A);
	mvaddstr(21, 32, space);
	for (int i = 0; i < 3; i++) {
		mvaddstr(22, 30+i, space);
	}
	attrset(COLOR_PAIR(1));
	char START[BUFFSIZE] = "START GAME";
	mvaddstr(21, (int(maxX/2)-5), START);
	refresh();
}

/*��ʂQ�@�Q�[�����*/
void screen2(charaInf* player1, charaInf* player2) {
	erase();
	printLine1P(4);
	printLine2P(4);
	print_char1P(player1);
	print_char2P(player2);
	refresh();
}

/*��ʂR�@2P�������*/
void screen3() {
	erase();
	print_number(4, 1, 3, 1);
	print_alph(5, 1, 3, 15);
	print_alph(6, 1, 3, 26);
	print_alph(7, 1, 3, 22);
	print_alph(8, 1, 3, 8);
	print_alph(9, 1, 3, 13);
	attrset(COLOR_PAIR(5));
	for (int i = 0; i < 3; i++) {
		mvaddstr(20, 30 + i, space);
	}
	char Q[BUFFSIZE] = "Q";
	mvaddstr(21, 30, space);
	mvaddstr(21, 31, Q);
	mvaddstr(21, 32, space);
	for (int i = 0; i < 3; i++) {
		mvaddstr(22, 30 + i, space);
	}
	attrset(COLOR_PAIR(1));
	char END[BUFFSIZE] = "END GAME";
	mvaddstr(21, (int(maxX / 2) - 5), END);
	refresh();
}

/*��ʂS�@1P�������*/
void screen4() {
	erase();
	print_number(4, 1, 2, 0);
	print_alph(5, 1, 2, 15);
	print_alph(6, 1, 2, 26);
	print_alph(7, 1, 2, 22);
	print_alph(8, 1, 2, 8);
	print_alph(9, 1, 2, 13);
	attrset(COLOR_PAIR(5));
	for (int i = 0; i < 3; i++) {
		mvaddstr(20, 30 + i, space);
	}
	char Q[BUFFSIZE] = "Q";
	mvaddstr(21, 30, space);
	mvaddstr(21, 31, Q);
	mvaddstr(21, 32, space);
	for (int i = 0; i < 3; i++) {
		mvaddstr(22, 30 + i, space);
	}
	attrset(COLOR_PAIR(1));
	char END[BUFFSIZE] = "END GAME";
	mvaddstr(21, (int(maxX / 2) - 5), END);
	refresh();
}