#pragma once
#include "mealPrep.h"
using namespace std;
//PTA overlord
class PtaOverlord : public Mealprep{

	private:
		int talk;
		//Has the chance to bore dadbod skipping attack turn
	public:
		//Constructors
		PtaOverlord(string new_name = "Empty", int new_hp = 100, int new_speed = 100, int new_attack = 100, int new_defense = 100, int new_poison = 5, int new_plusHP = 10, int new_talk = 5) : Mealprep(new_name, new_hp, new_speed, new_attack, new_defense, new_poison, new_plusHP), talk(new_talk) {}

		//Getters
		int gettalk() const {return talk;}

		//Setters
		void settalk(int talk) {this->talk = talk;}

		//Output
		friend ostream& operator<<(ostream& lhs, const PtaOverlord& rhs) {
			lhs << static_cast<const Mealprep&>(rhs);
			return lhs << ", " << rhs.talk;
		}

		//Input
		friend istream& operator>>(istream& lhs, PtaOverlord& rhs) {
			lhs >> static_cast<Mealprep&>(rhs);
			return lhs >> rhs.talk;
		}
};

