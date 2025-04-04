#ifndef OCTET_H
#define OCTET_H

#include <string>
#include <cstdint>
#include "core/Registre.h"

using namespace std;

class Octet : public Registre {
public:
	Octet()
		: Registre(8) {}

	Octet(const string& binaire);

	Octet(uint8_t hex);

	Octet xtime() const;

	Octet operator*(uint8_t r) const;

	Octet operator^(const Octet& r) const;
};

inline Octet::Octet(const string& binaire)
	: Registre(binaire)
{
	if (binaire.size() != 8)
		throw invalid_argument("La chaine doit contenir 8 bits.");
}

inline Octet::Octet(uint8_t hex)
	: Registre(8)
{
	_registre = hex;
}

inline Octet Octet::xtime() const
{
	uint8_t oct = _registre;
	uint8_t bit7 = oct >> 7;
	oct <<= 1;

	if (bit7)
		oct ^= 0x1b;

	return Octet(oct);
}

inline Octet Octet::operator*(uint8_t r) const
{
	Octet result(0);
	Octet temp = *this;

	for (int i = 0; i < 8; ++i)
	{
		if ((r >> i) & 1)
			result = result ^ temp;

		temp = temp.xtime();
	}

	return result;
}

inline Octet Octet::operator^(const Octet& r) const
{
	Octet res;
	res._registre = _registre ^ r._registre;
	return res;
}

#endif // OCTET_H