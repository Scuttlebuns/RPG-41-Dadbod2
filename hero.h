#pragma once
#include "actors.h"
using namespace std;

class Hero : public Actor{

private: 
	int specialAttack;

public:
	//Constructors
	Hero(string new_name = "Empty", int new_hp = 100, int new_speed = 100, int new_attack = 100, int new_defense = 100, int new_specialAttack = 5) : Actor(new_name, new_hp, new_speed, new_attack, new_defense), specialAttack(new_specialAttack){} 

		//int new_specialAttack = 5) : Actor(), specialAttack(new_specialAttack) {}

	//Getters
	int getSpecialAttack() const {return specialAttack;}

	//Setters
	void setSpecialAttack(int specialAttack) {this->specialAttack = specialAttack;}

	//Output
	friend ostream& operator<<(ostream& lhs, const Hero& rhs) {
		lhs << static_cast<const Actor&>(rhs);
		return lhs << ", " << rhs.specialAttack;
	}

	friend bool operator==(const Hero &lhs, const Hero &rhs) {
		return lhs.getName() == rhs.getName();
	}

	//Input
	friend istream& operator>>(istream& lhs, Hero& rhs) {
		lhs >> static_cast<Actor&>(rhs);
		return lhs >> rhs.specialAttack;
	}
};
