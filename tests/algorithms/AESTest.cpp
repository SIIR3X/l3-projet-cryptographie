#include "algorithms/AES.h"
#include <gtest/gtest.h>

TEST(AES, KeyExpansion) {
	// Arrange
	string hex = "2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c";
	Key key(hex);
	vector<Word> w;

	// Act
	AES::KeyExpansion(key, w);

	// Assert
	Word firstWord1("2b 7e 15 16");
	Word firstWord2("28 ae d2 a6");
	Word firstWord3("ab f7 15 88");
	Word firstWord4("09 cf 4f 3c");

	Word lastWord1("d0 14 f9 a8");
	Word lastWord2("c9 ee 25 89");
	Word lastWord3("e1 3f 0c c8");
	Word lastWord4("b6 63 0c a6");

	EXPECT_EQ(w[0], firstWord1);
	EXPECT_EQ(w[1], firstWord2);
	EXPECT_EQ(w[2], firstWord3);
	EXPECT_EQ(w[3], firstWord4);

	EXPECT_EQ(w[4 * (10 + 1) - 4], lastWord1);
	EXPECT_EQ(w[4 * (10 + 1) - 3], lastWord2);
	EXPECT_EQ(w[4 * (10 + 1) - 2], lastWord3);
	EXPECT_EQ(w[4 * (10 + 1) - 1], lastWord4);
}

TEST(AES, Cipher) {
	// Arrange
	string hex = "32 43 f6 a8 88 5a 30 8d 31 31 98 a2 e0 37 07 34";
	State in(hex);
	vector<Word> w;
	AES::KeyExpansion(Key("2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c"), w);

	// Act
	State out;
	AES::Cipher(in, out, w);

	// Assert
	string expected = "39 25 84 1d 02 dc 09 fb dc 11 85 97 19 6a 0b 32";
	State expectedState(expected);
	EXPECT_EQ(out, expectedState);
}

TEST(AES, InvCipher) {
	// Arrange
	string hex = "39 25 84 1d 02 dc 09 fb dc 11 85 97 19 6a 0b 32";
	State in(hex);
	vector<Word> w;
	AES::KeyExpansion(Key("2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c"), w);

	// Act
	State out;
	AES::InvCipher(in, out, w);

	// Assert
	string expected = "32 43 f6 a8 88 5a 30 8d 31 31 98 a2 e0 37 07 34";
	State expectedState(expected);
	EXPECT_EQ(out, expectedState);
}

TEST(AES, AddRoundKey) {
	// Arrange
	string hex = "32 43 f6 a8 88 5a 30 8d 31 31 98 a2 e0 37 07 34";
	State state(hex);
	Word w[4] = { Word("2b7e1516"), Word("28aed2a6"), Word("abf71588"), Word("09cf4f3c") };

	// Act
	AES::AddRoundKey(state, w);

	// Assert
	string expected = "19 3d e3 be a0 f4 e2 2b 9a c6 8d 2a e9 f8 48 08";
	State expectedState(expected);
	EXPECT_EQ(state, expectedState);
}

TEST(AES, SubBytes) {
	// Arrange
	string hex = "19 3d e3 be a0 f4 e2 2b 9a c6 8d 2a e9 f8 48 08";
	State state(hex);

	// Act
	AES::SubBytes(state);

	// Assert
	string expected = "d4 27 11 ae e0 bf 98 f1 b8 b4 5d e5 1e 41 52 30";
	State expectedState(expected);
	EXPECT_EQ(state, expectedState);
}

TEST(AES, ShiftRows) {
	// Arrange
	string hex = "d4 27 11 ae e0 bf 98 f1 b8 b4 5d e5 1e 41 52 30";
	State state(hex);

	// Act
	AES::ShiftRows(state);

	// Assert
	string expected = "d4 bf 5d 30 e0 b4 52 ae b8 41 11 f1 1e 27 98 e5";
	State expectedState(expected);
	EXPECT_EQ(state, expectedState);
}

TEST(AES, MixColumns) {
	// Arrange
	string hex = "d4 bf 5d 30 e0 b4 52 ae b8 41 11 f1 1e 27 98 e5";
	State state(hex);

	// Act
	AES::MixColumns(state);

	// Assert
	string expected = "04 66 81 e5 e0 cb 19 9a 48 f8 d3 7a 28 06 26 4c";
	State expectedState(expected);
	EXPECT_EQ(state, expectedState);
}

TEST(AES, InvSubBytes) {
	// Arrange
	string hex = "d4 27 11 ae e0 bf 98 f1 b8 b4 5d e5 1e 41 52 30";
	State state(hex);

	// Act
	AES::InvSubBytes(state);

	// Assert
	string expected = "19 3d e3 be a0 f4 e2 2b 9a c6 8d 2a e9 f8 48 08";
	State expectedState(expected);
	EXPECT_EQ(state, expectedState);
}

TEST(AES, InvShiftRows) {
	// Arrange
	string hex = "d4 bf 5d 30 e0 b4 52 ae b8 41 11 f1 1e 27 98 e5";
	State state(hex);

	// Act
	AES::InvShiftRows(state);

	// Assert
	string expected = "d4 27 11 ae e0 bf 98 f1 b8 b4 5d e5 1e 41 52 30";
	State expectedState(expected);
	EXPECT_EQ(state, expectedState);
}

TEST(AES, InvMixColumns) {
	// Arrange
	string hex = "04 66 81 e5 e0 cb 19 9a 48 f8 d3 7a 28 06 26 4c";
	State state(hex);

	// Act
	AES::InvMixColumns(state);

	// Assert
	string expected = "d4 bf 5d 30 e0 b4 52 ae b8 41 11 f1 1e 27 98 e5";
	State expectedState(expected);
	EXPECT_EQ(state, expectedState);
}