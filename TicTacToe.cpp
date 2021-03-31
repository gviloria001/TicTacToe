#include <iostream>
#include <algorithm>

using namespace std;


int evaluation(char board[3][3]);
int miniMax(char board[3][3], bool isMax, int depth);
bool movesLeft(char board[3][3]);
void displayBoard(char board[3][3]);
bool gameOver(char board[3][3]) {
	if (!movesLeft(board)) {
		return true;
	}
	else
		return false;
}
class Player {
private:
	int x;
	int y;
public:
	void playerMove(char board[3][3]) {
		cout << "Input x:" << endl;
		cin >> x;
		cout << "Input y:" << endl;
		cin >> y;
		while (!isValid(board, x, y)) {
			cout << "Input valid x:" << endl;
			cin >> x;
			cout << "Input valid y:" << endl;
			cin >> y;
		}
		makePlayerMove(board, x, y);
	}
	void makePlayerMove(char board[3][3], int x, int y) {
		board[y][x] = 'O';
	}
	bool isValid(char board[3][3], int x, int y) {
		if (board[y][x] == 'X' || board[y][x] == 'O')
			return false;
		else
			return true;
	}
};
class Move {
private:
	int bestVal = -100;
	int bestRow = -1;
	int bestCol = -1;
public:
	void bestMove(char board[3][3]) {
		int bestVal = -100;
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				if (board[row][col] == ' ') {
					board[row][col] = 'X';
					int compareVal = miniMax(board, false, 0);
					board[row][col] = ' ';
					if (bestVal < compareVal) {
						bestRow = row;
						bestCol = col;
						bestVal = compareVal;
					}
				}
			}
		}
	}
	int getBestRow() {
		return bestRow;
	}
	int getBestCol() {
		return bestCol;
	}
	int getBestVal() {
		return bestVal;
	}
};
bool movesLeft(char board[3][3]) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (board[row][col] == ' ') {
				return true;
			}
		}
	}
	return false;
}
int miniMax(char board[3][3], bool isMax, int depth) {

	int score = evaluation(board);
	if (movesLeft(board) == false)
		return 0;
	if (score >= 100)
		return score;
	if (score <= -100)
		return score;
	if (isMax == true) {
		int best = -1000;
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				if (board[row][col] == ' ') {
					board[row][col] = 'X';
					int value = miniMax(board, !isMax, depth + 1);
					best = std::max(best, value);
					board[row][col] = ' ';
				}
			}
		}
		return best;
	}
	else {
		int least = 1000;
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				if (board[row][col] == ' ') {
					board[row][col] = 'O';
					int value = miniMax(board, !isMax, depth + 1);
					least = std::min(least, value);
					board[row][col] = ' ';
				}
			}
		}
		return least;
	}
}
int evaluation(char board[3][3]) {
	int score = 0;
	if (movesLeft(board) == false)
		return 0;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Count the amount of Xs and Os in the rows. +100 3X, +10 2x, +1  1x, 0 cats game, -1 1o, -10 2o, -100 3o
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (int row = 0; row < 3; row++) {								
		if (board[row][0] == 'X' || board[row][1] == 'X' || board[row][2] == 'X') {
			if (board[row][0] == board[row][1] || board[row][0] == board[row][2] || board[row][1] == board[row][2]) {
				if (board[row][0] == board[row][1] && board[row][0] == board[row][2]) {
					score += 100;
				}
				score += 10;
			}
			score += 1;
		}
		else if (board[row][0] == 'O' || board[row][1] == 'O' || board[row][2] == 'O') {
			if (board[row][0] == board[row][1] || board[row][0] == board[row][2] || board[row][1] == board[row][2]) {
				if (board[row][0] == board[row][1] && board[row][0] == board[row][2]) {
					score -= 100;
				}
				score -= 10;
			}
			score -= 1;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Count the amount of Xs and Os in the cols. +100 3X, +10 2x, +1  1x, 0 cats game, -1 1o, -10 2o, -100 3o
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (int col = 0; col < 3; col++) {
		if (board[0][col] == 'X' || board[1][col] == 'X' || board[2][col] == 'X') {
			if (board[0][col] == board[1][col] || board[0][col] == board[2][col] || board[1][col] == board[2][col]) {
				if (board[0][col] == board[1][col] && board[0][col] == board[2][col]) {
					score += 100;
				}
				score += 10;
			}
			score += 1;
		}
		else if (board[0][col] == 'O' || board[1][col] == 'O' || board[2][col] == 'O') {
			if (board[0][col] == board[1][col] || board[0][col] == board[2][col] || board[1][col] == board[2][col]) {
				if (board[0][col] == board[1][col] && board[0][col] == board[2][col]) {
					score -= 100;
				}
				score -= 10;
			}
			score -= 1;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Count the amount of Xs and Os in the diagonals. +100 3X, +10 2x, +1  1x, 0 cats game, -1 1o, -10 2o, -100 3o
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Top right to bottom left
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (board[0][2] == 'X' || board[1][1] == 'X' || board[2][0] == 'X') {
		if (board[0][2] == board[1][1] || board[0][2] == board[2][0] || board[1][1] == board[2][0]) {
			if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
				score += 100;
			}
			score += 10;
		}
		score += 1;
	}
	if (board[0][2] == 'O' || board[1][1] == 'O' || board[2][0] == 'O') {
		if (board[0][2] == board[1][1] || board[0][2] == board[2][0] || board[1][1] == board[2][0]) {
			if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
				score -= 100;
			}
			score -= 10;
		}
		score -= 1;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Top left to bottom right
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (board[0][0] == 'X' || board[1][1] == 'X' || board[2][2] == 'X') {
		if (board[0][0] == board[1][1] || board[0][0] == board[2][2] || board[1][1] == board[2][2]) {
			if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
				score += 100;
			}
			score += 10;
		}
		score += 1;
	}
	if (board[0][0] == 'O' || board[1][1] == 'O' || board[2][2] == 'O') {
		if (board[0][0] == board[1][1] || board[0][0] == board[2][2] || board[1][1] == board[2][2]) {
			if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
				score -= 100;
			}
			score -= 10;
		}
		score -= 1;
	}
	return score;
}
void displayBoard(char board[3][3]) {
	cout << "=====================" << endl;
	cout << "      X axis    \n" << "      0 1 2 " << endl;
	cout << "    0 " << board[0][0] << "|" << board[0][1] << "|" << board[0][2] << endl;
	cout << "      " << "-+-+-" << endl;
	cout << " Y  1 " << board[1][0] << "|" << board[1][1] << "|" << board[1][2] << endl;
	cout << "axis  " << "-+-+-" << endl;
	cout << "    2 " << board[2][0] << "|" << board[2][1] << "|" << board[2][2] << endl << endl;
}
bool isWinner(char board[3][3], char symbol) {
	for (int i = 0; i < 3; i++) {	// i	check each row
		if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)// 0
			return true;
	}
	// for each column
	// i  0  1  2
	for (int i = 0; i < 3; i++) {
		if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)
			return true;

	}
	//  or diagonal left to right down
	if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
		return true;
	if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
		return true;
	else
		return false;
}
int main() {
	char board[3][3] = {
	{' ', ' ', ' '},
	{' ', ' ', ' '},
	{' ', ' ', ' '}
	};
	Move BestMove;
	Player player;
	int x = 0;
	int y = 0;
	while (!movesLeft(board) || !isWinner(board, 'X' || !isWinner(board, 'O'))) {
		BestMove.bestMove(board);
		board[BestMove.getBestRow()][BestMove.getBestCol()] = 'X';
		displayBoard(board);
		if (!movesLeft(board) || isWinner(board, 'X')){
			break;
		}
		player.playerMove(board);
		displayBoard(board);
		if (!movesLeft(board) || isWinner(board, 'O')) {
			break;
		}
	}
	if (!movesLeft(board)) {
		cout << "================\n" << "= Cats Game!!! =\n" << "================\n";
	}
	else {
		if (isWinner(board, 'X')) {
			cout << "================\n" << "=   X Wins!!!  =\n" << "================\n";
		}
		else {
			cout << "================\n" << "=   O Wins!!!  =\n" << "================\n";
		}
	}
	return 0;
}