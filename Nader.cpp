#include <ncurses.h>    // Library for drawing in terminal
#include <iostream>     // For input and output
using namespace std;

string Difficulty = "NORMAL";    // Set starting difficulty
string Word = "Rock";            // The word for the game

WINDOW* win = newwin(22,92,1,2);  // Create a window for the game

// Draw the bottom base of the gallows
void drawbase(){
    cbreak();
    noecho();
    WINDOW* base = newwin(2,30,21,9);    // Create base window
    wmove(win,20,10);
    box(base, 0,0);                      // Draw a box around base
    wrefresh(base);
    getch();
    endwin();
}

// Draw second base part
void drawbase2(){
    cbreak();
    noecho();
    WINDOW* base2 = newwin(3,16,19,16);   // Create another base window
    wmove(win,20,10);
    box(base2, 0,0);
    wrefresh(base2);
    getch();
    endwin();
}

// Draw vertical pole (changes with difficulty)
void drawbase3(){
    cbreak();
    noecho();
    int h3,w3,x3,y3;
    if (Difficulty=="EASY") { h3=12; w3=3; y3=8; x3=24; }
    else { h3=15; w3=3; y3=8; x3=12; }
    
    WINDOW* base3 = newwin(h3,w3,y3,x3);   // Create pole window
    wmove(win,20,10);
    box(base3, 0,0);
    wrefresh(base3);
    getch();
    endwin();
}

// Draw top horizontal bar (changes with difficulty)
void drawbase4(){
    cbreak();
    noecho();
    int h4,w4,x4,y4;
    if (Difficulty=="EASY") { h4=2; w4=15; y4=8; x4=26; }
    else { h4=2; w4=20; y4=8; x4=14; }
    
    WINDOW* base4 = newwin(h4,w4,y4,x4);   // Create top bar window
    wmove(win,20,10);
    box(base4, 0,0);
    wrefresh(base4);
    getch();
    endwin();
}

// Draw rope (line down from the bar)
void drawbase5(){
    cbreak();
    noecho();
    int h5,w5,x5,y5;
    if (Difficulty=="EASY") { h5=5; w5=1; y5=9; x5=38; }
    else { h5=6; w5=1; y5=9; x5=25; }
    
    WINDOW* base5 = newwin(h5,w5,y5,x5);   // Create rope window
    wmove(win,20,10);
    box(base5, 0,0);
    wrefresh(base5);
    getch();
    endwin();
}

// Draw the head of the character
void drawhead(){
    cbreak();
    noecho();
    int h6,w6,x6,y6;
    if (Difficulty=="EASY") { h6=3; w6=5; y6=13; x6=36; }
    else { h6=3; w6=5; y6=13; x6=23; }
    
    WINDOW* head = newwin(h6,w6,y6,x6);   // Create head window
    wmove(win,20,10);
    wborder(head, 0, 0, 0, 0, 0, 0, 0, 0); // Draw borders (round head)
    wrefresh(head);
    getch();
    endwin();
}

// Draw the body of the character
void drawbody(){
    cbreak();
    noecho();
    int h7,w7,x7,y7;
    if (Difficulty=="EASY") { h7=5; w7=1; y7=15; x7=38; }
    else { h7=5; w7=1; y7=15; x7=25; }
    
    WINDOW* body = newwin(h7,w7,y7,x7);   // Create body window
    wmove(win,20,10);
    wborder(body, 0, 0, 0, 0, ' ', ' ', ' ', ' ');  // Simple line for body
    wrefresh(body);
    getch();
    endwin();
}

// Draw left arm (diagonal line)
void drawlarm(){
    int x,y;
    y=16;
    if (Difficulty=="EASY") { x=37; }
    else { x=24; }

    for (size_t i = 0; i < 3; i++) {
        wmove(win,y--,x++);
        wprintw(win,"/");    // Print "/" for left arm
        wrefresh(win);
    }
    getch();
    endwin();
}

// Draw right arm (diagonal line)
void drawrarm(){
    int x,y;
    y=16;
    if (Difficulty=="EASY") { x=35; }
    else { x=22; }

    for (size_t i = 0; i < 3; i++) {
        wmove(win,y--,x--);
        wprintw(win,"\\");   // Print "\" for right arm
        wrefresh(win);
    }
    getch();
    endwin();
}

// Draw left leg
void drawlleg(){
    int x,y;
    y=18;
    if (Difficulty=="EASY") { x=35; }
    else { x=22; }

    for (size_t i = 0; i < 3; i++) {
        wmove(win,y++,x--);
        wprintw(win,"/");    // Print "/" for left leg
        wrefresh(win);
    }
    getch();
    endwin();
}

// Draw right leg
void drawrleg(){
    int x,y;
    y=18;
    if (Difficulty=="EASY") { x=37; }
    else { x=24; }

    for (size_t i = 0; i < 3; i++) {
        wmove(win,y++,x++);
        wprintw(win,"\\");   // Print "\" for right leg
        wrefresh(win);
    }
    getch();
    endwin();
}

// Draw the full game screen
void drawgameui(){
    cbreak();
    noecho();
    initscr();                          // Start ncurses mode
    win = newwin(22,92,1,2);             // Create main window
    refresh();
    box(win, 0,0);                       // Draw window border
    wrefresh(win);

    wmove(win,2,46-3);                   // Move to position and print title
    wprintw(win,"Hangin?");

    wmove(win,11,65-Word.size());        // Move to word position
    for (size_t i = 0; i < Word.size(); i++) {
        waddch(win, ' ' | A_UNDERLINE);  // Print underlines for each letter
        waddch(win, ' ');
    }
    
    wrefresh(win);
    endwin();
}

