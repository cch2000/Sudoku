using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Sudoku;
namespace WindowsFormsExample
{
    class SudokuSolver
    {
        
        public static string solveGame(string game)
        {
            SudokuSolverWrapper sudokuSolver = new SudokuSolverWrapper();
            return sudokuSolver.solveGame(game);
        }
        public static int getGameLevel(string game)
        {
            SudokuSolverWrapper sudokuSolver = new SudokuSolverWrapper();
            return sudokuSolver.getGameLevel(game);
        }

        public static bool isSolutionUnique(string game)
        {
            SudokuSolverWrapper sudokuSolver = new SudokuSolverWrapper();
            return sudokuSolver.isSolutionUnique(game);
        }

        public static string generateGame(int level)
        {
            SudokuSolverWrapper sudokuSolver = new SudokuSolverWrapper();
            return sudokuSolver.generateGame(level);
        }

        public static bool hasASolution(string game)
        {
            SudokuSolverWrapper sudokuSolver = new SudokuSolverWrapper();
            return sudokuSolver.hasASolution(game);
        }
    }
}
