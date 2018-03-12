#pragma once

#include "Snake.h"
#include "List.h"

#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

class Game{
	struct Player {
		char* name;
		unsigned int score;
	};

	struct Food {
		unsigned char x, y;
	};

	Snake snake;
	List<Player> leaders, sorted_list;
	Food food;

	void update();

	void sortList(List<Player>&, List<Player>*);
	bool findInList(unsigned int a, List<unsigned int>& list);

	const unsigned char Y_SIZE = 30, X_SIZE = 20;
	unsigned int score = 0;

	public:
		void readLeaders();
		void addLeader();
		void printLeaders();

		void restart();
		void start();
};

