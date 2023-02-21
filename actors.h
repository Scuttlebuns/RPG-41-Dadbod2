#pragma once
#include <string>
#include <iostream>

using namespace std;

class Actor{

	private:
		string name;
		int hp;
		int speed;
		int attack;
		int defense;

	public:
		//Constructors
		Actor(string new_name = "Empty", int new_hp = 100, int new_speed = 100, int new_attack = 100, int new_defense = 100) : name(new_name), hp(new_hp), speed(new_speed), attack(new_attack), defense(new_defense) {
			if (hp < 0) throw 42;
		} 

		//Getters
		string getName() const {return name;}
		int getHP() const {return hp;}
		int getSpeed() const {return speed;}
		int getAttack() const {return attack;}
		int getDefense() const {return defense;}


		//Setters
		void setName(string name) {this->name = name;}
		void setHP(int hp) {this->hp = hp;}
		void setSpeed(int speed) {this->speed = speed;}
		void setAttack(int attack) {this->attack = attack;}
		void setDefense(int defense) {this->defense = defense;}

		//Output
		friend ostream& operator<<(ostream& lhs, const Actor& rhs){
			lhs << rhs.name << ", " << rhs.hp << ", " << rhs.speed << ", " << rhs.attack << ", " << rhs.defense;
			return lhs;
		}

		//Input
		friend istream& operator>>(istream& lhs, Actor& rhs){ 
			lhs >> rhs.name >> rhs.hp >> rhs.speed >> rhs.attack >> rhs.defense;
			return lhs;
		}


};
