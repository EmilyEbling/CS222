#include <cstdlib>
#include <cstring>
#include <iostream>
#include "Human.h"

using namespace std;

/* Default Constructor */
Human::Human(void) {

  name = "Bruce Campbell";
  strength = HUMAN_DEFAULT_STRENGTH;

}

Human::Human(const string &name, int strength) {
	
	this->name = name;
	this->strength = strength;

}

Human::~Human(void) {


}

string Human::getName() {

	return name;

}

int Human::getStrength() {

	return strength;

}

int Human::hurt(int damage) {	

	if (strength < HUMAN_DEFAULT_STRENGTH)
		strength += 1;

	strength = strength - damage;

	return strength;

}

int Human::makeAttack() {

	int number = (rand() % 10) + 1;

	if (number == 1) {
		cout << "*Critical miss!* ";
		return 0;
	}

	else if (number == 10) {
		cout << "*Critical hit!* ";
		return 20;
	}

	else
		return number;
		
}






