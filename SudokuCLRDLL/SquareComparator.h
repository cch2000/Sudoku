#pragma once
#include "Square.h"
namespace Sudoku
{
	class SquareComparator
{
  bool reverse;
public:
  SquareComparator(const bool& revparam=false)
    {reverse=revparam;}
  bool operator() (const Square& lhs, const Square&rhs) const
  {
	  if (reverse) return (lhs.getNumOfPossibilities()>rhs.getNumOfPossibilities());
	  else return (lhs.getNumOfPossibilities()<rhs.getNumOfPossibilities());
  }
};
}