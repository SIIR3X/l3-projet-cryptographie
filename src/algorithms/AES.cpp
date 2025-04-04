#include "algorithms/AES.h"

void AES::KeyExpansion(const Key& key, vector<Word>& w) {
	size_t nbWords = key.getNbWords();
	size_t nbRounds = key.getNbRounds();

	w.resize(NB_COLS * (nbRounds + 1));
	Word temp;
	size_t i = 0;

	while (i < nbWords) {
		w[i] = key[i];
		i++;
	}

	while (i < NB_COLS * (nbRounds + 1)) {
		temp = w[i - 1];

		if (i % nbWords == 0) {
			temp <<= 1;
			SubWord(temp);
			temp ^= Rcon[(i / nbWords) - 1];
		} 
		else if (nbWords > 6 && i % nbWords == 4) {
			SubWord(temp);
		}

		w[i] = w[i - nbWords] ^ temp;
		i++;
	}
}

void AES::Cipher(const State& in, State& out, const vector<Word>& w)
{
	size_t nbWords = w.size() / NB_COLS - 1;

	State state;

	state = in;

	AddRoundKey(state, (Word*)&w[0]);

	for (size_t round = 1; round < nbWords; ++round) {
		SubBytes(state);
		ShiftRows(state);
		MixColumns(state);
		AddRoundKey(state, (Word*)&w[round * NB_COLS]);
	}

	SubBytes(state);
	ShiftRows(state);
	AddRoundKey(state, (Word*)&w[nbWords * NB_COLS]);

	out = state;
}

void AES::InvCipher(const State& in, State& out, const vector<Word>& w)
{
	size_t nbWords = w.size() / NB_COLS - 1;

	State state;

	state = in;

	AddRoundKey(state, (Word*)&w[nbWords * NB_COLS]);

	for (size_t round = nbWords - 1; round > 0; --round) {
		InvShiftRows(state);
		InvSubBytes(state);
		AddRoundKey(state, (Word*)&w[round * NB_COLS]);
		InvMixColumns(state);
	}

	InvShiftRows(state);
	InvSubBytes(state);
	AddRoundKey(state, (Word*)&w[0]);

	out = state;
}