#include "algorithms/modes/ECB.h"
#include "algorithms/AES.h"

void ECB::EncryptBlock(const State& in, State& out) const
{
	State state = in;

	AES::Cipher(state, out, _words);
}

void ECB::DecryptBlock(const State& in, State& out) const
{
	State state = in;
	
	AES::InvCipher(in, out, _words);
}