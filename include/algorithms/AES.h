#ifndef AES_H
#define AES_H

#include <vector>
#include "core/Key.h"
#include "core/Word.h"
#include "core/State.h"
#include "types/Types.h"

using namespace std;

class AES {
private:
	static Octet SubByte(const Octet& byte);

	static Octet InvSubByte(const Octet& byte);

	static void SubWord(Word& w);

public:
	static const int NB_COLS = 4;

	AES() = delete;

	static void KeyExpansion(const Key& key, vector<Word>& w);

	static void Cipher(const State& in, State& out, const vector<Word>& w);

	static void InvCipher(const State& in, State& out, const vector<Word>& w);

	static void AddRoundKey(State& state, Word w[NB_COLS]);

	static void SubBytes(State& state);

	static void ShiftRows(State& state);

	static void MixColumns(State& state);

	static void InvSubBytes(State& state);

	static void InvShiftRows(State& state);

	static void InvMixColumns(State& state);
};

inline Octet AES::SubByte(const Octet& byte)
{
	return Octet(SBox[byte.getLeft() * 16 + byte.getRight()]);
}

inline Octet AES::InvSubByte(const Octet& byte)
{
	return Octet(InvSBox[byte.getLeft() * 16 + byte.getRight()]);
}

inline void AES::SubWord(Word& w)
{
	for (int i = 0; i < 4; i++)
		w.setOctet(i, SubByte(w[i]));
}

inline void AES::AddRoundKey(State& state, Word w[AES::NB_COLS]) 
{
	for (int i = 0; i < 4; i++)
		state.xorColumn(i, w[i]);
}

inline void AES::SubBytes(State& state)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			state.setOctet(i, j, SubByte(state[i][j]));
	}
}

inline void AES::ShiftRows(State& state)
{
	state <<= [](size_t row) { return row; };
}

inline void AES::MixColumns(State& state)
{
	for (int i = 0; i < 4; i++)
	{
		array<Octet, 4> colonne = state[i];
		Octet c0 = colonne[0];
		Octet c1 = colonne[1];
		Octet c2 = colonne[2];
		Octet c3 = colonne[3];

		colonne[0] = c0.xtime() ^ c1.xtime() ^ c1 ^ c2 ^ c3;
		colonne[1] = c0 ^ c1.xtime() ^ c2.xtime() ^ c2 ^ c3;
		colonne[2] = c0 ^ c1 ^ c2.xtime() ^ c3.xtime() ^ c3;
		colonne[3] = c0.xtime() ^ c0 ^ c1 ^ c2 ^ c3.xtime();

		state.setCol(colonne, i);
	}
}

inline void AES::InvSubBytes(State& state)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			state.setOctet(i, j, InvSubByte(state[i][j]));
	}
}

inline void AES::InvShiftRows(State& state)
{
	state >>= [](size_t row) { return row; };
}

inline void AES::InvMixColumns(State& state)
{
	for (int i = 0; i < 4; i++)
	{
		array<Octet, 4> colonne = state[i];
		Octet c0 = colonne[0];
		Octet c1 = colonne[1];
		Octet c2 = colonne[2];
		Octet c3 = colonne[3];

		colonne[0] = (c0 * 0x0e) ^ (c1 * 0x0b) ^ (c2 * 0x0d) ^ (c3 * 0x09);
		colonne[1] = (c0 * 0x09) ^ (c1 * 0x0e) ^ (c2 * 0x0b) ^ (c3 * 0x0d);
		colonne[2] = (c0 * 0x0d) ^ (c1 * 0x09) ^ (c2 * 0x0e) ^ (c3 * 0x0b);
		colonne[3] = (c0 * 0x0b) ^ (c1 * 0x0d) ^ (c2 * 0x09) ^ (c3 * 0x0e);

		state.setCol(colonne, i);
	}
}

#endif // AES_H