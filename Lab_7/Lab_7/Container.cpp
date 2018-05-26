#include "Container.h"

Container::Container(CONTAINER_TYPE t, void* var) {
	switch (type = t) {
		case INT:
			data.idata = *((int*)var);
			break;
		case FLOAT:
			data.fdata = *((float*)var);
			break;
		case BOOL:
			data.bdata = *((bool*)var);
			break;
	}
}
Container::Container(float val){
	type = FLOAT;
	data.fdata = val;
}
Container::Container(int val) {
	type = INT;
	data.idata = val;
}
Container::Container(bool val) {
	type = BOOL;
	data.bdata = val;
}

void Container::toString(char* buf) {
	switch(type) {
		case INT:
			sprintf(buf, "%d", data.idata);
			break;
		case FLOAT:
			sprintf(buf, "%f", data.fdata);
			break;
		case BOOL:
			sprintf(buf, "%s", data.bdata ? "true" : "false");
			break;
		case NONE:
			sprintf(buf, "NULL");
			break;
	}
}
bool Container::operator==(const Object& o) {
	Container* tmp = (Container*)&o;

	if (type != tmp->type) return false;

	return data.idata == tmp->data.idata;
}

bool Container::operator!=(const Object & o){
	return !((*this) == o);
}
