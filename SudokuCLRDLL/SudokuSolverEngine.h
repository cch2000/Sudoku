#pragma once
#include "stdafx.h"
#include <vector>
#include <map>
#include <string>
#include <set>
#include <iterator>
#include <queue>

#include <cctype>
#include <algorithm>

#include <iostream>
#include "SudokuMisc.h"
#include "Square.h"
#include "SquareComparator.h"

using std::vector;
using std::map;
using std::string;
using std::set;

namespace Sudoku {

	class SudokuSolverEngine
	{
	private:
		vector<int> fillingOrder;
		map<int, vector<int>> choices;
		vector<int> squares;
		vector<int> _squares;
		map<int, int> choiceOrder;
		bool hasASolution;
		int steps;
		bool reverse;
		LEVEL level;

	private:
		void reduceSquaresInRow(int row, int col, int value, map<int, set<int>>& _choices);
		void reduceSquaresInCol(int row, int col, int value, map<int, set<int>>& _choices);
		void reduceSquaresIn3X3(int row, int col, int value, map<int, set<int>>& _choices);
		bool isSafe(int row, int col, int val, int usedValue, const vector<int>& game);
		bool isSafe(int row, int col, int val, int usedValue);
		int genNumToFill(LEVEL level);
		void init();
		void string2IntArray(const std::string & origin);
		void calculateLevel(int n);
	public:
		SudokuSolverEngine() {};
		SudokuSolverEngine(std::vector<int>& game, bool reverse);
		SudokuSolverEngine(const string& origin, bool reverse);
		bool checkIfHasSolution();
		void Solve();
		void Solve(bool filterUsedValue, const vector<int> &  oldSolution);
		std::vector<int> getSolution() const;
		//bool isSolutionEqual(const SudokuSolverEngine solver) const;
		void printSolution();
		vector<int> generateGame(LEVEL level);
		//bool hasUqniueSolution();
		LEVEL getLEVEL() const { return this->level; }
		bool findSecondSolution();
	};
}