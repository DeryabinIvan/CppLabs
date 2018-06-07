#pragma once

#include <memory>

enum ERROR_CODE{OK, NOT_FIND, MULTIPLIE_ELEMNTS};

template<class Key, class Value> class Map{
	Value** vals;
	Key* keys;
	size_t* valueSize;

	size_t lastKeyInd, size, iteratorPos=0;

	Value* findValue;

	size_t getKeyIndex(Key& k);
	size_t getValueMaxIndex(size_t index);
	size_t getValueSize(size_t index);

	public:
		Map();
		~Map();

		void add(Key& key, Value& val);
		//Используется для ключей, содержащих несколько значений
		//Полсе begin для получения всех значений последовательно вызываем get
		//В конце get вернет nullptr
		void begin();
		const Value* get(Key& key);
		const Value* operator[](Key& key);

		Map& findBy(Value& searchValue);
		ERROR_CODE remove(Key& key);
		void clear();

		bool exist(Key& key);
		size_t getKeysCount() { return lastKeyInd; }
		size_t getValCount(Key& k) { return getValueSize(getKeyIndex(k)); }

		friend std::ostream& operator<<(std::ostream& os, Map<Key, Value>& m) {
			if (m.lastKeyInd == 0) return os;

			for (size_t i = 0; i < m.lastKeyInd; i++) {
				Key key = m.keys[i];
				os << key << ": ";
				m.begin();
				for (size_t j = 0; j <= m.valueSize[i]-1; j++) {
					os << *m[key];
					if (m.valueSize[i] - j != 1)
						os << ' ';
				}
				//m.iteratorPos = 0;
				if (m.lastKeyInd - i != 1)
					os << '\n';
			}
			return os;
		}
		friend std::istream& operator>>(std::istream& os, Map<Key, Value>& m);
};

template<class Key, class Value>
inline size_t Map<Key, Value>::getKeyIndex(Key& k){
	for (size_t i = 0; i < lastKeyInd; i++)
		if (keys[i] == k)
			return i;
	return 0;
}
template<class Key, class Value>
inline size_t Map<Key, Value>::getValueSize(size_t index){
	return valueSize[index];
}
template<class Key, class Value>
inline size_t Map<Key, Value>::getValueMaxIndex(size_t index){
	return getValueSize(index)-1;
}

template<class Key, class Value>
inline Map<Key, Value>::Map(){
	size = 10;

	vals = new Value*[size];
	valueSize = new size_t[size];
	keys = new Key[size];

	lastKeyInd = 0;
	memset(valueSize, (size_t)0, sizeof(size_t)*10);
}
template<class Key, class Value>
inline Map<Key, Value>::~Map(){
	for (size_t i = 0; i < lastKeyInd; i++)
		if(valueSize[i] > 1) delete[] vals[i];

	delete[] vals;
	delete[] keys;
	delete[] valueSize;
	delete findValue;

	size = 0;
	iteratorPos = 0;
	lastKeyInd = 0;
}

template<class Key, class Value>
inline void Map<Key, Value>::add(Key& k, Value& v){
	if (exist(k)) {
		size_t keyIndex = getKeyIndex(k);
		size_t lastVal = getValueSize(keyIndex);

		Value* valCopy = new Value[lastVal];
		for (size_t i = 0; i < lastVal; i++)
			valCopy[i] = vals[keyIndex][i];

		delete[] vals[keyIndex];
		vals[keyIndex] = new Value[lastVal + 1];

		for (size_t i = 0; i < lastVal; i++)
			vals[keyIndex][i] = valCopy[i];
		
		vals[keyIndex][lastVal] = v;
		valueSize[keyIndex]++;

		delete[] valCopy;
	}else {
		if (lastKeyInd + 1 > size) {
			//Reallocate keys...
			Key* keyCopy = new Key[lastKeyInd];
			memcpy(keyCopy, keys, sizeof(Key)*lastKeyInd);

			delete[] keys;
			keys = new Key[size + 5];
			memcpy(keys, keyCopy, sizeof(Key)*lastKeyInd);
			delete[] keyCopy;

			//Reallocating values...
			Value** valCopy = new Value*[lastKeyInd];
			memcpy(valCopy, vals, sizeof(Value)*lastKeyInd);

			delete[] vals;
			vals = new Value*[size + 5];
			memcpy(vals, valCopy, sizeof(Value)*lastKeyInd);
			delete[] valCopy;

			size += 5;
		}

		keys[lastKeyInd] = k;

		if (getValueSize(lastKeyInd) == 0)
			vals[lastKeyInd] = new Value[1];

		vals[lastKeyInd][valueSize[lastKeyInd]] = v;
		
		valueSize[lastKeyInd]++;
		lastKeyInd++;
	}
}

