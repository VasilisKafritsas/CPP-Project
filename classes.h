#pragma once
#include "lib.h"

class Werewolf;
class Vampire;

class Entity {
    private:
        int health = 5;
        int strength = (rand() % 3 + 1);
        int defense = (rand() % 2 + 1);
        int healing = (rand() % 3);
    protected:
        int pos;
    public:
	    Entity(int test_pos);

        int get_pos();
        void set_pos(int x);
        virtual void heal();

	    ~Entity() {}
        
        friend class Werewolf;
        friend class Vampire;
};

class Vampire: public Entity{//child no1
    private:
    
    public:
        Vampire(int test_posV):Entity(test_posV){};
        int get_health();
        int get_strength();
        int get_defense();
        int get_healing();
        void set_health(int health);
        void set_healing(int healing);
        void attackW(Werewolf*);
        void heal();

        ~Vampire() {}
};

class Werewolf: public Entity{//child n02 same
    private:
    
    public:
        Werewolf(int test_posW):Entity(test_posW){};
        int get_health();
        int get_strength();
        int get_defense();
        int get_healing();
        void set_health(int health);
        void set_healing(int healing);
        void attackV(Vampire*);
        void heal();

        ~Werewolf() {}
};

class Potion;

class Avatar: public Entity{//child no3
    private:
        int avatar_potions = 1;
    public:
        Avatar(int test_pos):Entity(test_pos){};
        int get_pot();
        void set_pot(int potions);
        void pickUp(Potion*);
        void heal();
        ~Avatar(){};
};


    


class Obstacle {
    protected:
        int pos;
    public:
        Obstacle(int test_pos);
        int get_pos();
        ~Obstacle(){}
};

class Tree: public Obstacle {
    private:

    public:
        Tree(int test_posT): Obstacle(test_posT) {};

        ~Tree() {}
};

class Lake: public Obstacle {
    private:

    public:
        Lake(int test_posL): Obstacle(test_posL) {};

        ~Lake() {}
};

class Potion: public Obstacle {
    public:
       Potion(int test_posL): Obstacle(test_posL) {};
       friend void Avatar::pickUp(Potion*);

       ~Potion() {} 
};