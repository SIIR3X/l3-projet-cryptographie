#include "algorithms/modes/CBC.h"
#include <gtest/gtest.h>

TEST(CBC, EncryptBlock) {
	// Arrange
	Key key("2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c");
	State iv("00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f");
	State in("6b c1 be e2 2e 40 9f 96 e9 3d 7e 11 73 93 17 2a");
	State out = iv;
	CBC cbc(key, iv);

	// Act
	cbc.EncryptBlock(in, out);

	// Assert
	string expected = "76 49 ab ac 81 19 b2 46 ce e9 8e 9b 12 e9 19 7d";
	State expectedState(expected);
	EXPECT_EQ(out, expectedState);
}

TEST(CBC, DecryptBlock) {
	// Arrange
	Key key("2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c");
	State iv("00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f");
	State in("76 49 ab ac 81 19 b2 46 ce e9 8e 9b 12 e9 19 7d");
	State out = iv;
	CBC cbc(key, iv);

	// Act
	cbc.DecryptBlock(in, out);

	// Assert
	string expected = "6b c1 be e2 2e 40 9f 96 e9 3d 7e 11 73 93 17 2a";
	State expectedState(expected);
	EXPECT_EQ(out, expectedState);
}

TEST(CBC, EncryptAndDecrypt) {
	// Arrange
	string plaintext = "Hello World! Hello World!";
	Key key("2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c");
	State iv("00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f");
	CBC cbc(key, iv);
	string ciphertext;
	string decrypted;

	// Act
	cbc.Encrypt(plaintext, ciphertext);
	cbc.Decrypt(ciphertext, decrypted);

	// Assert
	EXPECT_EQ(plaintext, decrypted);
}