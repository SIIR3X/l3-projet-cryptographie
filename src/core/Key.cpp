#include "core/Key.h"
#include "utils/Utils.h"

Key::Key(const string& hex)
{
	string cleanedHex = Utils::cleanString(hex);

	if (cleanedHex.size() % 2 != 0)
		throw invalid_argument("Nombre impair de caractères hexadécimaux");

	_nbWords = cleanedHex.size() / 8;
	_nbRounds = _nbWords + 6;

	for (size_t i = 0; i < cleanedHex.size(); i += 8)
		_words.push_back(Word(cleanedHex.substr(i, 8)));
}