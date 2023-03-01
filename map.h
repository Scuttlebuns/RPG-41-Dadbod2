
#include <string>
#include <iostream>
#include <random>
#include <ncurses.h>
#include "/public/read.h"
#include <sstream>
using namespace std; //Boo hiss

class Map {
	vector<vector<char>> map;
	default_random_engine gen;
	int displaySize;
	int startingPointX;
	int startingPointY;
	string mapFile;
	public:
	Map() {
		//	init_map();
		startingPointX = -1;
		startingPointY = -1;
		displaySize = 30;
		mapFile = "map.txt";
		loadMap();
	}
	Map(string fileName) {
		startingPointX = -1;
		startingPointY = -1;
		displaySize = 30;
		mapFile = fileName;
		loadMap();
	}
	Map(string fileName, int display){
		startingPointX = -1;
		startingPointY = -1;
		mapFile = fileName;
		displaySize = display;
		loadMap();
	}
	//TODO: Write a getter and a setter to get/set the characters in the map
	//Getters:
	char get(int x, int y) const { return map.at(y).at(x); }
	int getDisplaySize() const { return displaySize; }

	int getStartingPointX() const {return startingPointX; }
	int getStartingPointY() const {return startingPointY; }

	//Setters:
	void set(int x, int y, char c){
		map.at(y).at(x) = c;
	}
	void setDisplaySize(int windowSize) {
		displaySize = windowSize;
	}
	void setStartingPoint(int x , int y){
		startingPointX = x;
		startingPointY = y;
	}


	static const char A_BOSS    = 'a';
	static const char A_BORDER  = 'A';
	static const char B_BOSS    = 'b';
	static const char B_BORDER  = 'B';
	static const char C_BOSS    = 'c';
	static const char C_BORDER  = 'C';
	static const char D_BOSS    = 'd';
	static const char D_BORDER  = 'D';

	static const char TREASURE_1 = '$';
	static const char TREASURE_2 = '%';
	static const char TREASURE_3 = '^';
	static const char TREASURE_4 = '&';

	static const char DOOR_1 = 'Q';
	static const char DOOR_2 = 'W';
	static const char DOOR_3 = 'E';

	static const char HERO     = 'H';
	static const char WALL     = '#';
	static const char WATER    = '~';
	static const char OPEN     = '.';
	static const size_t SIZE = 100; //World is a 100x100 map
	//static const size_t DISPLAY = 30; //Show a 30x30 area at a time
	//static const char MONSTER  = 'M';

	//TODO: Write a function to save the map and reload the map
	void loadMap(){
		map.resize(SIZE); //100 rows tall
		for (auto &v : map) v.resize(SIZE,'.'); //100 columns wide
		ifstream ins(mapFile);
		if(!ins) cerr << "Problem loading the map..." << endl;
		for (int i = 0; i < SIZE; i++){
			string row;
			getline(ins, row);
			if(!ins) break;
			stringstream sts(row);
			for(int j = 0; j < SIZE; j++){
				char temp;
				sts >> temp;
				if(!sts) break;
				if (temp == '*') this->setStartingPoint(j,i);
				map.at(i).at(j) = temp;
			}
		}
		if(startingPointX == -1 and startingPointY == -1) this->setStartingPoint(SIZE/2,SIZE/2);
	}

	void saveMap(int saveSlot) const {
		string saveFile = "saveSlot" + to_string(saveSlot) + "/map.txt";
		ofstream outs(saveFile);	
		if(!outs) cerr << "Problem saving map" << endl;

		for(int i = 0; i < SIZE; i++){
			for(int j = 0; j < SIZE; j++){
				outs << map.at(i).at(j);
			}								
			outs << "\n";
		}
		outs.close();
	}

	
	/*
	Randomly generate map 
	void init_map() {
	uniform_int_distribution<int> d100(1,100);
	map.clear();
	map.resize(SIZE); //100 rows tall
	for (auto &v : map) v.resize(SIZE,'.'); //100 columns wide
	for (size_t i = 0; i < SIZE; i++) {
	for (size_t j = 0; j < SIZE; j++) {
	//Line the map with walls
	if (i == 0 or j == 0 or i == SIZE-1 or j == SIZE-1) 
	map.at(i).at(j) = WALL;
	else if (i == SIZE/2 and j == SIZE/2) 
	map.at(i).at(j) = HERO;
	else {
	//5% chance of monster
	if (d100(gen) <= 5) {
	map.at(i).at(j) = MONSTER;
	}
	else if (d100(gen) <= 3) {
	map.at(i).at(j) = TREASURE;
	}
	else if (d100(gen) <= 10) { //10% each spot is wall
	map.at(i).at(j) = WALL;
	}
	else if (d100(gen) <= 3) { //3% each spot is water
	map.at(i).at(j) = WATER;
	}
	else if (d100(gen) <= 40) { //40% chance of water near other water
	if (map.at(i-1).at(j) == WATER or map.at(i+1).at(j) == WATER or map.at(i).at(j-1) == WATER or map.at(i).at(j+1) == WATER)
	map.at(i).at(j) = WATER;
	}
	}
	}
	}
	}
	*/
	//Draw the DISPLAY tiles around coordinate (x,y)
	void draw(int x, int y) {
		int start_x = x - displaySize/2;
		int end_x = x + displaySize/2;
		int start_y = y - displaySize/2;
		int end_y = y + displaySize/2;

		//Bounds check to handle the edges
		if (start_x < 0) {
			end_x = end_x - start_x;
			start_x = 0;
		}
		if (end_x > SIZE-1) {
			start_x = start_x - (end_x - (SIZE-1));
			end_x = SIZE-1;
		}
		if (start_y < 0) {
			end_y = end_y - start_y;
			start_y = 0;
		}
		if (end_y > SIZE-1) {
			start_y = start_y - (end_y - (SIZE-1));
			end_y = SIZE-1;
		}

		//Now draw the map using NCURSES
		for (size_t i = start_y; i <= end_y; i++) {
			for (size_t j = start_x; j <= end_x; j++) {
				if (i == y && j == x) {
					attron(A_UNDERLINE | A_BOLD | COLOR_PAIR(3));
					mvaddch(i-start_y,j-start_x,'H');
					attroff(A_UNDERLINE | A_BOLD | COLOR_PAIR(3));
				}
				else {
					int color = 1;
					char curChar = map.at(i).at(j);
					if (curChar == WALL) color = 5;
					else if (curChar == WATER) color = 2;
					else if (curChar == HERO) color = 3;
					else if (curChar == TREASURE_1 or curChar == TREASURE_2 or curChar == TREASURE_3 or curChar == TREASURE_4		
							or curChar == DOOR_1 or curChar == DOOR_2 or curChar == DOOR_3) 
						color = 4;
					else if (curChar == A_BORDER or curChar == A_BOSS 
							or curChar == B_BORDER or curChar == B_BOSS 
							or curChar == C_BORDER or curChar == C_BOSS 
							or curChar == D_BORDER or curChar == D_BOSS)
						color = 6;
					else if (curChar == OPEN) color = 7;
					attron(COLOR_PAIR(color));
					mvaddch(i-start_y,j-start_x,map.at(i).at(j));
					attroff(COLOR_PAIR(color));
				}
			}
		}
	}
};
