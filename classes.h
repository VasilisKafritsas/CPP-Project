/* Ηeader αρχείο για της κλάσεις */

#pragma once //Απότρεψη πολλαπλής μεταγλώτισης αρχείου

#include "lib.h"

//ορισμός των υποκλάσεων για μετέπειτα χρήση ως friendly
class Werewolf;
class Vampire;

class Entity {//Entity hyperclass
    private: 
        int health = 5; //Ζωή=5
        int strength = (rand() % 3 + 1); //Δύναμη=τυχαία τιμή απο 1-3
        int defense = (rand() % 2 + 1); //Άμυνα= τυχαία τιμή από 1-2
        int healing = (rand() % 3); //Επούλωση= τυχαία τιμή από 0-2
    protected:
        int pos; //θέση
    public:
	    Entity(int test_pos); //Entity Constructor

        //Μέθοδοι
        int get_pos();
        void set_pos(int x);
        virtual void heal();

	    ~Entity() {} //Entity Destructor
        
        friend class Werewolf;
        friend class Vampire;
};

class Vampire: public Entity{ //Child Vampire of Entity
    public:
        Vampire(int test_posV):Entity(test_posV){}; //Vampire Constructor

        //Mέθοδοι
        int get_health();
        int get_strength();
        int get_defense();
        int get_healing();
        void set_health(int health);
        void set_healing(int healing);
        void attackW(Werewolf*);
        void heal();

        ~Vampire() {} //Vampire Destructor 
};

class Werewolf: public Entity{ //Child Werewolf of Entity
    public:
        Werewolf(int test_posW):Entity(test_posW){}; //Werewolf Constructor

        //Μέθοδοι
        int get_health();
        int get_strength();
        int get_defense();
        int get_healing();
        void set_health(int health);
        void set_healing(int healing);
        void attackV(Vampire*);
        void heal();

        ~Werewolf() {} //Werewolf Destructor
};

class Potion; //ορισμός της κλάσης Potion για μετέπειτα χρήση στην κλάση Avatar

class Avatar: public Entity{ //Child Avatar of Entity
    private:
        int avatar_potions = 1; //Αρχικοποίηση ποσότητας μαγικών φιλτρών σε 1
    public:
        Avatar(int test_pos):Entity(test_pos){}; //Avatar Constructor

        // Μέθοδοι
        int get_pot();
        void set_pot(int potions);
        void pickUp(Potion*);
        void heal();

        ~Avatar(){}; //Avatar Destructor
};


    


class Obstacle { //Obstacle hyperclass
    protected:
        int pos; //Θέση
    public:
        Obstacle(int test_pos); // Obstacle Constructor

        //Μέθοδοι
        int get_pos();

        ~Obstacle(){}  //Obstacle Destructor
};

class Tree: public Obstacle { //Child Tree of Obstacle
    public:
        Tree(int test_posT): Obstacle(test_posT) {};

        ~Tree() {} //Tree Destructor
};

class Lake: public Obstacle { //Child Lake of Obstacle
    public:
        Lake(int test_posL): Obstacle(test_posL) {};

        ~Lake() {} //Lake Destructor 
};

class Potion: public Obstacle { //Child Potion of Obstacle
    public:
       Potion(int test_posL): Obstacle(test_posL) {}; //Potion Constructor
       friend void Avatar::pickUp(Potion*); //Ορισμός friend της μεθόδου pickUp 

       ~Potion() {} //Potion Destructor
};