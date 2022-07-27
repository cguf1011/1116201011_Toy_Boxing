// Toy_Boxing.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include "TB_Head.h"
#include <curses.h>

charaInf *player1 = new charaInf();
charaInf *player2 = new charaInf();

int maxYsize, maxXsize;

int main()
{
    int key;
    int screenNum = 1;
    if (initscr() == NULL) {
        return 1;
    }
    getmaxyx(stdscr, maxYsize, maxXsize);
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    standby(player1, player2);
    while (true) {
        if (screenNum == 1) {
            screen1();
            key = getch();
            if (key == 'q') {
                break;
            }
            else if (key == 'a') {
                Aflashing();
                screenNum = 2;
            }
        }
        else if (screenNum == 2) {
            countdown();
            screen2(player1, player2);
            gameMode(player1, player2);
            if (player1->Y > maxYsize - 4) {
                screenNum = 3;
            }
            else {
                screenNum = 4;
            }
        }
        else if (screenNum == 3) {
            screen3();
            key = getch();
            if (key == 'q') {
                printGameResult(player1, player2);
                break;
            }
        }
        else if (screenNum == 4) {
            screen4();
            key = getch();
            if (key == 'q') {
                printGameResult(player1, player2);
                break;
            }
        }
    }
    endwin();
    return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
