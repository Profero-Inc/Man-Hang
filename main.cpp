#include <ncurses.h>
#include <iostream>
using namespace std;

string Difficulty = "NORMAL";

WINDOW* win = newwin(22,92,1,2);

void drawbase(){
    cbreak();
    noecho();
    WINDOW* base = newwin(2,30,21,9);
    wmove(win,20,10);
    box(base, 0,0);
    wrefresh(base);
    wmove(base,1,45);
    wrefresh(base);
    
    getch();

    endwin();
}

void drawbase2(){
    cbreak();
    noecho();
    WINDOW* base2 = newwin(3,16,19,16);
    wmove(win,20,10);
    box(base2, 0,0);
    wrefresh(base2);
    wmove(base2,1,45);
    wrefresh(base2);
    
    getch();

    endwin();
}

void drawbase3(){
    cbreak();
    noecho();
    int h3,w3,x3,y3;
    if (Difficulty=="EASY")
    {
        h3=12;
        w3=3;
        y3=8;
        x3=24;
    }
    else
    {
        h3=15;
        w3=3;
        y3=8;
        x3=12;
    }
    
    
    WINDOW* base3 = newwin(h3,w3,y3,x3);
    wmove(win,20,10);
    box(base3, 0,0);
    wrefresh(base3);
    wmove(base3,1,45);
    wrefresh(base3);
    
    getch();

    endwin();
}


void drawbase4(){
    cbreak();
    noecho();
    int h4,w4,x4,y4;
    if (Difficulty=="EASY")
    {
        h4=2;
        w4=15;
        y4=8;
        x4=26;
    }
    else
    {
        h4=2;
        w4=20;
        y4=8;
        x4=14;
    }
    
    
    WINDOW* base4 = newwin(h4,w4,y4,x4);
    wmove(win,20,10);
    box(base4, 0,0);
    wrefresh(base4);
    wmove(base4,1,45);
    wrefresh(base4);
    
    getch();

    endwin();
}


void drawbase5(){
    cbreak();
    noecho();
    int h5,w5,x5,y5;
    if (Difficulty=="EASY")
    {
        h5=5;
        w5=1;
        y5=9;
        x5=38;
    }
    else
    {
        h5=6;
        w5=1;
        y5=9;
        x5=25;
    }
    
    
    WINDOW* base5 = newwin(h5,w5,y5,x5);
    wmove(win,20,10);
    box(base5, 0,0);
    wrefresh(base5);
    wmove(base5,1,45);
    wrefresh(base5);
    
    getch();

    endwin();
}

void drawhead(){
    cbreak();
    noecho();
    int h6,w6,x6,y6;
    if (Difficulty=="EASY")
    {
        h6=3;
        w6=5;
        y6=13;
        x6=36;
    }
    else
    {
        h6=3;
        w6=5;
        y6=13;
        x6=23;
    }
    
    
    WINDOW* head = newwin(h6,w6,y6,x6);
    wmove(win,20,10);
    // box(head, 0,0);

    wborder(head, 0, 0, 0, 0, 0, 0, 0, 0);
    wrefresh(head);
    wmove(head,1,45);
    wrefresh(head);
    
    getch();

    endwin();
}

void drawgameui(){
    cbreak();
    noecho();
    initscr();
    win = newwin(22,92,1,2);
    refresh();
    box(win, 0,0);
    wrefresh(win);
    wmove(win,2,45);
    wprintw(win,"Hangin?");
    wrefresh(win);
    
    
    endwin();
    }


int main(){
drawgameui();
//drawbase();
//drawbase2();
drawbase3();
drawbase4();
drawbase5();
drawhead();
}