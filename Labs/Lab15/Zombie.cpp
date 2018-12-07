#include <iostream>
#include <cstdlib>
#include "Zombie.h"

using namespace std;

/* Default Constructor */
Zombie::Zombie(void) {
  name = "Blearghh";
  strength = ZOMBIE_DEFAULT_STRENGTH;
}

Zombie::Zombie(const string& name, int strength) {	

	this->name = name;
	this->strength = strength;

}

Zombie::~Zombie(void) { 

}

string Zombie::getName() {	
	
	return name;

}

int Zombie::getStrength() {	

	return strength;

}

int Zombie::hurt(int damage) {

	strength = strength - damage;
	
	return strength;

}

int Zombie::makeAttack() {   

	int number = (rand() % 10) + 1;

	return number;

}
  
