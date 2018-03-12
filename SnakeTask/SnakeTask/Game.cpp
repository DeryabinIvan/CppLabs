#include "Game.h"

#include <conio.h>

void Game::restart() {
	srand(time(0));
	food.x = 1 + rand() % (X_SIZE - 2);
	food.y = 1 + rand() % (X_SIZE - 2);

	score = 0;
	snake.clear();
}
void Game::update () {
	snake.draw(X_SIZE, Y_SIZE, food.x, food.y);
	cout << "Score: " << score << endl;
	for (unsigned int i = 0; i < 50000000; i++);
}

bool Game::findInList(unsigned int a, List<unsigned int>& list) {
	if (list.getSize() < 1) return false;

	list.begin();
	unsigned int* elem;

	while (elem = list.getElement()) {
		if (*elem == a)
			return true;
	}

	return false;
}
void Game::sortList(List<Player>& list, List<Player>* sorted) {
	static List<unsigned int> elems;

	if (elems.getSize() == list.getSize()) {
		elems.clear();
		return;
	}

	list.begin();
	Player* elem;

	unsigned int max_score = 0;
	while (elem = list.getElement()) {
		if (elem->score > max_score && !findInList(elem->score, elems))
			max_score = elem->score;
	}

	list.begin();
	while (elem = list.getElement()) {
		if (elem->score == max_score && !findInList(elem->score, elems))
			sorted->addInEnd(*elem);
	}
	elems.addInEnd(max_score);
	sortList(list, sorted);
}

void Game::start() {
	system("cls");

	DIRECTION dir = snake.getHeadDir();
	bool keyPressed = false;
	while (true) {
		update();
		unsigned char key;

		//если нажали на клавишу...
		if (_kbhit()) {
			key = _getch();
			keyPressed = true;

			switch (key) {
				case 'w':
				case 230:
					dir = UP;
					break;
				case 'a':
				case 228:
					dir = LEFT;
					break;
				case 's':
				case 235:
					dir = DOWN;
					break;
				case 'd':
				case 162:
					dir = RIGTH;
					break;

				case 27://ESC
				case 'x':
					cout << "Exit the game? y/n ";
					cin >> key;
					if (key == 'y') {
						snake.clear();
						return;
					}
					break;

				default:
					continue;
			}
		}
		
		if (snake.getX() == food.x && snake.getY() == food.y) {
			score++;
			do {
				food.x = 1+rand()%(X_SIZE-2);
				food.y = 1+rand()%(X_SIZE-2);
			} while (food.x == snake.getX() || food.y == snake.getY());

			snake.addTail();
		}
		snake.move(dir, keyPressed);
		keyPressed = false;

		if (snake.getX() == 0 || snake.getY() == 0 || snake.getX() == X_SIZE - 1 || snake.getY() == Y_SIZE - 1) return;

		system("cls");
	}
}

const char* LEADERS_FILE = "leader.brd";
void Game::readLeaders	() {
	leaders.clear();
	ifstream board(LEADERS_FILE);

	if (!board.is_open()) {
		cerr << "Leaderbord file don`t exist! Creating new file..." << endl;

		ofstream tmp(LEADERS_FILE);
		tmp.close();
		return;
	}

	while (!board.eof()) {
		char buf[255];

		board.getline(buf, 255);

		char *name, *score;
		name = strtok(buf, ";");
		score = strtok(nullptr, ";");

		if (!name || !score) continue;

		Player tmp;
		tmp.name = new char[strlen(name)];
		strcpy(tmp.name, name);

		tmp.score = atoi(score);

		leaders.addInEnd(tmp);
	}
	board.close();

	sorted_list.clear();
	sortList(leaders, &sorted_list);
}
void Game::addLeader	() {
	char buf[255];

	cout << "Enter your name: ";
	cin.ignore();
	cin.getline(buf, 255);

	ofstream board("leader.brd", ios::app);

	board << buf << ';' << score << endl;

	board.close();
}
void Game::printLeaders () {
	if (!sorted_list.getSize()) {
		cout << "Leaderboard is empty! O_o " << endl;
		return;
	}

	sorted_list.begin();
	Player* pl = sorted_list.getElement();
	char pos = 1;
	do {
		cout << int(pos++) << ") " << pl->name << " " << pl->score << endl;
	} while ((pl = sorted_list.getElement()) && pos <= 10);
}