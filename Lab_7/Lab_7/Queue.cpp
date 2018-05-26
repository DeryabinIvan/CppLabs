#include "Queue.h"

Queue::Queue() {
	queue = new Object*[size = 10];
	lastIndex = 0;
}
Queue::~Queue() {
	delete[] queue;

	size = lastIndex = 0;
}

Queue& Queue::operator<<(Object& o){
	if (lastIndex > size) {
		Object** copy = new Object*[size];
		
		memcpy(copy, queue, sizeof(Object*)*size);
		for (size_t i = 0; i < lastIndex; i++)
			delete queue[i];
		delete[] queue;

		queue = new Object*[size + 5];
		memcpy(queue, copy, sizeof(Object*)*size);
		size += 5;
	}

	queue[lastIndex++] = &o;

	return *this;
}

void Queue::toString(char* buf) {
	sprintf(buf, "[");
	for (size_t i = 0; i < lastIndex; i++) {
		queue[i]->toString(buf + strlen(buf));

		if (i != lastIndex - 1) sprintf(buf + strlen(buf), ", ");
	}
	sprintf(buf + strlen(buf), "]");
}

bool Queue::operator==(const Object &o) {
	Queue* tmp = (Queue*)&o;
	
	if(lastIndex != tmp->lastIndex) return false;
	for (size_t i = 0; i < lastIndex; i++)
		if (queue[i] != tmp->queue[i])
			return false;
	return true;
}
bool Queue::operator!=(const Object & o){
	return !((*this) == o);
}
