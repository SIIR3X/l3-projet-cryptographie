#include "core/State.h"
#include "utils/Utils.h"
#include <stdexcept>

State::State(const string& hex)
{
	string cleanedHex = Utils::cleanString(hex);

	if (cleanedHex.size() % 2 != 0)
		throw invalid_argument("Nombre impair de caractères hexadécimaux");

	vector<Octet> octets;

	for (size_t i = 0; i < cleanedHex.size(); i += 2)
		octets.push_back(Octet(stoi(cleanedHex.substr(i, 2), nullptr, 16)));

	if (octets.size() % 4 != 0)
		throw invalid_argument("Nombre de caractères hexadécimaux non multiple de 4");

	_nbColumn = octets.size() / 4;
	_state.resize(_nbColumn);

	for (size_t col = 0; col < _nbColumn; ++col) 
	{
		for (size_t row = 0; row < 4; ++row)
			_state[col][row] = octets[col * 4 + row];
	}
}