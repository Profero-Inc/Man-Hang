#ifndef TOTAL_H_INCLUDED
#define TOTAL_H_INCLUDED
#include <curses.h>

extern WINDOW* win;

void LOSE();
void WIN();
std::string RandomWord();
std::string custom();
int loadDifficultyFromFile();
int settings();
int mainmenu();
void drawgameui();
void drawbase();
void drawbase2();
void drawbase3();
void drawbase4();
void drawbase5();
void drawhead();
void drawbody();
void drawlarm();
void drawrarm();
void drawlleg();
void drawrleg();

#endif