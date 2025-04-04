#ifndef ECB_H
#define ECB_H

#include "algorithms/modes/Mode.h"

using namespace std;

class ECB : public Mode {
private:
	static const int BLOCK_SIZE = 16;

public:
	ECB(const Key& key)
		: Mode(key, BLOCK_SIZE) {}

	void Encrypt(const string& plaintext, string& ciphertext) const;

	void Decrypt(const string& ciphertext, string& plaintext) const;

	void EncryptBlock(const State& in, State& out) const override;

	void DecryptBlock(const State& in, State& out) const override;
};

inline void ECB::Encrypt(const string& plaintext, string& ciphertext) const
{
	ciphertext = encrypt(plaintext, State());
}

inline void ECB::Decrypt(const string& ciphertext, string& plaintext) const
{
	plaintext = decrypt(ciphertext, State());
}

#endif // ECB_H