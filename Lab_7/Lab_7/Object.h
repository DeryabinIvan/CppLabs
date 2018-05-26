#pragma once

class Object abstract{
	public:
		virtual void toString(char* buf) abstract;
		virtual bool operator==(const Object& o) abstract;
		virtual bool operator!=(const Object& o) abstract;
};

