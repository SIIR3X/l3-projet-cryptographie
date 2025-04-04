#include "core/Word.h"
#include <gtest/gtest.h>

TEST(Word, ConstructeurString) {
	// Arrange
	string hex = "2b 28 ab 09";

	// Act
	Word w(hex);

	// Assert
	EXPECT_EQ(w[0], Octet(0x2b));
	EXPECT_EQ(w[1], Octet(0x28));
	EXPECT_EQ(w[2], Octet(0xab));
	EXPECT_EQ(w[3], Octet(0x09));
}

TEST(Word, SetOctet) {
	// Arrange
	Word w("2b 28 ab 09");

	// Act
	w.setOctet(0, Octet(0x00));
	w.setOctet(1, Octet(0x00));
	w.setOctet(2, Octet(0x00));
	w.setOctet(3, Octet(0x00));

	// Assert
	EXPECT_EQ(w[0], Octet(0x00));
	EXPECT_EQ(w[1], Octet(0x00));
	EXPECT_EQ(w[2], Octet(0x00));
	EXPECT_EQ(w[3], Octet(0x00));
}

TEST(Word, Xor) {
	// Arrange
	Word w1("2b 28 ab 09");
	Word w2("7e 76 3d 3e");

	// Act
	Word w3 = w1 ^ w2;

	// Assert
	EXPECT_EQ(w3[0], Octet(0x55));
	EXPECT_EQ(w3[1], Octet(0x5e));
	EXPECT_EQ(w3[2], Octet(0x96));
	EXPECT_EQ(w3[3], Octet(0x37));
}

TEST(Word, XorEquals) {
	// Arrange
	Word w1("2b 28 ab 09");
	Word w2("7e 76 3d 3e");

	// Act
	w1 ^= w2;

	// Assert
	EXPECT_EQ(w1[0], Octet(0x55));
	EXPECT_EQ(w1[1], Octet(0x5e));
	EXPECT_EQ(w1[2], Octet(0x96));
	EXPECT_EQ(w1[3], Octet(0x37));
}

TEST(Word, ShiftLEquals) {
	// Arrange
	Word w("2b 28 ab 09");

	// Act
	w <<= 1;

	// Assert
	EXPECT_EQ(w[0], Octet(0x28));
	EXPECT_EQ(w[1], Octet(0xab));
	EXPECT_EQ(w[2], Octet(0x09));
	EXPECT_EQ(w[3], Octet(0x2b));
}

TEST(Word, EqualsEquals) {
	// Arrange
	Word w1("2b 28 ab 09");
	Word w2("2b 28 ab 09");

	// Act
	bool result = w1 == w2;

	// Assert
	EXPECT_TRUE(result);
}