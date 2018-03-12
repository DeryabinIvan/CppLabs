#pragma once

enum DIRECTION { UP, DOWN, LEFT, RIGTH };

#include "List.h"

#include <iostream>

using std::cout;
using std::endl;

class Snake {
	struct SnakePart {
		unsigned char x, y;
		unsigned char sym;
		DIRECTION dir;
	};
	List<SnakePart> snake;
	SnakePart* head;

	public:
		Snake() {
			SnakePart tmp_tail, tmp_head;
			tmp_head.x = 5; tmp_head.y = 5;
			tmp_head.sym = 'S';

			tmp_tail.x = tmp_head.x + 1; tmp_tail.y = tmp_head.y;
			tmp_tail.sym = 'v';

			snake.clear();

			snake.addInEnd(tmp_head);
			snake.addInEnd(tmp_tail);

			snake.begin();
			head = snake.getElement();
		}

		unsigned char getX() { return head->x; }
		unsigned char getY() { return head->y; }
		DIRECTION getHeadDir() { return head->dir; }

		void move(DIRECTION dir, bool changeDir) {
			DIRECTION tmp = head->dir;
			snake.begin();
			SnakePart* prt = snake.getElement();
			do {
				if (changeDir) {
					tmp = prt->dir;
					prt->dir = dir;
					dir = tmp;
				}
				else {
					dir = prt->dir;
					prt->dir = tmp;
					tmp = dir;
				}

				switch (prt->dir) {
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
		}

		void draw(unsigned char xsize, unsigned char ysize, unsigned char fx, unsigned char fy) {
			bool drawed = false;
			for (unsigned char i = 0; i < xsize; i++) {
				for (unsigned char j = 0; j < ysize; j++) {
					//рисуем углы
					if (!i && !j) {
						cout << (unsigned char)201;
						continue;
					}
					else if (!i && j == ysize - 1) {
						cout << (unsigned char)187;
						continue;
					}
					else if (i == xsize - 1 && !j) {
						cout << (unsigned char)200;
						continue;
					}
					else if (i == xsize - 1 && j == ysize - 1) {
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
					} while (prt = snake.getElement());

					if (!drawed) {
						if (fx == i && fy == j) cout << '@';
						else if (i == 0) cout << (unsigned char)205;
						else if (j == 0) cout << (unsigned char)186;
						else if (i == xsize - 1) cout << (unsigned char)205;
						else if (j == ysize - 1) cout << (unsigned char)186;
						else cout << ' ';
					}
					drawed = false;
				}
				cout << endl;
			}
		}

		void clear() {
			snake.clear();

			SnakePart tmp_tail, tmp_head;
			tmp_head.x = 10; tmp_head.y = 10;
			tmp_head.sym = 'S';

			tmp_tail.x = tmp_head.x + 1; tmp_tail.y = tmp_head.y;
			tmp_tail.sym = 'v';

			snake.clear();

			snake.addInEnd(tmp_head);
			snake.addInEnd(tmp_tail);

			snake.begin();
			head = snake.getElement();
		}

		void addTail() {
			snake.begin();
			SnakePart* prt = snake.getElement();
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
};
