#include "algorithms/modes/CMAC.h"
#include "utils/Utils.h"
#include <gtest/gtest.h>

TEST(CMACTest, GenerateSubKeys)
{
	// Arrange
	Key key("2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c");

	// Act
	CMAC cmac(key);

	// Assert
	State expectedKey1("fb ee d6 18 35 71 33 66 7c 85 e0 8f 72 36 a8 de");
	State expectedKey2("f7 dd ac 30 6a e2 66 cc f9 0b c1 1e e4 6d 51 3b");
	EXPECT_EQ(cmac.getKey1(), expectedKey1);
	EXPECT_EQ(cmac.getKey2(), expectedKey2);
}

TEST(CMACTest, GenerateMAC)
{
	// Arrange
	Key key("2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c");
	CMAC cmac(key);

	// Act
	string hexInput = "6bc1bee22e409f96e93d7e117393172a";
	string tagBase64 = cmac.GenerateMAC(Utils::hexToRawString(hexInput));

	// Assert
	string expected = "BwoWtGtNQUT3m92d0EoofA==";
	EXPECT_EQ(tagBase64, expected);
}