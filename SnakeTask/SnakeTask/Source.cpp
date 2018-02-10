#include <iostream>
#include <fstream>

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
	size_t list_size = -1;
	size_t position = 0;

	public:
		List() {
			head = new Node<T>;
			head->next = nullptr;
		}
		~List(){
			while (list_size) removeLast();
			delete head;
		}

		void addInEnd(T new_data) {
			if (list_size == -1) {
				head->data = new_data;
				list_size = 0;
				return;
			}

			head->add(head, new_data);
			list_size++;
		}
		void addInStart(T new_data) {
			if (list_size == -1) {
				head->data = new_data;
				list_size = 0;
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
		
};

struct Player {
	char* name;
	unsigned int score;
};

void init();
void readLeaders();
void addLeader();
void showLeaders();
void newGame();

void clear() { system("cls"); }

List<Player> leaders;

#define W_SIZE 25
#define H_SIZE 30

char map[W_SIZE][H_SIZE];

enum MENU{START=1, BOARD, HELP, EXIT};

unsigned int score=0;

int main() {
	char menu_key;

	init();

	while (true){
		printf("Menu:\n\t%d) New Game\n\t%d) Leaderboard\n\t%d) Help\n\t%d) Exit\n", START, BOARD, HELP, EXIT);

		readLeaders();

		cin >> menu_key;
		clear();
		switch (menu_key-'0'){
			case START:
				newGame();
				addLeader();
				showLeaders();
				break;
			case BOARD:
				showLeaders();
				break;
			case HELP:
				cout << "WASD - control" << endl;
				cout << "That`s all ;)"<<endl;
				break;
			case EXIT:
				return 0;
		}
	}
	return 0;
}

void update() {
	for (int i = 0; i < W_SIZE; i++) {
		for (int j = 0; j < H_SIZE; j++)
			cout << map[i][j];
		cout << endl;
	}
}

void init() {
	for (int i = 0; i < W_SIZE; i++){
		map[0][i] = '-';
		map[H_SIZE - 1][i] = '#';
	}
	update();
}



void newGame() {
	
}

const char* LEADERS_FILE = "leader.brd";

void readLeaders() {
	ifstream board(LEADERS_FILE);

	if (!board.is_open()) {
		cerr << "Leaderbord file don`t exist! Creating new file..." << endl;

		ofstream tmp(LEADERS_FILE);
		tmp.close();

		board.open(LEADERS_FILE);
		return;
	}

	unsigned int best = 0;
	while (!board.eof()) {
		char buf[255];

		board.getline(buf, 255);

		char *name, *score;

		name = strtok(buf, ";");
		score = strtok(nullptr, ";");

		if (!name || !score) {
			cerr << "Leaderboard file corrupted!" << endl;
			return;
		}

		Player tmp;
		tmp.name = new char[strlen(name)];
		strcpy(tmp.name, name);

		
		tmp.score = atoi(score);

		if (tmp.score > best) {
			leaders.addInStart(tmp);
			best = tmp.score;
		}else leaders.addInEnd(tmp);
	}
	board.close();
}

void addLeader() {
	char buf[255];

	cin.ignore();
	cin.getline(buf, 255);

	ofstream board("leader.brd");

	Player tmp;
	tmp.name = new char[strlen(buf)];
	strcpy(tmp.name, buf);

	tmp.score = score;

	leaders.addInEnd(tmp);

	leaders.begin();
	Player* pl = leaders.getElement();
	do {
		board << pl->name << ';' << pl->score;
	} while (pl = leaders.getElement());

	leaders.~List();

	readLeaders();
}

void showLeaders(){
	leaders.begin();
	Player* pl = leaders.getElement();
	char pos = 1;
	do {
		cout << int(pos++) << ") " << pl->name << " " << pl->score << endl;
	} while (pl = leaders.getElement());
}
