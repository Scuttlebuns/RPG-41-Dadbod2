#pragma once
#include "monster.h"
using namespace std;
//Grand Moff Meal Prep
class Mealprep : public Monster{

	private:
		int plusHP;

	public:
		//Constructors
		Mealprep(int new_plusHP = 5) : Monster(), plusHP(new_plusHP) {}

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

