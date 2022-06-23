#include "menu_func.h"
#include <curses.h>

int add_new_dwarf(char* dummy_string, WINDOW* win){

    //attron(COLOR_PAIR(3));
    mvwaddstr(win, 15, 3, "add_new_dwarf");
    //attroff(COLOR_PAIR(3));

    wrefresh(win);
    getch();

    mvwaddstr(win, 15, 3, "               ");
    return 0;
}

void dummy_func(char* dummy_string, WINDOW* win){
    WINDOW* temp;
    int c = 1;
    c++;
    temp = derwin(win, 3, 7, 17, 3);
    wbkgd(temp, COLOR_PAIR(3));
    mvwaddch(temp, 1, 1, 'c');
    wrefresh(temp);
}
