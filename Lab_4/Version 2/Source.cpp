#include <iostream>

using namespace std;

//Я мучился несколько часов но придумал "универсальные" версии List и Node
//И да писал их я...(наверное там куча ошибок)
template<typename T> struct Node {
	T data;
	Node* next;

	void add(Node* head, T new_data) {
		Node* tmp = head->next;

		if (!tmp) {
			head->next = new Node{ new_data, nullptr };
			return;
		}

		while (tmp->next) tmp = tmp->next;

		tmp->next = new Node{ new_data, nullptr };
	}
};
template<typename T> class  List  {
	private:
		Node<T>* head;
		size_t list_size = 0;

	public:
		List() {
			head = new Node<T>;
			head->next = nullptr;
		}

		void addLast(T new_data) {
			head->add(head, new_data);
			list_size++;
		}
		void addFirst(T new_data) {
			head = new Node{ new_data, head };
			list_size++;
		}

		void removeLast() {
			if (!head->next) {
				cerr << "Can`t remove in empty list" << endl;
				return;
			}

			Node<T>* tmp = head->next;

			for (size_t i = 1; i < list_size - 1 && tmp->next; i++)
				tmp = tmp->next;

			delete tmp->next;
			tmp->next = nullptr;

			list_size--;
		}
		void removeFirst() {
			if (!head->next) {
				cerr << "Can`t remove in empty list" << endl;
				return;
			}

			Node<T>* tmp = head;
			head = head->next;
			delete tmp;

			list_size--;
		}

		void swap(Node<T>* v1, Node<T>* v2) {
			size_t v1_n, v2_n;

			Node<T>* tmp = head->next;
			for (v1_n = 0; tmp->next; v1_n++)
				if (tmp == v1) break;
				else tmp = tmp->next;

			tmp = head->next;
			for (v2_n = 0; tmp->next; v2_n++)
				if (tmp == v2) break;
				else tmp = tmp->next;

			Node<T> *v1_l, *v2_l;
			tmp = head->next;
			for (size_t i = 0; i < v1_n; i++)
				tmp = tmp->next;
			v1_l = tmp;

			tmp = head->next;
			for (size_t i = 0; i < v2_n; i++)
				tmp = tmp->next;
			v2_l = tmp;

			v2_l->next = v1;
			tmp = v1->next;
			v1->next = v2->next;

			v1_l->next = v2;
			v2->next = tmp;
		}

		Node<T>* getHead() { return head; }
		size_t getSize() { return list_size; }

		void print() {
			Node<T>* tmp = head->next;
			while (tmp) {
				cout << tmp->data;
				tmp = tmp->next;
			}
			cout << endl;
		}
};

//Собственно наша структура
struct Note {
	char* FI;
	unsigned int phone;
	unsigned short date[3];

	//Чтобы можно было выводить в cout
	friend ostream& operator<<(ostream& os, const Note note) {
		cout << "Name: " << note.FI << "\nPhone: " << note.phone << "\nDate: " << note.date[0] << "." << note.date[1] << "." << note.date[2] << endl;
		return os;
	}
};

//Необходимые методы
void addNote();
void findNote();
void sort();

//И переменные
List<Note> list;
enum MENU { ENTER = 1, FIND, PRINT, HELP, EXIT };

int main() {
	short menu_key;

	while (true) {
		printf("Menu:\n\t%d) Enter note\n\t%d) Find by month\n\t%d) Print note list\n\t%d) Help\n\t%d) Exit\n", ENTER, FIND, PRINT, HELP, EXIT);

		cin >> menu_key;
		system("cls");
		switch (menu_key) {
		case ENTER:
			addNote();
			sort();
			break;

		case FIND:
			findNote();
			break;

		case HELP:
			cout << "Note input format: FI;PHONE;DATE" << endl;
			cout << "Date format: DD.MM.YYYY" << endl;
			cout << endl;
			break;

		case PRINT:
			list.print();
			break;

		case EXIT:
			return 0;
		}
	}

	return 0;
}

int compare(const Note* v1, const Note* v2) {
	char *n1 = v1->FI, *n2 = v2->FI;

	for (unsigned short i = 0; n1[i] != ' ' && n2[i] != ' '; i++) {
		if ((n1[i] - n2[i]) != 0) return int(n1[i] - n2[i]);
	}

	return 0;
}

//Я не знаю где, но тут есть ошибка
//Хотя вроде все должно работать...
void sort() {
	if (list.getSize() < 2) {
		cout << "Nothing to sort" << endl << endl;
		return;
	}

	Node<Note>* v1 = list.getHead()->next;
	Node<Note>* v2 = v1->next;
	Node<Note>* min = nullptr;
	

	while (v2->next){
		int res = compare(&(v1->data), &(v2->data));

		if (res < 0) min = v1;
		else if (res > 0) min = v2;

		v1 = v2;
		v2 = v2->next;
	}
	list.swap(list.getHead()->next, min);
	Node<Note>* tmp = min->next;
	for (size_t i = 0; i < list.getSize(); i++){
		while (v2->next) {
			if (v1 != min && v2 != min) {
				int res = compare(&(v1->data), &(v2->data));

				if (res < 0) min = v1;
				else if (res > 0) min = v2;

				v1 = v2;
				v2 = v2->next;
			} else {
				continue;
			}
		}
		list.swap(tmp, min);
		tmp = min->next;
	}

	list.print();
}

void addNote() {
	cout << "Enter - to exit or...\n";
	cin.ignore();
	for (short i = 0; i < 8; i++) {
		char line[255];

		cout << "Enter " << i + 1 << "-note: ";
		cin.getline(line, 255);

		if (!isalpha(line[0])) return;

		char* fi = strtok(line, ";");
		char* phone = strtok(nullptr, ";");
		char* date = strtok(nullptr, ";");

		Note new_note;

		new_note.FI = new char[strlen(fi)];
		strcpy(new_note.FI, fi);

		new_note.phone = atoi(phone);

		new_note.date[0] = atoi(strtok(date, "."));
		new_note.date[1] = atoi(strtok(nullptr, "."));
		new_note.date[2] = atoi(strtok(nullptr, "."));

		list.addLast(new_note);
	}
}

void findNote() {
	short m;
	cin >> m;
	for (Node<Note>* tmp = list.getHead(); tmp->next; tmp = tmp->next)
		if (tmp->data.date[1] == m) cout << "Find: " << tmp->data.FI << endl;
	
	cout << endl;
}