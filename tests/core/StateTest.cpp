#include "core/State.h"
#include <gtest/gtest.h>

TEST(State, ConstructeurString) {
	// Arrange
	string hex = "32 43 f6 a8 88 5a 30 8d 31 31 98 a2 e0 37 07 34";
	
	// Act
	State state(hex);

	// Assert
	EXPECT_EQ(state[0][0], Octet(0x32));
	EXPECT_EQ(state[0][1], Octet(0x43));
	EXPECT_EQ(state[0][2], Octet(0xf6));
	EXPECT_EQ(state[0][3], Octet(0xa8));
	EXPECT_EQ(state[1][0], Octet(0x88));
	EXPECT_EQ(state[1][1], Octet(0x5a));
	EXPECT_EQ(state[1][2], Octet(0x30));
	EXPECT_EQ(state[1][3], Octet(0x8d));
	EXPECT_EQ(state[2][0], Octet(0x31));
	EXPECT_EQ(state[2][1], Octet(0x31));
	EXPECT_EQ(state[2][2], Octet(0x98));
	EXPECT_EQ(state[2][3], Octet(0xa2));
	EXPECT_EQ(state[3][0], Octet(0xe0));
	EXPECT_EQ(state[3][1], Octet(0x37));
	EXPECT_EQ(state[3][2], Octet(0x07));
	EXPECT_EQ(state[3][3], Octet(0x34));
}

TEST(State, SetCol) {
	// Arrange
	string hex = "32 43 f6 a8 88 5a 30 8d 31 31 98 a2 e0 37 07 34";
	State state(hex);
	array<Octet, 4> col = { Octet(0x01), Octet(0x02), Octet(0x03), Octet(0x04) };
	
	// Act
	state.setCol(col, 1);

	// Assert
	EXPECT_EQ(state[1][0], Octet(0x01));
	EXPECT_EQ(state[1][1], Octet(0x02));
	EXPECT_EQ(state[1][2], Octet(0x03));
	EXPECT_EQ(state[1][3], Octet(0x04));
}

TEST(State, GetRow) {
	// Arrange
	string hex = "32 43 f6 a8 88 5a 30 8d 31 31 98 a2 e0 37 07 34";
	State state(hex);
	
	// Act
	vector<Octet> row = state.getRow(1);

	// Assert
	EXPECT_EQ(row[0], Octet(0x43));
	EXPECT_EQ(row[1], Octet(0x5a));
	EXPECT_EQ(row[2], Octet(0x31));
	EXPECT_EQ(row[3], Octet(0x37));
}

TEST(State, SetRow) {
	// Arrange
	string hex = "32 43 f6 a8 88 5a 30 8d 31 31 98 a2 e0 37 07 34";
	State state(hex);
	vector<Octet> row = { Octet(0x01), Octet(0x02), Octet(0x03), Octet(0x04) };
	
	// Act
	state.setRow(row, 1);

	// Assert
	EXPECT_EQ(state[0][1], Octet(0x01));
	EXPECT_EQ(state[1][1], Octet(0x02));
	EXPECT_EQ(state[2][1], Octet(0x03));
	EXPECT_EQ(state[3][1], Octet(0x04));
}

TEST(State, XorColumn) {
	// Arrange
	string hex = "32 43 f6 a8 88 5a 30 8d 31 31 98 a2 e0 37 07 34";
	State state(hex);
	Word w("09 cf 4f 3c");

	// Act
	state.xorColumn(1, w);

	// Assert
	EXPECT_EQ(state[1][0], Octet(0x81));
	EXPECT_EQ(state[1][1], Octet(0x95));
	EXPECT_EQ(state[1][2], Octet(0x7f));
	EXPECT_EQ(state[1][3], Octet(0xb1));
}

TEST(State, OperatorXor) {
	// Arrange
	State state1("32 43 f6 a8 88 5a 30 8d 31 31 98 a2 e0 37 07 34");
	State state2("2b 28 ab 09 7e ae f7 cf 15 d2 15 4f 16 a6 88 3c");

	// Act
	State result = state1 ^ state2;

	// Assert
	State expected("19 6b 5d a1 f6 f4 c7 42 24 e3 8d ed f6 91 8f 08");
	EXPECT_EQ(result, expected);
}

TEST(State, OperatorXorEquals) {
	// Arrange
	State state1("32 43 f6 a8 88 5a 30 8d 31 31 98 a2 e0 37 07 34");
	State state2("2b 28 ab 09 7e ae f7 cf 15 d2 15 4f 16 a6 88 3c");

	// Act
	state1 ^= state2;

	// Assert
	State expected("19 6b 5d a1 f6 f4 c7 42 24 e3 8d ed f6 91 8f 08");
	EXPECT_EQ(state1, expected);
}

TEST(State, ShiftLEqualsFunc) {
	// Arrange
	State state("32 43 f6 a8 88 5a 30 8d 31 31 98 a2 e0 37 07 34");

	// Act
	state <<= [](size_t row) { return row; };

	// Assert
	State expected("32 5a 98 34 88 31 07 a8 31 37 f6 8d e0 43 30 a2");
	EXPECT_EQ(state, expected);
}

TEST(State, ShiftLEqualsOctet)
{
	// Arrange
	State state("80 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00");
	Octet reduction(0x87);

	// Act
	state <<= reduction;

	// Assert
	State expected("00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 87");
	EXPECT_EQ(state, expected);
}

TEST(State, ShiftREqualsFunc) {
	// Arrange
	State state("32 43 f6 a8 88 5a 30 8d 31 31 98 a2 e0 37 07 34");

	// Act
	state >>= [](size_t row) { return row; };

	// Assert
	State expected("32 37 98 8d 88 43 07 a2 31 5a f6 34 e0 31 30 a8");
	EXPECT_EQ(state, expected);
}

TEST(State, OperatorEqualsEquals) {
	// Arrange
	State state1("32 43 f6 a8 88 5a 30 8d 31 31 98 a2 e0 37 07 34");
	State state2("32 43 f6 a8 88 5a 30 8d 31 31 98 a2 e0 37 07 34");

	// Act
	bool result = state1 == state2;

	// Assert
	EXPECT_TRUE(result);
}