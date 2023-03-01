#pragma once
#include "actors.h"
using namespace std;

class Monster : public Actor{

private: 
	int poison;

public:
	//Constructors
	Monster(string new_name = "Empty", int new_hp = 100, int new_speed = 100, int new_attack = 100, int new_defense = 100, int new_poison = 5) : Actor(new_name, new_hp, new_speed, new_attack, new_defense), poison(new_poison) {}

	//Getters
	int getPoison() const {return poison;}

	//Setters
	void setPoison(int poison) {this->poison = poison;}

	//Output
	friend ostream& operator<<(ostream& lhs, const Monster& rhs) {
		lhs << static_cast<const Actor&>(rhs);
		return lhs << ", " << rhs.poison;
	}

	//Input
	friend istream& operator>>(istream& lhs, Monster& rhs) {
		lhs >> static_cast<Actor&>(rhs);
		return lhs >> rhs.poison;
	}
};
