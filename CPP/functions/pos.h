#ifndef POS_H
#define POS_H
#include <Windows.h>

namespace ps{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    void gotoxy(const short x, const short y){
        COORD coord = {x,y};
        SetConsoleCursorPosition(console,coord);
    }
}

#endif