/* Ορισμός συναρτήσεων */

#include "lib.h"
#include "classes.h"

unsigned int x, y; //Μεταβλητές για τις διαστάσεις
char player_support; //Μεταβλητή για το ποια ομάδα υποστηρίζει ο παίχτης

HANDLE hConsole;

void printTitleScreen() { //Εκτύπωση Τίτλου Παιχιδιού
	
    for (int i = 0; i < 61; i++) cout << '\4';  // '\4'= ρόμβος      

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
    cout << "\n\n";                                  

}


void request_dimensions() {  ////Εισαγωγή διαστάσεων
    do {
        cout << "Please give dimensions to create the grid(x,y >= 5): " << endl;
        cin >> x;
        cin >> y; 
    } while (x < 5 || y < 5); //Απαίτηση χ και y μεγαλύτερο του 5
}




void printInstructions() { //Εκτύπωση οδηγιών με πάυσεις
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

    system("pause"); //Αναμονή εκκίνησης παιχνιδιού από τον παίκτη

    system("cls");
}


char request_side() { //Επιλογή ομάδας παίκτη 
    cout << endl << "Choose a side (V for Vampires or W for Werewolfs): ";
    cin >> player_support;
    if (player_support == 'V' || player_support == 'v')  { //v ή V για Vampires
        player_support = 'V';
        cout << player_support;
    }
    else if (player_support == 'W' || player_support == 'w') { //w ή W για Werewolves
        player_support = 'W';
        cout << player_support;
    }
    else {
        while (player_support != 'V' && player_support != 'v' && player_support != 'W' && player_support != 'w') { //Έλεγχος σωστού input
            cout << "Not right input! \n";
            cout << endl << "Choose a side (V for Vampires or W for Werewolfs): ";
            cin >> player_support;
        }
    }

    return player_support;
}

 Potion setPotionPosition(Avatar a) { //Eύρεση κατάλληλης θέσης για το μαγικό φίλτρο στο χάρτη
    int potion_pos = (rand() % (x*y) + 1); //Τυχαία θέση
    if (potion_pos == a.get_pos()) { //Έλεγχος σύμπτωσης θέσης με τον παίκτη
        while (potion_pos == a.get_pos()) {
            potion_pos = (rand() % (x*y) + 1);
        }
    }
    Potion p(potion_pos); //Κάλεσμα constructor του Potion

    return p;
}

void fillTrees(int size,vector<Tree*>& Trees, Avatar a, Potion p) { //Γέμισμα του vector των Trees με αντικείμενα Tree
    int test_position;
    for (int i = 0; i < size; i++) {            
        test_position = (rand() % (x*y) + 1); //Εύρεση τυχαίας θέσης για τα Trees στο χάρτη
        for (int k = 0 ; k < i ; k++) {         
            while (test_position == Trees[k]->get_pos() || test_position == a.get_pos() || test_position == p.get_pos()) test_position = (rand() % (x*y) + 1); //Έλεγχος σύμπτωσης θέσης με τις ήδη ορισμένες θέσεις
        }      
		Tree* t1 = new Tree(test_position); //Δημιουργία pointer σε αντικείμενο Tree 
		Trees.push_back(t1); //Εισαγωγή του pointer στον vector Trees
	}
}

void fillLakes(int size,vector<Tree*>& Trees, vector<Lake*>& Lakes,Avatar a, Potion p) { //Γέμισμα του vector των Lakes με αντικείμενα Lake
    int test_position;
    for (int i = 0; i < size; i++) {           
        test_position = (rand() % (x*y) + 1); //Εύρεση τυχαίας θέσης για τα Lakes στο χάρτη
        for (int j = 0 ; j < size ; j++) {
            while (test_position == Trees[j]->get_pos() || test_position == p.get_pos() || test_position == a.get_pos()) test_position = (rand() % (x*y) + 1); //Έλεγχος σύμπτωσης θέσης με τις ήδη ορισμένες θέσεις     
        }
        for (int k = 0 ; k < i ; k++) {         
            while (test_position == Lakes[k]->get_pos()) test_position = (rand() % (x*y) + 1); //Έλεγχος σύμπτωσης θέσης με τις ήδη ορισμένες θέσεις     
        }
        Lake* l1 = new Lake(test_position); //Δημιουργία pointer σε αντικείμενο Lake
		Lakes.push_back(l1); //Εισαγωγή του pointer στον vector Lakes
    }
}

