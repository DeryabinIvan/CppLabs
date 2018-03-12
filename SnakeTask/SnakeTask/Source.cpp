#include <iostream>
#include "Game.h"

using namespace std;

enum MENU{START=1, BOARD, HELP, EXIT};

int main() {
	char menu_key;
	Game snakeGame;

	while (true){
		printf("Menu:\n\t%d) New Game\n\t%d) Leaderboard\n\t%d) Help\n\t%d) Exit\n", START, BOARD, HELP, EXIT);

		cin >> menu_key;
		system("cls");
		switch (menu_key-'0'){
			case START:
				snakeGame.restart();
				snakeGame.start();

				snakeGame.addLeader();
				snakeGame.readLeaders();
				snakeGame.printLeaders();
				break;
			case BOARD:
				snakeGame.readLeaders();
				snakeGame.printLeaders();
				break;
			case HELP:
				cout << "WASD - control; X or ESC-exit" << endl;
				cout << "That`s all ;)"<<endl;
				break;
			case EXIT:
				return 0;
		}
	}
	return 0;
}
