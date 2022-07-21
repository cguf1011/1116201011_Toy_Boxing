#include <iostream>
#include <stdio.h>
#include "TB_Head.h"
#include "character8.h"
#include <curses.h>

char space[BUFFSIZE] = " ";
int colorBlack = 1;

/*1P���w�肳�ꂽ�F�ŕ\��*/
void print_char1P(int x, int y,  int colorNum) {
	unsigned char cbit;	/*����r�b�g*/
	int part, tx, ty;
	for (part = 0; part < 3; part++) {
		for (ty = 0; ty < 8; ty++) {
			cbit = 0x80;	/*����r�b�g��8�r�b�g�̍ŏ��*/
			for (tx = 0; tx < 8; tx++) {
				/*�r�b�g�ʒu�̔���*/
				if ((charPart1P[part][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
					draw_point((x * 8 + tx), (y * 8 + ty), colorNum);	/*�w�肳�ꂽ�F�ŕ`��*/
				}
				else {	/*0�̏ꍇ*/
					draw_point((x * 8 + tx), (y * 8 + ty), colorBlack);	/*���ŕ`��*/
				}
				cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
			}
		}
	}
}

/*2P���w�肳�ꂽ�F�ŕ\��*/
void print_char2P(int x, int y, int colorNum) {
	unsigned char cbit;	/*����r�b�g*/
	int part, tx, ty;
	for (part = 0; part < 3; part++) {
		for (ty = 0; ty < 8; ty++) {
			cbit = 0x80;	/*����r�b�g��8�r�b�g�̍ŏ��*/
			for (tx = 0; tx < 8; tx++) {
				/*�r�b�g�ʒu�̔���*/
				if ((charPart2P[part][ty] & cbit) == cbit) {	/*1�̏ꍇ*/
					draw_point((x * 8 + tx), (y * 8 + ty), colorNum);	/*�w�肳�ꂽ�F�ŕ`��*/
				}
				else {	/*0�̏ꍇ*/
					draw_point((x * 8 + tx), (y * 8 + ty), colorBlack);	/*���ŕ`��*/
				}
				cbit = cbit >> 1;	/*����r�b�g��1�r�b�g�E�փV�t�g*/
			}
		}
	}
}

/*�A���t�@�x�b�g���w�肳�ꂽ�F�ŕ\��*/
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

/*�w�肵�����W�Ɏw�肳�ꂽ�F�ŕ`��*/
void draw_point(int x, int y, int color) {
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_RED);
	init_pair(3, COLOR_BLACK, COLOR_BLUE);
	init_pair(4, COLOR_BLACK, COLOR_GREEN);
	attrset(COLOR_PAIR(color));
	mvaddstr(y, x, space);	/*(x, y)��color�ŕ`��*/
}

