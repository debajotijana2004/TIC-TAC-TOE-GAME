#include <iostream>
#include <limits>
#include <string>
using namespace std;

char board[3][3];
int scoreX = 0, scoreO = 0;
char currentPlayer = 'X';
string playerX, playerO;

void initBoard() {
    char pos = '1';
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = pos++;
}

void drawBoard() {
    cout << "\n";
    for (int i = 0; i < 3; ++i) {
        cout << " ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "---|---|---\n";
    }
    cout << "\n";
}

bool checkWin() {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == currentPlayer &&
            board[i][1] == currentPlayer &&
            board[i][2] == currentPlayer)
            return true;
        if (board[0][i] == currentPlayer &&
            board[1][i] == currentPlayer &&
            board[2][i] == currentPlayer)
            return true;
    }
    if (board[0][0] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][2] == currentPlayer)
        return true;
    if (board[0][2] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][0] == currentPlayer)
        return true;

    return false;
}

bool isDraw() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

string getCurrentPlayerName() {
    return (currentPlayer == 'X') ? playerX : playerO;
}

bool makeMove() {
    string input;
    int choice;

    while (true) {
        cout << getCurrentPlayerName() << " (" << currentPlayer << "), enter a number (1-9) or 'q' to quit: ";
        getline(cin, input);

        if (input == "q" || input == "Q") {
            cout << "Player chose to quit the game.\n";
            exit(0);
        }

        try {
            choice = stoi(input); // Throws if input is not a valid number
        } catch (...) {
            cout << "Invalid input. Please enter a number between 1 and 9.\n";
            continue;
        }

        if (choice < 1 || choice > 9) {
            cout << "Number must be between 1 and 9. Try again.\n";
            continue;
        }

        int row = (choice - 1) / 3;
        int col = (choice - 1) % 3;

        if (board[row][col] == 'X' || board[row][col] == 'O') {
            cout << "Cell already taken. Try again.\n";
            continue;
        }

        board[row][col] = currentPlayer;
        return true;
    }
}

int main() {
    cout << "Enter name of 1st Player:";
    getline(cin, playerX);
    cout << "Enter name 2nd Player:";
    getline(cin, playerO);

    char playAgain;

    do {
        initBoard();
        currentPlayer = 'X';
        bool gameEnded = false;

        while (!gameEnded) {
            drawBoard();
            if (makeMove()) {
                if (checkWin()) {
                    drawBoard();
                    cout << getCurrentPlayerName() << " (" << currentPlayer << ") wins!\n";
                    if (currentPlayer == 'X') scoreX++;
                    else scoreO++;
                    gameEnded = true;
                } else if (isDraw()) {
                    drawBoard();
                    cout << "It's a draw!\n";
                    gameEnded = true;
                } else {
                    switchPlayer();
                }
            }
        }

        cout << "\nScoreboard:\n";
        cout << playerX << " (X): " << scoreX << "\n";
        cout << playerO << " (O): " << scoreO << "\n";

        cout << "\nPlay again? (y/n): ";
        cin >> playAgain;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "\nThanks for playing!\n";
    return 0;
}
