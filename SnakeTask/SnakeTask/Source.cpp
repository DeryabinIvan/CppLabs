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

struct SnakePart {
	unsigned char x, y;
	char sym;
};

void readLeaders();
void addLeader();
void showLeaders();
void newGame();

void clear() { system("cls"); }

List<Player> leaders;
List<SnakePart> snake;
Food food;

unsigned char hx, hy;

const unsigned char Y_SIZE = 30, X_SIZE = 20;

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
				addLeader();
				leaders.clear();
				readLeaders();
				showLeaders();
				break;
			case BOARD:
				if(!leaders.getSize()) readLeaders();
				showLeaders();
				break;
			case HELP:
				cout << "WASD - control; X-exit" << endl;
				cout << "That`s all ;)"<<endl;
				break;
			case EXIT:
				return 0;
		}
	}
	return 0;
}

void update() {
	snake.begin();
	SnakePart* prt = snake.getElement();
	do {
		for (unsigned char i = 0; i < X_SIZE; i++){
			for (unsigned char j = 0; j < Y_SIZE; j++) {
				if (prt->x == i && prt->y == j) cout << prt->sym;
				else if (food.x == i && food.y == j) cout << '@';
				else if (i == 0) cout << '#';
				else if (j == 0) cout << '#';
				else if (i == X_SIZE-1) cout << '#';
				else if (j == Y_SIZE-1) cout << '#';
				else cout << ' ';
			}
			cout << endl;
		}
	} while (prt = snake.getElement());
}

void init() {
	SnakePart head;
	head.sym = 'S';
	hx = head.x = 10; hy = head.y = 10;

	snake.addInEnd(head);

	food.x = ran_x(generator);
	food.y = ran_y(generator);
}

void newGame() {
	init();
	clear();
	update();

	snake.begin();
	SnakePart* head = snake.getElement();

	while (true){
		char key;
		
		key = _getch();

		switch (key){
			case 'w':
				head->x--;
				break;
			case 'a':
				head->y--;
				break;
			case 's':
				head->x++;
				break;
			case 'd':
				head->y++;
				break;

			case 'x':
				cout << "Exit the game? y/n ";
				cin >> key;
				if (key == 'y') {
					snake.clear();
					return;
				}
				break;
		}

		if (head->x == food.x && head->y == food.y) {
			score++;
			do{
				food.x = ran_x(generator);
				food.y = ran_y(generator);
			} while (food.x == head->x || food.y == head->y);
			
		}

		if (head->x == 0 || head->y == 0 || head->x == X_SIZE - 1 || head->y == Y_SIZE - 1) return;

		clear();
		update();
	}
}

const char* LEADERS_FILE = "leader.brd";

void readLeaders() {
	ifstream board(LEADERS_FILE);

	if (!board.is_open()) {
		cerr << "Leaderbord file don`t exist! Creating new file..." << endl;

		ofstream tmp(LEADERS_FILE);
		tmp.close();
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

		if (tmp.score > best) {
			leaders.addInStart(tmp);
			best = tmp.score;
		}else leaders.addInEnd(tmp);
	}
	board.close();
}

void addLeader() {
	char buf[255];

	cout << "Enter your name: ";
	cin.ignore();
	cin.getline(buf, 255);

	Player tmp;
	tmp.name = new char[strlen(buf)];
	strcpy(tmp.name, buf);

	tmp.score = score;

	leaders.addInEnd(tmp);

	ofstream board("leader.brd");
	leaders.begin();
	Player* pl = leaders.getElement();
	do {
		board << pl->name << ';' << pl->score << endl;
	} while (pl = leaders.getElement());
}

void showLeaders(){
	if (!leaders.getSize()) {
		cout << "Leaderboard is empty! O_o " << endl;
		return;
	}

	leaders.begin();
	Player* pl = leaders.getElement();
	char pos = 1;
	do {
		cout << int(pos++) << ") " << pl->name << " " << pl->score << endl;
	} while (pl = leaders.getElement());
}
