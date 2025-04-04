#ifndef CMAC_H
#define CMAC_H

#include "algorithms/modes/Mode.h"

using namespace std;

class CMAC : public Mode {
private:
	static const int BLOCK_SIZE = 16;
	const Octet C_MAC = Octet(0x87);
	State _key1;
	State _key2;

	void GenerateSubKey(State& key);

	void GenerateSubKey1();

	void GenerateSubKey2();

	void GenerateSubKeys();

public:
	CMAC(const Key& key)
		: Mode(key, BLOCK_SIZE), _key1(Mode::_key.getNbWords()), _key2(Mode::_key.getNbWords())
	{
		GenerateSubKeys();
	}

	const State& getKey1() const { return _key1; }

	const State& getKey2() const { return _key2; }

	void addPadding(vector<Octet>& data) const;

	void EncryptBlock(const State& in, State& out) const override;

	void DecryptBlock(const State& in, State& out) const override;

	string GenerateMAC(const string& plaintext);
};

inline void CMAC::addPadding(vector<Octet>& data) const
{
	size_t paddingSize = _blockSize - data.size() % _blockSize;

	data.push_back(Octet(1));

	for (size_t i = 1; i < paddingSize; ++i)
    {
        data.push_back(Octet(0));
    }
}

inline void CMAC::GenerateSubKey(State& key)
{
	key <<= C_MAC;
}

inline void CMAC::GenerateSubKey1()
{
	State B0(Mode::_key.getNbWords());

	AES::Cipher(B0, _key1, _words);

	GenerateSubKey(_key1);
}

inline void CMAC::GenerateSubKey2()
{
	_key2 = _key1;

	GenerateSubKey(_key2);
}

inline void CMAC::GenerateSubKeys()
{
	GenerateSubKey1();
	GenerateSubKey2();
}

#endif // CMAC_H