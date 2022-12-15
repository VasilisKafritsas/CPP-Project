#include "lib.h"
#include "classes.h"

unsigned int x, y;
char player_support;

HANDLE hConsole;

void printTitleScreen() {
	
    for (int i = 0; i < 61; i++) cout << '\4';        //Start of title screen

    cout << endl << '\4';
    for (int i = 0; i < 59; i++) cout << ' ';
    cout << '\4' << endl;

    cout << '\4';
    for (int i = 0; i < 13; i++) cout << ' ';
    cout << "Welcome to Vampires VS Werewolfs!";
    for (int i = 0; i < 13; i++) cout << ' ';
    cout << '\4' << endl;

    cout << '\4';
    for (int i = 0; i < 59; i++) cout << ' ';
    cout << '\4' << endl;

    for (int i = 0; i < 61; i++) cout << '\4';
    cout << "\n\n";                                  //End of title screen

}


void request_dimensions() {  
    do {
        cout << "Please give dimensions to create the grid(x > y recommended): " << endl;
        cin >> x;
        cin >> y; 
    } while (x < 5 || y < 5);
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
    cout << "You can heal your team one more time if you collect the healing  that spawns around the map.\n\n";
    this_thread::sleep_for(500ms);

    cout << "Your goal is to keep your team alive till the end of the game.\n";
    cout << "The game ends when a team has 0 alive members.\n\n";
    this_thread::sleep_for(500ms);

    cout << "You can force stop the game with [SPACEBAR] or pause/resume with [P] to view alive members of each team and how many healing s you have.\n\n";
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

 Potion setPotionPosition(Avatar a) {
    int potion_pos = (rand() % (x*y) + 1);
    if (potion_pos == a.get_pos()) {
        while (potion_pos == a.get_pos()) {
            potion_pos = (rand() % (x*y) + 1);
        }
    }
    Potion p(potion_pos);

    return p;
}

void fillTrees(int size, vector<Tree*>& Trees, Avatar a, Potion p) {
    int test_position;
    for (int i = 0; i < size; i++) {            //Fill Trees vector
        test_position = (rand() % (x*y) + 1); 
        for (int k = 0 ; k < i ; k++) {         //Test if pos equals to previous positions
            while (test_position == Trees[k]->get_pos() || test_position == a.get_pos() || test_position == p.get_pos()) test_position = (rand() % (x*y) + 1);
        }      
		Tree* t1 = new Tree(test_position);
		Trees.push_back(t1);
	}
}

void fillLakes(int size, vector<Tree*>& Trees, vector<Lake*>& Lakes,Avatar a, Potion p) {
    int test_position;
    for (int i = 0; i < size; i++) {           //Fill Lakes vector
        test_position = (rand() % (x*y) + 1);
        for (int j = 0 ; j < size ; j++) {
            while (test_position == Trees[j]->get_pos() || test_position == p.get_pos() || test_position == a.get_pos()) test_position = (rand() % (x*y) + 1);     
        }
        for (int k = 0 ; k < i ; k++) {         //Test if pos equals to previous positions
            while (test_position == Lakes[k]->get_pos()) test_position = (rand() % (x*y) + 1);
        }
        Lake* l1 = new Lake(test_position);
		Lakes.push_back(l1);
    }
}

void fillVampires(int obstacles_size, int vampires_size, vector<Tree*>& Trees, vector<Lake*>& Lakes, vector<Vampire*>& Vampires,Avatar a, Potion p){
    int test_position;
    for (int i = 0; i < vampires_size; i++) {           //Fill Vampires vector
        test_position = (rand() % (x*y) + 1);  
        for (int j = 0 ; j < obstacles_size ; j++) { 
            while (test_position == Trees[j]->get_pos() || test_position == Lakes[j]->get_pos() || test_position == p.get_pos() || test_position == a.get_pos()) 
                test_position = (rand() % (x*y) + 1);     
        }
        for (int k = 0 ; k < i ; k++) {         //Test if pos equals to previous positions
            while (test_position == Vampires[k]->get_pos()) test_position = (rand() % (x*y) + 1);    
        }
        Vampire* v1 = new Vampire(test_position);
		Vampires.push_back(v1);
    }
}

void fillWerewolves(int obstacles_size, int vampires_size, int werewolves_size,vector<Tree*>& Trees, vector<Lake*>& Lakes,vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a, Potion p) {
    int test_position;
    for (int i = 0; i < werewolves_size; i++) {           //Fill Werewolves vector
        test_position = (rand() % (x*y) + 1);
        for (int j = 0 ; j < obstacles_size ; j++) {
            while (test_position == Trees[j]->get_pos() || test_position == Lakes[j]->get_pos() || test_position == p.get_pos() || test_position == a.get_pos()) 
                test_position = (rand() % (x*y) + 1);
        }
        for (int m = 0 ; m < vampires_size ; m++) {
            while (test_position == Vampires[m]->get_pos()) test_position = (rand() % (x*y) + 1);
        }
        for (int k = 0 ; k < i ; k++) {         //Test if pos equals to previous positions
            while (test_position == Werewolves[k]->get_pos()) test_position = (rand() % (x*y) + 1);
        }
        Werewolf* w1 = new Werewolf(test_position);
		Werewolves.push_back(w1);
    }
}

void BubbleSortObstacles(int obstacles_size, vector<Tree*>& Trees, vector<Lake*>& Lakes) {
    Tree* t_tempPos;
    Lake* l_tempPos;
    for (int i = 0 ; i < obstacles_size ; i++) {            //bubblesort Trees and Lakes vectors in ascending order
        for (int j = i+1 ; j < obstacles_size ; j++) {      
            if (Trees[i]->get_pos() > Trees[j]->get_pos()) {
                t_tempPos = Trees[i];
                Trees[i] = Trees[j];
                Trees[j] = t_tempPos;
            }

            if (Lakes[i]->get_pos() > Lakes[j]->get_pos()) {
                l_tempPos = Lakes[i];
                Lakes[i] = Lakes[j];
                Lakes[j] = l_tempPos;
            }
        }
    }
}

void BubbleSortEntities(int vampires_size, int werewolves_size, vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves) {
    Vampire* v_tempPos;
    Werewolf* w_tempPos;
    for (int i = 0 ; i < vampires_size ; i++) {                 //bubblesort Vampires vector in ascending order
        for (int j = i+1 ; j < vampires_size ; j++) {      
            if (Vampires[i]->get_pos() > Vampires[j]->get_pos()) {
                v_tempPos = Vampires[i];
                Vampires[i] = Vampires[j];
                Vampires[j] = v_tempPos;
            }
        }
    }

    for (int i = 0 ; i < werewolves_size ; i++) {                 //bubblesort Werewolves vector in ascending order
        for (int j = i+1 ; j < werewolves_size ; j++) {
            if (Werewolves[i]->get_pos() > Werewolves[j]->get_pos()) {
                    w_tempPos = Werewolves[i];
                    Werewolves[i] = Werewolves[j];
                    Werewolves[j] = w_tempPos;
            }
        }
    }
}

int AvatarMovement(int obstacles_size, int vampires_size, int werewolves_size, vector<Tree*>& Trees, vector<Lake*>& Lakes,vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a) {
    int tempPos;
    bool collision = false;
    if (GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP)) {    //WWW
            tempPos = a.get_pos() - x;

            for (int t = 0 ; t < vampires_size ; t++) {
                if ( tempPos == Vampires[t]->get_pos()) collision = true; //if next move does not collide with another object
            }
             for (int t = 0 ; t < werewolves_size ; t++) {
                 if( tempPos == Werewolves[t]->get_pos())collision = true;
             }
            for (int t = 0 ; t < obstacles_size ; t++) if (tempPos == Trees[t]->get_pos() || tempPos == Lakes[t]->get_pos()) collision = true;

            if (tempPos > 0 && !collision) return tempPos;
    } 
    else if (GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN)) {   //SSS
            tempPos = a.get_pos() + x;

             for (int t = 0 ; t < vampires_size ; t++) {
                if ( tempPos == Vampires[t]->get_pos()) collision = true; //if next move does not collide with another object
            }
             for (int t = 0 ; t < werewolves_size ; t++) {
                 if( tempPos == Werewolves[t]->get_pos())collision = true;
             }
            for (int t = 0 ; t < obstacles_size ; t++) if (tempPos == Trees[t]->get_pos() || tempPos == Lakes[t]->get_pos()) collision = true;

            if (tempPos <= x*y && !collision) return tempPos;
    } 
    else if (GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT)) {   //AAA
            tempPos = a.get_pos() - 1;

            for (int t = 0 ; t < vampires_size ; t++) {
                if ( tempPos == Vampires[t]->get_pos()) collision = true; //if next move does not collide with another object
            }
            for (int t = 0 ; t < werewolves_size ; t++) {
                 if( tempPos == Werewolves[t]->get_pos())collision = true;
            }     
            for (int t = 0 ; t < obstacles_size ; t++) if (tempPos == Trees[t]->get_pos() || tempPos == Lakes[t]->get_pos()) collision = true;

            for (int i = 1 ; i <= y ; i++) if (tempPos == x*i) collision = true;

            if (tempPos > 0 && !collision) return tempPos;
    }
    else if (GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT)) {  ///DDD
            tempPos = a.get_pos() + 1;

            for (int t = 0 ; t < vampires_size ; t++) {
                if ( tempPos == Vampires[t]->get_pos()) collision = true; //if next move does not collide with another object
            }
            for (int t = 0 ; t < werewolves_size ; t++) {
                 if( tempPos == Werewolves[t]->get_pos())collision = true;
            }
            for (int t = 0 ; t < obstacles_size ; t++) if (tempPos == Trees[t]->get_pos() || tempPos == Lakes[t]->get_pos()) collision = true;

            for (int i = 1 ; i <= y ; i++) if (tempPos == x*i+1) collision = true;  

            if (tempPos <= x*y && !collision) return tempPos;
    } 
    return a.get_pos();
}

