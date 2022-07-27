#pragma once

#define BUFFSIZE 1024
#define CHARBUFF 124

/*�L�������*/
struct charaInf {
	int playerNum;	/*1P��2P��*/
	int X;	/*x���W*/
	int Y;	/*y���W*/
	int punchingL;	/*�����*/
	int punchingR;	/*�E���*/
	int colorNum;	/*�F�ԍ�*/
	int punchL1;	/*���p���`�@����*/
	int punchL2;	/*���p���`�@���*/
	int punchR1;	/*�E�p���`�@����*/
	int punchR2;	/*�E�p���`�@���*/
	int winTime;	/*������*/
};

/*�t�@�C�����o��*/
void getCurrentDirectory(char* currentDirectory);
bool readChar(const char* section, const char* keyword, const char* defaultValue, char* returnValue, const char* filePath);
void readCSV(charaInf* player1, charaInf* player2);
void printGameResult(charaInf* player1, charaInf* player2);

/*��ʕ\��*/
void print_alph(int x, int y, int colorNum, int alphNum);
void print_number(int x, int y, int colorNum, int numberNum);
void draw_point(int x, int y, int color);
void Aflashing();
void countdown();

/*�L�����\��*/
void print_char1P(charaInf* player1);
void print_char2P(charaInf* player2);
void player1PunchL1(charaInf* player1);
void player1PunchL2(charaInf* player1);
void player1PunchR1(charaInf* player1);
void player1PunchR2(charaInf* player1);
void player2PunchL1(charaInf* player2);
void player2PunchL2(charaInf* player2);
void player2PunchR1(charaInf* player2);
void player2PunchR2(charaInf* player2);
void printLine1P(int colorNum);
void printLine2P(int colorNum);
void line1Pflashing();
void line2Pflashing();

/*�Q�[������*/
void standby(charaInf* player1, charaInf* player2);
void colorMake();

/*�Q�[�����[�h*/
void gameMode(charaInf* player1, charaInf* player2);

/*�X�N���[��*/
void screen1();
void screen2(charaInf* player1, charaInf* player2);
void screen3();
void screen4();

