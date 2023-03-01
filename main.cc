//Put your name(s) here: Sayre, Voss, Heins
//What bullet points did you do: Map, Linked List, Inheritance, Combat, class design, (all but bridges // partial save state/ load)
//Our music
//https://youtu.be/HZk5zUBJGSo
//Delete this next line to let the code compile
//#error Delete This!

#include "hero.h"
#include "monster.h"
#include "mealPrep.h"
#include "ptaOverlord.h"
#include "yodaYoga.h"
#include "joke_db.h"
#include "menus.h"
#include "combat.h"
#include "combat2.h"
#include "combat3.h"
#include "podRace.h"
#include <unistd.h>

//Turns on full screen text mode
void turn_on_ncurses() {
	initscr();//Start curses mode
	start_color(); //Enable Colors if possible
	init_pair(1,COLOR_WHITE,COLOR_BLACK); //Set up some color pairs
	init_pair(2,COLOR_CYAN,COLOR_BLACK);
	init_pair(3,COLOR_GREEN,COLOR_BLACK);
	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	init_pair(5,COLOR_RED,COLOR_BLACK);
	init_pair(6,COLOR_MAGENTA,COLOR_BLACK);
	init_pair(7,COLOR_BLACK,COLOR_BLACK); //Set up some color pairs
	clear();
	noecho();
	cbreak();
	timeout(TIMEOUT); //Set a max delay for key entry
}

//Exit full screen mode - also do this if you ever want to use cout or gtest or something
void turn_off_ncurses() {
	clear();
	endwin(); // End curses mode
	if (system("clear")) {}
}

bool door1Open = false;
bool door2Open = false;
bool door3Open = false;
bool bossADoor = false;
bool bossBDoor = false;
bool bossCDoor = false;
bool bossDDoor = false;

bool hasAbilityOne = false;
bool hasAbilityTwo = false;
bool hasAbilityThree = false;
bool hasAbilityFour = false;

string mapFileToLoad = "map1.txt";

void saveBools(int saveSlot) {
	string saveFile = "saveSlot" + to_string(saveSlot) + "/bools.txt";
	ofstream outs(saveFile);	
	if(!outs) cerr << "Problem saving bools" << endl;


	outs << door1Open;
	outs << door2Open;
	outs << door3Open;
	outs << bossADoor;
	outs << bossBDoor;
	outs << bossCDoor;
	outs << bossDDoor;
	outs << hasAbilityOne;
	outs << hasAbilityTwo;
	outs << hasAbilityThree;
	outs << hasAbilityFour;

	outs.close();
}

void loadBools(int saveSlot) {
	string saveFile = "saveSlot" + to_string(saveSlot) + "/bools.txt";
	ifstream ins(saveFile);	
	if(!ins) cerr << "Problem saving bools" << endl;


	ins >> door1Open;
	ins >> door2Open;
	ins >> door3Open;
	ins >> bossADoor;
	ins >> bossBDoor;
	ins >> bossCDoor;
	ins >> bossDDoor;
	ins >> hasAbilityOne;
	ins >> hasAbilityTwo;
	ins >> hasAbilityThree;
	ins >> hasAbilityFour;

	ins.close();
}


void saveGame(const Map &map) {
	while (true) {
		refresh();
		mvprintw(0,0, "What save slot would you like to use? Press 1, 2, or 3");
		timeout(5000);
		int ch = getch();
		ch -= 48;

		if (ch < 1 or ch > 3) {
			mvprintw(1,0, "Please try again...");
			usleep(2'500'000);
		} else {
			map.saveMap(ch);
			saveBools(ch);
			mvprintw(1,0, "Game Saved to slot %i:", ch);
			usleep(2'500'000);
			clear();
			break;
		}
	}
	timeout(TIMEOUT); //Set a max delay for key entry
}

void loadGame() {
	while (true) {
		refresh();
		centerDisplay("Would you like to 1) Start a new game or 2) Load from a save slot", 5);
		refresh();
		timeout(5000);
		int ch2 = getch();
		ch2 -= 48;

		if (ch2 < 1 or ch2 > 2) {
			centerDisplay("Please try again!");
			continue;
		} else if (ch2 == 1) return; 
		else {
			while (true) {
				refresh();
				mvprintw(0,0, "What save slot would you like to use? Press 1, 2, or 3");
				timeout(5000);
				int ch = getch();
				ch -= 48;

				if (ch < 1 or ch > 3) {
					mvprintw(1,0, "Please try again...");
					usleep(2'500'000);
					continue;
				} else {
					mapFileToLoad =  "saveSlot" + to_string(ch) + "/map.txt";
					loadBools(ch);
					mvprintw(1,0, "Game loaded from slot %i:", ch);
					usleep(2'500'000);
					clear();
					return;
				}
			}
		}
	}
	timeout(TIMEOUT); //Set a max delay for key entry
}

