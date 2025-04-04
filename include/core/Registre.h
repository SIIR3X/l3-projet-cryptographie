#ifndef REGISTRE_H
#define REGISTRE_H

#include <string>
#include <ostream>
#include <iostream>
#include <stdexcept>

using namespace std;

typedef unsigned int uint;
typedef unsigned long long u_long_;

class Registre {
protected:
	size_t _size;
	u_long_ _registre;

public:
	Registre(size_t size)
		: _size(size), _registre(0) {}

	Registre(const string& binaire);

	Registre(const Registre& r)
		: _size(r._size), _registre(r._registre) {}

	size_t getSize() const { return _size; }

	uint get() const { return _registre; }

	uint get(size_t numbit) const;

	uint getLeft() const { return _registre >> (_size / 2); }

	uint getRight() const { return _registre & ((1 << (_size / 2)) - 1); }

	void set(size_t numbit, uint b);

	Registre operator&(const Registre& r) const;

	Registre& operator&=(const Registre& r);

	Registre operator|(const Registre& r) const;

	Registre& operator|=(const Registre& r);

	Registre operator^(const Registre& r) const;

	Registre& operator^=(const Registre& r);

	Registre operator<<(uint nbbits) const;

	Registre operator>>(uint nbbits) const;

	Registre& operator<<=(uint nbbits);

	Registre& operator>>=(uint nbbits);

	Registre& operator=(const Registre& r);

	bool operator==(const Registre& r) const { return _registre == r._registre; }

	string toHex() const;

	string toBin() const;

	operator string() const;

	ostream& print(ostream& os = cout) const;

	friend ostream& operator<<(ostream& os, const Registre& registre)
	{
		return registre.print(os);
	}
};

inline uint Registre::get(size_t numbit) const
{
	if (numbit >= _size)
		throw out_of_range("Indice incorrect.");

	return (_registre >> numbit) & 1;
}

inline void Registre::set(size_t numbit, uint b)
{
	if (numbit >= _size)
		throw out_of_range("Indice incorrect.");

	_registre = (_registre & ~(1 << (_size - 1 - numbit))) | (b << (_size - 1 - numbit));
}

inline Registre Registre::operator&(const Registre& r) const
{
	Registre res(_size);
	res._registre = _registre & r._registre;
	return res;
}

inline Registre& Registre::operator&=(const Registre& r)
{
	_registre &= r._registre;
	return *this;
}

inline Registre Registre::operator|(const Registre& r) const
{
	Registre res(_size);
	res._registre = _registre | r._registre;
	return res;
}

inline Registre& Registre::operator|=(const Registre& r)
{
	_registre |= r._registre;
	return *this;
}

inline Registre Registre::operator^(const Registre& r) const
{
	Registre res(_size);
	res._registre = _registre ^ r._registre;
	return res;
}

inline Registre& Registre::operator^=(const Registre& r)
{
	_registre ^= r._registre;
	return *this;
}

inline Registre Registre::operator<<(uint nbbits) const
{
	Registre r(_size);
	r._registre = _registre << nbbits;
	return r;
}

inline Registre Registre::operator>>(uint nbbits) const
{
	Registre r(_size);
	r._registre = _registre >> nbbits;
	return r;
}

inline Registre& Registre::operator<<=(uint nbbits)
{
	_registre <<= nbbits;
	return *this;
}

inline Registre& Registre::operator>>=(uint nbbits)
{
	_registre >>= nbbits;
	return *this;
}

inline Registre& Registre::operator=(const Registre& r)
{
	_registre = r._registre;
	return *this;
}

inline string Registre::toHex() const
{
	string res;
	string hex = "0123456789ABCDEF";

	for (size_t i = 0; i < _size; i += 4)
		res += hex[(_registre >> (_size - 4 - i)) & 0xF];

	return res;
}

inline string Registre::toBin() const
{
	string res;

	for (size_t i = 0; i < _size; ++i)
		res += to_string(get(i));

	return res;
}

inline Registre::operator string() const
{
	return string(1, (char)_registre);
}

inline ostream& Registre::print(ostream& os) const
{
	return os << _registre;
}

#endif // REGISTRE_H