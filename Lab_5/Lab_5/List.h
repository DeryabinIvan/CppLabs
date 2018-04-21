#pragma once

template<typename T> class List {
	template<typename T> struct Node {
		T data;
		Node<T>* next;

		void add(Node<T>* head, T& new_data) {
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
		~List() {
			while (list_size > 1) removeLast();

			head->next = nullptr;
			delete head;

			list_size = 0;
		}

		void addInEnd(T& new_data) {
			if (!list_size) {
				head->data = new_data;
				list_size = 1;
				return;
			}

			head->add(head, new_data);
			list_size++;
		}
		void addInStart(T& new_data) {
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