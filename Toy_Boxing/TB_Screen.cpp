#include <iostream>
#include <stdio.h>
#include "TB_Head.h"
#include "character8.h"
#include <curses.h>

char space[BUFFSIZE] = " ";
int colorBlack = 1;

/*1Pを指定された色で表示*/
void print_char1P(int x, int y,  int colorNum) {
	unsigned char cbit;	/*判定ビット*/
	int part, tx, ty;
	for (part = 0; part < 3; part++) {
		for (ty = 0; ty < 8; ty++) {
			cbit = 0x80;	/*判定ビットを8ビットの最上位*/
			for (tx = 0; tx < 8; tx++) {
				/*ビット位置の判定*/
				if ((charPart1P[part][ty] & cbit) == cbit) {	/*1の場合*/
					draw_point((x * 8 + tx), (y * 8 + ty), colorNum);	/*指定された色で描画*/
				}
				else {	/*0の場合*/
					draw_point((x * 8 + tx), (y * 8 + ty), colorBlack);	/*黒で描画*/
				}
				cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
			}
		}
	}
}

/*2Pを指定された色で表示*/
void print_char2P(int x, int y, int colorNum) {
	unsigned char cbit;	/*判定ビット*/
	int part, tx, ty;
	for (part = 0; part < 3; part++) {
		for (ty = 0; ty < 8; ty++) {
			cbit = 0x80;	/*判定ビットを8ビットの最上位*/
			for (tx = 0; tx < 8; tx++) {
				/*ビット位置の判定*/
				if ((charPart2P[part][ty] & cbit) == cbit) {	/*1の場合*/
					draw_point((x * 8 + tx), (y * 8 + ty), colorNum);	/*指定された色で描画*/
				}
				else {	/*0の場合*/
					draw_point((x * 8 + tx), (y * 8 + ty), colorBlack);	/*黒で描画*/
				}
				cbit = cbit >> 1;	/*判定ビットを1ビット右へシフト*/
			}
		}
	}
}

/*アルファベットを指定された色で表示*/
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

/*指定した座標に指定された色で描画*/
void draw_point(int x, int y, int color) {
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_RED);
	init_pair(3, COLOR_BLACK, COLOR_BLUE);
	init_pair(4, COLOR_BLACK, COLOR_GREEN);
	attrset(COLOR_PAIR(color));
	mvaddstr(y, x, space);	/*(x, y)をcolorで描画*/
}

