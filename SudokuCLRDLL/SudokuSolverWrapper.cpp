#include "stdafx.h"
#include "SudokuSolverWrapper.h"
#include "SudokuSolverEngine.h"
#include <vcclr.h>
#include <msclr/marshal_cppstd.h>
#include <windows.h>
#include <string>

	std::wstring s2ws(const std::string& s)
	{
		int len;
		int slength = (int)s.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
		std::wstring r(buf);
		delete[] buf;
		return r;
	}

	int Sudoku::SudokuSolverWrapper::getGameLevel(String ^ game) {
		std::string input = msclr::interop::marshal_as< std::string >(game);
		SudokuSolverEngine sudokuSolver(input, false);
		if (sudokuSolver.checkIfHasSolution()) {
			sudokuSolver.Solve();
		}
		if (sudokuSolver.checkIfHasSolution()) {
			return static_cast<unsigned>(sudokuSolver.getLEVEL()) - static_cast<unsigned>(EASY);
		}
		else
		{
			return static_cast<unsigned>(INVALID) - static_cast<unsigned>(EASY);
		}
	}
	
	bool Sudoku::SudokuSolverWrapper::isSolutionUnique(String ^ game) {
		std::string input = msclr::interop::marshal_as< std::string >(game);
		SudokuSolverEngine sudokuFwdSolver(input, false);
		if (sudokuFwdSolver.checkIfHasSolution()) {
			sudokuFwdSolver.Solve();
			return(sudokuFwdSolver.checkIfHasSolution() && (!sudokuFwdSolver.findSecondSolution()));
		}
		else {
			return false;
		}
	}

	String ^ Sudoku::SudokuSolverWrapper::generateGame(int difficulty) {
		
		LEVEL level;
		switch (difficulty) {
		case 0: level = EASY; break;
		case 1: level = MEDIUM; break;
		case 2: level = HARD; break;
		case 3: level = SAMURAI; break;
		default: level = EASY; break;
		}

		SudokuSolverEngine sudokuSolver;	
		vector<int> game = sudokuSolver.generateGame(level);
		string output;
		for (int i = 0; i < 81; i++) {
			output.append(std::to_string(game.at(i)));
		}
		return msclr::interop::marshal_as<String^>(output);
	}

	String ^ Sudoku::SudokuSolverWrapper::solveGame(String ^ game) {
		std::string input = msclr::interop::marshal_as<std::string >(game);
		SudokuSolverEngine sudokuSolver(input, false);
		if (sudokuSolver.checkIfHasSolution()) {
			sudokuSolver.Solve();
		}
		vector<int> solution = sudokuSolver.getSolution();
		string output;
		for (int i = 0; i < 81; i++) {
			output.append(std::to_string(solution.at(i)));
		}
		return msclr::interop::marshal_as<String^>(output);
	}

	bool Sudoku::SudokuSolverWrapper::hasASolution(String ^ game) {
		std::string input = msclr::interop::marshal_as<std::string >(game);
		SudokuSolverEngine sudokuSolver(input, false);
		return sudokuSolver.checkIfHasSolution();
	}