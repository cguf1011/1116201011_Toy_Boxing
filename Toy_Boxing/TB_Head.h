#pragma once

#define BUFFSIZE 1024
#define CHARBUFF 124

struct charaInf {
	int playerNum;	/*1Pか2Pか*/
	int X;	/*x座標*/
	int Y;	/*y座標*/
	int colorNum;	/*色番号*/
};

void print_char1P(int x, int y, int colorNum);
void print_char2P(int x, int y, int colorNum);
void print_alph(int x, int y, int colorNum, int alphNum);
void draw_point(int x, int y, int color);
