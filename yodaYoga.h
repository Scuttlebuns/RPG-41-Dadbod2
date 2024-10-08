#pragma once
#include "ptaOverlord.h"
using namespace std;
//yoda yoga
class YodaYoga : public PtaOverlord{

	private:
		int yoga;
		//increase speed? chance of missing attack
	public:
		//Constructors
		YodaYoga(string new_name = "Empty",int new_hp = 100, int new_speed = 100, int new_attack = 100, int new_defense = 100, int new_poison = 5, int new_plusHP = 10, int new_talk = 5, int new_yoga = 5) : PtaOverlord(new_name, new_hp, new_speed, new_attack, new_defense, new_poison, new_plusHP, new_talk), yoga(new_yoga) {}

		//Getters
		int getyoga() const {return yoga;}

		//Setters
		void setyoga(int yoga) {this->yoga = yoga;}

		//Output
		friend ostream& operator<<(ostream& lhs, const YodaYoga& rhs) {
			lhs << static_cast<const PtaOverlord&>(rhs);
			return lhs << ", " << rhs.yoga;
		}

		//Input
		friend istream& operator>>(istream& lhs, YodaYoga& rhs) {
			lhs >> static_cast<PtaOverlord&>(rhs);
			return lhs >> rhs.yoga;
		}
};

