#pragma once

#include <memory>

template<class Key, class Value> class Map{
	Value** vals;
	Key* keys;

	size_t lastKeyInd, size, iteratorPos=0;

	size_t getKeyIndex(Key k);
	size_t getValueMaxIndex(size_t index);
	size_t getValueSize(size_t index);

	public:
		Map();
		~Map();

		void add(Key key, Value val);
		//Используется для ключей, содержащих несколько значений
		//Полсе begin для получения всех значений последовательно вызываем get
		//В конце get вернет nullptr
		void begin();
		Value* get(Key key);

		void remove(Key key);

		bool exist(Key key);
};

template<class Key, class Value>
inline size_t Map<Key, Value>::getKeyIndex(Key k){
	for (size_t i = 0; i < lastKeyInd; i++)
		if (keys[i] == k)
			return i;
	return 0;
}

template<class Key, class Value>
inline size_t Map<Key, Value>::getValueMaxIndex(size_t index){
	return sizeof(vals[index]) / sizeof(vals[index][0]);
}

template<class Key, class Value>
inline size_t Map<Key, Value>::getValueSize(size_t index)
{
	return getValueMaxIndex(index)-1;
}

template<class Key, class Value>
inline Map<Key, Value>::Map(){
	vals = new Value*[1];
	keys = new Key[1];

	lastKeyInd = 0;
	size = 10;
}

template<class Key, class Value>
inline Map<Key, Value>::~Map(){
	for (size_t i = 0; i < lastKeyInd; i++)
		if(vals[i]) delete[] vals[i];

	delete[] keys;
}

template<class Key, class Value>
inline void Map<Key, Value>::add(Key k, Value v){
	if (exist(k)) {
		size_t keyIndex = getKeyIndex(k);
		size_t lastVal = getValueMaxIndex(keyIndex);

		Value* valCopy = new Value[lastVal];
		memcpy(valCopy, vals[keyIndex], sizeof(Value)*lastVal);

		delete[] vals[keyIndex];
		vals[keyIndex] = new Value[lastVal + 1];

		memcpy(vals[keyIndex], valCopy, sizeof(Value)*lastVal);
		
		vals[keyIndex][lastVal] = v;

		delete[] valCopy;
	}
	else {
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

		vals[lastKeyInd++][0] = v;
	}
}

template<class Key, class Value>
inline void Map<Key, Value>::begin(){
	iteratorPos = 0;
}

template<class Key, class Value>
inline Value * Map<Key, Value>::get(Key k){
	if (!exist(k)) return nullptr;

	size_t tmpIndex = getKeyIndex(k);
	if (iteratorPos > getValueSize(tmpIndex)) {
		iteratorPos = 0;
		return nullptr;
	}
	if(getValueSize(tmpIndex) > 1)
		return &vals[tmpIndex][iteratorPos++];
	else
		return &vals[tmpIndex][0];
}

template<class Key, class Value>
inline bool Map<Key, Value>::exist(Key k){
	for (size_t i = 0; i < lastKeyInd; i++) {
		if (keys[i] == k)
			return true;
	}
	return false;
}
