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

CircleLinkedList<shared_ptr<Actor>> combatLoop2;

void combatSetup2(Hero &hero){
	vector<shared_ptr<Actor>> turnOrder;
	Ability baseMonster("Scratch", 0, 75);
	Ability bossAttack("Vegan Screech", 3, 60);
	Ability bossAttack2("Clipboard Bash", 3, 60);
	Monster monster1("Air Simp", 50, 50, 30, 20, 5);
	monster1.inventory.push_back(baseMonster);
	Monster monster2("Earth Simp", 50, 40, 30, 20, 5);
	monster2.inventory.push_back(baseMonster);
	PtaOverlord boss("PTA OverLord", 100, 20, 65, 40, 10, 10);
	boss.inventory.push_back(baseMonster);
	boss.inventory.push_back(bossAttack);
	boss.inventory.push_back(bossAttack2);

	turnOrder.push_back(make_shared<Monster>(monster1));
	turnOrder.push_back(make_shared<Monster>(monster2));
	turnOrder.push_back(make_shared<PtaOverlord>(boss));
	turnOrder.push_back(make_shared<Hero>(hero));

	sort(turnOrder.rbegin(),turnOrder.rend(), [](shared_ptr<Actor> a, shared_ptr<Actor> b){ return a->getSpeed() < b->getSpeed(); });

	for (auto x : turnOrder) {
		combatLoop2.push_back(x);
	}
}

void combatDisplay2(int textColor = 3){
	Interaction full;
	clear();
	printBorder(textColor, 0, 0, 100, 100);
	string toPrint = "Turn order: ";
	auto currNode = combatLoop2.getHead();
	for (int i = 1; i <= combatLoop2.getSize(); i++) {
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

void printAbility2(Hero &hero, int textColor = 3){
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
		toPrint += to_string(currNode->data.getTurnsRemaining());
		toPrint += " | ";
		currNode = currNode->next;
	}
	attron(COLOR_PAIR(textColor));
	usleep(3'000'000);
	mvprintw(full.getTermSizeY() - 2,(full.getTermSizeX() - toPrint.length()) / 2, toPrint.c_str());
	attroff(COLOR_PAIR(textColor));
	refresh();
}

bool combat2(Hero &hero){
	Interaction full;
	combatSetup2(hero);
	centerDisplay("Aright!, Morty...Ugh I mean DadBod!.. yea DadBod... Looks like we have another opponent to take down.", 8);
	centerDisplay("Up at bat we have, PTA Overloard Karen, with some serious connections, watch out!", 8);
	centerDisplay("Now get your ass to it Morty, *burb* I mean ... DADBOD, just testing you there! ", 8);
	auto currNode = combatLoop2.getHead();
	auto heroNode = combatLoop2.getHead();
	while (true) {
		if(heroNode->data->getName() == hero.getName()) break; 
		heroNode = heroNode->next;
	}
	while(true) {
		if (heroNode->data->getHP() < 0) return false;
		if (combatLoop2.getSize() < 2 and heroNode->data->getHP() > 0) return true;
		/* cerr << "Inside loop" << endl; */
		/* return true; */
		combatDisplay2();
		if (currNode->data->getName() == hero.getName()) {
			/* cerr << "after == " << endl; */
			/* return 0; */
			printAbility2(hero);
			string toPrint = "Select Enemy To Attack Then Ablility To Use.... You Have 5 Seconds, Go.";
			attron(COLOR_PAIR(4));
			mvprintw((full.getTermSizeY() - 2) - 1,(full.getTermSizeX() - toPrint.length()) / 2, toPrint.c_str());
			attroff(COLOR_PAIR(4));
			refresh();
			timeout(5000);
			int mch = getch();
			mch -= 48;
			auto attackeeNode = combatLoop2.getHead();
			if(!(mch <= 0 or mch > combatLoop2.getSize())) {
				auto attackeeNodeChoice = combatLoop2.getHead();
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
				if(!(ch <= 0 or ch > hero.inventory.getSize() or abilityChoice->data.getTurnsRemaining() > 1)) {
					for (int i = 1; i < ch; i++){
						abilityChoice = abilityChoice->next;
					}

					auto phuckIt = hero.inventory.getHead();
					for (int i = 0; i < hero.inventory.getSize(); i++){
						if (phuckIt->data.getName() != abilityChoice->data.getName()) {
							phuckIt->data.setTurnsRemain(phuckIt->data.getTurnsRemaining() - 1);
						}
						phuckIt = phuckIt->next;
					}

					attackeeNode->data->setHP(attackeeNode->data->getHP() - abilityChoice->data.calculateDamage(hero.getAttack(), hero.getAttack(), attackeeNode->data->getDefense()));
					centerDisplayNoClear(randomJoke(), 5, 2);
					if (attackeeNode->data->getHP() < 0){
						combatLoop2.remove(attackeeNode->data);
					}
					abilityChoice->data.resetTurnsRemaining();
					break;
				}	
				else{
					centerDisplayNoClear("Invalid Input! Try again",2,6);
					continue;
				}
			}	
		}
		else{ //Monster Attack
			uniform_int_distribution<size_t> abilityRandom(0, currNode->data->inventory.getSize());
			int ch = abilityRandom(gen);
			auto abilityChoice = currNode->data->inventory.getHead();
			if(!(ch <= 0 or ch > currNode->data->inventory.getSize() or abilityChoice->data.getTurnsRemaining() > 1)) {
				for (int i = 1; i < ch; i++){
					abilityChoice = abilityChoice->next;
				}

				auto phuckIt = currNode->data->inventory.getHead();
				for (int i = 0; i < currNode->data->inventory.getSize(); i++){
					if (phuckIt->data.getName() != abilityChoice->data.getName()) {
						phuckIt->data.setTurnsRemain(phuckIt->data.getTurnsRemaining() - 1);
					}
					phuckIt = phuckIt->next;
				}

				heroNode->data->setHP(heroNode->data->getHP() - abilityChoice->data.calculateDamage(hero.getAttack(), currNode->data->getAttack(), heroNode->data->getDefense()));
				abilityChoice->data.resetTurnsRemaining();
				centerDisplayNoClear("Overlord Karen and the PTA simps attacking",5, 2);
			}	

		}
		currNode = currNode->next;
	}
	refresh();
	usleep(10'000'000);
}
