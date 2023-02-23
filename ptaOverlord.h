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
		PtaOverlord(int new_talk = 5) : Mealprep(), talk(new_talk) {}

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