void fillVampires(int size,vector<Tree*>& Trees, vector<Lake*>& Lakes, vector<Vampire*>& Vampires,Avatar a, Potion p){ //Γέμισμα του vector των Vampires με αντικείμενα Vampire
    int test_position;
    for (int i = 0; i < size; i++) {         
        test_position = (rand() % (x*y) + 1); //Εύρεση τυχαίας θέσης για τα Vampires στο χάρτη  
        for (int j = 0 ; j < Trees.size() ; j++) { 
            while (test_position == Trees[j]->get_pos() || test_position == Lakes[j]->get_pos() || test_position == p.get_pos() || test_position == a.get_pos())  //Έλεγχος σύμπτωσης θέσης με τις ήδη ορισμένες θέσεις   
                test_position = (rand() % (x*y) + 1);     
        }
        for (int k = 0 ; k < i ; k++) {     
            while (test_position == Vampires[k]->get_pos()) test_position = (rand() % (x*y) + 1); //Έλεγχος σύμπτωσης θέσης με τις ήδη ορισμένες θέσεις       
        }
        Vampire* v1 = new Vampire(test_position); //Δημιουργία pointer σε αντικείμενο Vampire
		Vampires.push_back(v1); //Εισαγωγή του pointer στον vector Vampires
    }
}

void fillWerewolves(int size,vector<Tree*>& Trees, vector<Lake*>& Lakes,vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a, Potion p) { //Γέμισμα του vector των Werewolves με αντικείμενα Vampire
    int test_position;
    for (int i = 0; i < size; i++) {
        test_position = (rand() % (x*y) + 1); //Εύρεση τυχαίας θέσης για τα Werewolves στο χάρτη 
        for (int j = 0 ; j < Lakes.size() ; j++) {
            while (test_position == Trees[j]->get_pos() || test_position == Lakes[j]->get_pos() || test_position == p.get_pos() || test_position == a.get_pos()) //Έλεγχος σύμπτωσης θέσης με τις ήδη ορισμένες θέσεις   
                test_position = (rand() % (x*y) + 1);
        }
        for (int m = 0 ; m < Vampires.size() ; m++) {
            while (test_position == Vampires[m]->get_pos()) test_position = (rand() % (x*y) + 1); //Έλεγχος σύμπτωσης θέσης με τις ήδη ορισμένες θέσεις   
        }
        for (int k = 0 ; k < i ; k++) {         //Test if pos equals to previous positions
            while (test_position == Werewolves[k]->get_pos()) test_position = (rand() % (x*y) + 1); //Έλεγχος σύμπτωσης θέσης με τις ήδη ορισμένες θέσεις   
        }
        Werewolf* w1 = new Werewolf(test_position); //Δημιουργία pointer σε αντικείμενο Werewolf
		Werewolves.push_back(w1); //Εισαγωγή του pointer στον vector Werewolves
    }
}

