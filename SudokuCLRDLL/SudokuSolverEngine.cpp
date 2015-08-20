#include "stdafx.h"
#include <time.h>
#include "SudokuSolverEngine.h"

namespace Sudoku
{
	static std::string easy_template = "51.....838..416..5..........985.461....9.1....642.357..........6..157..478.....96";
	static std::string medium_template = "7...9...32..468..1..8...6...4..2..9....3.4....8..1..3...9...7..5..142..68...5...2";
	static std::string hard_template = ".523..6..6...4...3............63..1.47.....35.2..58............1...9...6..5..172.";
	static std::string samurai_template = "5.....1.7..43..5.....2...8..9.4.2...4.......6...1.3.5..8...4.....2..67..3.9.....1";
	
	typedef void(*pfunc)(vector<int>& puzzle);

	std::vector<int> permute9Array() {
		srand(time(NULL));
		int values[9] = { 1,2,3,4,5,6,7,8,9 };
		std::vector<int> numbers(values, values + 9);
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < (9 - i); j++)
			{
				int index = rand() % (9 - i);
				std::swap(numbers[8 - i], numbers[index]);
			}
		}
		return numbers;
	}

	void rotateVertical(vector<int> & game) {

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 9; j++) {
				int up = i * 9 + j;
				int down = (8 - i) * 9 + j;
				std::swap(game.begin() + up, game.begin() + down);
			}
		}
	}

	void rotateHorizontal(vector<int> & game) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 4; j++) {
				int left = i * 9 + j;
				int right = i * 9 + (8 - j);
				std::swap(game.begin() + left, game.begin() + right);
			}
		}
	}

	void rotateMajorDiagonal(vector<int> & game) {
		for (int i = 0; i < 9; i++) {
			for (int j = i + 1; j < 9; j++) {
				int upperRight = i * 9 + j;
				int lowerLeft = j * 9 + j;
				std::swap(game.begin() + upperRight, game.begin() + lowerLeft);
			}
		}
	}

	void rotateMinorDiagonal(vector<int> & game) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < i; j++) {
				int upperLeft = i * 9 + j;
				int LowerRight = (8 - j) * 9 + (8 - i);
				std::swap(game.begin() + upperLeft, game.begin() + LowerRight);
			}
		}
	}

	void SudokuSolverEngine::reduceSquaresInRow(int row, int col, int value, map<int, set<int>>& _choices) {
		for (int j = 0; j < 9; j++) {
			if (j != col && choices.find(row * 9 + j) != choices.end()) {
				_choices[row * 9 + j].erase(value);
			}
		}
	}
	void SudokuSolverEngine::reduceSquaresInCol(int row, int col, int value, map<int, set<int>>& _choices) {
		for (int i = 0; i < 9; i++) {
			if (i != row && choices.find(i * 9 + col) != choices.end()) {
				_choices[i * 9 + col].erase(value);
			}
		}
	}
	void SudokuSolverEngine::reduceSquaresIn3X3(int row, int col, int value, map<int, set<int>>& _choices) {
		int base_row = row / 3 * 3;
		int base_col = col / 3 * 3;
		for (int m = base_row; m < base_row + 3; m++) {
			for (int n = base_col; n < base_col + 3; n++) {
				if ((m != row || n != col) && choices.find(m * 9 + n) != choices.end()) {
					_choices[m * 9 + n].erase(value);
				}
			}
		}
	}

	bool SudokuSolverEngine::isSafe(int row, int col, int val, int usedValue) {
		return this->isSafe(row, col, val, usedValue, squares);
	}
	bool SudokuSolverEngine::isSafe(int row, int col, int val, int usedValue, const vector<int>& game) {
		if (val == usedValue)
			return false;
		for (int j = 0; j < 9; j++) {
			if (game[row * 9 + j] == 0)
				continue;
			if (game[row * 9 + j] == val) {
				return false;
			}
		}
		for (int i = 0; i < 9; i++) {
			if (game[i * 9 + col] == 0)
				continue;
			if (game[i * 9 + col] == val) {
				return false;
			}
		}
		int base_row = row / 3 * 3;
		int base_col = col / 3 * 3;
		for (int m = base_row; m < base_row + 3; m++) {
			for (int n = base_col; n < base_col + 3; n++) {
				if (game[m * 9 + n] == 0)
					continue;
				if (game[m * 9 + n] == val) {
					return false;
				}
			}
		}
		return true;
	}

	void SudokuSolverEngine::init() {

		int nums[9] = { 1,2,3,4,5,6,7,8,9 };
		set<int> all(nums, nums + 9);
		map<int, set<int>> _choices;
		for (int i = 0; i < GAME_SIZE; i++) {
			_choices[i] = all;
		}
		for (int i = 0; i < GAME_SIZE; i++) {
			if (squares[i] != 0) {
				_choices.erase(i);
				int row = i / 9;
				int col = i % 9;
				reduceSquaresInRow(row, col, squares[i], _choices);
				reduceSquaresInCol(row, col, squares[i], _choices);
				reduceSquaresIn3X3(row, col, squares[i], _choices);
			}
		}
		std::priority_queue<Square, std::vector<Square>, SquareComparator> squarePQ;
		for (auto _choice = _choices.begin(); _choice != _choices.end(); _choice++) {
			std::vector<int> choice;
			std::copy(_choice->second.begin(), _choice->second.end(), std::back_inserter(choice));
			choices[_choice->first] = choice;
			Square square(_choice->first, _choice->second.size());
			squarePQ.push(square);
			choiceOrder[_choice->first] = -1;
		}
		if (squarePQ.top().getNumOfPossibilities() == 0) {
			std::cout << "The top element has no possibilities" << std::endl;
			hasASolution = false;
		}
		else {
			while (!squarePQ.empty()) {
				fillingOrder.push_back(squarePQ.top().getGid());
				squarePQ.pop();
			}
		}
		if (reverse) {
			std::reverse(fillingOrder.begin(), fillingOrder.end());
		}
	}

	void SudokuSolverEngine::string2IntArray(const string & origin) {
		hasASolution = true;
		if (origin.size() != GAME_SIZE) {
			std::cout << "input format wrong. Can't solve the puzzle" << std::endl;
			hasASolution = false;
		}
		squares.assign(GAME_SIZE, 0);
		for (size_t i = 0; i < origin.size(); i++) {
			if (isdigit(origin.at(i))) {
				const char c[2] = { origin.at(i), '\0' };
				squares[i] = atoi(c);
			}
		}
		_squares = squares;

	}
	SudokuSolverEngine::SudokuSolverEngine(std::vector<int>& game, bool _reverse) : reverse(_reverse) {
		hasASolution = true;
		squares = game;
		_squares = game;
		init();
	}
	SudokuSolverEngine::SudokuSolverEngine(const string & origin, bool _reverse) : reverse(_reverse){
		string2IntArray(origin);
		init();
	}
	bool SudokuSolverEngine::checkIfHasSolution() {
		return hasASolution;
	}

	std::vector<int> SudokuSolverEngine::getSolution() const {
		return squares;
	}

	void print(std::vector<int> & game) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				std::cout << game[i * 9 + j] << " ";
			}
			std::cout << std::endl;
		}
	}
	std::vector<int> SudokuSolverEngine::generateGame(LEVEL difficulty) {
		static std::map<LEVEL, std::string> templateMap;
		templateMap[EASY] = easy_template;
		templateMap[MEDIUM] = medium_template;
		templateMap[HARD] = hard_template;
		templateMap[SAMURAI] = samurai_template;
		level = difficulty;
		string2IntArray(templateMap[difficulty]);
		std::vector<int> row = permute9Array();
		std::map<int, int> swapMap;
		int id = 1;
		for each (int num in row)
		{
			swapMap[id] = num;
			id++;
		}

		
		for (auto iter = squares.begin(); iter < squares.end(); iter++)
		{
			*iter = swapMap[*iter];
		}

		printSolution();
		int transformations[] = { 0,1,2,3 };
		std::vector<int> transform(transformations, transformations + 4);
		map<int, pfunc> funcMap;
		funcMap[0] = rotateVertical;
		funcMap[1] = rotateHorizontal;
		funcMap[2] = rotateMajorDiagonal;
		funcMap[3] = rotateMinorDiagonal;

		srand(time(NULL));
		int trans_id = rand() % 4;
		for (int i = 0; i < 64; i++) {
			pfunc f = funcMap[transform[trans_id]];
			(*f)(squares);
			std::swap(transform.begin() + 3, transform.begin() + trans_id);
			trans_id = rand() % 3;
		}
		//init();
		return squares;
	}

	int SudokuSolverEngine::genNumToFill(LEVEL level) {
		srand(time(NULL));
		switch (level) {
		case EASY: return rand() % (CHECKPOINT_EASY - VALIDLOWERBOUND + 1) + VALIDLOWERBOUND;
		case MEDIUM: return rand() % (CHECKPOINT_MEDIUM - CHECKPOINT_EASY + 1) + CHECKPOINT_EASY;
		case HARD: return rand() % (CHECKPOINT_HARD - CHECKPOINT_MEDIUM + 1) + CHECKPOINT_MEDIUM;
		case SAMURAI: return rand() % (VALIDUPPERBOUND - CHECKPOINT_HARD + 1) + CHECKPOINT_HARD;
		}
	}

	void SudokuSolverEngine::Solve() {
		this->Solve(false, vector<int>());
	}

	bool SudokuSolverEngine::findSecondSolution() {
		squares = _squares;
		std::vector<int> oldSolution = squares;
		this->Solve(true, oldSolution);
		return hasASolution;
	}

	void SudokuSolverEngine::Solve(bool filterUsedValue, const vector<int>& oldSolution) {
		steps = 0;
		bool found;
		for (size_t k = 0; k < fillingOrder.size();) {
			int limit = choices[fillingOrder[k]].size();
			choiceOrder[fillingOrder[k]]++;
			found = false;
			while (!found && choiceOrder[fillingOrder[k]] < limit) {
				int row = fillingOrder[k] / 9;
				int col = fillingOrder[k] % 9;
				int value = choices[fillingOrder[k]].at(choiceOrder[fillingOrder[k]]);
				int usedValue = -1;
				if (filterUsedValue) {
					usedValue = oldSolution[fillingOrder[k]];
				}
				if (isSafe(row, col, value, usedValue)) {
					found = true;
					squares[fillingOrder[k]] = value;
					k++;
				}
				else {
					choiceOrder[fillingOrder[k]]++;
					steps++;
				}
			}
			if (!found) {
				squares[fillingOrder[k]] = 0;
				choiceOrder[fillingOrder[k]] = -1;
				k--;
			}
		}
		hasASolution = found;
		calculateLevel((int)((double)steps / (double)fillingOrder.size()));
	}

	void SudokuSolverEngine::calculateLevel(int n) {
		if (n <= LEVEL0) {
			level = EASY;
		}
		else if (n <= LEVEL1) {
			level = MEDIUM;
		}
		else if (n <= LEVEL2) {
			level = HARD;
		}
		else {
			level = SAMURAI;
		}
	}

	void SudokuSolverEngine::printSolution() {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				std::cout << squares[i * 9 + j] << " ";
			}
			std::cout << std::endl;
		}
	}
};