int getStartingHealth(vector<Vampire*>& Vampires, int vampires_size) {
    int starting_health = 0;

    for (int i = 0 ; i < vampires_size ; i++) {
        starting_health += Vampires[i]->get_health();
    }

    return starting_health;
}

void PrintTeamHealth(vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, int vampires_size, int werewolves_size, int starting_health) {
    int werewolves_health = 0, vampires_health = 0;

    for (int i = 0 ; i < werewolves_size ; i++) {
        werewolves_health += Werewolves[i]->get_health();
    }
    for (int i = 0 ; i < vampires_size ; i++) {
        vampires_health += Vampires[i]->get_health();
    }

    cout << "    W: " << werewolves_health << '/' << starting_health << "    V: " << vampires_health << '/' << starting_health << endl;

}

void PrintMap(int obstacles_size, int vampires_size, int werewolves_size,vector<Tree*>& Trees, vector<Lake*>& Lakes,vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a, Potion p) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    for (int i = 0 ; i < x+2 ; i++) cout << '-';  //Upper Border
        cout << endl;

        int la = 0, tr = 0, va = 0, we = 0;

        for (int i = 0 ; i < y ; i++) {                       
            cout << "|";                   //left border   
            for(int j=0 ; j < x ; j++){
                if(Vampires[va]->get_pos()==(i*x)+j+1){
                    SetConsoleTextAttribute(hConsole, 13);
                    cout << 'V';
                    SetConsoleTextAttribute(hConsole, 7);
                    if (va < vampires_size-1) va++;
                }
                else if(Werewolves[we]->get_pos()==(i*x)+j+1){
                    SetConsoleTextAttribute(hConsole, 4);
                    cout << 'W';
                    SetConsoleTextAttribute(hConsole, 7);
                    if (we < werewolves_size-1) we++;
                }
                else if(Trees[tr]->get_pos()==(i*x)+j+1){
                    SetConsoleTextAttribute(hConsole, 10); 
                    cout << 'T';
                    SetConsoleTextAttribute(hConsole, 7);
                    if (tr < obstacles_size-1) tr++;    
                }
                else if(Lakes[la]->get_pos()==(i*x)+j+1){
                    SetConsoleTextAttribute(hConsole, 3);
                    cout << 'O';
                    SetConsoleTextAttribute(hConsole, 7);
                    if (la < obstacles_size-1) la++;
                }
                
                else if (p.get_pos()==(i*x)+j+1) {
                    cout << '+';
                }
                else if (a.get_pos() == (i*x)+j+1){
                    cout << 'P';
                    continue;
                }
                else if (j != x) cout << ' ';
                       
                
                    
            }

            
            cout << "|\n";                       //right border
        }

        for (int i = 0 ; i < x+2 ; i++) cout << '-';   //Lower Border      
        cout << endl;
}

