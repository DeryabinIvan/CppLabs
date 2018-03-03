#include <iostream>
#include <fstream>
#include <random>
#include <conio.h>

using namespace std;

//моя реализация списка
template<typename T> class List {
	template<typename T> struct Node {
		T data;
		Node<T>* next;

		void add(Node<T>* head, T new_data) {
			if (!head->next) {
				head->next = new Node<T>{ new_data, nullptr };
				return;
			}

			Node<T>* tmp = head->next;
			while (tmp->next) tmp = tmp->next;

			tmp->next = new Node<T>{ new_data, nullptr };
		}
	};
	Node<T>* head;
	size_t list_size = 0;
	size_t position = 1;

	public:
		List() {
			head = new Node<T>;
			head->next = nullptr;
		}
		~List(){
			while (list_size > 1) removeLast();
			
			head->next = nullptr;
			delete head;

			list_size = 0;
		}

		void addInEnd(T new_data) {
			if (!list_size) {
				head->data = new_data;
				list_size = 1;
				return;
			}

			head->add(head, new_data);
			list_size++;
		}
		void addInStart(T new_data) {
			if (!list_size) {
				head->data = new_data;
				list_size = 1;
				return;
			}

			head = new Node<T>{ new_data, head };

			list_size++;
		}

		void removeLast() {
			if (!head->next) return;

			Node<T>* tmp = head->next;

			for (size_t i = 1; i < list_size - 1; i++)
				tmp = tmp->next;

			delete tmp->next;
			tmp->next = nullptr;

			list_size--;
		}
		void removeFirst() {
			if (!head->next) return;

			Node<T>* tmp = head;
			head = head->next;
			delete tmp;

			list_size--;
		}

		void clear() {
			if (!list_size) return;

			while (list_size < 1) removeLast();

			head->next = nullptr;
			delete head;

			list_size = 0;

			head = new Node<T>;
			head->next = nullptr;
		}

		//Инструкция: при инициализации вызываем begin 
		//затем получаем элемент при помощи getElement
		//при достижении конца списка getElemnt возвращает nullptr
		void begin() { position = 0; }
		T* getElement() {
			if (position > list_size) return nullptr;

			Node<T>* tmp = head;
			for (size_t i = 0; i < position; i++) tmp = tmp->next;

			position++;

			return &(tmp->data);
		}
		
		size_t getSize() { return list_size; }
};

struct Player {
	char* name;
	unsigned int score;
};

struct Food {
	unsigned char x, y;
};

enum DIRECTION { UP, DOWN, LEFT, RIGTH };

struct SnakePart {
	unsigned char x, y;
	DIRECTION dir;
	unsigned char sym;
};

void readLeaders();
void addLeader();
void showLeaders();
void newGame();
void sortList(List<Player>&, List<Player>*);

void clear() { system("cls"); }

List<Player> leaders, sorted_list;
List<SnakePart> snake;
Food food;

const unsigned char Y_SIZE = 20, X_SIZE = 10;

//Генерация случайных координат еды
//В С есть srand() и rand()...
//Но мы же изучаем С++ и его средства...
random_device device;
mt19937 generator(device());
uniform_int_distribution<> ran_x(1, X_SIZE-2), ran_y(1, Y_SIZE-2);

enum MENU{START=1, BOARD, HELP, EXIT};

unsigned int score=0;

