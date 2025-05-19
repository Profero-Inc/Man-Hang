#include <curses.h>
#include <fstream>
#include <iostream>
using namespace std;

extern std::string Difficulty;
extern std::string Word;
extern int flag;
extern WINDOW* win;

int mainmenu() {
    erase();
    noecho();
    cbreak();
    curs_set(0);

    int term_height, term_width;
    getmaxyx(stdscr, term_height, term_width);

    int win_height = 10;
    int win_width = 80;
    int start_y = (term_height - win_height) / 2;
    int start_x = (term_width - win_width) / 2;

    WINDOW* mainmenu = newwin(win_height, win_width, start_y, start_x);
    box(mainmenu, 0, 0);
    keypad(mainmenu, true);
    refresh();

    std::string choices[4] = {"Play", "Custom", "Settings", "Quit"};
    int choice;
    int highlight = 0;
    int num_choices = sizeof(choices) / sizeof(choices[0]);


    int start_line = (win_height - num_choices) / 2;

    while (true) {
        for (int i = 0; i < num_choices; i++) {
            std::string text = choices[i];
            int text_x = (win_width - 2 - text.length()) / 2;  

            int row = i + start_line;

            if (i == highlight) {
                wattron(mainmenu, A_REVERSE);
                mvwprintw(mainmenu, row, 1, std::string(win_width - 2, ' ').c_str());
                mvwprintw(mainmenu, row, text_x + 1, text.c_str());
                wattroff(mainmenu, A_REVERSE);
            } else {
                mvwprintw(mainmenu, row, 1, std::string(win_width - 2, ' ').c_str());
                mvwprintw(mainmenu, row, text_x + 1, text.c_str());
            }
        }

        wrefresh(mainmenu);

        choice = wgetch(mainmenu);
        switch (choice) {
            case KEY_UP:
                highlight = (highlight - 1 + num_choices) % num_choices;
                break;
            case KEY_DOWN:
                highlight = (highlight + 1) % num_choices;
                break;
            case 10: // Enter
                delwin(mainmenu);
                erase();
                return highlight;
            default:
                break;
        }
    }
}

int loadDifficultyFromFile() {
    std::ifstream in("settings.txt");
    if (!in.is_open()) {
        return 1;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line.find("difficulty=") == 0) {
            std::string value = line.substr(11);
            if (value == "EASY")return 0;
            if (value == "NORMAL") return 1;
            if (value == "HARD") return 2;
        }
    }

    return 1;
}

string RandomWord() {
    const int MAX_WORDS = 530;
    static bool seeded = false;
    if (!seeded) {
        srand(time(nullptr)); // seed once
        seeded = true;
    }

    string filename = Difficulty + ".txt";
    ifstream in(filename);
    if (!in.is_open()) {
        return "";
    }

    string words[MAX_WORDS];
    int count = 0;
    string line;

    while (getline(in, line) && count < MAX_WORDS) {
        if (!line.empty()) {
            words[count++] = line;
        }
    }

    in.close();

    if (count == 0) {
        return "";
    }

    int index = rand() % count;
    return words[index];
}

int settings() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    int term_height, term_width;
    getmaxyx(stdscr, term_height, term_width);

    int win_height = 10;
    int win_width = 80;
    int start_y = (term_height - win_height) / 2;
    int start_x = (term_width - win_width) / 2;

    WINDOW* mainmenu = newwin(win_height, win_width, start_y, start_x);
    box(mainmenu, 0, 0);
    keypad(mainmenu, true);
    refresh();

    std::string choices[3] = {"Difficulty", "Save", "Discard"};
    std::string difficulties[3] = {"EASY", "NORMAL", "HARD"};
    int difficultyIndex = loadDifficultyFromFile();
    int highlight = 0;
    int num_choices = sizeof(choices) / sizeof(choices[0]);
    int start_line = (win_height - num_choices) / 2;

    while (true) {
        for (int i = 0; i < num_choices; i++) {
            std::string label = choices[i];
            if (i == 0) {
                label += ": " + difficulties[difficultyIndex];
            }

            int text_x = (win_width - 2 - label.length()) / 2;
            int row = i + start_line;

            if (i == highlight) {
                wattron(mainmenu, A_REVERSE);
                mvwprintw(mainmenu, row, 1, std::string(win_width - 2, ' ').c_str());
                mvwprintw(mainmenu, row, text_x + 1, label.c_str());
                wattroff(mainmenu, A_REVERSE);
            } else {
                mvwprintw(mainmenu, row, 1, std::string(win_width - 2, ' ').c_str());
                mvwprintw(mainmenu, row, text_x + 1, label.c_str());
            }
        }

        wrefresh(mainmenu);

        int choice = wgetch(mainmenu);
        switch (choice) {
            case KEY_UP:
                highlight = (highlight - 1 + num_choices) % num_choices;
                break;
            case KEY_DOWN:
                highlight = (highlight + 1) % num_choices;
                break;
            case KEY_LEFT:
                if (highlight == 0) {
                    difficultyIndex = (difficultyIndex - 1 + 3) % 3;
                }
                break;
            case KEY_RIGHT:
                if (highlight == 0) {
                    difficultyIndex = (difficultyIndex + 1) % 3;
                }
                break;
            case 10: // Enter
                if (choices[highlight] == "Save") {
                    std::ofstream out("settings.txt");
                    if (out.is_open()) {
                        out << "difficulty=" << difficulties[difficultyIndex] << std::endl;
                        out.close();
                    }
                    delwin(mainmenu);
                    erase();
                    return 0;
                } else if (choices[highlight] == "Discard") {
                    delwin(mainmenu);
                    erase();
                    return 1;
                }
                break;
            default:
                break;
        }
    }
}

