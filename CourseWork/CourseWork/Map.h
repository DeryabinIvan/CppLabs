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

		void add(Key& key, Value val);
		//Используется для ключей, содержащих несколько значений
		//Полсе begin для получения всех значений последовательно вызываем get
		//В конце get вернет nullptr
		void begin();
		const Value* get(Key& key);
		const Value* operator[](Key& key);

		Map& findBy(Value searchValue);
		ERROR_CODE remove(Key& key);

		bool exist(Key& key);
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
}

template<class Key, class Value>
inline void Map<Key, Value>::add(Key& k, Value v){
	if (exist(k)) {
		size_t keyIndex = getKeyIndex(k);
		size_t lastVal = getValueSize(keyIndex)+1;

		Value* valCopy = new Value[lastVal];
		memcpy(valCopy, vals[keyIndex], sizeof(Value)*lastVal);

		delete[] vals[keyIndex];
		vals[keyIndex] = new Value[lastVal + 1];

		memcpy(vals[keyIndex], valCopy, sizeof(Value)*lastVal);
		
		vals[keyIndex][lastVal-1] = v;
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
		if (iteratorPos > getValueSize(tmpIndex)) {
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
inline Map<Key, Value>& Map<Key, Value>::findBy(Value searchValue){
	findValue = new Value(searchValue);
	return *this;
}

template<class Key, class Value>
inline ERROR_CODE Map<Key, Value>::remove(Key& key){
	if (!exist(key)) return NOT_FIND;

	size_t index = getKeyIndex(key);
	if (getValueSize(index) > 1 && !findValue) return MULTIPLIE_ELEMNTS;

	if (getValueSize(index) > 1) {
		size_t newSize = valueSize[index]--;
		Value* valCopy = new Value[newSize];
		for (size_t i = 0, j = 0; i < newSize; i++)
			if (vals[index][i] != *findValue)
				valCopy[j++] = vals[index][i];
		delete[] vals[index];

		vals[index] = new Value[newSize];
		memcpy(vals, valCopy, sizeof(Value)*newSize);
		delete[] valCopy;
	}
	else {
		Value** valCopy = new Value*[--size];
		for (size_t i = 0, j = 0; i < size; i++)
			if (i != index)
				valCopy[j++] = vals[i];
		delete[] vals;

		vals = new Value*[size];
		memcpy(vals, valCopy, sizeof(Value)*size);
		delete[] valCopy;

		Key* keyCopy = new Key[--lastKeyInd];
		for (size_t i = 0, j = 0; i < lastKeyInd; i++)
			if (keys[i] != key)
				keyCopy[j++] = keys[i];
		delete[] keys;

		keys = new Key[lastKeyInd];
		memcpy(keys, keyCopy, sizeof(Key)*lastKeyInd);
		delete[] keyCopy;
	}
	
	return OK;
}
template<class Key, class Value>
inline bool Map<Key, Value>::exist(Key& k){
	for (size_t i = 0; i < lastKeyInd; i++) {
		if (keys[i] == k)
			return true;
	}
	return false;
}