int main() {
	char menu_key;

	while (true){
		printf("Menu:\n\t%d) New Game\n\t%d) Leaderboard\n\t%d) Help\n\t%d) Exit\n", START, BOARD, HELP, EXIT);

		cin >> menu_key;
		clear();
		switch (menu_key-'0'){
			case START:
				newGame();
				leaders.clear();
				sorted_list.clear();

				addLeader();
				readLeaders();
				sortList(leaders, &sorted_list);
				showLeaders();
				break;
			case BOARD:
				if (!leaders.getSize()) {
					readLeaders();
					sortList(leaders, &sorted_list);
				}
				showLeaders();
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

void update() {
	bool drawed = false;
	for (unsigned char i = 0; i < X_SIZE; i++){
		for (unsigned char j = 0; j < Y_SIZE; j++) {
			//рисуем углы
			if (!i && !j) {
				cout << (unsigned char)201;
				continue;
			}else if (!i && j == Y_SIZE - 1) {
				cout << (unsigned char)187;
				continue;
			}else if (i == X_SIZE - 1 && !j) {
				cout << (unsigned char)200;
				continue;
			}else if (i == X_SIZE - 1 && j == Y_SIZE - 1) {
				cout << (unsigned char)188;
				continue;
			}

			snake.begin();
			SnakePart* prt = snake.getElement();
			do {
				if (prt->x == i && prt->y == j) {
					cout << prt->sym;
					drawed = true;
					break;
				}
			}while (prt = snake.getElement());

			if (!drawed) {
				if (food.x == i && food.y == j) cout << '@';
				else if (i == 0) cout << (unsigned char)205;
				else if (j == 0) cout << (unsigned char)186;
				else if (i == X_SIZE - 1) cout << (unsigned char)205;
				else if (j == Y_SIZE - 1) cout << (unsigned char)186;
				else cout << ' ';
			}
			drawed = false;
		}
		cout << endl;
	}
	cout << "Score: " << score << endl;
	for (unsigned int i = 0; i < 50000000; i++);
}
void init() {
	SnakePart head, tail;
	head.sym = 'S';
	head.x = X_SIZE/2; head.y = Y_SIZE/2;
	head.dir = UP;

	tail.sym = 'v';
	tail.dir = UP;
	tail.x = head.x+1; tail.y = head.y;

	snake.clear();

	snake.addInEnd(head);
	snake.addInEnd(tail);

	food.x = ran_x(generator);
	food.y = ran_y(generator);

	score = 0;
}
void newGame() {
	init();
	clear();

	snake.begin();
	SnakePart* head = snake.getElement();

	DIRECTION dir = head->dir;
	bool keyPressed = false;
	while (true){
		update();
		unsigned char key;
		
		//если нажали на клавишу...
		if(_kbhit()){
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

		DIRECTION tmp = head->dir;

		snake.begin();
		SnakePart* prt = snake.getElement();
		do {
			if (keyPressed) {
				tmp = prt->dir;
				prt->dir = dir;
				dir = tmp;
			} else {
				dir = prt->dir;
				prt->dir = tmp;
				tmp = dir;
			}
			
			switch (prt->dir){
				case UP:
					prt->x--;
					break;
				case DOWN:
					prt->x++;
					break;
				case LEFT:
					prt->y--;
					break;
				case RIGTH:
					prt->y++;
					break;
			}
		} while (prt = snake.getElement());
		keyPressed = false;

		if (head->x == food.x && head->y == food.y) {
			score++;
			do{
				food.x = ran_x(generator);
				food.y = ran_y(generator);
			} while (food.x == head->x || food.y == head->y);
			
			snake.begin();
			prt = snake.getElement();
			for (size_t i = snake.getSize(); i > 1; i--) prt = snake.getElement();

			SnakePart tail;
			tail.dir = prt->dir;
			tail.x = prt->x;
			tail.y = prt->y;
			
			switch (tail.dir) {
				case UP:
					tail.x++;
					tail.sym = 'v';
					break;
				case DOWN:
					tail.x--;
					tail.sym = '^';
					break;
				case LEFT:
					tail.y++;
					tail.sym = '>';
					break;
				case RIGTH:
					tail.y--;
					tail.sym = '<';
					break;
			}

			snake.addInEnd(tail);
		}

		if (snake.getSize() > 1) {
			snake.begin();
			prt = snake.getElement();
			for (size_t i = snake.getSize(); i > 1; i--) {
				prt = snake.getElement();

				if (head->x == prt->x && head->y == prt->y) return;

				prt->sym = 's';
			}
		
			switch (prt->dir) {
				case UP:
					prt->sym = 'v';
					break;
				case DOWN:
					prt->sym = '^';
					break;
				case LEFT:
					prt->sym = '>';
					break;
				case RIGTH:
					prt->sym = '<';
					break;
			}
		}
		
		if (head->x == 0 || head->y == 0 || head->x == X_SIZE - 1 || head->y == Y_SIZE - 1) return;

		clear();
	}
}

const char* LEADERS_FILE = "leader.brd";

bool findInList(unsigned int a, List<unsigned int>& list) {
	if (list.getSize() < 1) return false;

	list.begin();
	unsigned int* elem;

	while (elem = list.getElement()) {
		if (*elem == a)
			return true;
	}

	return false;
}
void sortList(List<Player>& list, List<Player>* sorted) {
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

void readLeaders() {
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

		if (!name || !score) {
			if (!leaders.getSize()) {
				cerr << "Leaderboard file corrupted!" << endl;
				leaders.clear();
			}
			board.close();
			return;
		}

		Player tmp;
		tmp.name = new char[strlen(name)];
		strcpy(tmp.name, name);

		tmp.score = atoi(score);

		leaders.addInEnd(tmp);
	}
	board.close();
}
void addLeader() {
	char buf[255];

	cout << "Enter your name: ";
	cin.ignore();
	cin.getline(buf, 255);

	ofstream board("leader.brd", ios::app);
	
	board << buf << ';' << score << endl;

	board.close();
}
void showLeaders(){
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
