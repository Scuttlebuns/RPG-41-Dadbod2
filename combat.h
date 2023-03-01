#pragma once
#include "hero.h"
#include "monster.h"
#include "yodaYoga.h"
#include "ptaOverlord.h"
#include "mealPrep.h"
#include "menus.h"
#include "joke_db.h"
#include <vector>
#include <algorithm>
using namespace std;

CircleLinkedList<shared_ptr<Actor>> combatLoop;

void combatSetup1(Hero &hero){
	vector<shared_ptr<Actor>> turnOrder;
	Monster monster1("Water Simp", 50, 50, 30, 20, 5);
	Monster monster2("Fire Simp", 50, 40, 30, 20, 5);
	Mealprep boss("The Vegan Teacher", 100, 20, 55, 40, 10, 10);
	turnOrder.push_back(make_shared<Monster>(monster1));
	turnOrder.push_back(make_shared<Monster>(monster2));
	turnOrder.push_back(make_shared<Mealprep>(boss));
	turnOrder.push_back(make_shared<Hero>(hero));

	sort(turnOrder.rbegin(),turnOrder.rend(), [](shared_ptr<Actor> a, shared_ptr<Actor> b){ return a->getSpeed() < b->getSpeed(); });

	for (auto x : turnOrder) {
		combatLoop.push_back(x);
	}
}

void combatDisplay(int textColor = 3){
	Interaction full;
	clear();
	printBorder(textColor, 0, 0, 100, 100);
	string toPrint = "Turn order: ";
	auto currNode = combatLoop.getHead();
	for (int i = 1; i <= combatLoop.getSize(); i++) {
		toPrint += to_string(i);
		toPrint += ") ";
		toPrint += currNode->data->getName();
		toPrint += " HP: ";
		toPrint += to_string(currNode->data->getHP());
		toPrint += " | ";
		currNode = currNode->next;
	}
	attron(COLOR_PAIR(textColor));
	usleep(3'000'000);
	mvprintw(2,(full.getTermSizeX() - toPrint.length()) / 2, toPrint.c_str());
	attroff(COLOR_PAIR(textColor));
	refresh();
}

void printAbility(Hero &hero, int textColor = 3){
	Interaction full;
	/* clear(); */
	printBorder(textColor, 0, 0, 100, 100);
	string toPrint = "Dadbod abilities: ";
	auto currNode = hero.inventory.getHead();
	for (int i = 1; i <= hero.inventory.getSize(); i++) {
		/* cerr << "inside loop" << endl; */
		toPrint += to_string(i);
		toPrint += ") ";
		toPrint += currNode->data.getName();
		toPrint += "Cooldown: "; 
		toPrint += to_string(currNode->data.getTurnsRemaing());
		toPrint += " | ";
		currNode = currNode->next;
	}
	attron(COLOR_PAIR(textColor));
	usleep(3'000'000);
	mvprintw(full.getTermSizeY() - 2,(full.getTermSizeX() - toPrint.length()) / 2, toPrint.c_str());
	attroff(COLOR_PAIR(textColor));
	refresh();
}

bool combat1(Hero &hero){
	combatSetup1(hero);
	centerDisplay("Alight, guys, we've got a real clusterf*ck of a situation here...", 5);
	centerDisplay("We've got the Vegan Teacher, a water simp, and a fire simp all teaming up against ya' boy, Dad Bod.", 5);
	centerDisplay("And let me tell you, these guys are no joke. The Vegan teacher has got some serious plant-based powers. Also, I have no idea what a simp is.", 5);
	int heroHealth = hero.getHP();
	auto currNode = combatLoop.getHead();
	while(true) {
		if (heroHealth < 0) return false;
		if (combatLoop.getSize() < 2) return true;
		/* cerr << "Inside loop" << endl; */
		/* return true; */
		combatDisplay();
		if (currNode->data->getName() == hero.getName()) {
			/* cerr << "after == " << endl; */
			/* return 0; */
			printAbility(hero);
			timeout(5000);
			int mch = getch();
			mch -= 48;
			auto attackeeNode = combatLoop.getHead();
			if(!(mch <= 0 or mch > combatLoop.getSize())) {
				auto attackeeNodeChoice = combatLoop.getHead();
				for (int i = 1; i < mch; i++) {
					attackeeNodeChoice = attackeeNodeChoice->next;
				}
				if (attackeeNodeChoice->data->getName() == hero.getName()) {
					centerDisplayNoClear("You've Keithed yourself...Idiot",4,5);
				}
				attackeeNode = attackeeNodeChoice;
			}
			else{
				centerDisplay("Invalid Input! Try again",2,5);
				continue;
			}

			while (true) {
				int ch = getch();
				/* cerr << ch << endl; */
				ch -= 48;
				auto abilityChoice = hero.inventory.getHead();
				if(!(ch <= 0 or ch > hero.inventory.getSize())) {
					for (int i = 1; i < ch; i++){
						abilityChoice = abilityChoice->next;
					}
					attackeeNode->data->setHP(attackeeNode->data->getHP() - abilityChoice->data.calculateDamage(hero.getAttack(), hero.getAttack(), attackeeNode->data->getDefense()));
					centerDisplayNoClear(randomJoke(), 5, 2);
					if (attackeeNode->data->getHP() < 0){
						combatLoop.remove(attackeeNode->data);
					}
					break;
				}	
				else{
					centerDisplay("Invalid Input! Try again",2,6);
					continue;
				}
			}	
		}
		currNode = currNode->next;
	}
	refresh();
	usleep(10'000'000);
}

	//Actor choice;
	//Actor attackee;
	//Ability attackUsed;

	//choice.setHP(choice.getHP() - attackUsed.calculateDamage(choice.getAttack(), choice.getAttack(), attackee.getDefense()));












