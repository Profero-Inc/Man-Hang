#include <iostream>
#include <algorithm>
#include <ncurses.h>
#include <fstream>
#include "Headers/Total.h"
using namespace std;

string Difficulty = "NORMAL";

string Word;

int flag=0;

WINDOW* win = newwin(22,92,1,2);

int main(){
    cout << "Checking Dependencies"<< endl;
    if (!checkNcursesInstalledArch())
    {
        char yn;
        cout << "Do you want to install dependencies (Y/N):";
        cin >> yn;
        yn=toupper(yn);
        if (yn=='Y')
        {
            system("sudo pacman -S ncurses");
        }
        else
        {
            exit(1);
        }

    }
    bool T=1;
    initscr();
    while (T==1) {
        switch (mainmenu()) {
            case 0:
                switch (loadDifficultyFromFile())
                {
                case 0:
                    Difficulty="EASY";
                    break;
                case 1:
                    Difficulty="NORMAL";
                    break;
                case 2:
                    Difficulty="HARD";
                    break;
            
                default:
                    break;
                }
                Word=RandomWord();
                T=0;
                break;
            case 1:
                switch (loadDifficultyFromFile())
                {
                case 0:
                    Difficulty="EASY";
                    break;
                case 1:
                    Difficulty="NORMAL";
                    break;
                case 2:
                    Difficulty="HARD";
                    break;
            
                default:
                    break;
                }
                Word=custom();
                T=0;
                break;
            case 2:
                settings();
                break;
            case 3:
                endwin();
                exit(0);
            default:
                break;
        }
    }
    transform(Word.begin(), Word.end(), Word.begin(), ::toupper);
    cbreak();
    noecho();
    win = newwin(22,92,1,2);
    refresh();
    box(win, 0,0);
    wrefresh(win);
    wmove(win,2,46-4);
    wattron(win,A_STANDOUT);
    wprintw(win,"man hang");
    wattroff(win,A_STANDOUT);
    refresh();
    wmove(win,11,65-Word.size());
    
    for (size_t i = 0; i < Word.size(); i++) {
        waddch(win, ' ' | A_UNDERLINE);
        waddch(win, ' ');
    }

    wrefresh(win);

    int d = (Difficulty=="EASY") ? 11 : 9;
    int correct = 0;
    bool guessed[Word.size()] = {false};

    for (int i = 0; i < d; ++i) {
        int c = getch();
        c = toupper(c);

        bool match_found = false;
        for (size_t j = 0; j < Word.size(); ++j) {
            if (Word[j] == c && !guessed[j]) {
                guessed[j] = true;
                wmove(win,11,65 - Word.size() + j*2);
                waddch(win, c | A_UNDERLINE);
                wrefresh(win);
                correct++;
                d++;
                match_found = true;
            }
        }

        if (!match_found) {
            flag++;
            wmove(win,20,43);
            wprintw(win, "     ");
            wrefresh(win);
        }

        if (match_found)
        {
            wmove(win,20,43);
            wprintw(win, "     ");
            wrefresh(win);
        }
        

        if (correct == Word.size()) {
            getch();
            WIN();
            getch();
            endwin();
            cout << "You Win!" << endl;
            exit(0);
        }

        if (Difficulty=="EASY") {
            if (flag==1) drawbase();
            else if (flag==2) drawbase2();
            else if (flag==3){
                    int random;
                    srand(time(0));
                    random=rand() % Word.size();
                    c=Word[random];
                        for (size_t j2 = 0; j2 < Word.size(); ++j2) {
                if (Word[j2] == c && !guessed[j2]) {
                    guessed[j2] = true;
                    wmove(win,11,65 - Word.size() + j2*2);
                    waddch(win, c);
                    wmove(win,20,43);
                    wprintw(win, "Hint!");
                    wrefresh(win);
                    correct++;
                }
            }
                drawbase3();}
            else if (flag==4) drawbase4();
            else if (flag==5) drawbase5();
            else if (flag==6){ 
                    int random;
                    srand(time(0));
                    random=rand() % Word.size();
                    c=Word[random];
                        for (size_t j2 = 0; j2 < Word.size(); ++j2) {
                if (Word[j2] == c && !guessed[j2]) {
                    guessed[j2] = true;
                    wmove(win,11,65 - Word.size() + j2*2);
                    waddch(win, c);
                    wmove(win,20,43);
                    wprintw(win, "Hint!");
                    wrefresh(win);
                    correct++;
                }
            }
                drawhead();}
            else if (flag==7) drawbody();
            else if (flag==8) drawlarm();
            else if (flag==9){ 
                    int random;
                    srand(time(0));
                    random=rand() % Word.size();
                    c=Word[random];
                        for (size_t j2 = 0; j2 < Word.size(); ++j2) {
                if (Word[j2] == c && !guessed[j2]) {
                    guessed[j2] = true;
                    wmove(win,11,65 - Word.size() + j2*2);
                    waddch(win, c);
                    wmove(win,20,43);
                    wprintw(win, "Hint!");
                    wrefresh(win);
                    correct++;
                }
            }
                drawrarm();}
            else if (flag==10) drawlleg();
            else if (flag==11){ 
            drawrleg();
            for (size_t j = 0; j < Word.size(); ++j) {
                wmove(win, 11, 65 - Word.size() + j*2);
                waddch(win, Word[j] | A_UNDERLINE);
            }
            wrefresh(win);
            getch();
            LOSE();
            getch();
            endwin();
            cout << "You Lose!" << endl;
            exit(0);
        }
        } else {
            if (flag==1) drawbase3();
            else if (flag==2) drawbase4();
            else if (flag==3){ 
                int sum=0;
                for (size_t i2 = 0; i2 < Word.size(); i2++)
                {
                    sum+=guessed[i2];
                }
                if (!(Word.size()-sum<2))
                {
                    int random;
                    srand(time(0));
                    random=rand() % Word.size();
                    c=Word[random];
                        for (size_t j2 = 0; j2 < Word.size(); ++j2) {
                if (Word[j2] == c && !guessed[j2]) {
                    guessed[j2] = true;
                    wmove(win,11,65 - Word.size() + j2*2);
                    waddch(win, c);
                    wmove(win,20,43);
                    wprintw(win, "Hint!");
                    wrefresh(win);
                    correct++;
                }
            }
                }
                drawbase5();}
            else if (flag==4) drawhead();
            else if (flag==5) drawbody();
            else if (flag==6){ 
                if (Difficulty!="HARD")
                {
                int sum=0;
                for (size_t i2 = 0; i2 < Word.size(); i2++)
                {
                    sum+=guessed[i2];
                }
                if (!(Word.size()-sum<2))
                {
                    int random;
                    srand(time(0));
                    random=rand() % Word.size();
                    c=Word[random];
                        for (size_t j2 = 0; j2 < Word.size(); ++j2) {
                if (Word[j2] == c && !guessed[j2]) {
                    guessed[j2] = true;
                    wmove(win,11,65 - Word.size() + j2*2);
                    waddch(win, c);
                    wmove(win,20,43);
                    wprintw(win, "Hint!");
                    wrefresh(win);
                    correct++;
                }
            }
                }}
                drawlarm();}
            else if (flag==7) drawrarm();
            else if (flag==8) drawlleg();
            else if (flag==9) {
                drawrleg();
                for (size_t j = 0; j < Word.size(); ++j) {
                    wmove(win, 11, 65 - Word.size() + j*2);
                    waddch(win, Word[j] | A_UNDERLINE);
                }
                wrefresh(win);
                getch();
                LOSE();
                getch();
                endwin();
                cout << "You Lose!" << endl;
                exit(0);
            }
        }
    }
return(0);
}