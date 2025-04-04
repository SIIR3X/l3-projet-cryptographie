#include "core/Registre.h"

Registre::Registre(const string& binaire)
{
	_size = binaire.size();
	_registre = 0;

	for (char c : binaire)
	{
		if (c != '0' && c != '1')
			throw invalid_argument("Chaîne binaire invalide.");

		_registre <<= 1;
		_registre |= (c - '0');
	}
}