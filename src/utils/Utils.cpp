#include "utils/Utils.h"
#include "algorithms/AES.h"
#include "algorithms/random/LFSR.h"
#include <cctype>
#include <fstream>
#include <sstream>
#include <algorithm>

const string base64_chars = 
			 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			 "abcdefghijklmnopqrstuvwxyz"
			 "0123456789+/";

string Utils::cleanString(const string& str)
{
	string result;
	
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (isalnum(str[i]))
			result += str[i];
	}
	
	return result;
}

vector<Octet> Utils::stringToOctets(const string& str)
{
	return vector<Octet>(str.begin(), str.end());
}

string Utils::hexToRawString(const std::string& hex)
{
	if (hex.length() % 2 != 0)
		throw std::invalid_argument("La taille de la chaîne hexadécimale doit être paire.");

	string result;
	result.reserve(hex.length() / 2);

	for (size_t i = 0; i < hex.length(); i += 2) {
		std::string byteStr = hex.substr(i, 2);
		char byte = static_cast<char>(std::stoul(byteStr, nullptr, 16));
		result.push_back(byte);
	}

	return result;
}

State Utils::octetsToState(const vector<Octet>& octets, int start)
{
	State state;

	for (size_t col = 0; col < AES::NB_COLS; ++col)
	{
		array<Octet, 4> column;

		for(size_t row = 0; row < 4; ++row)
		{
			int index = start + col * 4 + row;
			column[row] = octets[index];
		}

		state.setCol(column, (size_t)col);
	}

	return state;
}

void Utils::addStateToVector(const State& state, vector<Octet>& octets)
{
	for (size_t col = 0; col < AES::NB_COLS; ++col)
	{
		for (size_t row = 0; row < 4; ++row)
			octets.push_back(state[col][row]);
	}
}

State Utils::generateIV(size_t nbOctets, const string& registre, const string& retro)
{
	uint sequenceLegth = nbOctets * 8;

	LFSR lfsr(registre, retro);

	string sequence = lfsr.genererSequence(sequenceLegth);

	vector<Octet> octets = Utils::stringToOctets(sequence);

	State iv = Utils::octetsToState(octets);

	return iv;
}

string Utils::base64Encode(const string& str) {
	string output;

	int val = 0, valb = -6;

	for (uint8_t c : str)
	{
		val = (val << 8) + c;
		valb += 8;

		while (valb >= 0)
		{
			output.push_back(base64_chars[(val >> valb) & 0x3F]);
			valb -= 6;
		}
	}

	if (valb > -6) output.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);

	while (output.size() % 4) output.push_back('=');

	return output;
}

string Utils::base64Decode(const string& str) {
	std::vector<int> T(256, -1);

	for (int i = 0; i < 64; ++i) T[base64_chars[i]] = i;

	std::string ret;

	int val = 0, valb = -8;
	for (unsigned char c : str)
	{
		if (T[c] == -1) break;

		val = (val << 6) + T[c];
		valb += 6;

		if (valb >= 0)
		{
			ret.push_back(char((val >> valb) & 0xFF));
			valb -= 8;
		}
	}
	
	return ret;
}

string Utils::readFile(const string& filename)
{
	ifstream file(filename, ios::binary);

	if (!file.is_open())
		throw runtime_error("Impossible d'ouvrir le fichier: " + filename);

	stringstream buffer;
	buffer << file.rdbuf();

	return buffer.str();
}

void Utils::writeFile(const string& filename, const string& data)
{
	ofstream file(filename, ios::binary);

	if (!file.is_open())
		throw runtime_error("Impossible d'ouvrir le fichier: " + filename);

	file << data;
}