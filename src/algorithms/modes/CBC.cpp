#include "algorithms/modes/CBC.h"
#include "algorithms/AES.h"

void CBC::EncryptBlock(const State& in, State& out) const
{
	State state;

	state = in;

	state ^= out;

	AES::Cipher(state, out, _words);
}

void CBC::DecryptBlock(const State& in, State& out) const
{
	State state;

	state = in;

	State xorBlock = out;

	AES::InvCipher(state, out, _words);

	out ^= xorBlock;
}