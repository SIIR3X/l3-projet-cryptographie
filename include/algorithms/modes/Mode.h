#ifndef MODE_H
#define MODE_H

#include <string>
#include "core/Key.h"
#include "core/Word.h"
#include "core/State.h"
#include "core/Octet.h"
#include "algorithms/AES.h"

using namespace std;

class Mode {
protected:
	Key _key;
	int _blockSize;
	vector<Word> _words;

	string encrypt(const string& plaintext, const State& out) const;

	string decrypt(const string& ciphertext, const State& out) const;

	void addPadding(vector<Octet>& data) const;

	void removePadding(vector<Octet>& data) const;

public:
	Mode(const Key& key, int blockSize) 
		: _key(key), _blockSize(blockSize)
	{
		AES::KeyExpansion(_key, _words);
	}

	virtual ~Mode() = default;

	virtual void EncryptBlock(const State& in, State& out) const = 0;

	virtual void DecryptBlock(const State& in, State& out) const = 0;
};

inline void Mode::addPadding(vector<Octet>& data) const
{
	size_t paddingSize = _blockSize - data.size() % _blockSize;

	data.insert(data.end(), paddingSize, Octet(paddingSize));
}

inline void Mode::removePadding(vector<Octet>& data) const
{
	uint8_t paddingSize = data.back().get();

	if (paddingSize > 0 && paddingSize <= _blockSize)
		data.resize(data.size() - paddingSize);
}

#endif // MODE_H