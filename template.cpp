// template.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
template <typename PairTKey, typename PairTValue>
class KeyValuePair {
public:
	PairTKey key;
	PairTValue value;
	KeyValuePair() :key(), value() {}
	KeyValuePair(const PairTKey key, const PairTValue value)
		:key(key), value(value) {
	}
	PairTValue& operator[](PairTKey key) { return value; }
};
template <typename TKey, typename TValue>
class Dictionary {
public:
	Dictionary()
	{
		_pairs = new KeyValuePair<TKey, TValue>[_capacity];
	}
	TValue& item(const TKey key);
	TValue& operator[](const TKey key)
	{
		for (size_t i = 0; i < _count; i++)
		{
			if (_pairs[i].key == key) return _pairs[i][key];
		}

		// Key tapılmasa yenisini əlavə edin.
		if (_count >= _capacity) {
			_capacity *= 2;
			auto newPairs = new KeyValuePair<TKey, TValue>[_capacity];
			for (size_t i = 0; i < _count; i++)
				newPairs[i] = _pairs[i];
			delete[] _pairs;
			_pairs = newPairs;
		}

		_pairs[_count] = KeyValuePair<TKey, TValue>(key, TValue());
		return _pairs[_count++].value;
	
	}
	void add(const KeyValuePair<TKey, TValue> pair);
	void add(const TKey key, const TValue value) {
		// check capacity
		_pairs[_count++] = { key, value };
		// Alternative
		//_pairs[_count++] = KeyValuePair<TKey, TValue>{ key, value };
	}
	size_t count() const {
		return _count;
	}
	size_t capacity() const {
		return _capacity;
	}
	TKey* keys();
	TValue* values();
	KeyValuePair<TKey, TValue>* items();
	void clear() {
		delete[] _pairs;
		_count = 0;
		_capacity = 5;
		_pairs = new KeyValuePair<TKey, TValue>[_capacity];
	}
	bool containsKey(const TKey key) const {
		for (size_t i = 0; i < _count; i++) {
			if (_pairs[i].key == key)
				return true;
		}
		return false;
	}
	bool containsValue(const TValue value) const {
		for (size_t i = 0; i < _count; i++) {
			if (_pairs[i].value == value)
				return true;
		}
		return false;
	}
	bool remove(const TKey key) {
		for (size_t i = 0; i < _count; i++) {
			if (_pairs[i].key == key) {
				for (size_t j = i; j < _count - 1; j++) {
					_pairs[j] = _pairs[j + 1];
				}
				_count--;
				return true;
			}
		}
		return false;
	}
private:
	KeyValuePair<TKey, TValue>* _pairs = nullptr;
	size_t _count = 0;
	size_t _capacity = 5;
};


int main()
{
	Dictionary<int, string> dict;
	dict.add(1, "Apple");
	// dict[1] = "Apple";
	cout << dict[1] << endl;
	dict[1] = "Banana";
	cout << dict[1] << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
