#include "core/Key.h"
#include "core/Word.h"
#include <gtest/gtest.h>

TEST(Key, ConstructeurString) {
	// Arrange
	string hex = "2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c";

	// Act
	Key key(hex);

	// Assert
	EXPECT_EQ(key.getNbWords(), (size_t)4);
	EXPECT_EQ(key.getNbRounds(), (size_t)10);
	EXPECT_EQ(key[0], Word("2b7e1516"));
	EXPECT_EQ(key[1], Word("28aed2a6"));
	EXPECT_EQ(key[2], Word("abf71588"));
	EXPECT_EQ(key[3], Word("09cf4f3c"));
}