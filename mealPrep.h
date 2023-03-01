#pragma once
#include "monster.h"
using namespace std;
//Grand Moff Meal Prep
class Mealprep : public Monster{

	private:
		int plusHP;

	public:
		//Constructors
		Mealprep(string new_name = "Empty", int new_hp = 100, int new_speed = 100, int new_attack = 100, int new_defense = 100, int new_poison = 5, int new_plusHP = 5) : Monster(new_name, new_hp, new_speed, new_attack, new_defense, new_poison), plusHP(new_plusHP) {}

		//Getters
		int getPlusHP() const {return plusHP;}

		//Setters
		void setPlusHP(int plusHP) {this->plusHP = plusHP;}

		//Output
		friend ostream& operator<<(ostream& lhs, const Mealprep& rhs) {
			lhs << static_cast<const Monster&>(rhs);
			return lhs << ", " << rhs.plusHP;
		}

		//Input
		friend istream& operator>>(istream& lhs, Mealprep& rhs) {
			lhs >> static_cast<Monster&>(rhs);
			return lhs >> rhs.plusHP;
		}
};