void BubbleSortObstacles(vector<Tree*>& Trees, vector<Lake*>& Lakes) { //Ταξινόμηση BubbleSort των εμποδίων σε άυξουσα σειρά
    Tree* t_tempPos;
    Lake* l_tempPos;
    for (int i = 0 ; i < Trees.size() ; i++) {       
        for (int j = i+1 ; j <Trees.size(); j++) {      
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

void BubbleSortEntities(vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves) { //Ταξινόμηση BubbleSort των οντοτήτων σε άυξουσα σειρά
    Vampire* v_tempPos;
    Werewolf* w_tempPos;
    for (int i = 0 ; i < Vampires.size() ; i++) {           //Ταξινόμηση για τον vector Vampires        
        for (int j = i+1 ; j < Vampires.size() ; j++) {      
            if (Vampires[i]->get_pos() > Vampires[j]->get_pos()) {
                v_tempPos = Vampires[i];
                Vampires[i] = Vampires[j];
                Vampires[j] = v_tempPos;
            }
        }
    }

    for (int i = 0 ; i < Werewolves.size() ; i++) {           //Ταξινόμηση για τον vector Werewolves     
        for (int j = i+1 ; j < Werewolves.size() ; j++) {
            if (Werewolves[i]->get_pos() > Werewolves[j]->get_pos()) {
                    w_tempPos = Werewolves[i];
                    Werewolves[i] = Werewolves[j];
                    Werewolves[j] = w_tempPos;
            }
        }
    }
}

int AvatarMovement(vector<Tree*>& Trees, vector<Lake*>& Lakes,vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a) { //Κίνηση του avatar από τον παίκτη
    int tempPos;
    bool collision = false;
    if (GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP)) {     //Κίνηση προς τα πάνω 
            tempPos = a.get_pos() - x;

            //Έλεγχος σύγκρουσης με εμπόδια ή με οντότητες ή με το border 
            for (int t = 0 ; t < Vampires.size() ; t++) {
                if ( tempPos == Vampires[t]->get_pos()) collision = true;   
            }
             for (int t = 0 ; t < Werewolves.size() ; t++) {
                 if( tempPos == Werewolves[t]->get_pos())collision = true;
             }
            for (int t = 0 ; t < Trees.size() ; t++) if (tempPos == Trees[t]->get_pos() || tempPos == Lakes[t]->get_pos()) collision = true;

            if (tempPos > 0 && !collision) return tempPos; //Επιστροφή έγκυρης θέσης
    } 
    else if (GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN)) {   //Κίνηση προς τα κάτω
            tempPos = a.get_pos() + x;

            //Έλεγχος σύγκρουσης με εμπόδια ή με οντότητες ή με το border
             for (int t = 0 ; t < Vampires.size() ; t++) {
                if ( tempPos == Vampires[t]->get_pos()) collision = true; 
            }
             for (int t = 0 ; t <  Werewolves.size()  ; t++) {
                 if( tempPos == Werewolves[t]->get_pos())collision = true;
             }
            for (int t = 0 ; t < Trees.size() ; t++) if (tempPos == Trees[t]->get_pos() || tempPos == Lakes[t]->get_pos()) collision = true;

            if (tempPos <= x*y && !collision) return tempPos; //Επιστροφή έγκυρης θέσης
    } 
    else if (GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT)) {   //Κίνηση προς τα αριστερά
            tempPos = a.get_pos() - 1;

            //Έλεγχος σύγκρουσης με εμπόδια ή με οντότητες ή με το border 
            for (int t = 0 ; t <  Vampires.size() ; t++) {
                if ( tempPos == Vampires[t]->get_pos()) collision = true; 
            }
            for (int t = 0 ; t < Werewolves.size() ; t++) {
                 if( tempPos == Werewolves[t]->get_pos())collision = true;
            }     
            for (int t = 0 ; t < Trees.size() ; t++) if (tempPos == Trees[t]->get_pos() || tempPos == Lakes[t]->get_pos()) collision = true;

            for (int i = 1 ; i <= y ; i++) if (tempPos == x*i) collision = true;

            if (tempPos > 0 && !collision) return tempPos; //Επιστροφή έγκυρης θέσης
    }
    else if (GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT)) {  //Κίνηση προς τα δεξιά
            tempPos = a.get_pos() + 1;

            //Έλεγχος σύγκρουσης με εμπόδια ή με οντότητες ή με το border
            for (int t = 0 ; t < Vampires.size() ; t++) {
                if ( tempPos == Vampires[t]->get_pos()) collision = true; 
            }
            for (int t = 0 ; t < Werewolves.size() ; t++) {
                 if( tempPos == Werewolves[t]->get_pos())collision = true;
            }
            for (int t = 0 ; t < Trees.size() ; t++) if (tempPos == Trees[t]->get_pos() || tempPos == Lakes[t]->get_pos()) collision = true;

            for (int i = 1 ; i <= y ; i++) if (tempPos == x*i+1) collision = true;  

            if (tempPos <= x*y && !collision) return tempPos; //Επιστροφή έγκυρης θέσης
    } 
    return a.get_pos(); //default τιμή
}

int getStartingHealth(vector<Vampire*>& Vampires) { //Υπολογισμός αρχικής υγείας
    int starting_health = 0;

    for (int i = 0 ; i < Vampires.size() ; i++) {
        starting_health += Vampires[i]->get_health();
    }

    return starting_health;
}

void PrintTeamHealth(vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, int starting_health) { //Εκτύπωση συνολικής υγείας κάθε ομάδας
    int werewolves_health = 0, vampires_health = 0;

    for (int i = 0 ; i < Werewolves.size() ; i++) {
        werewolves_health += Werewolves[i]->get_health();
    }
    for (int i = 0 ; i <Vampires.size() ; i++) {
        vampires_health += Vampires[i]->get_health();
    }

    cout << "    W: " << werewolves_health << '/' << starting_health << "    V: " << vampires_health << '/' << starting_health << endl;

}

