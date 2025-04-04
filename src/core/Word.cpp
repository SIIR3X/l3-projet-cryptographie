#include "core/Word.h"
#include "utils/Utils.h"
#include <vector>

Word::Word(const string& hex)
{
	string cleanedHex = Utils::cleanString(hex);

	if (cleanedHex.size() % 2 != 0)
		throw invalid_argument("Nombre impair de caractères hexadécimaux");

	vector<Octet> octets;

	for (size_t i = 0; i < cleanedHex.size(); i += 2)
		octets.push_back(Octet(stoi(cleanedHex.substr(i, 2), nullptr, 16)));

	if (octets.size() != 4)
		throw invalid_argument("Nombre de caractères hexadécimaux différent de 8");

	for (size_t i = 0; i < 4; ++i)
		_octets[i] = octets[i];
}