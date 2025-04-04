#include "algorithms/modes/CMAC.h"
#include "utils/Utils.h"

string CMAC::GenerateMAC(const string& plaintext) {
	vector<Octet> initial = Utils::stringToOctets(plaintext);
	vector<Octet> data = initial;

	State inputBlock;
	State outputBlock;

	bool needPad = (data.size() % _blockSize != 0);

	if (needPad) {
		addPadding(data);
	}
	
	size_t i;
	for (i = 0; i < data.size() - _blockSize; i += _blockSize) {
		inputBlock = Utils::octetsToState(data, i);

		EncryptBlock(inputBlock, outputBlock);
	}
	inputBlock = Utils::octetsToState(data, i);

	if (data == initial) {
		outputBlock ^= _key1;
	}
	else {
		outputBlock ^= _key2;
	}
	string mac;
	EncryptBlock(inputBlock, outputBlock); 
	vector<Octet> octets;
	Utils::addStateToVector(outputBlock, octets);

	for (const Octet& octet : octets) {
		mac.append((string)octet);
	}

	return Utils::base64Encode(mac);
}

void CMAC::EncryptBlock(const State& in, State& out) const
{
	State state;

	state = in;

	state ^= out;

	AES::Cipher(state, out, _words);
}

void CMAC::DecryptBlock(const State& in, State& out) const
{
	State state;

	state = in;

	State xorBlock = out;

	AES::InvCipher(state, out, _words);

	out ^= xorBlock;
}