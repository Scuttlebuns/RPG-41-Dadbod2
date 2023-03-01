#pragma once
#include <chrono>
#include "map.h"
#include "menus.h"
#include <ncurses.h>
using namespace std;

const int MAX_FPS = 90; //Cap frame rate 
const unsigned int TIMEOUT = 10; //Milliseconds to wait for a getch to finish
const int UP = 65; //Key code for up arrow
const int DOWN = 66;
const int LEFT = 68;
const int RIGHT = 67;

const int TIME_TO_BEAT = 75;

bool podRace() {
	Interaction race;
	/* Map track((race.getTermSizeY() - 5), "maprace.txt"); */
	Map track("maprace.txt");
	int x2 = race.getStartingPointX(), y2 = race.getStartingPointY();
	int old_x2 = 1, old_y2 = 1;

	auto start = chrono::high_resolution_clock::now();
	auto end = chrono::high_resolution_clock::now();

	while (true) {
		int ch = getch();
		if (ch == 'q' || ch == 'Q') break;
		else if (ch == RIGHT) {
			x2++;
			if (x2 >= Map::SIZE) x2 = Map::SIZE - 1; //Clamp value
		}
		else if (ch == LEFT) {
			x2--;
			if (x2 < 0) x2 = 0;
		}
		else if (ch == UP) {
			y2--;
			if (y2 < 0) y2 = 0;
		}
		else if (ch == DOWN) {
			y2++;
			if (y2 >= Map::SIZE) y2 = Map::SIZE - 1; //Clamp value
		}
		else if (ch == ERR) { //No keystroke
			; //Do nothing
		}
		//Stop flickering by only redrawing on a change
		if (x2 != old_x2 or y2 != old_y2) {
			// Do something like this, idk 
			if (track.get(x2,y2) == Map::TREASURE_1) {
				centerDisplay("Go!", 3, 5);
				start = chrono::high_resolution_clock::now();
			}
			else if (track.get(x2,y2) == Map::A_BORDER) {
				end = chrono::high_resolution_clock::now();
				break;
			}
			else if (track.get(x2,y2) == Map::WALL or track.get(x2,y2) == Map::WATER) {
				x2 = old_x2;
				y2 = old_y2;
			}
		
			//clear(); //Put this in if the screen is getting corrupted
			track.draw(x2,y2);
			mvprintw(track.getDisplaySize()+1,0,"X: %i Y: %i\n",x2,y2);
			refresh();
		}
		old_x2 = x2;
		old_y2 = y2;
		usleep(1'000'000/MAX_FPS);
	}
	chrono::duration<double> elapsed = end - start;
	string toPrint = "It took you: ";
	toPrint += to_string(elapsed.count());
	toPrint += " seconds. ";
	if (elapsed.count() < TIME_TO_BEAT) toPrint += "You have beaten Dadbod 2! Congratulations!!!!";
	else toPrint += "Unfortunately you have lost...Bye!";
	centerDisplay(toPrint, 10, 6);
	return elapsed.count() < TIME_TO_BEAT;
}
