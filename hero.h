#pragma once
#include "actors.h"
using namespace std;

class Hero : public Actor{

private: 
	int specialAttack;

public:
	//Constructors
	Hero(int new_specialAttack = 5) : Actor(), specialAttack(new_specialAttack) {}

	//Getters
	int getSpecialAttack() const {return specialAttack;}

	//Setters
	void setSpecialAttack(int specialAttack) {this->specialAttack = specialAttack;}

	//Output
	friend ostream& operator<<(ostream& lhs, const Hero& rhs) {
		lhs << static_cast<const Actor&>(rhs);
		return lhs << ", " << rhs.specialAttack;
	}

	//Input
	friend istream& operator>>(istream& lhs, Hero& rhs) {
		lhs >> static_cast<Actor&>(rhs);
		return lhs >> rhs.specialAttack;
	}
};
