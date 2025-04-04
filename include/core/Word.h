#ifndef WORD_H
#define WORD_H

#include <array>
#include <string>
#include <ostream>
#include <iostream>
#include <stdexcept>
#include "core/Octet.h"

using namespace std;

class Word {
private:
	array<Octet, 4> _octets;

public:
	Word() = default;

	Word(const string& hex);

	const Octet& operator[](size_t index) const { return _octets[index]; }

	void setOctet(size_t index, const Octet& octet);

	Word operator^(const Word& w) const;

	Word& operator^=(const Word& w);

	Word& operator<<=(size_t n);

	bool operator==(const Word& w) const { return _octets == w._octets; }

	ostream& print(ostream& os = cout) const;

	friend ostream& operator<<(ostream& os, const Word& word)
	{
		return word.print(os);
	}
};

inline void Word::setOctet(size_t index, const Octet& octet)
{
	if (index >= 4)
		throw out_of_range("Indice incorrect.");

	_octets[index] = octet;
}

inline Word Word::operator^(const Word& w) const
{
	Word res("00000000");

	for (size_t i = 0; i < 4; ++i)
		res._octets[i] = _octets[i] ^ w._octets[i];

	return res;
}

inline Word& Word::operator^=(const Word& w)
{
	for (size_t i = 0; i < 4; ++i)
		_octets[i] ^= w._octets[i];

	return *this;
}

inline Word& Word::operator<<=(size_t n)
{
	for (size_t i = 0; i < n; ++i)
	{
		Octet tmp = _octets[0];

		for (size_t j = 0; j < 3; ++j)
			_octets[j] = _octets[j + 1];

		_octets[3] = tmp;
	}

	return *this;
}

inline ostream& Word::print(ostream& os) const
{
	for (size_t i = 0; i < 4; ++i)
		os << _octets[i].toHex() << " ";

	return os;
}

#endif // WORD_H