#pragma once
#include "classes.h"

void printTitleScreen();

void request_dimensions();

void printInstructions();

char request_side();

void printPauseMenu();

void pause_function();

void printResultMenu();

Potion setPotionPosition(Avatar a);

void fillTrees(int size, vector<Tree*>& Trees, Avatar a, Potion potion);

void fillLakes(int size, vector<Tree*>& Trees, vector<Lake*>& Lakes,Avatar a, Potion potion);

void fillVampires(int obstacles_size, int vampires_size, vector<Tree*>& Trees, vector<Lake*>& Lakes,
vector<Vampire*>& Vampires,Avatar a, Potion potion);

void fillWerewolves(int obstacles_size, int vampires_size, int werewolves_size,vector<Tree*>& Trees, vector<Lake*>& Lakes,
vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a, Potion potion);

void BubbleSortObstacles(int obstacles_size, vector<Tree*>& Trees, vector<Lake*>& Lakes);

void BubbleSortEntities(int vampires_size, int werewolves_size, vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves);

int AvatarMovement(int obstacles_size, int vampires_size, int werewolves_size, vector<Tree*>& Trees, vector<Lake*>& Lakes,vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a);

void moveWerewolves(int obstacles_size, int vampires_size, int werewolves_size, vector<Tree*>& Trees, vector<Lake*>& Lakes,vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a, Potion potion);

void moveVampires(int obstacles_size, int vampires_size, int werewolves_size, vector<Tree*>& Trees, vector<Lake*>& Lakes,vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a, Potion potion);

int getStartingHealth(vector<Vampire*>& Vampires, int vampires_size);

void PrintTeamHealth(vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, int vampires_size, int werewolves_size, int starting_health);

void PrintMap(int obstacles_size, int vampires_size, int werewolves_size,vector<Tree*>& Trees, vector<Lake*>& Lakes,
vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a, Potion potion);

void vamps_attack(int vampires_size, int werewolves_size, vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves);

void vamps_heal(int vampires_size, vector<Vampire*>& Vampires);

void weres_attack(int vampires_size, int werewolves_size, vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves);

void weres_heal(int werewolves_size, vector<Werewolf*>& Werewolves);

int check_healthV(int vampires_size,vector<Vampire*>& Vampires);

int check_healthW(int werewolves_size, vector<Werewolf*>& Werewolves);

void heal(Avatar a, char p_support,bool Day, int vampires_size,int werewolves_size, vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves);

bool ChangeDay(int counter, bool day);

void pause_function(int vampires_size, int werewolves_size, Avatar a);

void EndScreen(int werewolves_size);
