/* Ηeader αρχείο για της συναρτήσεις */

#pragma once
#include "classes.h"

//Ορίσματα προτύπων συναρτήσεων
void printTitleScreen(); //Εκτύπωση Τίτλου Παιχνιδιού

void request_dimensions(); //Εισαγωγή διαστάσεων

void printInstructions(); //Εκτύπωση οδηγιών με πάυσεις

char request_side(); //Επιλογή ομάδας παίκτη 

Potion setPotionPosition(Avatar a); //Eύρεση κατάλληλης θέσης για το μαγικό φίλτρο στο χάρτη

void fillTrees(int size,vector<Tree*>& Trees, Avatar a, Potion potion); //Γέμισμα του vector των Trees με αντικείμενα Tree

void fillLakes(int size,vector<Tree*>& Trees, vector<Lake*>& Lakes,Avatar a, Potion potion); //Γέμισμα του vector των Lakes με αντικείμενα Lake

void fillVampires(int size,vector<Tree*>& Trees, vector<Lake*>& Lakes,
vector<Vampire*>& Vampires,Avatar a, Potion potion); //Γέμισμα του vector των Vampires με αντικείμενα Vampire

void fillWerewolves(int size,vector<Tree*>& Trees, vector<Lake*>& Lakes,
vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a, Potion potion); //Γέμισμα του vector των Werewolves με αντικείμενα Vampire

void BubbleSortObstacles(vector<Tree*>& Trees, vector<Lake*>& Lakes); //Ταξινόμηση BubbleSort των εμποδίων σε άυξουσα σειρά

void BubbleSortEntities(vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves); //Ταξινόμηση BubbleSort των οντοτήτων σε άυξουσα σειρά

int AvatarMovement( vector<Tree*>& Trees, vector<Lake*>& Lakes,vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a); //Κίνηση του avatar από τον παίκτη

int getStartingHealth(vector<Vampire*>& Vampires); //Υπολογισμός αρχικής υγείας

void PrintTeamHealth(vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, int starting_health); //Εκτύπωση συνολικής υγείας κάθε ομάδας

void PrintMap(vector<Tree*>& Trees, vector<Lake*>& Lakes,
vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a, Potion potion); //Εκτύπωση χάρτη

void moveWerewolves( vector<Tree*>& Trees, vector<Lake*>& Lakes,vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a, Potion potion); //Τυχαία κίνηση των Werewolves

void moveVampires( vector<Tree*>& Trees, vector<Lake*>& Lakes,vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves, Avatar a, Potion potion); //Τυχαία κίνηση των Vampires

int vamps_attack(vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves); //Επίθεση των Vampires σε εχθρούς διπλανών θέσεων 

void vamps_heal(vector<Vampire*>& Vampires); //Επούλωση υγείας μεταξύ των Vampires

int weres_attack(vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves); //Επίθεση των Werewolves σε εχθρούς διπλανών θέσεων 

void weres_heal(vector<Werewolf*>& Werewolves); //Επούλωση υγείας μεταξύ των Werewolves

int heal(Avatar a, char p_support,bool Day,vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves); //Γέμισμα υγείας της υποστηριζόμενης ομάδας από τον παίχτη με το κουμπί [Η]

void pause_function(Avatar a, vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves); //Παύση του προγράμματος με το κουμπί [P]

bool ChangeDay(int counter, bool day); //Αλλαγή μέρας ανάλογα τον μετρητή των frames

void EndScreen(vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves); //Εκτύπωση αποτελέσματος του παιχνιδιού

void ClearVectors(vector<Tree*>& Trees, vector<Lake*>& Lakes,vector<Vampire*>& Vampires, vector<Werewolf*>& Werewolves); //Αποδέσμευση μνήμης όλων των vectors και των αντικειμένων που περιλαμβάνουν