template<class Key, class Value>
inline void Map<Key, Value>::begin(){
	iteratorPos = 0;
}
template<class Key, class Value>
inline const Value* Map<Key, Value>::get(Key& k){
	if (!exist(k)) return nullptr;

	size_t tmpIndex = getKeyIndex(k);
	
	if (getValueSize(tmpIndex) > 1) {
		if (iteratorPos > getValueMaxIndex(tmpIndex)) {
			iteratorPos = 0;
			return nullptr;
		}
		return &vals[tmpIndex][iteratorPos++];
	}
	else
		return &vals[tmpIndex][0];
}
template<class Key, class Value>
inline const Value* Map<Key, Value>::operator[](Key& key)
{
	return get(key);
}

template<class Key, class Value>
inline Map<Key, Value>& Map<Key, Value>::findBy(Value& searchValue){
	findValue = new Value(searchValue);
	return *this;
}

template<class Key, class Value>
inline ERROR_CODE Map<Key, Value>::remove(Key& key){
	if (!exist(key)) return NOT_FIND;

	size_t index = getKeyIndex(key);
	if (getValueSize(index) > 1 && !findValue) return MULTIPLIE_ELEMNTS;

	if (getValueSize(index) > 1) {
		size_t newSize = valueSize[index] - 1;
		Value* valCopy = new Value[newSize];
		for (size_t i = 0, j = 0; i < valueSize[index]; i++) {
			if (vals[index][i] != *findValue)
				valCopy[j++] = vals[index][i];
		}
		delete[] vals[index];

		vals[index] = new Value[newSize];
		for (size_t i = 0; i < newSize; i++) {
			vals[index][i] = valCopy[i];
		}
		delete[] valCopy;

		valueSize[index]--;
	}
	else {
		Value** valCopy = new Value*[size-1];
		for (size_t i = 0, j = 0; i < size; i++) {
			if (i != index)
				valCopy[j++] = vals[i];
		}
		size--;
		//delete[] vals[index];
		delete[] vals;
		

		vals = new Value*[size];
		for (size_t i = 0; i < size; i++) {
			vals[i] = valCopy[i];
		}
		delete[] valCopy;

		Key* keyCopy = new Key[lastKeyInd];
		for (size_t i = 0, j = 0; i < lastKeyInd; i++) {
			if (keys[i] != key)
				keyCopy[j++] = keys[i];
		}
		lastKeyInd--;
		delete[] keys;

		keys = new Key[lastKeyInd];
		for (size_t i = 0; i < lastKeyInd; i++) {
			keys[i] = keyCopy[i];
		}
		delete[] keyCopy;
	}
	
	return OK;
}
template<class Key, class Value>
inline void Map<Key, Value>::clear() {
	for (size_t i = 0; i < lastKeyInd; i++)
		if (valueSize[i] > 1) delete[] vals[i];

	delete[] vals;
	delete[] keys;
	delete[] valueSize;
	delete findValue;

	size = 10;

	vals = new Value*[size];
	valueSize = new size_t[size];
	keys = new Key[size];

	lastKeyInd = 0;
	memset(valueSize, (size_t) 0, sizeof(size_t) * 10);
}
template<class Key, class Value>
inline bool Map<Key, Value>::exist(Key& k){
	for (size_t i = 0; i < lastKeyInd; i++) {
		if (keys[i] == k)
			return true;
	}
	return false;
}

