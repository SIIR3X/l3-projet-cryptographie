#ifndef LFSR_H
#define LFSR_H

#include "core/Registre.h"

class LFSR {
private:
	Registre _registre;
	Registre _retro;

	uint getBitSortie();

	uint getValeurRetroaction();

	void rotLeft();

public:
	LFSR(const string& registre, const string& retro)
		: _registre(registre), _retro(retro) 
	{
		if (registre.size() != retro.size())
			throw invalid_argument("Les registres doivent avoir la meme taille.");
	}

	string genererSequence(uint length);
};

inline uint LFSR::getBitSortie()
{
	return _registre.get(0);
}

inline uint LFSR::getValeurRetroaction()
{
	uint bit = 0;

	for (size_t i = 0; i < _retro.getSize(); ++i)
	{
		if (_retro.get(i) == 1)
			bit ^= _registre.get(i);
	}

	return bit;
}

inline void LFSR::rotLeft()
{
	uint bit = getValeurRetroaction();

	_registre >>= 1;

	_registre.set(0, bit);
}

inline string LFSR::genererSequence(uint length)
{
	string str = "";

	for (uint i = 0; i < length; ++i)
	{
		str += to_string(getBitSortie());
		rotLeft();
	}

	return str;
}

#endif // LFSR_H