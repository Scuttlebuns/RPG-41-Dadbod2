#pragma once
#include <iostream>
#include "interactions.h"
#include <unistd.h>
using namespace std;

void printBorder(int textColor = 3, int startPercentX = 0, int startPercentY = 0, int endPercentX = 100, int endPercentY = 100) { 
	//cerr << "2A" << endl;
	Interaction pane(0,0,100,100);
	/* cerr << "2B" << "Start perc x: " << pane.getStartingPointX()<< endl; */
	/* cerr << "2B" << "Start perc y: " << pane.getStartingPointY()<< endl; */
	/* cerr << "2B" << "End perc x: " << pane.getEndingPointX()<< endl; */
	/* cerr << "2B" << "End perc y: " << pane.getEndingPointY()<< endl; */
	attron(COLOR_PAIR(textColor));
	//cerr << "2C" << endl;
	for (int i = pane.getStartingPointX(); i <= pane.getEndingPointX(); i++){
	//cerr << "2D" << i << endl;
		mvaddch(pane.getStartingPointY(),i,'=');
		mvaddch(pane.getEndingPointY() - 1,i,'=');
	}
	//cerr << "2E" << endl;
	for (int i = pane.getStartingPointY(); i <= pane.getEndingPointY(); i++){
	//cerr << "2F" << endl;
		mvaddch(i,pane.getStartingPointX(),'|');
		mvaddch(i,pane.getEndingPointX() - 1,'|');
	}
	//cerr << "2G" << endl;
	attroff(COLOR_PAIR(textColor));
}

void printGameBorder(){


}

void centerDisplay(string itemOutput, float displayLength = 2.5, int textColor = 3){
	Interaction interItem;
	clear();
	printBorder(textColor);
	attron(COLOR_PAIR(textColor));
	mvprintw(interItem.getTermSizeY() / 2 , (interItem.getTermSizeX() - itemOutput.length()) / 2 ,itemOutput.c_str());
	attroff(COLOR_PAIR(textColor));
	refresh();
	usleep(displayLength * 1'000'000);
	clear();
}

void centerDisplayNoClear(string itemOutput, float displayLength = 2.5, int textColor = 3){
	Interaction interItem;
	attron(COLOR_PAIR(textColor));
	mvprintw(interItem.getTermSizeY() / 2 , (interItem.getTermSizeX() - itemOutput.length()) / 2 ,itemOutput.c_str());
	attroff(COLOR_PAIR(textColor));
	refresh();
	usleep(displayLength * 1'000'000);
}
void pauseMenu(){
	clear();
	//Interaction pause();
	printBorder();
	//Interaction pause();
	printBorder();
	
}
