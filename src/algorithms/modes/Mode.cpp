#include "algorithms/modes/Mode.h"
#include "utils/Utils.h"

string Mode::encrypt(const string& plaintext, const State& out) const
{
	vector<Octet> data = Utils::stringToOctets(plaintext);

	addPadding(data);

	State inputBlock;
	State outputBlock = out;

	vector<State> blocks;

	for (size_t i = 0; i < data.size(); i += _blockSize)
	{
		inputBlock = Utils::octetsToState(data, i);

		EncryptBlock(inputBlock, outputBlock);

		blocks.push_back(outputBlock);
	}

	vector<Octet> octets;

	for (const State& block : blocks)
		Utils::addStateToVector(block, octets);

	string ciphertext;
	for (const Octet& octet : octets) {
		ciphertext.append((string)octet);
	}

	return Utils::base64Encode(ciphertext);
}

string Mode::decrypt(const string& ciphertext, const State& out) const
{
	string ciphertext2 = Utils::base64Decode(ciphertext);

	vector<Octet> data = Utils::stringToOctets(ciphertext2);

	State inputBlock;
	State outputBlock = out;

	vector<State> blocks;

	for (size_t i = 0; i < data.size(); i += _blockSize)
	{
		inputBlock = Utils::octetsToState(data, i);

		DecryptBlock(inputBlock, outputBlock);

		blocks.push_back(outputBlock);

		outputBlock = inputBlock;
	}

	vector<Octet> octets;

	for (const State& block : blocks)
		Utils::addStateToVector(block, octets);

	removePadding(octets);

	string plaintext;
	for (const Octet& octet : octets)
		plaintext.append((string)octet);

	return plaintext;
}