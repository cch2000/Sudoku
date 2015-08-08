// This is the main DLL file.

#include "stdafx.h"

#include "SudokuCLRDLL.h"
#include "SudokuSolverEngine.h"
#include <stdexcept>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace Sudoku
{
	vector<int> SudokuSolverWrapper::solveGame(const string game) {
		SudokuSolverEngine sudokuSolver(game, false);
		if (sudokuSolver.checkIfHasSolution()) {
			sudokuSolver.Solve();
			return sudokuSolver.getSolution();
		}
		else
			return vector<int>(0);
	}
	LEVEL SudokuSolverWrapper::getGameLevel(const string game) {
		SudokuSolverEngine sudokuSolver(game, false);
		if (sudokuSolver.checkIfHasSolution()) {
			sudokuSolver.Solve();
			return sudokuSolver.getLevel();
		}
		return INVALID;
	}
	bool SudokuSolverWrapper::hasUniqueSolution(const string game) {
		SudokuSolverEngine sudokuFwdSolver(game, false);
		SudokuSolverEngine sudokuRevSolver(game, true);
		if (sudokuRevSolver.checkIfHasSolution()) {
			sudokuRevSolver.Solve();
		}
		if (sudokuFwdSolver.checkIfHasSolution()) {
			sudokuFwdSolver.Solve();
		}
		return sudokuFwdSolver.isSolutionEqual(sudokuRevSolver);
	}
	vector<int> SudokuSolverWrapper::generateGame(LEVEL level) {

		return vector<int>(GAME_SIZE, 0);
	}
}
