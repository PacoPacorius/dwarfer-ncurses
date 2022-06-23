#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <menu.h>
#include "menu_func.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

char* choices[] = { "New Dwarf Entry",
                    "Modify Dwarf Entry",
                    "Delete Dwarf Entry",
                    "View Dwarf Entries",
                    "Search In Dwarf Entries",
                    "New Fort File",
                    "Load Fort File",
                    (char*) NULL,
                    };

WINDOW* create_win(int height, int width, int starty, int startx);

void menu_func_caller(char* name, WINDOW* win);

int main(){
    // init ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    start_color();
    
    // menu variables
    ITEM** my_items;
    MENU* my_menu;
    int n_choices;
    ITEM* cur_item;

    // variables / secondary initialisation
    int c;
    int i, j;
    int height = LINES / 2, width = COLS / 3;
    char* menu_title = "DWARFER v0.0";
    WINDOW* my_win = create_win(height, width, (LINES - height) / 2, (COLS - width) / 2);
    getmaxyx(my_win, height, width);
    WINDOW* sub_win = derwin(my_win, ARRAY_SIZE(choices) + 1, 30, 4, width - 45);

    // menu initialisation
    n_choices = ARRAY_SIZE(choices);
    my_items = (ITEM**)calloc(n_choices, sizeof(ITEM*));
    
    for(i = 0; i < n_choices; ++i){
        my_items[i] = new_item(choices[i], choices[i]);

        set_item_userptr(my_items[i], menu_func_caller);    // set user pointer for functions
        }

    my_menu = new_menu((ITEM**)my_items);

    set_menu_win(my_menu, my_win);
    set_menu_sub(my_menu, sub_win);

    menu_opts_off(my_menu, O_SHOWDESC);
    // color initialisation
    init_color(COLOR_CYAN, 400, 800, 1000);
    init_pair(1, COLOR_CYAN, COLOR_MAGENTA);
    init_pair(2, COLOR_MAGENTA, COLOR_CYAN);
    init_pair(3, COLOR_YELLOW, COLOR_RED);

    set_menu_fore(my_menu, COLOR_PAIR(1));
    set_menu_back(my_menu, COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    mvwaddstr(my_win, 1, (width - strlen(menu_title)) / 2, menu_title);
    wbkgd(my_win, COLOR_PAIR(1));
    attroff(COLOR_PAIR(1));

    // main program
    refresh();
    post_menu(my_menu);
    wrefresh(my_win);

    keypad(my_win, true);
    while((c = wgetch(my_win)) != 'q'){
        switch(c){
        case KEY_UP:
            menu_driver(my_menu, REQ_UP_ITEM);
            break;
        case KEY_DOWN:
            menu_driver(my_menu, REQ_DOWN_ITEM);
            break;
        case '\n':
            {
            void(* p)(char *, WINDOW *);

            cur_item = current_item(my_menu);
            p = item_userptr(cur_item);
            p((char* )item_name(cur_item), my_win); // what in the world is going on here, function pointers biccth!
            pos_menu_cursor(my_menu);
            break;
            }
         }
            
        wrefresh(my_win);
    }

    // free memory, end ncurses mode
    unpost_menu(my_menu);
    free_menu(my_menu);
    for(i = 0; i < n_choices; ++i)
        free_item(my_items[i]);
    destroy_win(my_win);
    destroy_win(sub_win);
    endwin();
    return 0;
}


WINDOW* create_win(int height, int width, int starty, int startx){
    WINDOW* local_win;

    local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0);

    wrefresh(local_win);

    return local_win;
}

void destroy_win(WINDOW* local_win){
    wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');

    wrefresh(local_win);
    delwin(local_win);
}

void menu_func_caller(char* name, WINDOW* win){
    int y,x;
    getyx(win, y, x);
    mvwprintw(win, 13, 3, "                         "); // erase previous print
    wmove(win, 13, 3);
    wprintw(win, name);
    //waddch(win, ':');
    wmove(win, y, x);

    if(name == "New Dwarf Entry") add_new_dwarf(name, win);
    else if(name == "Modify Dwarf Entry") dummy_func(name, win);
    else if(name == "Delete Dwarf Entry") dummy_func(name, win);
    else if(name == "View Dwarf Entries") dummy_func(name, win);
    else if(name == "Search In Dwarf Entries") dummy_func(name, win);
    else if(name == "New Fort File") dummy_func(name, win);
    else if(name == "Load Fort File") dummy_func(name, win);
}
