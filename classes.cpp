#include "classes.h"

Entity :: Entity(int test_pos){pos = test_pos;}

int Entity :: get_pos() {return pos;}

void Entity :: set_pos(int x) {pos = x;}


int Vampire :: get_health() {return health;}

int Vampire :: get_defense() {return defense;}

int Vampire :: get_strength() {return strength;}

int Vampire :: get_healing() {return healing;}

void Vampire :: set_health(int health) {this->health = health;}

void Vampire :: set_healing(int healing) {this->healing = healing;}




int Werewolf :: get_health() {return health;}

int Werewolf :: get_defense() {return defense;}

int Werewolf :: get_strength() {return strength;}

int Werewolf :: get_healing() {return healing;}

void Werewolf :: set_health(int health) {this->health = health;}

void Werewolf :: set_healing(int healing) {this->healing = healing;}

int Avatar :: get_pot() {return avatar_potions;}

void Avatar :: set_pot(int potions){avatar_potions=potions;}


Obstacle :: Obstacle(int test_pos){pos = test_pos;}

int Obstacle :: get_pos() {return pos;}

void Avatar :: pickUp(Potion* p) {
    p->pos = -10;
    avatar_potions++;
}