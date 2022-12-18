/* Ορισμός μεθόδων κλάσεων */

#include "classes.h"  

Entity :: Entity(int test_pos){pos = test_pos;}  // Entity Constructor

int Entity :: get_pos() {return pos;} //Accessor της θέσης  

void Entity :: set_pos(int x) {pos = x;} //Mutator της θέσης

void Entity :: heal(){} //virtual συναρτηση


int Vampire :: get_health() {return health;} //Accessor της υγείας

int Vampire :: get_defense() {return defense;} //Accessor της άμυνας

int Vampire :: get_strength() {return strength;} //Accessor της δύναμης

int Vampire :: get_healing() {return healing;} //Accessor του γιατρικού

void Vampire :: set_health(int health) {this->health = health;} //Μutator της υγείας

void Vampire :: set_healing(int healing) {this->healing = healing;} //Μutator του γιατρικού

void Vampire :: heal(){set_health(5);} //Επούλωση 

void Vampire :: attackW(Werewolf* w){ //Επίθεση του Vampire σε Werewolf
     w->set_health(w->get_health() - strength + w->get_defense()); // Nέα υγεία Werewolf = παλιά υγεία Werewolf - δύναμη Vampire + άμυνα Werewolf
}


int Werewolf :: get_health() {return health;} //Accessor της υγείας

int Werewolf :: get_defense() {return defense;} //Accessor της άμυνας

int Werewolf :: get_strength() {return strength;} //Accessor της δύναμης

int Werewolf :: get_healing() {return healing;} //Accessor του γιατρικού

void Werewolf :: set_health(int health) {this->health = health;} //Μutator της υγείας

void Werewolf :: set_healing(int healing) {this->healing = healing;} //Μutator του γιατρικού

void Werewolf :: heal(){set_health(5);} //Επούλωση

void Werewolf :: attackV(Vampire* v){  //Επίθεση του Werewolf σε Vampire
     v->set_health(v->get_health() - strength + v->get_defense()); // Nέα υγεία Vampire = παλιά υγεία Vampire - δύναμη Werewolf + άμυνα Vampire
}


int Avatar :: get_pot() {return avatar_potions;} //Accessor των μαγικών φίλτρων

void Avatar :: set_pot(int potions){avatar_potions=potions;} //Μutator των μαγικών φίλτρων

void Avatar :: heal(){avatar_potions--;} //Επούλωση της ομάδας που έχει επιλέξει ο παίκτης

void Avatar :: pickUp(Potion* p) { //Συλλογή του μαγικού φίλτρου
    p->pos = -10; //Ορισμός της θέσης του μαγικού φίλτρου έξω από το χάρτη
    avatar_potions++; //Αύξηση των μαγικών φίλτρων του παίχτη
}


Obstacle :: Obstacle(int test_pos){pos = test_pos;} //Obstacle Constructor

int Obstacle :: get_pos() {return pos;} //Accessor της θέσης