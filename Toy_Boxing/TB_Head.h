#pragma once

#define BUFFSIZE 1024
#define CHARBUFF 124

/*キャラ情報*/
struct charaInf {
	int playerNum;	/*1Pか2Pか*/
	int X;	/*x座標*/
	int Y;	/*y座標*/
	int punchingL;	/*左情報*/
	int punchingR;	/*右情報*/
	int colorNum;	/*色番号*/
	int punchL1;	/*左パンチ　強め*/
	int punchL2;	/*左パンチ　弱め*/
	int punchR1;	/*右パンチ　強め*/
	int punchR2;	/*右パンチ　弱め*/
	int winTime;	/*勝利数*/
};

/*ファイル入出力*/
void getCurrentDirectory(char* currentDirectory);
bool readChar(const char* section, const char* keyword, const char* defaultValue, char* returnValue, const char* filePath);
void readCSV(charaInf* player1, charaInf* player2);
void printGameResult(charaInf* player1, charaInf* player2);

/*画面表示*/
void print_alph(int x, int y, int colorNum, int alphNum);
void print_number(int x, int y, int colorNum, int numberNum);
void draw_point(int x, int y, int color);
void Aflashing();
void countdown();

/*キャラ表示*/
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

/*ゲーム準備*/
void standby(charaInf* player1, charaInf* player2);
void colorMake();

/*ゲームモード*/
void gameMode(charaInf* player1, charaInf* player2);

/*スクリーン*/
void screen1();
void screen2(charaInf* player1, charaInf* player2);
void screen3();
void screen4();

