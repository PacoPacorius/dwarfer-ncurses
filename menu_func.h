#ifndef MENU_FUNC
#define MENU_FUNC

#include <ncurses.h>

struct Dwarf{
    char* name;
    char* profession;
    char* personality;
    char* details;
};

int add_new_dwarf(char* dummy_string, WINDOW* win);

void dummy_func(char* dummy_string, WINDOW* win);

#endif
