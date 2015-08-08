// SudokuCLRDLL.h

#pragma once

#include <vector>
#include "SudokuMisc.h"

using namespace System;

#include <string>
#include <vector>
#include <windows.h>
#include <vcclr.h>
#using <System.dll>

#include "SudokuMisc.h"
#include "SudokuSolverWrapper.h"

namespace Sudoku
{

	public ref class ManagedSudokuSolver
	{
	public:
		// Get the difficulty level of the game
		int getGameLevel(String ^ game) {
			auto sudokuSolver = gcnew SudokuSolverWrapper();
			return sudokuSolver->getGameLevel(game);
		}

		// Check if the game has a unique solution
		bool isSolutionUnique(String ^ game) {
			auto sudokuSolver = gcnew SudokuSolverWrapper();
			return  sudokuSolver->isSolutionUnique(game);
		}

		// Generate the game based on difficulty
		String ^ generateGame(int level) {
			auto sudokuSolver = gcnew SudokuSolverWrapper();
			return gcnew String(sudokuSolver->generateGame(level));
		}

		// Solve the game and return the solution
		String ^ solveGame(String ^ game) {
			auto sudokuSolver = gcnew SudokuSolverWrapper();
			return gcnew String(sudokuSolver->solveGame(game));
		}

	};
};