void PrintMap(vector<Tree*>& Trees, vector<Lake*>& Lakes,vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a, Potion p) { //Εκτύπωση χάρτη
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Εντολή χρωμάτων (από την βιβλιοθήκη windows.h)
    
    for (int i = 0 ; i < x+2 ; i++) cout << '-';  //Άνω border χάρτη
        cout << endl;

        int la = 0, tr = 0, va = 0, we = 0; //Αρχικοποίηση των indexes για κάθε στοιχείο

        for (int i = 0 ; i < y ; i++) {                       
            cout << "|";                //Aριστερό border   
            for(int j=0 ; j < x ; j++){ //Σειριακή εκτύπωση στοιχείων μέσα στο χάρτη ανάλογα με τη θέση
                if(Vampires[va]->get_pos()==(i*x)+j+1){ 
                    SetConsoleTextAttribute(hConsole, 13); //Ορισμός μωβ χρώματος (13)
                    cout << 'V'; //Εκτύπωση V για τα Vampires
                    SetConsoleTextAttribute(hConsole, 7); //Επαναφορά χρώματος στο λευκό 
                    if (va < Vampires.size()-1) va++; //Αύξηση του index κάθε φορά που τυπώνεται
                }
                else if(Werewolves[we]->get_pos()==(i*x)+j+1){
                    SetConsoleTextAttribute(hConsole, 4); //Ορισμός κόκκινου χρώματος (4)
                    cout << 'W'; //Εκτύπωση W για τα Werewolves
                    SetConsoleTextAttribute(hConsole, 7); //Επαναφορά χρώματος στο λευκό
                    if (we < Werewolves.size()-1) we++; //Αύξηση του index κάθε φορά που τυπώνεται
                }
                else if(Trees[tr]->get_pos()==(i*x)+j+1){
                    SetConsoleTextAttribute(hConsole, 10); //Ορισμός πράσινου χρώματος (10)
                    cout << 'T'; //Εκτύπωση Τ για τα Τrees
                    SetConsoleTextAttribute(hConsole, 7); //Επαναφορά χρώματος στο λευκό
                    if (tr < Trees.size()-1) tr++; //Αύξηση του index κάθε φορά που τυπώνεται   
                }
                else if(Lakes[la]->get_pos()==(i*x)+j+1){
                    SetConsoleTextAttribute(hConsole, 3); //Ορισμός πράσινου χρώματος (10)
                    cout << 'O'; //Εκτύπωση O για τα Lakes
                    SetConsoleTextAttribute(hConsole, 7); //Επαναφορά χρώματος στο λευκό
                    if (la < Lakes.size()-1) la++; //Αύξηση του index κάθε φορά που τυπώνεται
                }
                
                else if (p.get_pos()==(i*x)+j+1) {
                    cout << '+'; //Εκτύπωση + για το μαγικό φίλτρο
                }
                else if (a.get_pos() == (i*x)+j+1){
                    cout << 'P'; //Εκτύπωση P για τον Avatar
                    continue;
                }
                else if (j != x) cout << ' '; //Εκτύπωση κενού εκτός απο την περίπτωση που τυπωθεί στοιχείο σε δεξιά άκρη του χάρτη     
            }

            
            cout << "|\n";                       //Δεξί border
        }

        for (int i = 0 ; i < x+2 ; i++) cout << '-';   //Κάτω Border      
        cout << endl;
}

