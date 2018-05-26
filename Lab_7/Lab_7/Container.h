#pragma once

#include "Object.h"

#include <string>
#include <iostream>

enum CONTAINER_TYPE{INT, FLOAT, BOOL, NONE};

class Container:public Object {
	union {
		int idata;
		float fdata;
		bool bdata;
	} data;
	CONTAINER_TYPE type;

	public:
		Container(CONTAINER_TYPE t, void* var);
		Container(float data);
		Container(int data);
		Container(bool data);

		CONTAINER_TYPE getType() { return type; }

		// Inherited via Object
		virtual void toString(char* buf) override;
		virtual bool operator==(const Object& o) override;
		virtual bool operator!=(const Object& o) override;

		friend std::ostream& operator<<(std::ostream& stream, Container &c) {
			switch (c.type){
				case INT:
					stream << c.data.idata;
					break;
				case FLOAT:
					stream << c.data.fdata;
					break;
				case BOOL:
					stream << std::boolalpha << c.data.bdata;
					break;
			}
			return stream;
		}
};

