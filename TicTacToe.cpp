#include <iostream>;

using namespace std;


int evaluation(char board[3][3]);
int miniMax(char board[3][3], bool isMax);
bool movesLeft(char board[3][3]);
bool gameOver(char board[3][3]) {
	if (movesLeft(board) == false) {
		return true;
	}
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
		makePlayerMove(board, x, y);
	}
	void makePlayerMove(char board[3][3], int x, int y) {
		board[y][x] = 'O';
	}
};
class Move {
private:
	int bestVal = -100;
	int bestRow = -1;
	int bestCol = -1;
public:
	void bestMove(char board[3][3]) {
		/*int depth = 0;
		depth++;
		cout << "Depth: " << depth << endl;*/
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				if (board[row][col] == ' ') {
					//cout << "Line 42: " << row << " " << col << " " << endl;
					board[row][col] = 'X';
					int compareVal = miniMax(board, false);
					//cout << "Line 44: " << compareVal << endl;
					board[row][col] = ' ';
					if (compareVal > bestVal) {
						//cout << "in Line 46" << endl;
						bestRow = row;
						bestCol = col;
						//cout << bestRow << "," << bestCol << endl;
						bestVal = compareVal;
					}
				}
			}
		}
		bestVal = 0;
		//cout << bestRow << endl << bestCol << endl;
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
int miniMax(char board[3][3], bool isMax) {
	int score = evaluation(board);
	//if (movesLeft(board) == false)
	//	return 0;
	if (isMax) {
		int best = -100;
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				if (board[row][col] == ' ') {
					board[row][col] = 'X';
					best = max(best, miniMax(board, false));
					board[row][col] = ' ';
				}
			}
		}
		return best + score;
	}
	else {
		int best = 100;
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				if (board[row][col] == ' ') {
					board[row][col] = 'O';
					best = min(best, miniMax(board, true));
					board[row][col] = ' ';
				}
			}
		}
		return best + score;
	}
}
int evaluation(char board[3][3]) {
	for (int rows = 0; rows < 3; rows++) {
		if (board[rows][0] == board[rows][1] && board[rows][1] == board[rows][2]) {
			if (board[rows][0] == 'X')
				return +10;
			else if (board[rows][0] == 'O')
				return -10;
		}
	}
	for (int cols = 0; cols < 3; cols++) {
		if (board[0][cols] == board[1][cols] && board[1][cols] == board[2][cols]) {
			if (board[0][cols] == 'X')
				return +10;
			else if (board[0][cols] == 'O')
				return -10;
		}
	}
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
		if (board[0][0] == 'X')
			return +10;
		else if (board[0][0] == 'O')
			return -10;
	}
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
		if (board[0][2] == 'X')
			return +10;
		else if (board[0][2] == 'O')
			return -10;
	}
	return 0;
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
	while (!gameOver(board)) {
		BestMove.bestMove(board);
		//cout << BestMove.getBestRow() << " , " << BestMove.getBestCol() << endl;
		board[BestMove.getBestRow()][BestMove.getBestCol()] = 'X';
		displayBoard(board);
		player.playerMove(board);
		displayBoard(board);
	}
	return 0;
}