void moveWerewolves(vector<Tree*>& Trees, vector<Lake*>& Lakes,vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a, Potion p) { //Τυχαία κίνηση των Werewolves
    int move_optionW, tempPos; 
    bool collision = false;

    for (int i = 0 ; i < Werewolves.size() ; i++) { 
        move_optionW = (rand() % 5); //Επιλογή κίνησης τυχαία (Aκινησία, Πάνω, Κάτω, Αριστερά, Δεξιά)
            
        switch (move_optionW) {
            case 0:  //Ακινησία
                break;
            case 1:  //Κίνηση προς τα πάνω
                collision = false;
                tempPos = Werewolves[i]->get_pos() - x;

                //Έλεγχος σύγκρουσης με εμπόδια ή με άλλες οντότητες ή με το border
                for (int j = 0 ; j <Werewolves.size() ; j++) {
                    if (tempPos == Werewolves[j]->get_pos()) 
                        if (Werewolves[i] != Werewolves[j]) collision = true; //παράλειψη ελέγχου με τον εαυτό του
                }
                for (int j = 0 ; j < Vampires.size() ; j++){
                    if(tempPos == Vampires[j]->get_pos())collision = true;
                }
                for (int j = 0 ; j < Lakes.size() ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                if (tempPos > 0 && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Werewolves[i]->set_pos(tempPos); //Ορισμός έγκυρης θέσης
                break;
            case 2:  //Κίνηση προς τα κάτω
                collision = false;
                tempPos = Werewolves[i]->get_pos() + x;

                //Έλεγχος σύγκρουσης με εμπόδια ή με άλλες οντότητες ή με το border
                for (int j = 0 ; j < Werewolves.size() ; j++) {
                    if (tempPos == Werewolves[j]->get_pos())
                        if (Werewolves[i] != Werewolves[j]) collision = true; //παράλειψη ελέγχου με τον εαυτό του
                }
                for (int j = 0 ; j < Vampires.size() ; j++){
                    if(tempPos == Vampires[j]->get_pos())collision = true;
                }
                for (int j = 0 ; j < Trees.size() ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                if (tempPos <= x*y && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Werewolves[i]->set_pos(tempPos); //Ορισμός έγκυρης θέσης
                break;
            case 3:  //Κίνηση προς τα αριστερά
                tempPos = Werewolves[i]->get_pos() - 1;

                for (int j = 0 ; j < Werewolves.size() ; j++) {
                    if (tempPos == Werewolves[j]->get_pos())
                        if (Werewolves[i] != Werewolves[j]) collision = true; //παράλειψη ελέγχου με τον εαυτό του
                }
                for (int j = 0 ; j < Vampires.size() ; j++){
                    if(tempPos == Vampires[j]->get_pos())collision = true;
                }
                for (int j = 0 ; j < Trees.size() ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                for (int j = 1 ; j <= y ; j++) if (tempPos == x*j) collision = true;  

                if (tempPos > 0 && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Werewolves[i]->set_pos(tempPos); //Ορισμός έγκυρης θέσης
                break;
            case 4: //Κίνηση προς τα δεξιά 
                tempPos = Werewolves[i]->get_pos() + 1;

                for (int j = 0 ; j < Werewolves.size() ; j++) {
                    if (tempPos == Werewolves[j]->get_pos()) 
                        if (Werewolves[i] != Werewolves[j]) collision = true; //παράλειψη ελέγχου με τον εαυτό του
                }
                for (int j = 0 ; j < Vampires.size() ; j++){
                    if(tempPos == Vampires[j]->get_pos())collision = true;
                }
                for (int j = 0 ; j < Trees.size() ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                for (int j = 1 ; j <= y ; j++) if (tempPos == x*j+1) collision = true;  

                if (tempPos <= x*y && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Werewolves[i]->set_pos(tempPos); //Ορισμός έγκυρης θέσης
                break;
        }
    }
}


void moveVampires(vector<Tree*>& Trees, vector<Lake*>& Lakes,vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a, Potion p) { //Τυχαία κίνηση των Vampires
    int move_optionV, tempPos; 
    bool collision = false; 

    for (int i = 0 ; i < Vampires.size() ; i++) {
            move_optionV = (rand() % 9); //Επιλογή κίνησης τυχαία (Ακινησία, Πάνω, Κάτω, Αριστερά, Δεξιά, Πάνω αριστερα, Πάνω δεξιά, Κάτω αριστερά, Κάτω δεξιά)
            switch (move_optionV) {  
                case 0:  //Ακινησία
                    break;
                case 1:  //Κίνηση προς τα πάνω
                    tempPos = Vampires[i]->get_pos() - x;

                    //Έλεγχος σύγκρουσης με εμπόδια ή με άλλες οντότητες ή με το border
                    for (int j = 0 ; j < Vampires.size() ; j++) {
                    if ( tempPos == Vampires[j]->get_pos()) 
                        if (Vampires[i] != Vampires[j]) collision = true; //παράλειψη ελέγχου με τον εαυτό του
                    }
                    for (int j = 0 ; j < Werewolves.size() ; j++) {
                        if(tempPos == Werewolves[j]->get_pos())collision = true;
                    }
                    for (int j = 0 ; j < Trees.size() ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                    if (tempPos > 0 && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Vampires[i]->set_pos(tempPos); //Ορισμός έγκυρης θέσης
                    break;
                case 2:  //Κίνηση προς τα κάτω
                    tempPos = Vampires[i]->get_pos() + x;

                    //Έλεγχος σύγκρουσης με εμπόδια ή με άλλες οντότητες ή με το border
                    for (int j = 0 ; j < Vampires.size() ; j++) {
                    if ( tempPos == Vampires[j]->get_pos()) 
                        if (Vampires[i] != Vampires[j]) collision = true; //παράλειψη ελέγχου με τον εαυτό του
                    }
                    for (int j = 0 ; j < Werewolves.size() ; j++) {
                        if(tempPos == Werewolves[j]->get_pos())collision = true;
                    }
                    for (int j = 0 ; j < Trees.size() ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                    if (tempPos <= x*y && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Vampires[i]->set_pos(tempPos); //Ορισμός έγκυρης θέσης
                    break;
                case 3:  //Κίνηση προς τα αριστερά
                    tempPos = Vampires[i]->get_pos() - 1;

                    //Έλεγχος σύγκρουσης με εμπόδια ή με άλλες οντότητες ή με το border
                    for (int j = 0 ; j < Vampires.size() ; j++) {
                    if ( tempPos == Vampires[j]->get_pos()) 
                        if (Vampires[i] != Vampires[j]) collision = true; //παράλειψη ελέγχου με τον εαυτό του
                    }
                    for (int j = 0 ; j < Werewolves.size() ; j++) {
                        if(tempPos == Werewolves[j]->get_pos())collision = true;
                    }
                    for (int j = 0 ; j < Trees.size() ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                    for (int j = 1 ; j <= y ; j++) if (tempPos == x*j) collision = true;  

                    if (tempPos > 0 && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Vampires[i]->set_pos(tempPos); //Ορισμός έγκυρης θέσης
                    break;
                case 4: //Κίνηση προς τα δεξιά
                    tempPos = Vampires[i]->get_pos() + 1;

                    //Έλεγχος σύγκρουσης με εμπόδια ή με άλλες οντότητες ή με το border
                    for (int j = 0 ; j < Vampires.size() ; j++) {
                    if ( tempPos == Vampires[j]->get_pos()) 
                        if (Vampires[i] != Vampires[j]) collision = true; //παράλειψη ελέγχου με τον εαυτό του
                    }
                    for (int j = 0 ; j < Werewolves.size() ; j++) {
                        if(tempPos == Werewolves[j]->get_pos())collision = true;
                    }
                    for (int j = 0 ; j < Trees.size() ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                    for (int j = 1 ; j <= y ; j++) if (tempPos == x*j+1) collision = true;  

                    if (tempPos <= x*y && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Vampires[i]->set_pos(tempPos); //Ορισμός έγκυρης θέσης
                    break;
                case 5: //Κίνηση προς τα πάνω αριστερά
                    tempPos = Vampires[i]->get_pos() - (x+1);

                    //Έλεγχος σύγκρουσης με εμπόδια ή με άλλες οντότητες ή με το border
                    for (int j = 0 ; j < Vampires.size() ; j++) {
                    if ( tempPos == Vampires[j]->get_pos()) 
                        if (Vampires[i] != Vampires[j]) collision = true; //παράλειψη ελέγχου με τον εαυτό του
                    }
                    for (int j = 0 ; j < Werewolves.size() ; j++) {
                        if(tempPos == Werewolves[j]->get_pos())collision = true;
                    }
                    for (int j = 0 ; j < Trees.size() ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                    for (int j = 1 ; j <= y ; j++) if (tempPos == x*j) collision = true;  

                    if (tempPos > 0 && tempPos <= x*y && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Vampires[i]->set_pos(tempPos); //Ορισμός έγκυρης θέσης
                    break;
                case 6: //Κίνηση προς τα πάνω δεξιά
                    tempPos = Vampires[i]->get_pos() - (x-1);

                    //Έλεγχος σύγκρουσης με εμπόδια ή με άλλες οντότητες ή με το border
                    for (int j = 0 ; j < Vampires.size() ; j++) {
                    if ( tempPos == Vampires[j]->get_pos()) 
                        if (Vampires[i] != Vampires[j]) collision = true; //παράλειψη ελέγχου με τον εαυτό του
                    }
                    for (int j = 0 ; j < Werewolves.size() ; j++) {
                        if(tempPos == Werewolves[j]->get_pos())collision = true;
                    }
                    for (int j = 0 ; j < Trees.size() ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                    for (int j = 1 ; j <= y ; j++) if (tempPos == x*j+1) collision = true; 

                    if (tempPos > 0 && tempPos <= x*y && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Vampires[i]->set_pos(tempPos); //Ορισμός έγκυρης θέσης
                    break;
                case 7: //Κίνηση προς τα κάτω αριστερά
                    tempPos = Vampires[i]->get_pos() + (x-1);

                    //Έλεγχος σύγκρουσης με εμπόδια ή με άλλες οντότητες ή με το border
                    for (int j = 0 ; j < Vampires.size() ; j++) {
                    if ( tempPos == Vampires[j]->get_pos()) 
                        if (Vampires[i] != Vampires[j]) collision = true;  //παράλειψη ελέγχου με τον εαυτό του
                    }
                    for (int j = 0 ; j < Werewolves.size() ; j++) {
                        if(tempPos == Werewolves[j]->get_pos())collision = true;
                    }
                    for (int j = 0 ; j < Trees.size() ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                    for (int j = 1 ; j <= y ; j++) if (tempPos == x*j) collision = true;  

                    if (tempPos > 0 && tempPos <= x*y && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Vampires[i]->set_pos(tempPos); //Ορισμός έγκυρης θέσης
                    break;
                case 8: //Κίνηση προς τα κάτω δεξιά
                    tempPos = Vampires[i]->get_pos() + (x+1);

                    //Έλεγχος σύγκρουσης με εμπόδια ή με άλλες οντότητες ή με το border
                    for (int j = 0 ; j < Vampires.size() ; j++) {
                    if ( tempPos == Vampires[j]->get_pos()) 
                        if (Vampires[i] != Vampires[j]) collision = true; //παράλειψη ελέγχου με τον εαυτό του
                    }
                    for (int j = 0 ; j < Werewolves.size() ; j++) {
                        if(tempPos == Werewolves[j]->get_pos())collision = true;
                    }
                    for (int j = 0 ; j < Trees.size() ; j++) if (tempPos == Trees[j]->get_pos() || tempPos == Lakes[j]->get_pos()) collision = true;

                    for (int j = 1 ; j <= y ; j++) if (tempPos == x*j+1) collision = true; 

                    if (tempPos > 0 && tempPos <= x*y && !collision && tempPos != p.get_pos() && tempPos != a.get_pos()) Vampires[i]->set_pos(tempPos); //Ορισμός έγκυρης θέσης
                    break;
            } 
        }
}

void vamps_attack( vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves ){ //Επίθεση των Vampires σε εχθρούς διπλανών θέσεων 
     for (int i = 0 ; i < Vampires.size() ; i++){  
        int battle_pos = Vampires[i]->get_pos();
        for (int j = 0 ; j < Werewolves.size() ; j++){
            if(battle_pos == Werewolves[j]->get_pos()-x || battle_pos == Werewolves[j]->get_pos()+x || battle_pos == Werewolves[j]->get_pos()-1 || battle_pos == Werewolves[j]->get_pos()+1){
                if(Vampires[i]->get_strength() >= Werewolves[j]->get_strength() && Vampires[i]->get_strength() >= Werewolves[j]->get_defense()){
                    Vampires[i]->attackW(Werewolves[j]); //Αν το Vampire έχει μεγαλύτερη δύναμη από το Werewolf και μεγαλύτερη δύναμη από την άμυνα του Werewolf κάνε επίθεση
                }
                if (Werewolves[j]->get_health() <= 0) { //Αν το Werewolf έχει υγεία μικρότερη ή ίση με το μηδέν 
                    delete Werewolves[j]; //Διαγραφή του αντικειμένου
                    Werewolves.erase(Werewolves.begin()+j); //Διαγραφή του pointer από τον vector
                } 
            }
        }
    }
}

void vamps_heal(vector<Vampire*>& Vampires) { //Επούλωση υγείας μεταξύ των Vampires
   for (int i = 0 ; i < Vampires.size() ; i++){ 
        int assist_pos = Vampires[i]->get_pos();
        bool choice;
        for (int j = 0 ; j < Vampires.size() ; j++){
            choice = (rand() % 2); //Πιθανότητα 50% να πραγματοποιηθεί επούλωση
            if(assist_pos == Vampires[j]->get_pos()-x || assist_pos == Vampires[j]->get_pos()+x || assist_pos == Vampires[j]->get_pos()-1 || assist_pos == Vampires[j]->get_pos()+1){ //Αν υπάρχει Vampire σε διπλανή θέση
                if(Vampires[i]->get_health() > Vampires[j]->get_health() && Vampires[i]->get_healing()>0 && choice){ //Το Vampire με την περισσότερη υγεία κάνει την επούλωση στο άλλο αν έχει γιατρικό
                    Vampires[j]->set_health((Vampires[j]->get_health())+1); //Αύξηση της υγείας του Vampire που δέχεται επούλωση
                    Vampires[i]->set_healing((Vampires[i]->get_healing())-1); //Μείωση του γιατρικού του Vampire που προσφέρει την επούλωση
                }
            }
        }
    } 
}

void weres_attack(vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves ){ //Επίθεση των Werewolves σε εχθρούς διπλανών θέσεων 
     for (int i = 0 ; i < Werewolves.size() ; i++){  
        int battle_pos = Werewolves[i]->get_pos();
        for (int j = 0 ; j < Vampires.size() ; j++){
            if(battle_pos == Vampires[j]->get_pos()-x || battle_pos == Vampires[j]->get_pos()+x || battle_pos == Vampires[j]->get_pos()-1 || battle_pos == Vampires[j]->get_pos()+1){
                if(Werewolves[i]->get_strength() >= Vampires[j]->get_strength() && Werewolves[i]->get_strength() >= Vampires[j]->get_defense()){
                    Werewolves[i]->attackV(Vampires[j]); //Αν το Werewolf έχει μεγαλύτερη δύναμη από το Vampire και μεγαλύτερη δύναμη από την άμυνα του Vampire κάνε επίθεση
                }
                if (Vampires[j]->get_health() <= 0) { //Αν το Werewolf έχει υγεία μικρότερη ή ίση με το μηδέν 
                    delete Vampires[j]; //Διαγραφή του αντικειμένου
                    Vampires.erase(Vampires.begin()+j); //Διαγραφή του pointer από τον vector
                }  
            }
        }
    }
}

void weres_heal(vector<Werewolf*>& Werewolves) { //Επούλωση υγείας μεταξύ των Werewolves
    for (int i = 0 ; i < Werewolves.size() ; i++){   
        int assist_pos = Werewolves[i]->get_pos();
        bool choice;
        for (int j = 0 ; j < Werewolves.size() ; j++){
            choice = (rand() % 2); //Πιθανότητα 50% να πραγματοποιηθεί επούλωση
            if(assist_pos == Werewolves[j]->get_pos()-x || assist_pos == Werewolves[j]->get_pos()+x || assist_pos == Werewolves[j]->get_pos()-1 || assist_pos == Werewolves[j]->get_pos()+1){  //Αν υπάρχει Werewolf σε διπλανή θέση
                if(Werewolves[i]->get_health() > Werewolves[j]->get_health() && Werewolves[i]->get_healing()>0 && choice){ //Το Werewolf με την περισσότερη υγεία κάνει την επούλωση στο άλλο αν έχει γιατρικό
                    Werewolves[j]->set_health((Werewolves[j]->get_health())+1); //Αύξηση της υγείας του Vampire που δέχεται επούλωση
                    Werewolves[i]->set_healing((Werewolves[i]->get_healing())-1); //Μείωση του γιατρικού του Vampire που προσφέρει την επούλωση
                }
            }
        }
    } 
}

int heal(Avatar a, char p_support,bool Day, vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves){ //Γέμισμα υγείας της υποστηριζόμενης ομάδας από τον παίχτη με το κουμπί [Η]
     if(GetAsyncKeyState('H')){
        if(a.get_pot()>0){ //Έλεγχος ύπαρξης διαθέσιμων μαγικών φίλτρων του παίχτη
            a.heal();
            if(p_support == 'V' && Day){ //Για γέμισμα υγείας Vampires συνθήκη μέρας
                for(int i = 0; i < Vampires.size() ; i++) Vampires[i]->heal();
            }
            else if(p_support == 'W' && !Day){ //Για γέμισμα υγείας Werewolves συνθήκη νύχτα
                for(int i = 0; i < Werewolves.size() ; i++) Werewolves[i]->heal();
            }
        }
        return a.get_pot(); //Επιστροφή ανανεωμένης ποσότητας μαγικού φίλτρου του παίχτη
    }
    return a.get_pot(); //Default Τιμή
}

void pause_function(Avatar a,  vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves) { //Παύση του προγράμματος με το κουμπί [P]
    if (GetKeyState('P')) {                     
        system("cls"); //Καθάρισμα οθόνης
        cout << "[Alive Vampires  : " <<  Vampires.size() << ']' << endl; //Εκτύπωση ζωντανών Vampires
        cout << "[Alive Werewolfs : " << Werewolves.size() << ']' << endl; //Εκτύπωση ζωντανών Werewolves
        cout << "[Avatar potions  : " << a.get_pot() << ']' << endl; //Εκτύπωση μαγικών φίλτρων στη κατοχή του παίκτη
        system("pause"); //Παύση προγράμματος
    }
}

bool ChangeDay(int counter, bool Day) { //Αλλαγή μέρας ανάλογα τον μετρητή των frames
    if (counter % 15 == 0) Day = !Day; //Αλλαγή μέρας ανά 15 frames

    return Day;
}

void EndScreen(vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves) { //Εκτύπωση αποτελέσματος του παιχνιδιού
    if(Werewolves.size()>0 && Vampires.size()>0){ //Εκτύπωση μηνύματος σε περίπτωση τερματισμού του παιχνιδιού από τον παίκτη
        cout<<"You exited the game!";
    }
    else{
        for (int i = 0 ; i < 60 ; i++) cout << '\4';       

        cout << endl << '\4';
        for (int i = 0 ; i < 58 ; i++) cout << ' '; 
        cout << '\4' << endl;

        cout << '\4';
        for (int i = 0 ; i < 22 ; i++) cout << ' ';  
        if(Werewolves.size() > Vampires.size())cout << "Werewolves win!"; //Μήνυμα για νίκη Werewolves
        else cout<<"Vampires win!"; //Μήνυμα για νίκη Vampires
        if(Werewolves.size() > 0) for (int i = 0 ; i < 21 ; i++) cout << ' ';
        else for (int i = 0 ; i < 23 ; i++) cout << ' ';
        cout << '\4' << endl;
        cout << '\4';
        for (int i = 0 ; i < 58 ; i++) cout << ' '; 
        cout << '\4' << endl;
        for (int i = 0 ; i < 60 ; i++) cout << '\4'; 
        cout << "\n\n";
    }
}

void ClearVectors(vector<Tree*>& Trees, vector<Lake*>& Lakes,vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves) { //Αποδέσμευση μνήμης όλων των vectors και των αντικειμένων που περιλαμβάνουν
    Trees.clear();
    Lakes.clear();
    Vampires.clear();
    Werewolves.clear();
}