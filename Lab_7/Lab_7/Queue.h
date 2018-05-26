#pragma once

#include "Object.h"

#include <memory>

class Queue:public Object {
	Object** queue;
	
	size_t size, lastIndex;

	public:
		Queue();
		~Queue();

		Queue& operator<<(Object &o);

		// Inherited via Object
		virtual void toString(char * buf) override;
		virtual bool operator==(const Object& o) override;
		virtual bool operator!=(const Object& o) override;
};