string custom() {
    int popup_height = 5;
    int popup_width = 40;
    int term_height, term_width;
    getmaxyx(stdscr, term_height, term_width);

    int start_y = (term_height - popup_height) / 2;
    int start_x = (term_width - popup_width) / 2;

    WINDOW* popup = newwin(popup_height, popup_width, start_y, start_x);
    box(popup, 0, 0);
    keypad(popup, false);

    std::string input = "";
    int max_input_len = popup_width - 4;
    int ch;
    mvwprintw(popup, 1, 2, "Enter a word:");
    wmove(popup, 2, 2);
    wrefresh(popup);

    while (true) {
        ch = wgetch(popup);

        if (ch == '\n' || ch == KEY_ENTER) {
            if (!input.empty()) break;
        }

        else if (ch == KEY_BACKSPACE || ch == 127 || ch == 8) {
            if (!input.empty()) {
                input.pop_back();
                int x, y;
                getyx(popup, y, x);
                mvwaddch(popup, y, x - 1, ' ');
                wmove(popup, y, x - 1);
            }
        }

        else if (std::isalnum(ch) || ch == '_') {
            if (input.length() < (size_t)max_input_len) {
                input.push_back((char)ch);
                waddch(popup, ch);
            }
        }
        wrefresh(popup);
    }

    noecho();
    delwin(popup);
    return input;
}

void WIN(){
    int popup_height = 5;
    int popup_width = 40;
    int term_height, term_width;
    getmaxyx(stdscr, term_height, term_width);

    int start_y = (term_height - popup_height) / 2;
    int start_x = (term_width - popup_width) / 2;

    WINDOW* popup = newwin(popup_height, popup_width, start_y, start_x);
    box(popup, 0, 0);
    keypad(popup, false);
    mvwprintw(popup, 2, 16, "You Win!");
    wrefresh(popup);
    noecho();
    delwin(popup);
}

void LOSE(){
    int popup_height = 5;
    int popup_width = 40;
    int term_height, term_width;
    getmaxyx(stdscr, term_height, term_width);
    int start_y = (term_height - popup_height) / 2;
    int start_x = (term_width - popup_width) / 2;

    WINDOW* popup = newwin(popup_height, popup_width, start_y, start_x);
    box(popup, 0, 0);
    keypad(popup, false);
    mvwprintw(popup, 2, 15, "You Lose!");
    wrefresh(popup);
    noecho();
    delwin(popup);
}

void drawbase(){
    cbreak();
    noecho();
    WINDOW* base = newwin(2,30,21,9);
    wmove(win,20,10);
    box(base, 0,0);
    wrefresh(base);
    wmove(base,1,45);
    wrefresh(base);
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
    wborder(head, 0, 0, 0, 0, 0, 0, 0, 0);
    wrefresh(head);
    wmove(head,1,45);
    wrefresh(head);
}

void drawbody(){
    cbreak();
    noecho();
    int h7,w7,x7,y7;
    if (Difficulty=="EASY")
    {
        h7=5;
        w7=1;
        y7=15;
        x7=38;
    }
    else
    {
        h7=5;
        w7=1;
        y7=15;
        x7=25;
    }
    
    
    WINDOW* body = newwin(h7,w7,y7,x7);
    wmove(win,20,10);
    wborder(body, 0, 0, 0, 0, ' ', ' ', ' ', ' ');
    wrefresh(body);
    wmove(body,1,45);
    wrefresh(body);
}

void drawlarm(){
    int x,y;
    y=16;
    if (Difficulty=="EASY")
    {
        x=37;
    }
    else
    {
        x=24;
    }
    for (size_t i = 0; i < 3; i++)
    {
        wmove(win,y--,x++);
        wprintw(win,"/");
        wrefresh(win);
    }
}

void drawrarm(){
    int x,y;
    y=16;
    if (Difficulty=="EASY")
    {
        x=35;
    }
    else
    {
        x=22;
    }    
    for (size_t i = 0; i < 3; i++)
    {
        wmove(win,y--,x--);
        wprintw(win,"\\");
        wrefresh(win);
    }
}

void drawlleg(){
    int x,y;
    y=18;
    if (Difficulty=="EASY")
    {
        x=35;
    }
    else
    {
        x=22;
    }    
    for (size_t i = 0; i < 3; i++)
    {
        wmove(win,y++,x--);
        wprintw(win,"/");
        wrefresh(win);
    }
}

void drawrleg(){
    int x,y;
    y=18;
    if (Difficulty=="EASY")
    {
        x=37;
    }
    else
    {
        x=24;
    }  
    for (size_t i = 0; i < 3; i++)
    {
        wmove(win,y++,x++);
        wprintw(win,"\\");
        wrefresh(win);
    }
}


