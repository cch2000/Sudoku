#pragma once
#include <windows.h>
#include <string>

using namespace System;

namespace Sudoku {
	public ref class SudokuSolverWrapper
	{
	public:
		int getGameLevel(String ^ game);
		bool isSolutionUnique(String ^ game);
		String ^ generateGame(int level);
		String ^ solveGame(String ^ game);
		bool hasASolution(String ^ game);
	};
};