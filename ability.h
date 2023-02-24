#pragma once
#include <random>
using namespace std;

class Ability {
	default_random_engine gen;
	string name;
	int successRateBuff;
	int cooldownTurns;
	float damageBuff;

	public:
	//Constructors
	Ability() = delete;
	Ability(string name, int cooldownTurns, int successRateBuff) {
		this->name = name;
		this->cooldownTurns = cooldownTurns;
		this->successRateBuff = successRateBuff;
		this->damageBuff = 0.0f;
	}

	//Getters
	string getName() const { return name; }
	int getCooldownTurns() const { return cooldownTurns; }
	int getSuccessRateBuff() const { return successRateBuff; }
	int getDamageBuff() const { return damageBuff; }

	//Setters
	void setName(string name) { this->name = name; }
	void setCooldownTurns(int cooldownTurns) { this->cooldownTurns = cooldownTurns; }
	void setSuccessRateBuff(int successRateBuff) { this->successRateBuff = successRateBuff; }

	//Returns damage modifier
	void getAttackVal(int attack, int defense) {
		uniform_int_distribution<int> d100(1,100);

		float retVal = 0.0f;
		int combinedAttack = attack + successRateBuff + d100(gen);
		combinedAttack -= defense;

		if (combinedAttack > 80) retVal = 1.5;

		damageBuff = retVal;
	}

	int calculateDamage(int baseDamage) {
		return baseDamage * damageBuff;
	}

	int calculateDamage(int baseDamage, int attack, int damage) {
		getAttackVal(attack, damage);
		return baseDamage * damageBuff;
	}
};
