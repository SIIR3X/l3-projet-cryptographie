#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "core/Octet.h"
#include "core/State.h"

using namespace std;

class Utils {
public:
	static string cleanString(const string& str);

	static vector<Octet> stringToOctets(const string& str);

	static string hexToRawString(const std::string& hex);
	
	static State octetsToState(const vector<Octet>& octets, int start = 0);

	static void addStateToVector(const State& state, vector<Octet>& octets);

	static State generateIV(size_t nbOctets, const string& registre, const string& retro);

	static string base64Encode(const string& str);

	static string base64Decode(const string& str);

	static string readFile(const string& filename);

	static void writeFile(const string& filename, const string& data);
};

#endif // UTILS_H