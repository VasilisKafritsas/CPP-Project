/* Κύριο αρχείο */

#include "lib.h"
#include "functions.h"
#include "classes.h"

extern int x,y;  //Ορίζονται οι διαστάσεις extern επειδή έχουν αρχικά οριστεί στο αρχείο functions.cpp

int main() {
    srand(time(NULL));    //Για πραγματικά τυχαίες τιμές
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);    //Αρχική εντολή για τις εντολές χρωμάτων (από την βιβλιοθήκη windows.h)
    SetConsoleTextAttribute(hConsole, 7);  //Αλλαγή χρώματος σε άσπρο

    system("cls");  //Καθάρισμα οθόνης 

    printTitleScreen();  //Εκτύπωση Τίτλου Παιχνιδιού

    request_dimensions();  //Εισαγωγή διαστάσεων

    printInstructions();  //Εκτύπωση οδηγιών
    
    char player_support = request_side();  //Αποθήκευση επιλογής ομάδας του παίχτη

    system("cls");  //Καθάρισμα οθόνης

    Avatar a1(x+(x/2));   //Δημιουργία αντικειμένου Avatar

    Potion p1 = setPotionPosition(a1);  // Δημιουργία αντικειμένου Potion

    //Δημιουργία των Vector
    vector<Tree*> Trees;  
    vector<Lake*> Lakes;
    vector<Vampire*> Vampires;
    vector<Werewolf*> Werewolves;

    int obstacles_population = (x*y)/140;  //Πληθυσμός εμποδίων
    if (obstacles_population < 1) obstacles_population = 1;  //Ο πληθυσμός θα είναι 1 και πάνω
    int sizeV = (x+y)/5;  //Πληθυσμός των Vampires 
    int sizeW = (x+y)/5;  //Πληθυσμός των Werewolves

    //Γέμισμα των vectors με αντικείμενα
    fillTrees(obstacles_population,Trees,a1,p1);
    fillLakes(obstacles_population,Trees,Lakes,a1,p1);
    fillVampires(sizeV,Trees,Lakes,Vampires,a1,p1);
    fillWerewolves(sizeW,Trees,Lakes,Vampires,Werewolves,a1,p1);

    //Ταξινόμηση BubbleSort των vectors
    BubbleSortObstacles(Trees,Lakes);
    BubbleSortEntities(Vampires,Werewolves);

    bool isDay = true;  //Αρχικοποίηση μεταβλητής bool για μέρα - νύχτα 
    int DayNightCounter = 0; // Μετρητής frames για αλλαγή μέρας

    int starting_health = getStartingHealth(Vampires);  //Αρχική υγεία των Vampires και Werewolves

    while (!GetKeyState(VK_SPACE) && Vampires.size() > 0 && Werewolves.size() > 0) {  //Το παιχίδι τρέχει μέχρι κάποια ομάδα να μην έχει μέλη ή να πατήσει ο χρήστης [SPACEBAR]
        a1.set_pos(AvatarMovement(Trees,Lakes,Vampires,Werewolves,a1));  //Κίνηση Παίχτη

        if (a1.get_pos() == p1.get_pos()) a1.pickUp(&p1);  //Εάν ο παίχτης πάει στην θέση του μαγικού φίλτρου γίνεται αύξηση των μαγικών φίλτρων που διαθέτει

        (isDay) ? cout << "Day Time" : cout << "Night Time";  //Εκτύπωση της κατάλληλη ένδειξης αναλόγως την μέρα

        PrintTeamHealth(Vampires,Werewolves,starting_health); //Εκτύπωση συνολικής υγείας κάθε ομάδας

        PrintMap(Trees,Lakes,Vampires,Werewolves,a1,p1);  //Εκτύπωση χάρτη

        this_thread::sleep_for(450ms);  //Παύση προγράμματος για 450ms
        system("cls");  //Καθάρισμα οθόνης


        moveWerewolves(Trees,Lakes,Vampires,Werewolves,a1,p1);  //Τυχαία κίνηση των Werewolves
        moveVampires(Trees,Lakes,Vampires,Werewolves,a1,p1);    //Τυχαία κίνηση των Vampires

        BubbleSortEntities(Vampires,Werewolves);  //Ταξινόμηση BubbleSort 

        
        weres_attack(Vampires, Werewolves);  //Επίθεση των Werewolves στους Vampires
        vamps_attack(Vampires, Werewolves);  //Επίθεση των Vampires στους Werewolves
        weres_heal(Werewolves);  //Επούλωση υγείας μεταξύ των Werewolves
        vamps_heal(Vampires);    //Επούλωση υγείας μεταξύ των Vampires
        
        a1.set_pot(heal(a1, player_support, isDay,  Vampires,Werewolves));  //Γέμισμα υγείας της υποστηριζόμενης ομάδας από τον παίχτη με το κουμπί [Η]

        pause_function(a1,Vampires, Werewolves);   //Παύση του προγράμματος με το κουμπί [P]

        DayNightCounter++;  //Αύξηση του μετρητή των frames
        isDay = ChangeDay(DayNightCounter, isDay);  //Αλλαγή μέρας ανάλογα τον μετρητή των frames
    }

    EndScreen(Vampires, Werewolves);  //Εκτύπωση αποτελέσματος του παιχνιδιού

    ClearVectors(Trees,Lakes,Vampires,Werewolves);  //Αποδέσμευση μνήμης

    return 0;  
}