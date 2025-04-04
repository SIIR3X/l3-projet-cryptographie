#include "algorithms/modes/ECB.h"
#include <gtest/gtest.h>

TEST(ECB, EncryptBlock) {
	// Arrange
	Key key("2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c");
	State in("6b c1 be e2 2e 40 9f 96 e9 3d 7e 11 73 93 17 2a");
	State out;
	ECB ecb(key);

	// Act
	ecb.EncryptBlock(in, out);

	// Assert
	string expected = "3a d7 7b b4 0d 7a 36 60 a8 9e ca f3 24 66 ef 97";
	State expectedState(expected);
	EXPECT_EQ(out, expectedState);
}

TEST(ECB, DecryptBlock) {
	// Arrange
	Key key("2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c");
	State in("3a d7 7b b4 0d 7a 36 60 a8 9e ca f3 24 66 ef 97");
	State out;
	ECB ecb(key);

	// Act
	ecb.DecryptBlock(in, out);

	// Assert
	string expected = "6b c1 be e2 2e 40 9f 96 e9 3d 7e 11 73 93 17 2a";
	State expectedState(expected);
	EXPECT_EQ(out, expectedState);
}

TEST(ECB, EncryptAndDecrypt) {
	// Arrange
	string plaintext = "Hello World! Hello World!";
	Key key("2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c");
	ECB ecb(key);
	string ciphertext;
	string decrypted;

	// Act
	ecb.Encrypt(plaintext, ciphertext);
	ecb.Decrypt(ciphertext, decrypted);

	// Assert
	EXPECT_EQ(plaintext, decrypted);
}