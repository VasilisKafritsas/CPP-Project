#include "classes.h"

Entity :: Entity(int test_pos){pos = test_pos;}

int Entity :: get_pos() {return pos;}

void Entity :: set_pos(int x) {pos = x;}

void Entity :: heal(){}


int Vampire :: get_health() {return health;}

int Vampire :: get_defense() {return defense;}

int Vampire :: get_strength() {return strength;}

int Vampire :: get_healing() {return healing;}

void Vampire :: set_health(int health) {this->health = health;}

void Vampire :: set_healing(int healing) {this->healing = healing;}

void Vampire :: heal(){set_health(5);}

void Vampire :: attackW(Werewolf* w){
     w->set_health(w->get_health() - strength + w->get_defense());
}


int Werewolf :: get_health() {return health;}

int Werewolf :: get_defense() {return defense;}

int Werewolf :: get_strength() {return strength;}

int Werewolf :: get_healing() {return healing;}

void Werewolf :: set_health(int health) {this->health = health;}

void Werewolf :: set_healing(int healing) {this->healing = healing;}

void Werewolf ::heal(){set_health(5);}

 void Werewolf :: attackV(Vampire* v){
     v->set_health(v->get_health() - strength + v->get_defense());
}


int Avatar :: get_pot() {return avatar_potions;}

void Avatar :: set_pot(int potions){avatar_potions=potions;}

void Avatar :: heal(){avatar_potions--;}

void Avatar :: pickUp(Potion* p) {
    p->pos = -10;
    avatar_potions++;
}


Obstacle :: Obstacle(int test_pos){pos = test_pos;}

int Obstacle :: get_pos() {return pos;}