int main() {
	Interaction terminal;
	turn_on_ncurses(); //DON'T DO CIN or COUT WHEN NCURSES MODE IS ON
	centerDisplay("Welcome to Dad Bod 2, Rated M for mature.", 4);
	centerDisplay("All Jokes are just that... Jokes. Be prepared for some spice in your life.", 6);
	loadGame();
	Hero dadbod("Dad Bod", 150, 55, 60, 60, 10);
	Ability one("Joke", 0, 55);
	Ability two("TV Remote Lightsaber", 5, 55);
	Ability three("Busch Keg Blaster", 3, 55);
	Ability four("Foam Finger Flame Thrower", 2, 55);
	//cerr << "dadbod.inventory: " << dadbod.inventory.getHead()->data.getName() << endl;
	if (hasAbilityOne) dadbod.inventory.push_back(one);
	if (hasAbilityTwo) dadbod.inventory.push_back(two);
	if (hasAbilityThree) dadbod.inventory.push_back(three);
	if (hasAbilityFour) dadbod.inventory.push_back(four);
	//cerr << "1." << endl;
	//cerr << "2." << endl;
	//printBorder();
	//cerr << "3." << endl;
	loadJokes();
	/* Map map((terminal.getTermSizeY() - 5), "map1.txt"); */
	Map map(mapFileToLoad);
	int x = map.getStartingPointX(), y = map.getStartingPointY(); //Start in middle of the world
	int old_x = -1, old_y = -1;
	while (true) {
		int ch = getch(); // Wait for user input, with TIMEOUT delay
		if (ch == 'q' || ch == 'Q') break;
		else if (ch == 's' || ch == 'S'){
			saveGame(map);
			mvprintw(map.getDisplaySize()+2,0,"Map Saved");
		}
		else if (ch == RIGHT) {
			x++;
			if (x >= Map::SIZE) x = Map::SIZE - 1; //Clamp value
		}
		else if (ch == LEFT) {
			x--;
			if (x < 0) x = 0;
		}
		else if (ch == UP) {
			/* If you want to do cin and cout, turn off ncurses, do your thing, then turn it back on
			   turn_off_ncurses();
			   string s;
			   cin >> s;
			   cout << s << endl;
			   sleep(1);
			   turn_on_ncurses();
			   */
			y--;
			if (y < 0) y = 0;
		}
		else if (ch == DOWN) {
			y++;
			if (y >= Map::SIZE) y = Map::SIZE - 1; //Clamp value
		}
		else if (ch == ERR) { //No keystroke
			; //Do nothing
		}
		//Stop flickering by only redrawing on a change
		if (x != old_x or y != old_y) {
			// Do something like this, idk 
			if (map.get(x,y) == Map::TREASURE_1) {
				map.set(x,y,Map::OPEN);
				dadbod.inventory.push_back(one);
				centerDisplay("You've picked up the power of Dad Joke. Use this power wisely. Use Joke to open the next treasure.", 7);
				door1Open = true;

			} 
			else if (map.get(x,y) == Map::TREASURE_2) {
				map.set(x,y,Map::OPEN);
				dadbod.inventory.push_back(two);
				centerDisplay("You just got more SHIT! whoo!. It's a TV Remote lightsaber or some shit.  GL MOFOS", 7);
				door2Open = true;
			} 
			else if (map.get(x,y) == Map::TREASURE_3) {
				map.set(x,y,Map::OPEN);
				dadbod.inventory.push_back(three);
				centerDisplay("A Busch Keg Blaster?!?! NANI!?!", 7);
				door3Open = true;
			} 
			else if (map.get(x,y) == Map::TREASURE_4) {
				map.set(x,y,Map::OPEN);
				dadbod.inventory.push_back(four);
				centerDisplay("We are just making shit up at this point. Here's a Foam Finger Flame Thrower.", 7);
				bossADoor = true;
			} 
			else if (map.get(x,y) == Map::A_BOSS) {
				map.set(x,y, Map::OPEN);
				bool combat = combat1(dadbod);
				if (combat) centerDisplay("Well done...you made it through the first boss...", 7);
				else {
					centerDisplay("Well f*ck...guess you gotta start all over again.", 7);
					break;
				}
				bossBDoor = true;
			}
			else if (map.get(x,y) == Map::B_BOSS) {
				map.set(x,y, Map::OPEN);
				bool combat = combat2(dadbod);
				if (combat) centerDisplay("Well...now you think you are tough shit now getting through two bosses...we shall see...", 7);
				else {
					centerDisplay("Well f*ck...guess you gotta start all over again.", 7);
					break;
				}
				bossCDoor = true;
			}
			else if (map.get(x,y) == Map::C_BOSS) {
				map.set(x,y, Map::OPEN);
				bool combat = combat3(dadbod);
				if (combat) centerDisplay("Well done...you made it through the Third boss...", 7);
				else {
					centerDisplay("Well f*ck...guess you gotta start all over again.", 7);
					break;
				}
				bossDDoor = true;
			}
			else if (map.get(x,y) == Map::D_BOSS) {
				bool race = podRace();
				if (race) break;
				else break;
			}

			else if ((map.get(x,y) == Map::DOOR_1 and !door1Open) or (map.get(x,y) == Map::DOOR_2 and !door2Open) or (map.get(x,y) == Map::DOOR_3 and !door3Open)){
				x = old_x;
				y = old_y;
				centerDisplay("You dun goofed, go find more shit and try again.", 3, 4);
			}
			else if ((map.get(x,y) == Map::A_BORDER and !bossADoor) or (map.get(x,y) == Map::B_BORDER and !bossBDoor) or (map.get(x,y) == Map::C_BORDER and !bossCDoor) or (map.get(x,y) == Map::D_BORDER and !bossDDoor)){
				x = old_x;
				y = old_y;
				centerDisplay("TF you think this is... Elden Ring?! The bosses come AFTER your lazy ass does something useful... Go away and try again!",5,5);
			}
			else if (map.get(x,y) == Map::WALL or map.get(x,y) == Map::WATER) {
				x = old_x;
				y = old_y;
			}

			//clear(); //Put this in if the screen is getting corrupted
			map.draw(x,y);
			mvprintw(map.getDisplaySize()+1,0,"X: %i Y: %i\n",x,y);
			refresh();
		}
		old_x = x;
		old_y = y;
		usleep(1'000'000/MAX_FPS);
	}
	turn_off_ncurses();
}
