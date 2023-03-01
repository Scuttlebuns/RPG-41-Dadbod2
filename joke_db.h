#pragma once

#include "/public/read.h"
#include <vector>
#include <random>
#include <string>
#include <ctime>
using namespace std;

vector<string> joke_db;
default_random_engine gen(time(0));

void loadJokes(string fileName = "joke_db.txt"){
	ifstream ins (fileName);
	if(!ins) cerr << "Error opening joke file!" << endl;
	string temp;
	while(true){
		temp = readline(ins);
		if(!ins) break;
		joke_db.push_back(temp);
	}
}

string randomJoke(){

	uniform_int_distribution<size_t> maxJokeSize(0,joke_db.size() -1);

	return joke_db.at(maxJokeSize(gen));
		
}
