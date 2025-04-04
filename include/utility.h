#ifndef UTILS_H
#define UTILS_H

#include <windows.h>

inline void gotoxy(short x, short y) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {x, y};
    SetConsoleCursorPosition(hStdout, position);
}

#endif // UTILS_H