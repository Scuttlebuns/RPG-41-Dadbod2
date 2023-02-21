#pragma once
#include "actors.h"
using namespace std;

class Monster : public Actor{

private: 
	int poison;

public:
	//Constructors
	Monster(int new_poison = 5) : Actor(), poison(new_poison) {}

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
