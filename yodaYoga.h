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
		YodaYoga(int new_yoga = 5) : PtaOverlord(), yoga(new_yoga) {}

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

