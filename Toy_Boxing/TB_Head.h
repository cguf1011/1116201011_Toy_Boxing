#pragma once

#define BUFFSIZE 1024
#define CHARBUFF 124

struct charaInf {
	int playerNum;	/*1P‚©2P‚©*/
	int X;	/*xÀ•W*/
	int Y;	/*yÀ•W*/
	int colorNum;	/*F”Ô†*/
};

void print_char1P(int x, int y, int colorNum);
void print_char2P(int x, int y, int colorNum);
void print_alph(int x, int y, int colorNum, int alphNum);
void draw_point(int x, int y, int color);
