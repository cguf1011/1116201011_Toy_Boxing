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

/*現在のカレントディレクトリ取得*/
void getCurrentDirectory(char* currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}

/*char読み込み*/
bool readChar(const char* section, const char* keyword, const char* defaultValue, char* returnValue, const char* filePath) {
	if (GetPrivateProfileString(section, keyword, defaultValue, returnValue, CHARBUFF, filePath) != 0) {
		return true;
	}
	else {
		return false;
	}
}

/*CSV読み込み*/
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
	/*データの読み込み*/
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

/*ゲーム結果出力*/
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
		fprintf(fp, "プレイヤー情報,左パンチ強,左パンチ弱,右パンチ強,右パンチ弱,パンチ合計,勝利数\n");
		fprintf(fp, "player1,%d,%d,%d,%d,%d,%d\n", player1->punchL1, player1->punchL2,
			player1->punchR1, player1->punchR2, player1PunchNum, player1->winTime);
		fprintf(fp, "player2,%d,%d,%d,%d,%d,%d\n", player2->punchL1, player2->punchL2,
			player2->punchR1, player2->punchR2, player2PunchNum, player2->winTime);
		fclose(fp);
	}
}

/*アルファベットを指定された色で表示　*/
void print_alph(int x, int y, int colorNum, int alphNum) {
	unsigned char cbit;	/*判定ビット*/
	int tx, ty;
	for (ty = 0; ty < 8; ty++) {
		cbit = 0x80;	/*判定ビットを8ビットの最上位*/
		for (tx = 0; tx < 8; tx++) {
			/*ビット位置の判定*/
			if ((alphabet[alphNum][ty] & cbit) == cbit) {	/*1の場合*/
				draw_point((x * 8 + tx), (y * 8 + ty), colorNum);	/*指定された色で描画*/
			}
			else {	/*0の場合*/
				draw_point((x * 8 + tx), (y * 8 + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
}

/*数字を指定された色で表示*/
void print_number(int x, int y, int colorNum, int numberNum) {
	unsigned char cbit;	/*判定ビット*/
	int tx, ty;
	for (ty = 0; ty < 8; ty++) {
		cbit = 0x80;	/*判定ビットを8ビットの最上位*/
		for (tx = 0; tx < 8; tx++) {
			/*ビット位置の判定*/
			if ((number[numberNum][ty] & cbit) == cbit) {	/*1の場合*/
				draw_point((x * 8 + tx), (y * 8 + ty), colorNum);	/*指定された色で描画*/
			}
			else {	/*0の場合*/
				draw_point((x * 8 + tx), (y * 8 + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
}

/*指定した座標に指定された色で描画*/
void draw_point(int x, int y, int color) {
	attrset(COLOR_PAIR(color));
	mvaddstr(y, x, space);	/*(x, y)をcolorで描画*/
}


/*A点滅*/
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

/*カウントダウン*/
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

/*1Pを指定された色で表示*/
void print_char1P(charaInf* player1) {
	unsigned char cbit;	/*判定ビット*/
	int tx, ty;
	/*顔*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*ビット位置の判定*/
			if ((charPart1P[0][ty] & cbit) == cbit) {	/*1の場合*/
				draw_point((player1->X + tx), (player1->Y + ty), player1->colorNum);	/*指定された色で描画*/
			}
			else {	/*0の場合*/
				draw_point((player1->X + tx), (player1->Y + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
	/*右手*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*ビット位置の判定*/
			if ((charPart1P[1][ty] & cbit) == cbit) {	/*1の場合*/
				if (player1->punchingR == 1) {
					draw_point((player1->X + 7 + tx), (player1->Y - 4 + ty), player1->colorNum);	/*指定された色で描画*/
				}
				else {
					draw_point((player1->X + 7 + tx), (player1->Y - 4 + ty), colorWhite);	/*指定された色で描画*/
				}
			}
			else {	/*0の場合*/
				draw_point((player1->X + 7 + tx), (player1->Y - 4 + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
	/*左手*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*ビット位置の判定*/
			if ((charPart1P[2][ty] & cbit) == cbit) {	/*1の場合*/
				if (player1->punchingL == 1) {
					draw_point((player1->X - 7 + tx), (player1->Y - 4 + ty), player1->colorNum);	/*指定された色で描画*/
				}
				else {
					draw_point((player1->X - 7 + tx), (player1->Y - 4 + ty), colorWhite);	/*白色で描画*/
				}
			}
			else {	/*0の場合*/
				draw_point((player1->X - 7 + tx), (player1->Y - 4 + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
}

/*2Pを指定された色で表示*/
void print_char2P(charaInf* player2) {
	unsigned char cbit;	/*判定ビット*/
	int tx, ty;
	/*顔*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*ビット位置の判定*/
			if ((charPart2P[0][ty] & cbit) == cbit) {	/*1の場合*/
				draw_point((player2->X + tx), (player2->Y + ty), player2->colorNum);	/*指定された色で描画*/
			}
			else {	/*0の場合*/
				draw_point((player2->X + tx), (player2->Y + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
	/*右手*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*ビット位置の判定*/
			if ((charPart2P[1][ty] & cbit) == cbit) {	/*1の場合*/
				if (player2->punchingR == 1) {
					draw_point((player2->X + 7 + tx), (player2->Y + 4 + ty), player2->colorNum);	/*指定された色で描画*/
				}
				else {
					draw_point((player2->X + 7 + tx), (player2->Y + 4 + ty), colorWhite);	/*白色で描画*/
				}
			}
			else {	/*0の場合*/
				draw_point((player2->X + 7 + tx), (player2->Y + 4 + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
	/*左手*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*ビット位置の判定*/
			if ((charPart2P[2][ty] & cbit) == cbit) {	/*1の場合*/
				if (player2->punchingL == 1) {
					draw_point((player2->X - 7 + tx), (player2->Y + 4 + ty), player2->colorNum);	/*指定された色で描画*/
				}
				else {
					draw_point((player2->X - 7 + tx), (player2->Y + 4 + ty), colorWhite);	/*白色で描画*/
				}
			}
			else {	/*0の場合*/
				draw_point((player2->X - 7 + tx), (player2->Y + 4 + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
}

/*1P左パンチ　強め*/
void player1PunchL1(charaInf* player1) {
	int tx, ty;
	unsigned char cbit;	/*判定ビット*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*ビット位置の判定*/
			if ((charPart1P[2][ty] & cbit) == cbit) {	/*1の場合*/
				draw_point((player1->X - 7 + tx), (player1->Y - 4 + ty), colorBlack);	/*黒色で描画*/
			}
			else {	/*0の場合*/
				draw_point((player1->X - 7 + tx), (player1->Y - 4 + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*ビット位置の判定*/
			if ((charPart1P[2][ty] & cbit) == cbit) {	/*1の場合*/
				draw_point((player1->X - 7 + tx), (player1->Y - 9 + ty), player1->colorNum);	/*指定された色で描画*/
			}
			else {	/*0の場合*/
				draw_point((player1->X - 7 + tx), (player1->Y - 9 + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
	refresh();
	Sleep(100);
}

/*1P左パンチ　弱め*/
void player1PunchL2(charaInf* player1) {
	int tx, ty;
	unsigned char cbit;	/*判定ビット*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*ビット位置の判定*/
			if ((charPart1P[2][ty] & cbit) == cbit) {	/*1の場合*/
				draw_point((player1->X - 7 + tx), (player1->Y - 4 + ty), colorBlack);	/*黒色で描画*/
			}
			else {	/*0の場合*/
				draw_point((player1->X - 7 + tx), (player1->Y - 4 + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*ビット位置の判定*/
			if ((charPart1P[2][ty] & cbit) == cbit) {	/*1の場合*/
				draw_point((player1->X - 7 + tx), (player1->Y - 5 + ty), player1->colorNum);	/*指定された色で描画*/
			}
			else {	/*0の場合*/
				draw_point((player1->X - 7 + tx), (player1->Y - 5 + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
	refresh();
	Sleep(100);
}

/*1P右パンチ　強め*/
void player1PunchR1(charaInf* player1) {
	int tx, ty;
	unsigned char cbit;	/*判定ビット*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*ビット位置の判定*/
			if ((charPart1P[1][ty] & cbit) == cbit) {	/*1の場合*/
				draw_point((player1->X + 7 + tx), (player1->Y - 4 + ty), colorBlack);	/*黒色で描画*/
			}
			else {	/*0の場合*/
				draw_point((player1->X + 7 + tx), (player1->Y - 4 + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*ビット位置の判定*/
			if ((charPart1P[1][ty] & cbit) == cbit) {	/*1の場合*/
				draw_point((player1->X + 7 + tx), (player1->Y - 9 + ty), player1->colorNum);	/*指定された色で描画*/
			}
			else {	/*0の場合*/
				draw_point((player1->X + 7 + tx), (player1->Y - 9 + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
	refresh();
	Sleep(100);
}

/*1P右パンチ　弱め*/
void player1PunchR2(charaInf* player1) {
	int tx, ty;
	unsigned char cbit;	/*判定ビット*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*ビット位置の判定*/
			if ((charPart1P[1][ty] & cbit) == cbit) {	/*1の場合*/
				draw_point((player1->X + 7 + tx), (player1->Y - 4 + ty), colorBlack);	/*黒色で描画*/
			}
			else {	/*0の場合*/
				draw_point((player1->X + 7 + tx), (player1->Y - 4 + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*ビット位置の判定*/
			if ((charPart1P[1][ty] & cbit) == cbit) {	/*1の場合*/
				draw_point((player1->X + 7 + tx), (player1->Y - 5 + ty), player1->colorNum);	/*指定された色で描画*/
			}
			else {	/*0の場合*/
				draw_point((player1->X + 7 + tx), (player1->Y - 5 + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
	refresh();
	Sleep(100);
}

/*2P左パンチ　強め*/
void player2PunchL1(charaInf* player2) {
	int tx, ty;
	unsigned char cbit;	/*判定ビット*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*ビット位置の判定*/
			if ((charPart2P[2][ty] & cbit) == cbit) {	/*1の場合*/
				draw_point((player2->X - 7 + tx), (player2->Y + 4 + ty), colorBlack);	/*黒色で描画*/
			}
			else {	/*0の場合*/
				draw_point((player2->X - 7 + tx), (player2->Y + 4 + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*ビット位置の判定*/
			if ((charPart2P[2][ty] & cbit) == cbit) {	/*1の場合*/
				draw_point((player2->X - 7 + tx), (player2->Y + 9 + ty), player2->colorNum);	/*指定された色で描画*/
			}
			else {	/*0の場合*/
				draw_point((player2->X - 7 + tx), (player2->Y + 9 + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
	refresh();
	Sleep(100);
}

/*2P左パンチ　弱め*/
void player2PunchL2(charaInf* player2) {
	int tx, ty;
	unsigned char cbit;	/*判定ビット*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*ビット位置の判定*/
			if ((charPart2P[2][ty] & cbit) == cbit) {	/*1の場合*/
				draw_point((player2->X - 7 + tx), (player2->Y + 4 + ty), colorBlack);	/*黒色で描画*/
			}
			else {	/*0の場合*/
				draw_point((player2->X - 7 + tx), (player2->Y + 4 + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*ビット位置の判定*/
			if ((charPart2P[2][ty] & cbit) == cbit) {	/*1の場合*/
				draw_point((player2->X - 7 + tx), (player2->Y + 5 + ty), player2->colorNum);	/*指定された色で描画*/
			}
			else {	/*0の場合*/
				draw_point((player2->X - 7 + tx), (player2->Y + 5 + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
	refresh();
	Sleep(100);
}

/*2P右パンチ　強め*/
void player2PunchR1(charaInf* player2) {
	int tx, ty;
	unsigned char cbit;	/*判定ビット*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*ビット位置の判定*/
			if ((charPart2P[1][ty] & cbit) == cbit) {	/*1の場合*/
				draw_point((player2->X + 7 + tx), (player2->Y + 4 + ty), colorBlack);	/*黒色で描画*/
			}
			else {	/*0の場合*/
				draw_point((player2->X + 7 + tx), (player2->Y + 4 + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*ビット位置の判定*/
			if ((charPart2P[1][ty] & cbit) == cbit) {	/*1の場合*/
				draw_point((player2->X + 7 + tx), (player2->Y + 9 + ty), player2->colorNum);	/*指定された色で描画*/
			}
			else {	/*0の場合*/
				draw_point((player2->X + 7 + tx), (player2->Y + 9 + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
	refresh();
	Sleep(100);
}

/*2P右パンチ　弱め*/
void player2PunchR2(charaInf* player2) {
	int tx, ty;
	unsigned char cbit;	/*判定ビット*/
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*ビット位置の判定*/
			if ((charPart2P[1][ty] & cbit) == cbit) {	/*1の場合*/
				draw_point((player2->X + 7 + tx), (player2->Y + 4 + ty), colorBlack);	/*黒色で描画*/
			}
			else {	/*0の場合*/
				draw_point((player2->X + 7 + tx), (player2->Y + 4 + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
	for (ty = 0; ty < 3; ty++) {
		cbit = 0x40;
		for (tx = 0; tx < 6; tx++) {
			/*ビット位置の判定*/
			if ((charPart2P[1][ty] & cbit) == cbit) {	/*1の場合*/
				draw_point((player2->X + 7 + tx), (player2->Y + 5 + ty), player2->colorNum);	/*指定された色で描画*/
			}
			else {	/*0の場合*/
				draw_point((player2->X + 7 + tx), (player2->Y + 5 + ty), colorBlack);	/*黒で描画*/
			}
			cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
		}
	}
	refresh();
	Sleep(100);
}

/*1P用ライン表示*/
void printLine1P(int colorNum) {
	int lx;
	attrset(COLOR_PAIR(colorNum));
	for (lx = 0; lx < maxX; lx++) {
		mvaddstr(maxY-1, lx, line);
	}
}

/*2P用ライン表示*/
void printLine2P(int colorNum) {
	int lx;
	attrset(COLOR_PAIR(colorNum));
	for (lx = 0; lx < maxX; lx++) {
		mvaddstr(0, lx, line);
	}
}

/*1P用ライン点滅*/
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

/*2P用ライン点滅*/
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

/*初期設定*/
void standby(charaInf* player1, charaInf* player2) {
	getmaxyx(stdscr, maxY, maxX);
	colorMake();
	player1->X = int(maxX / 2) - 3;
	player1->Y = int(maxY / 2) + 5;
	player2->X = int(maxX / 2) - 3;
	player2->Y = int(maxY / 2) - 8;
	readCSV(player1, player2);
}

/*表示する色設定*/
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

/*ゲームモード*/
void gameMode(charaInf* player1, charaInf* player2) {
	while (true) {
		int key;
		noecho();
		cbreak();
		keypad(stdscr, TRUE);
		key = getch();
		if ((player1->Y <= maxY - 4) && (player2->Y >= 1)) {
			/*1P左パンチ*/
			if (key == 'a') {
				player1->punchingL = 1;
				player1->punchingR = 0;
				if (player2->punchingL == 0) {
					/*左パンチ　強*/
					player1PunchL1(player1);
					player2->Y = player2->Y - 2;
					player1->Y = player1->Y - 2;
					player1->punchL1 = player1->punchL1 + 1;
				}
				else {
					/*左パンチ　弱*/
					player1PunchL2(player1);
					player2->Y = player2->Y - 1;
					player1->Y = player1->Y - 1;
					player1->punchL2 = player1->punchL2 + 1;
				}
			}
			/*1P右パンチ*/
			else if (key == 's') {
				player1->punchingR = 1;
				player1->punchingL = 0;
				if (player2->punchingR == 0) {
					/*右パンチ　強*/
					player1PunchR1(player1);
					player2->Y = player2->Y - 2;
					player1->Y = player1->Y - 2;
					player1->punchR1 = player1->punchR1 + 1;
				}
				else {
					/*右パンチ　弱*/
					player1PunchR2(player1);
					player2->Y = player2->Y - 1;
					player1->Y = player1->Y - 1;
					player1->punchR2 = player1->punchR2 + 1;
				}
			}
			/*2P左パンチ*/
			else if (key == 'k') {
				player2->punchingL = 1;
				player2->punchingR = 0;
				if (player1->punchingL == 0) {
					/*左パンチ　強*/
					player2PunchL1(player2);
					player1->Y = player1->Y + 2;
					player2->Y = player2->Y + 2;
					player2->punchL1 = player2->punchL1 + 1;
				}
				else {
					/*左パンチ　弱*/
					player2PunchL2(player2);
					player1->Y = player1->Y + 1;
					player2->Y = player2->Y + 1;
					player2->punchL2 = player2->punchL2 + 1;
				}
			}
			/*2P右パンチ*/
			else if (key == 'l') {
				player2->punchingR = 1;
				player2->punchingL = 0;
				if (player1->punchingR == 0) {
					/*右パンチ　強*/
					player2PunchR1(player2);
					player1->Y = player1->Y + 2;
					player2->Y = player2->Y + 2;
					player2->punchR1 = player2->punchR1 + 1;
				}
				else {
					/*右パンチ　弱*/
					player2PunchR2(player2);
					player1->Y = player1->Y + 1;
					player2->Y = player2->Y + 1;
					player2->punchR2 = player2->punchR2 + 1;
				}
			}
		}
		screen2(player1, player2);
		/*どちらかがラインを越える*/
		/*2P勝利*/
		if (player1->Y > maxY - 4) {
			line1Pflashing();
			player2->winTime = player2->winTime + 1;
			break;  /*ゲーム終了*/
		}
		/*1P勝利*/
		else if (player2->Y < 1) {
			line2Pflashing();
			player1->winTime = player1->winTime + 1;
			break;  /*ゲーム終了*/
		}
	}
}

/*画面１　開始画面*/
void screen1() {
	erase();
	/*TOY BOXING表示*/
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

/*画面２　ゲーム画面*/
void screen2(charaInf* player1, charaInf* player2) {
	erase();
	printLine1P(4);
	printLine2P(4);
	print_char1P(player1);
	print_char2P(player2);
	refresh();
}

/*画面３　2P勝利画面*/
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

/*画面４　1P勝利画面*/
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