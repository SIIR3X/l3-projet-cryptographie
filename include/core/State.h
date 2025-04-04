#ifndef STATE_H
#define STATE_H

#include <array>
#include <string>
#include <vector>
#include <ostream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include "core/Key.h"
#include "core/Word.h"
#include "core/Octet.h"

using namespace std;

class State {
private:
	vector<array<Octet, 4>> _state;
	size_t _nbColumn;

public:
	State(size_t nbColumn = 4);

	State(const string& hex);

	State(const State& s)
		: _state(s._state), _nbColumn(s._nbColumn) {}

	const array<Octet, 4>& operator[](size_t index) const { return _state[index]; }

	void setCol(const array<Octet, 4>& col, size_t index) { _state[index] = col; }

	vector<Octet> getRow(size_t row);

	void setRow(const vector<Octet>& row, size_t index);

	void setOctet(size_t col, size_t row, const Octet& octet);

	size_t getNbColumn() const { return _nbColumn; }

	void xorColumn(size_t index, const Word& w);

	State operator^(const State& s) const;

	State& operator^=(const State& s);

	State& operator^=(const Key& k);

	State& operator<<=(const function<size_t(size_t)>& shiftFunc);

	State& operator<<=(const Octet& o);

	State& operator>>=(const function<size_t(size_t)>& shiftFunc);

	State& operator=(const State& s);

	bool operator==(const State& s) const { return _state == s._state; }

	operator string() const;

	ostream& print(ostream& os = cout) const;

	friend ostream& operator<<(ostream& os, const State& state)
	{
		return state.print(os);
	}
};

inline State::State(size_t nbColumn)
	: _nbColumn(nbColumn)
{
	_state.resize(_nbColumn);
	
	for (size_t i = 0; i < 4; ++i)
		_state[i].fill(Octet(0));
}

inline vector<Octet> State::getRow(size_t row)
{
	vector<Octet> result;

	for (size_t col = 0; col < _nbColumn; ++col)
		result.push_back(_state[col][row]);

	return result;
}

inline void State::setRow(const vector<Octet>& row, size_t index)
{
	for (size_t col = 0; col < _nbColumn; ++col)
		_state[col][index] = row[col];
}

inline void State::setOctet(size_t col, size_t row, const Octet& octet)
{
	if (col >= _nbColumn)
		throw invalid_argument("Index de colonne hors limite");

	if (row >= 4)
		throw invalid_argument("Index de ligne hors limite");

	_state[col][row] = octet;
}

inline void State::xorColumn(size_t index, const Word& w)
{
	for (size_t row = 0; row < 4; ++row)
		_state[index][row] ^= w[row];
}

inline State State::operator^(const State& s) const
{
	State result(_nbColumn);

	for (size_t col = 0; col < _nbColumn; ++col)
		for (size_t row = 0; row < 4; ++row)
			result._state[col][row] = _state[col][row] ^ s._state[col][row];

	return result;
}

inline State& State::operator^=(const State& s)
{
	for (size_t col = 0; col < _nbColumn; ++col)
		for (size_t row = 0; row < 4; ++row)
			_state[col][row] ^= s._state[col][row];

	return *this;
}

inline State& State::operator^=(const Key& k) {
	for (size_t col = 0; col < _nbColumn; ++col)
		for (size_t row = 0; row < 4; ++row)
			_state[col][row] ^= k[col][row];

	return *this;
}

inline State& State::operator<<=(const function<size_t(size_t)>& shiftFunc)
{
	for (size_t row = 1; row < 4; ++row)
	{
		vector<Octet> tempRow;

		for (size_t col = 0; col < _nbColumn; ++col)
			tempRow.push_back(_state[col][row]);

		size_t shift = shiftFunc(row) % _nbColumn;
		
		rotate(tempRow.begin(), tempRow.begin() + shift, tempRow.end());

		for (size_t col = 0; col < _nbColumn; ++col)
			_state[col][row] = tempRow[col];
	}

	return *this;
}

inline State& State::operator<<=(const Octet& r)
{
	uint8_t carry = 0;

	bool msb = (_state[0][0].get() & 0x80) != 0;

	for (int col = (int)_nbColumn - 1; col >= 0; --col)
	{
		for (int row = 3; row >= 0; --row)
		{
			uint8_t temp = _state[col][row].get();
			
			_state[col][row] = Octet((temp << 1) | carry);
			
			carry = (temp & 0x80) ? 1 : 0;
		}
	}

	if (msb)
		_state[_nbColumn - 1][3] ^= r;

	return *this;
}

inline State& State::operator>>=(const function<size_t(size_t)>& shiftFunc)
{
	for (size_t row = 1; row < 4; ++row)
	{
		vector<Octet> tempRow;

		for (size_t col = 0; col < _nbColumn; ++col)
			tempRow.push_back(_state[col][row]);

		size_t shift = shiftFunc(row) % _nbColumn;

		rotate(tempRow.rbegin(), tempRow.rbegin() + shift, tempRow.rend());

		for (size_t col = 0; col < _nbColumn; ++col)
			_state[col][row] = tempRow[col];
	}

	return *this;
}

inline State& State::operator=(const State& s)
{
	_state = s._state;
	_nbColumn = s._nbColumn;
	return *this;
}

inline State::operator string() const
{
	string result;

	for (size_t row = 0; row < 4; ++row)
		for (size_t col = 0; col < _nbColumn; ++col)
			result += (string)_state[col][row];

	return result;
}

inline ostream& State::print(ostream& os) const
{
	for (size_t row = 0; row < 4; ++row) 
	{
		for (size_t col = 0; col < _nbColumn; ++col)
			os << _state[col][row].toHex() << " ";

		os << endl;
	}

	return os;
}

#endif // STATE_H