void moveWerewolves(int obstacles_size, int vampires_size, int werewolves_size, vector<Tree*>& Trees, vector<Lake*>& Lakes,vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a, Potion p) {
    int move_optionW, tempPos; 
    bool collision = false;

    for (int i = 0 ; i < werewolves_size ; i++) {
        move_optionW = (rand() % 5);
            
        switch (move_optionW) {  //Moves for Werewolves
            case 0:  //STAY
                break;
            case 1:  //UP
                collision = false;
                tempPos = Werewolves[i]->get_pos() - x;

                for (int j = 0 ; j < werewolves_size ; j++) {
                if (tempPos == Werewolves[j]->get_pos()) //if next move does not collide with another object
                    if (Werewolves[i] != Werewolves[j]) collision = true; //don't test collision with self
                }
                for (int j = 0 ; j < vampires_size ; j++){
                    if(tempPos == Vampires[j]->get_pos())collision = true;
                }
                for (int j = 0 ; j < obstacles_size ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                if (tempPos > 0 && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Werewolves[i]->set_pos(tempPos);
                break;
            case 2:  //DOWN
                collision = false;
                tempPos = Werewolves[i]->get_pos() + x;

                for (int j = 0 ; j < werewolves_size ; j++) {
                if (tempPos == Werewolves[j]->get_pos()) //if next move does not collide with another object
                    if (Werewolves[i] != Werewolves[j]) collision = true; //don't test collision with self
                }
                for (int j = 0 ; j < vampires_size ; j++){
                    if(tempPos == Vampires[j]->get_pos())collision = true;
                }
                for (int j = 0 ; j < obstacles_size ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                if (tempPos <= x*y && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Werewolves[i]->set_pos(tempPos);
                break;
            case 3:  //LEFT
                tempPos = Werewolves[i]->get_pos() - 1;

                for (int j = 0 ; j < werewolves_size ; j++) {
                if (tempPos == Werewolves[j]->get_pos()) //if next move does not collide with another object
                    if (Werewolves[i] != Werewolves[j]) collision = true; //don't test collision with self
                }
                for (int j = 0 ; j < vampires_size ; j++){
                    if(tempPos == Vampires[j]->get_pos())collision = true;
                }
                for (int j = 0 ; j < obstacles_size ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                for (int j = 1 ; j <= y ; j++) if (tempPos == x*j) collision = true;  

                if (tempPos > 0 && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Werewolves[i]->set_pos(tempPos);
                break;
            case 4: //RIGHT
                tempPos = Werewolves[i]->get_pos() + 1;

                for (int j = 0 ; j < werewolves_size ; j++) {
                if (tempPos == Werewolves[j]->get_pos()) //if next move does not collide with another object
                    if (Werewolves[i] != Werewolves[j]) collision = true; //don't test collision with self
                }
                for (int j = 0 ; j < vampires_size ; j++){
                    if(tempPos == Vampires[j]->get_pos())collision = true;
                }
                for (int j = 0 ; j < obstacles_size ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                for (int j = 1 ; j <= y ; j++) if (tempPos == x*j+1) collision = true;  

                if (tempPos <= x*y && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Werewolves[i]->set_pos(tempPos);
                break;
        }
    }
}


void moveVampires(int obstacles_size, int vampires_size, int werewolves_size, vector<Tree*>& Trees, vector<Lake*>& Lakes,vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a, Potion p) {
    int move_optionV, tempPos; 
    bool collision = false; 

    for (int i = 0 ; i < vampires_size ; i++) {
            move_optionV = (rand() % 9);
            switch (move_optionV) {  //Moves for Vampires
                case 0:  //STAY
                    break;
                case 1:  //UP -=x
                    tempPos = Vampires[i]->get_pos() - x;

                    for (int j = 0 ; j < vampires_size ; j++) {
                    if ( tempPos == Vampires[j]->get_pos()) //if next move does not collide with another object
                        if (Vampires[i] != Vampires[j]) collision = true; //don't test collision with self
                    }
                    for (int j = 0 ; j < werewolves_size ; j++) {
                        if(tempPos == Werewolves[j]->get_pos())collision = true;
                    }
                    for (int j = 0 ; j < obstacles_size ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                    if (tempPos > 0 && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Vampires[i]->set_pos(tempPos);
                    break;
                case 2:  //DOWN += x
                    tempPos = Vampires[i]->get_pos() + x;

                    for (int j = 0 ; j < vampires_size ; j++) {
                    if ( tempPos == Vampires[j]->get_pos()) //if next move does not collide with another object
                        if (Vampires[i] != Vampires[j]) collision = true; //don't test collision with self
                    }
                    for (int j = 0 ; j < werewolves_size ; j++) {
                        if(tempPos == Werewolves[j]->get_pos())collision = true;
                    }
                    for (int j = 0 ; j < obstacles_size ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                    if (tempPos <= x*y && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Vampires[i]->set_pos(tempPos);
                    break;
                case 3:  //LEFT -= 1
                    tempPos = Vampires[i]->get_pos() - 1;

                    for (int j = 0 ; j < vampires_size ; j++) {
                    if ( tempPos == Vampires[j]->get_pos()) //if next move does not collide with another object
                        if (Vampires[i] != Vampires[j]) collision = true; //don't test collision with self
                    }
                    for (int j = 0 ; j < werewolves_size ; j++) {
                        if(tempPos == Werewolves[j]->get_pos())collision = true;
                    }
                    for (int j = 0 ; j < obstacles_size ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                    for (int j = 1 ; j <= y ; j++) if (tempPos == x*j) collision = true;  

                    if (tempPos > 0 && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Vampires[i]->set_pos(tempPos);
                    break;
                case 4: //RIGHT += 1
                    tempPos = Vampires[i]->get_pos() + 1;

                    for (int j = 0 ; j < vampires_size ; j++) {
                    if ( tempPos == Vampires[j]->get_pos()) //if next move does not collide with another object
                        if (Vampires[i] != Vampires[j]) collision = true; //don't test collision with self
                    }
                    for (int j = 0 ; j < werewolves_size ; j++) {
                        if(tempPos == Werewolves[j]->get_pos())collision = true;
                    }
                    for (int j = 0 ; j < obstacles_size ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                    for (int j = 1 ; j <= y ; j++) if (tempPos == x*j+1) collision = true;  

                    if (tempPos <= x*y && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Vampires[i]->set_pos(tempPos);
                    break;
                case 5: //UP_LEFT -= (x+1)
                    tempPos = Vampires[i]->get_pos() - (x+1);

                    for (int j = 0 ; j < vampires_size ; j++) {
                    if ( tempPos == Vampires[j]->get_pos()) //if next move does not collide with another object
                        if (Vampires[i] != Vampires[j]) collision = true; //don't test collision with self
                    }
                    for (int j = 0 ; j < werewolves_size ; j++) {
                        if(tempPos == Werewolves[j]->get_pos())collision = true;
                    }
                    for (int j = 0 ; j < obstacles_size ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                    for (int j = 1 ; j <= y ; j++) if (tempPos == x*j) collision = true;  

                    if (tempPos > 0 && tempPos <= x*y && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Vampires[i]->set_pos(tempPos);
                    break;
                case 6: //UP_RIGHT -= (x-1)
                    tempPos = Vampires[i]->get_pos() - (x-1);

                    for (int j = 0 ; j < vampires_size ; j++) {
                    if ( tempPos == Vampires[j]->get_pos()) //if next move does not collide with another object
                        if (Vampires[i] != Vampires[j]) collision = true; //don't test collision with self
                    }
                    for (int j = 0 ; j < werewolves_size ; j++) {
                        if(tempPos == Werewolves[j]->get_pos())collision = true;
                    }
                    for (int j = 0 ; j < obstacles_size ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                    for (int j = 1 ; j <= y ; j++) if (tempPos == x*j+1) collision = true; 

                    if (tempPos > 0 && tempPos <= x*y && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Vampires[i]->set_pos(tempPos);
                    break;
                case 7: //DOWN_LEFT += (x-1)
                    tempPos = Vampires[i]->get_pos() + (x-1);

                    for (int j = 0 ; j < vampires_size ; j++) {
                    if ( tempPos == Vampires[j]->get_pos()) //if next move does not collide with another object
                        if (Vampires[i] != Vampires[j]) collision = true; //don't test collision with self
                    }
                    for (int j = 0 ; j < werewolves_size ; j++) {
                        if(tempPos == Werewolves[j]->get_pos())collision = true;
                    }
                    for (int j = 0 ; j < obstacles_size ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                    for (int j = 1 ; j <= y ; j++) if (tempPos == x*j) collision = true;  

                    if (tempPos > 0 && tempPos <= x*y && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Vampires[i]->set_pos(tempPos);
                    break;
                case 8: //DOWN_RIGHT += (x+1)
                    tempPos = Vampires[i]->get_pos() + (x+1);

                    for (int j = 0 ; j < vampires_size ; j++) {
                    if ( tempPos == Vampires[j]->get_pos()) //if next move does not collide with another object
                        if (Vampires[i] != Vampires[j]) collision = true; //don't test collision with self
                    }
                    for (int j = 0 ; j < werewolves_size ; j++) {
                        if(tempPos == Werewolves[j]->get_pos())collision = true;
                    }
                    for (int j = 0 ; j < obstacles_size ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                    for (int j = 1 ; j <= y ; j++) if (tempPos == x*j+1) collision = true; 

                    if (tempPos > 0 && tempPos <= x*y && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Vampires[i]->set_pos(tempPos);
                    break;
            } 
        }
}

void vamps_attack(int vampires_size, int werewolves_size, vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves ){
     for (int i = 0 ; i < vampires_size ; i++){  //Vampires Attack
        int battle_pos = Vampires[i]->get_pos();
        for (int j = 0 ; j < werewolves_size ; j++){
            if(battle_pos == Werewolves[j]->get_pos()-x || battle_pos == Werewolves[j]->get_pos()+x || battle_pos == Werewolves[j]->get_pos()-1 || battle_pos == Werewolves[j]->get_pos()+1){
                if(Vampires[i]->get_strength() >= Werewolves[j]->get_strength() && Vampires[i]->get_strength() >= Werewolves[j]->get_defense()){
                    Vampires[i]->attackW(Werewolves[j]);
                }
                // Werewolf* w=Werewolves[j];
                // if (w->get_health() <= 0) {
                //     delete w;
                //     w=NULL;
                //     werewolves_size--;
                // }
            }
        }
    }
}

void vamps_heal(int vampires_size, vector<Vampire*>& Vampires) {
   for (int i = 0 ; i < vampires_size ; i++){   //Vampires Heal
        int assist_pos = Vampires[i]->get_pos();
        bool choice;
        for (int j = 0 ; j < vampires_size ; j++){
            choice = (rand() % 2);
            if(assist_pos == Vampires[j]->get_pos()-x || assist_pos == Vampires[j]->get_pos()+x || assist_pos == Vampires[j]->get_pos()-1 || assist_pos == Vampires[j]->get_pos()+1){
                if(Vampires[i]->get_health() > Vampires[j]->get_health() && Vampires[i]->get_healing()>0 && choice){
                    Vampires[j]->set_health((Vampires[j]->get_health())+1);
                    Vampires[i]->set_healing((Vampires[i]->get_healing())-1);
                }
            }
        }
    } 
}

void weres_attack(int vampires_size, int werewolves_size, vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves ){
     for (int i = 0 ; i < werewolves_size ; i++){  //Vampires Attack
        int battle_pos = Werewolves[i]->get_pos();
        for (int j = 0 ; j < vampires_size ; j++){
            if(battle_pos == Vampires[j]->get_pos()-x || battle_pos == Vampires[j]->get_pos()+x || battle_pos == Vampires[j]->get_pos()-1 || battle_pos == Vampires[j]->get_pos()+1){
                if(Werewolves[i]->get_strength() >= Vampires[j]->get_strength() && Werewolves[i]->get_strength() >= Vampires[j]->get_defense()){
                    Werewolves[i]->attackV(Vampires[j]);
                }
                // Vampire* v = Vampires[j];
                // if (v->get_health()<=0) {
                //     delete v;
                //     v=NULL;
                //     vampires_size--;
                // }
            }
        }
    }
}

void weres_heal(int werewolves_size, vector<Werewolf*>& Werewolves) {
    for (int i = 0 ; i < werewolves_size ; i++){   
        int assist_pos = Werewolves[i]->get_pos();
        bool choice;
        for (int j = 0 ; j < werewolves_size ; j++){
            choice = (rand() % 2);
            if(assist_pos == Werewolves[j]->get_pos()-x || assist_pos == Werewolves[j]->get_pos()+x || assist_pos == Werewolves[j]->get_pos()-1 || assist_pos == Werewolves[j]->get_pos()+1){
                if(Werewolves[i]->get_health() > Werewolves[j]->get_health() && Werewolves[i]->get_healing()>0 && choice){
                    Werewolves[j]->set_health((Werewolves[j]->get_health())+1);
                    Werewolves[i]->set_healing((Werewolves[i]->get_healing())-1);
                }
            }
        }
    } 
}

int check_healthV(int vampires_size, vector<Vampire*>& Vampires) {
    for (int i = 0 ; i < vampires_size ; i++) {
        Vampire* v= Vampires[i];
        if (v->get_health()<=0) {
            delete v;
            v=NULL;
            vampires_size--;
        }
    }
    return vampires_size;
}

int check_healthW(int werewolves_size, vector<Werewolf*>& Werewolves){
    for (int i = 0 ; i < werewolves_size ; i++) {
        Werewolf* w=Werewolves[i];
        if (w->get_health() <= 0) {
            delete w;
            w=NULL;
            werewolves_size--;
        }
    }
    return werewolves_size;
}

void heal(Avatar a, char p_support,bool Day, int vampires_size,int werewolves_size, vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves){
     if(GetAsyncKeyState('H')){
        if(a.get_pot()>0){
            a.heal();
            if(p_support == 'V' && Day){
                for(int i = 0; i < vampires_size ; i++) Vampires[i]->heal();
            }
            else if(p_support == 'W' && !Day){
                for(int i = 0; i < werewolves_size ; i++) Werewolves[i]->heal();
            }
        }

    }
}

void pause_function(int vampires_size, int werewolves_size, Avatar a) {
    if (GetKeyState('P')) {                     
        system("cls");
        cout << "[Alive Vampires  : " <<  vampires_size << ']' << endl;
        cout << "[Alive Werewolfs : " << werewolves_size << ']' << endl;
        cout << "[Avatar potions  : " << a.get_pot() << endl;
        system("pause");
    }
}

bool ChangeDay(int counter, bool Day) {
    if (counter % 10 == 0) Day = !Day;

    return Day;
}

void EndScreen(int werewolves_size) {
    for (int i = 0 ; i < 60 ; i++) cout << '\4';        //End screen

    cout << endl << '\4';
    for (int i = 0 ; i < 58 ; i++) cout << ' '; 
    cout << '\4' << endl;

    cout << '\4';
    for (int i = 0 ; i < 22 ; i++) cout << ' ';  
    if(werewolves_size > 0)cout << "Werewolves win!";
    else cout<<"Vampires win!";
    if(werewolves_size > 0) for (int i = 0 ; i < 21 ; i++) cout << ' ';
    else for (int i = 0 ; i < 23 ; i++) cout << ' ';
    cout << '\4' << endl;
    cout << '\4';
    for (int i = 0 ; i < 58 ; i++) cout << ' '; 
    cout << '\4' << endl;
    for (int i = 0 ; i < 60 ; i++) cout << '\4'; 
    cout << "\n\n"; 
}