#include "core/Octet.h"
#include <gtest/gtest.h>

TEST(Octet, ConstructeurString) {
	// Arrange
	string binaire = "10101010";

	// Act
	Octet o(binaire);

	// Assert
	EXPECT_EQ(o.getSize(), (size_t)8);
	EXPECT_EQ(o.get(0), (uint)0);
	EXPECT_EQ(o.get(1), (uint)1);
	EXPECT_EQ(o.get(2), (uint)0);
	EXPECT_EQ(o.get(3), (uint)1);
	EXPECT_EQ(o.get(4), (uint)0);
	EXPECT_EQ(o.get(5), (uint)1);
	EXPECT_EQ(o.get(6), (uint)0);
	EXPECT_EQ(o.get(7), (uint)1);
}

TEST(Octet, ConstructeurHex) {
	// Arrange
	uint8_t hex = 0xAA;

	// Act
	Octet o(hex);

	// Assert
	EXPECT_EQ(o.getSize(), (size_t)8);
	EXPECT_EQ(o.get(0), (uint)0);
	EXPECT_EQ(o.get(1), (uint)1);
	EXPECT_EQ(o.get(2), (uint)0);
	EXPECT_EQ(o.get(3), (uint)1);
	EXPECT_EQ(o.get(4), (uint)0);
	EXPECT_EQ(o.get(5), (uint)1);
	EXPECT_EQ(o.get(6), (uint)0);
	EXPECT_EQ(o.get(7), (uint)1);
}

TEST(Octet, XTime) {
	// Arrange
	Octet o("10101010");

	// Act
	Octet o2 = o.xtime();

	// Assert
	EXPECT_EQ(o2.get(0), (uint)1);
	EXPECT_EQ(o2.get(1), (uint)1);
	EXPECT_EQ(o2.get(2), (uint)1);
	EXPECT_EQ(o2.get(3), (uint)1);
	EXPECT_EQ(o2.get(4), (uint)0);
	EXPECT_EQ(o2.get(5), (uint)0);
	EXPECT_EQ(o2.get(6), (uint)1);
	EXPECT_EQ(o2.get(7), (uint)0);
}

TEST(Octet, OperatorMult) {
	// Arrange
	Octet o("10101010");

	// Act
	Octet o2 = o * 0x0E;

	// Assert
	EXPECT_EQ(o2.get(0), (uint)0);
	EXPECT_EQ(o2.get(1), (uint)1);
	EXPECT_EQ(o2.get(2), (uint)1);
	EXPECT_EQ(o2.get(3), (uint)0);
	EXPECT_EQ(o2.get(4), (uint)1);
	EXPECT_EQ(o2.get(5), (uint)1);
	EXPECT_EQ(o2.get(6), (uint)1);
	EXPECT_EQ(o2.get(7), (uint)1);
}

TEST(Octet, OperatorXor) {
	// Arrange
	Octet o1("10101010");
	Octet o2("11001100");

	// Act
	Octet o3 = o1 ^ o2;

	// Assert
	EXPECT_EQ(o3.get(0), (uint)0);
	EXPECT_EQ(o3.get(1), (uint)1);
	EXPECT_EQ(o3.get(2), (uint)1);
	EXPECT_EQ(o3.get(3), (uint)0);
	EXPECT_EQ(o3.get(4), (uint)0);
	EXPECT_EQ(o3.get(5), (uint)1);
	EXPECT_EQ(o3.get(6), (uint)1);
	EXPECT_EQ(o3.get(7), (uint)0);
}