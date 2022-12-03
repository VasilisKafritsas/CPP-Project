#include <iostream>
#include "lib.h"
#include "classes.cpp"

unsigned int x, y;
char player_support;


void printTitleScreen() {
	
    for (int i = 0; i < 61; i++) cout << 'O';        //Start of title screen

    cout << endl << 'O';
    for (int i = 0; i < 59; i++) cout << ' ';
    cout << 'O' << endl;

    cout << 'O';
    for (int i = 0; i < 13; i++) cout << ' ';
    cout << "Welcome to Vampires VS Werewolfs!";
    for (int i = 0; i < 13; i++) cout << ' ';
    cout << 'O' << endl;

    cout << 'O';
    for (int i = 0; i < 59; i++) cout << ' ';
    cout << 'O' << endl;

    for (int i = 0; i < 61; i++) cout << 'O';
    cout << "\n\n";                                  //End of title screen

}


void request_dimensions() {
    cout << "Please give dimensions to create the grid(x > y recommended): " << endl;
    cin >> x;
    cin >> y;
}




void printInstructions() {
    cout << "\n*INSTRUCTIONS*\n";
    this_thread::sleep_for(500ms);

    cout << "There are 2 teams, Werewolfs and Vampires.You must choose a team to support but you are not part of it.\n\n";
    this_thread::sleep_for(500ms);

    cout << "You control your avatar with [WASD] keys.\n";
    cout << "Your avatar does not take damage.\n\n";
    this_thread::sleep_for(500ms);

    cout << "Each team moves randomly around the map in all 4 directions but Vampires can move diagonally too.\n";
    cout << "When 2 enemies collide they fight or try to run away. (Fights cannot happen diagonally)\n";
    cout << "When 2 allies collide and one of them does not have full health it may receive a healing effect from the other.\n\n";
    this_thread::sleep_for(500ms);

    cout << "You can heal[H] your team once only at the right time of day.(Day for Vampires, Night for Werewolfs)\n";
    cout << "You can heal your team one more time if you collect the healing potion that spawns around the map.\n\n";
    this_thread::sleep_for(500ms);

    cout << "Your goal is to keep your team alive till the end of the game.\n";
    cout << "The game ends when a team has 0 alive members.\n\n";
    this_thread::sleep_for(500ms);

    cout << "You can force stop the game with [SPACEBAR] or pause/resume with [P] to view alive members of each team and how many healing potions you have.\n\n";
    this_thread::sleep_for(500ms);

    cout << "Good Luck!\n";
    this_thread::sleep_for(500ms);

    system("pause");

    system("cls");
}


char request_side() { 
    cout << endl << "Choose a side (V for Vampires or W for Werewolfs): ";
    cin >> player_support;
    if (player_support == 'V' || player_support == 'v')  {
        player_support = 'V';
        cout << player_support;
    }
    else if (player_support == 'W' || player_support == 'w') {
        player_support = 'W';
        cout << player_support;
    }
    else {
        while (player_support != 'V' && player_support != 'v' && player_support != 'W' && player_support != 'w') {
            cout << "Not right input! \n";
            cout << endl << "Choose a side (V for Vampires or W for Werewolfs): ";
            cin >> player_support;
        }
    }

    return player_support;
}







void healTeam() {

}

void printPauseMenu() {
    cout << "[Alive Vampires  : " << "##" << ']' << endl;
    cout << "[Alive Werewolfs : " << "##" << ']' << endl;
    cout << "[Avatar Potions  : " << "1 ]" << endl;
}

void pause_function() {
    if (GetKeyState('P')) {                     
        system("cls");
        printPauseMenu();   // (Show alive Vampires, alive Werewolfs and amount of potions the player has)
        system("pause");
    }
}


void printResultMenu() {
    for (int i = 0 ; i < 60 ; i++) cout << '\3';        //Start of title screen

    cout << endl << '\3';
    for (int i = 0 ; i < 58 ; i++) cout << ' '; 
    cout << '\3' << endl;

    cout << '\3';
    for (int i = 0 ; i < 22 ; i++) cout << ' ';  
    cout << "Werewolfs win!";
    for (int i = 0 ; i < 22 ; i++) cout << ' ';
    cout << '\3' << endl;

    cout << '\3';
    for (int i = 0 ; i < 58 ; i++) cout << ' '; 
    cout << '\3' << endl;

    for (int i = 0 ; i < 60 ; i++) cout << '\3'; 
    cout << "\n\n";                                  //End of title screen
}
