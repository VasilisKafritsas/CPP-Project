#include "lib.h"
#include "functions.h"
#include "classes.h"

extern int x,y;

int main() {
    srand(time(NULL));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7);

    system("cls");

    printTitleScreen();

    request_dimensions();

    printInstructions();
    
    char player_support = request_side();

    system("cls");

    Avatar a1(x+(x/2));

    Potion p1 = setPotionPosition(a1);

    vector<Tree*> Trees;
    vector<Lake*> Lakes;
    vector<Vampire*> Vampires;
    vector<Werewolf*> Werewolves;

    int obstacles_population = (x*y)/140;
    if (obstacles_population < 1) obstacles_population = 1;
    int sizeV = (x+y)/5; 
    int sizeW = (x+y)/5;

    fillTrees(obstacles_population,Trees,a1,p1);
    fillLakes(obstacles_population,Trees,Lakes,a1,p1);
    fillVampires(obstacles_population,sizeV,Trees,Lakes,Vampires,a1,p1);
    fillWerewolves(obstacles_population,sizeV,sizeW,Trees,Lakes,Vampires,Werewolves,a1,p1);

    BubbleSortObstacles(obstacles_population,Trees,Lakes);
    BubbleSortEntities(sizeV,sizeW,Vampires,Werewolves);

    bool isDay = true;
    int DayNightCounter = 0;

    int starting_health = getStartingHealth(Vampires,sizeV);

    int tempPos;
    bool collision;

    while (!GetKeyState(VK_SPACE) && sizeV > 0 && sizeW > 0) {
        a1.set_pos(AvatarMovement(obstacles_population,sizeV,sizeW,Trees,Lakes,Vampires,Werewolves,a1));

        if (a1.get_pos() == p1.get_pos()) a1.pickUp(&p1);

        (isDay) ? cout << "Day Time" : cout << "Night Time";

        PrintTeamHealth(Vampires,Werewolves,sizeV,sizeW,starting_health);

        PrintMap(obstacles_population,sizeV,sizeW,Trees,Lakes,Vampires,Werewolves,a1,p1);

        this_thread::sleep_for(450ms);
        system("cls");


        moveWerewolves(obstacles_population,sizeV,sizeW,Trees,Lakes,Vampires,Werewolves,a1,p1);
        moveVampires(obstacles_population,sizeV,sizeW,Trees,Lakes,Vampires,Werewolves,a1,p1);

        BubbleSortEntities(sizeV,sizeW,Vampires,Werewolves);

        vamps_attack(sizeV, sizeW, Vampires, Werewolves);
        // vamps_heal(sizeV, Vampires);
        weres_attack(sizeV, sizeW, Vampires, Werewolves);
        // weres_heal(sizeW,Werewolves);
        sizeV = check_healthV(sizeV, Vampires);
        sizeW = check_healthW(sizeW, Werewolves);
        
        // heal(a1, player_support, isDay, sizeV, sizeW,Vampires,Werewolves);

        pause_function(sizeV, sizeW, a1);

        DayNightCounter++;
        isDay = ChangeDay(DayNightCounter, isDay);
    }

    EndScreen(sizeW);

    return 0;
}
