#ifndef KEY_H
#define KEY_H

#include <vector>
#include <ostream>
#include <iostream>
#include "core/Word.h"

using namespace std;

class Key {
private:
	vector<Word> _words;
	size_t _nbWords;
	size_t _nbRounds;

public:
	Key() = default;

	Key(const string& hex);

	const Word& operator[](size_t index) const { return _words[index]; }

	size_t getNbWords() const { return _nbWords; }

	size_t getNbRounds() const { return _nbRounds; }

	ostream& print(ostream& os = cout) const;

	friend ostream& operator<<(ostream& os, const Key& key)
	{
		return key.print(os);
	}
};

inline ostream& Key::print(ostream& os) const
{
	for (size_t i = 0; i < _words.size(); ++i)
		os << _words[i] << endl;

	return os;
}

#endif // KEY_H