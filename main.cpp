#include "lib.h"
#include "functions.cpp"
#include <iostream>

extern unsigned int x,y;
extern char player_support;

int main() {
    system("cls");

    printTitleScreen();

    request_dimensions();

    printInstructions();
    
    request_side();

    //system("cls");

    


    

    return 0;
}