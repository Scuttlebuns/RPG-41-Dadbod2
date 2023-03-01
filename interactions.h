#pragma once
#include <ncurses.h>
#include <string>
#include <map>
using namespace std;

class Interaction {
	//Terminal size
	int termSizeX;
	int termSizeY;

	//Where to start in %
	int startPercentageX;
	int startPercentageY;

	//Where to actually start
	int startingPointX;
	int startingPointY;

	//Where to end in %
	int endingPercentageX;
	int endingPercentageY;

	//Where to actually end
	int endingPointX;
	int endingPointY;

	public:
	//Getters:
	int getTermSizeX() const { return termSizeX; }
	int getTermSizeY() const { return termSizeY; }
	int getStartPercentageX() const { return startPercentageX; }
	int getStartPercentageY() const { return startPercentageY; }
	int getStartingPointX() const { return startingPointX; }
	int getStartingPointY() const { return startingPointY; }
	int getEndingPercentageX() const { return endingPercentageX; }
	int getEndingPercentageY() const { return endingPercentageY; }
	int getEndingPointX() const { return endingPointX; }
	int getEndingPointY() const { return endingPointY; }

	//Setters:
	void setTermSize(){
		termSizeX = getmaxx(stdscr);
		termSizeY = getmaxy(stdscr);
	}
	void setStartingPoint(){
		startingPointX = (termSizeX * startPercentageX) / 100;
		startingPointY = (termSizeY * startPercentageY) / 100;
	}
	void setStartingPercentageX(int startingPercent){
		startPercentageX = startingPercent;
	}
	void setStartingPercentageY(int startingPercent){
		startPercentageY = startingPercent;
	}
	void setEndingPoint(){
		endingPointX = (termSizeX * endingPercentageX) / 100;
		endingPointY = (termSizeY * endingPercentageY) / 100;
	}
	void setEndingPercentageX(int endingPercent){
		endingPercentageX = endingPercent;
	}
	void setEndingPercentageY(int endingPercent){
		endingPercentageY = endingPercent;
	}

	Interaction(int startPercentageX = 0, int startPercentageY = 0, int endingPercentageX = 0, int endingPercentageY = 0) {
		termSizeX = getmaxx(stdscr);
		termSizeY = getmaxy(stdscr);
		this->startPercentageX = startPercentageX;
		startingPointX = (termSizeX * startPercentageX) / 100;
		this->startPercentageY = startPercentageY;
		startingPointY = (termSizeY * startPercentageY) / 100;
		this->endingPercentageX = endingPercentageX;
		endingPointX = (termSizeX * endingPercentageX) / 100;
		this->endingPercentageY = endingPercentageY;
		endingPointY = (termSizeY * endingPercentageY) / 100;
	}
};
