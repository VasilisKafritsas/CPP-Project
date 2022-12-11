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

void AvatarMovement(int obstacles_size, int vampires_size, int werewolves_size, vector<Tree*>& Trees, vector<Lake*>& Lakes,vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a);

void moveWerewolves(int obstacles_size, int vampires_size, int werewolves_size, vector<Tree*>& Trees, vector<Lake*>& Lakes,vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a, Potion potion);

void moveVampires(int obstacles_size, int vampires_size, int werewolves_size, vector<Tree*>& Trees, vector<Lake*>& Lakes,vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a, Potion potion);

void PrintTeamLife(vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, int vampires_size, int werewolves_size);

void PrintMap(int obstacles_size, int vampires_size, int werewolves_size,vector<Tree*>& Trees, vector<Lake*>& Lakes,
vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a, Potion potion);
