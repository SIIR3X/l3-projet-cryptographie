#ifndef CBC_H
#define CBC_H

#include "algorithms/modes/Mode.h"
#include "utils/Utils.h"

using namespace std;

class CBC : public Mode {
private:
	static const int BLOCK_SIZE = 16;
	State _iv;
	
public:
	CBC(const Key& key, const State& iv)
		: Mode(key, BLOCK_SIZE) 
	{
		_iv = iv;
	}
	
	CBC(const Key& key)
		: Mode(key, BLOCK_SIZE) 
	{
		_iv = Utils::generateIV(_key.getNbWords() * 4, "1000000110000001", "1101101111011011");
	}

	void Encrypt(const string& plaintext, string& ciphertext) const;

	void Decrypt(const string& ciphertext, string& plaintext) const;

	void EncryptBlock(const State& in, State& out) const override;

	void DecryptBlock(const State& in, State& out) const override;
};

inline void CBC::Encrypt(const string& plaintext, string& ciphertext) const
{
	ciphertext = encrypt(plaintext, _iv);
}

inline void CBC::Decrypt(const string& ciphertext, string& plaintext) const
{
	plaintext = decrypt(ciphertext, _iv);
}

#endif // CBC_H