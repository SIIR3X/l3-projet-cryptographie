#include "core/Registre.h"
#include <gtest/gtest.h>

TEST(Registre, Constructeur) {
	// Arrange
	size_t size = 4;

	// Act
	Registre r(size);

	// Assert
	EXPECT_EQ(r.getSize(), size);
	EXPECT_EQ(r.get(), (uint)0);
}

TEST(Registre, ConstructeurString) {
	// Arrange
	string binaire = "1010";

	// Act
	Registre r(binaire);

	// Assert
	EXPECT_EQ(r.getSize(), (size_t)4);
	EXPECT_EQ(r.get(0), (uint)0);
	EXPECT_EQ(r.get(1), (uint)1);
	EXPECT_EQ(r.get(2), (uint)0);
	EXPECT_EQ(r.get(3), (uint)1);
}

TEST(Registre, GetLeft) {
	// Arrange
	Registre r("1010");

	// Act
	uint left = r.getLeft();

	// Assert
	EXPECT_EQ(left, (uint)2);
}

TEST(Registre, GetRight) {
	// Arrange
	Registre r("1010");

	// Act
	uint right = r.getRight();

	// Assert
	EXPECT_EQ(right, (uint)2);
}

TEST(Registre, OperatorAnd) {
	// Arrange
	Registre r1("1010");
	Registre r2("1100");

	// Act
	Registre r3 = r1 & r2;

	// Assert
	EXPECT_EQ(r3.getSize(), (size_t)4);
	EXPECT_EQ(r3.get(0), (uint)0);
	EXPECT_EQ(r3.get(1), (uint)0);
	EXPECT_EQ(r3.get(2), (uint)0);
	EXPECT_EQ(r3.get(3), (uint)1);
}

TEST(Registre, OperatorAndEquals) {
	// Arrange
	Registre r1("1010");
	Registre r2("1100");

	// Act
	r1 &= r2;

	// Assert
	EXPECT_EQ(r1.getSize(), (size_t)4);
	EXPECT_EQ(r1.get(0), (uint)0);
	EXPECT_EQ(r1.get(1), (uint)0);
	EXPECT_EQ(r1.get(2), (uint)0);
	EXPECT_EQ(r1.get(3), (uint)1);
}

TEST(Registre, OperatorOr) {
	// Arrange
	Registre r1("1010");
	Registre r2("1100");

	// Act
	Registre r3 = r1 | r2;

	// Assert
	EXPECT_EQ(r3.getSize(), (size_t)4);
	EXPECT_EQ(r3.get(0), (uint)0);
	EXPECT_EQ(r3.get(1), (uint)1);
	EXPECT_EQ(r3.get(2), (uint)1);
	EXPECT_EQ(r3.get(3), (uint)1);
}

TEST(Registre, OperatorOrEquals) {
	// Arrange
	Registre r1("1010");
	Registre r2("1100");

	// Act
	r1 |= r2;

	// Assert
	EXPECT_EQ(r1.getSize(), (size_t)4);
	EXPECT_EQ(r1.get(0), (uint)0);
	EXPECT_EQ(r1.get(1), (uint)1);
	EXPECT_EQ(r1.get(2), (uint)1);
	EXPECT_EQ(r1.get(3), (uint)1);
}

TEST(Registre, OperatorXor) {
	// Arrange
	Registre r1("1010");
	Registre r2("1100");

	// Act
	Registre r3 = r1 ^ r2;

	// Assert
	EXPECT_EQ(r3.getSize(), (size_t)4);
	EXPECT_EQ(r3.get(0), (uint)0);
	EXPECT_EQ(r3.get(1), (uint)1);
	EXPECT_EQ(r3.get(2), (uint)1);
	EXPECT_EQ(r3.get(3), (uint)0);
}

TEST(Registre, OperatorXorEquals) {
	// Arrange
	Registre r1("1010");
	Registre r2("1100");

	// Act
	r1 ^= r2;

	// Assert
	EXPECT_EQ(r1.getSize(), (size_t)4);
	EXPECT_EQ(r1.get(0), (uint)0);
	EXPECT_EQ(r1.get(1), (uint)1);
	EXPECT_EQ(r1.get(2), (uint)1);
	EXPECT_EQ(r1.get(3), (uint)0);
}

TEST(Registre, OperatorShiftL) {
	// Arrange
	Registre r("1010");

	// Act
	Registre r2 = r << 1;

	// Assert
	EXPECT_EQ(r2.getSize(), (size_t)4);
	EXPECT_EQ(r2.get(0), (uint)0);
	EXPECT_EQ(r2.get(1), (uint)0);
	EXPECT_EQ(r2.get(2), (uint)1);
	EXPECT_EQ(r2.get(3), (uint)0);
}

TEST(Registre, OperatorShiftR) {
	// Arrange
	Registre r("1010");

	// Act
	Registre r2 = r >> 1;

	// Assert
	EXPECT_EQ(r2.getSize(), (size_t)4);
	EXPECT_EQ(r2.get(0), (uint)1);
	EXPECT_EQ(r2.get(1), (uint)0);
	EXPECT_EQ(r2.get(2), (uint)1);
	EXPECT_EQ(r2.get(3), (uint)0);
}

TEST(Registre, OperatorShiftLEquals) {
	// Arrange
	Registre r("1010");

	// Act
	r <<= 1;

	// Assert
	EXPECT_EQ(r.getSize(), (size_t)4);
	EXPECT_EQ(r.get(0), (uint)0);
	EXPECT_EQ(r.get(1), (uint)0);
	EXPECT_EQ(r.get(2), (uint)1);
	EXPECT_EQ(r.get(3), (uint)0);
}

TEST(Registre, OperatorShiftREquals) {
	// Arrange
	Registre r("1010");

	// Act
	r >>= 1;

	// Assert
	EXPECT_EQ(r.getSize(), (size_t)4);
	EXPECT_EQ(r.get(0), (uint)1);
	EXPECT_EQ(r.get(1), (uint)0);
	EXPECT_EQ(r.get(2), (uint)1);
	EXPECT_EQ(r.get(3), (uint)0);
}