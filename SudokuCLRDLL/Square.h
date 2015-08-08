#pragma once

namespace Sudoku
{
	class Square
{
	int gid;
	int numOfPossibilities;

public:
	Square(int _gid, int _numOfPossibilities): gid(_gid), numOfPossibilities(_numOfPossibilities){}
	int getGid() const { return gid; }
	int getNumOfPossibilities() const { return numOfPossibilities; }
};
}