// Tic-tac-toe game
// Original author: Daniel Hillerström
// Rewritten in C++ and adapted to InfOS by: Vidminas Mikucionis

#include <infos.h>

// Tic-tac-toe game configuration
constexpr char empty = ' '; // Empty cell character
constexpr int boardDim = 3; // 3x3 board (can be bigger, but not exceed 9)
constexpr char playerMarks[] = {'X', 'O'}; // 2 players (can be more)

// Game board layout
char board[boardDim][boardDim];

// Resets the board to blank
void reset() {
    for (unsigned char i = 0; i < boardDim; ++i) {
        for (unsigned char j = 0; j < boardDim; ++j) {
            board[i][j] = empty;
        }
    }
}

// Predicate indicating whether all board cells are filled.
bool full() {
    for (unsigned char i = 0; i < boardDim; ++i) {
        for (unsigned char j = 0; j < boardDim; ++j) {
            if (board[i][j] != empty) {
                return false;
            }
        }
    }

    return true;
}

// Attempts to put mark in cell (row,col)
// Returns 1 on success, otherwise -1 is returned when the cell is already occupied, and 0 when the move is not within the board range.
int set(char row, char col, char mark) {
    int rowIndex = row - 'a';
    int colIndex = col - '0';

    if (rowIndex < 0 || rowIndex >= boardDim || colIndex < 0 || colIndex >= boardDim) {
        return 0;
    }

    if (board[rowIndex][colIndex] != empty) {
        return -1;
    }

    board[rowIndex][colIndex] = mark;
    return 1;
}

// prints the top part of the board, e.g.
// "     1   2   3\n"
// "   +---+---+---+\n"
void printBoardHeader() {
    printf("\n");
    printf("  ");

    for (int col = 0; col < boardDim; ++col) {
        printf("   %d", col+1);
    }
    printf("\n");
    printf("   +");

    for (int col = 0; col < boardDim; ++col) {
        printf("---+");
    }
    printf("\n");
}

// prints a row of the board, e.g.
// "a  |   |   |   |\n"
// "   +---+---+---+\n"
void printBoardRow(char row) {
    printf("%c  |", row);
    int rowIndex = row - 'a';

    for (int col = 0; col < boardDim; ++col) {
        printf(" %c |", board[rowIndex][col]);
    }
    printf("\n");
    printf("   +");

    for (int col = 0; col < boardDim; ++col) {
        printf("---+");
    }
    printf("\n");
}

// Prints the game board to stdout
void printGame() {
    printBoardHeader();
    
    char row = 'a';
    for (int i = 0; i < boardDim; ++i) {
        printBoardRow(row);
        row++;
    }
    printf("\n");
}

int nextPlayer(int currentPlayer) {
    if (currentPlayer < sizeof(playerMarks)) {
        return currentPlayer + 1;
    } else {
        return 1;
    }
}

char inputRow() {
    while (char row = getch()) {
        if (row >= 'a' && row <= 'z') {
            printf("%c", row);
            return row;
        }
    }
    return NULL;
}

char inputColumn() {
    while (char col = getch()) {
        if ((col >= '1' && col <= '9') || col == '\b') {
            printf("%c", col);
            return col;
        }
    }
    return NULL;
}

// Asks the current player to select his/her move.
void selectMove(int player) {
    bool selected = false;
    while (!selected) {
        printf("Player %d, select move (e.g. a2)> ", player);

        char row, col;
        bool goodInput = false;
        while (!goodInput) {
            row = inputRow();
            col = inputColumn();
            if (row != NULL && col != NULL && col != '\b') {
                goodInput = true;
                col--; // adjust column for 0-based index
            }
        }
        printf("\n");

        char mark = playerMarks[player-1];
        int success = set(row, col, mark);
        if (success == 0) {
            printf("That is not a valid move!\n");
        } else if (success == -1) {
            printf("That move is not possible!\n");
        } else {
            selected = true;
        }
    }
}

// Determines whether the player with the given mark has won.
bool won(int player) {
    char mark = playerMarks[player-1];
    int row, col;
    // check rows
    for (row = 0; row < boardDim; ++row) {
        bool rowWinner;
        for (col = 0; col < boardDim; ++col) {
            if (board[row][col] != mark) {
                rowWinner = false;
                break;
            } else {
                rowWinner = true;
            }
        }

        if (rowWinner) {
            return true;
        }
    }

    // check columns
    for (col = 0; col < boardDim; ++col) {
        bool colWinner;
        for (row = 0; row < boardDim; ++row) {
            if (board[row][col] != mark) {
                colWinner = false;
                break;
            } else {
                colWinner = true;
            }
        }

        if (colWinner) {
            return true;
        }
    }

    // check left-diagonal
    bool ldWinner;
    for (row = 0, col = 0; row < boardDim && col < boardDim; ++row, ++col) {
        if (board[row][col] != mark) {
            ldWinner = false;
            break;
        } else {
            ldWinner = true;
        }
    }
    
    if (ldWinner) {
        return true;
    }

    // check right-diagonal
    for (row = 0, col = boardDim - 1; row < boardDim && col >= 0; ++row, --col) {
        if (board[row][col] != mark) {
            return false;
        }
    }
    return true;
}

// Main entry point
int main(const char* cmdline)
{
    if (cmdline && strcmp(cmdline, "-h") == 0) {
        printf("     1   2   3\n");
        printf("   +---+---+---+\n");
        printf("a  | T | I | C |\n");
        printf("   +---+---+---+\n");
        printf("b  | T | A | C |\n");
        printf("   +---+---+---+\n");
        printf("c  | T | O | E |\n");
        printf("   +---+---+---+\n\n");

        printf("Tic-tac-toe (American English), noughts and crosses (British English), ");
        printf("or Xs and Os is a paper-and-pencil game for two players, X and O, who take turns ");
        printf("marking the spaces in a 3x3 grid. The player who succeeds in placing three of their ");
        printf("marks in a horizontal, vertical, or diagonal row is the winner. - Wikipedia\n\n");

        printf("This game implementation has been extended to allow bigger dimension grids, ");
        printf("as well as more players, but those numbers are hardcoded - see source for details.\n\n");
        return 0;
    }

    bool playing = true;
    int currentPlayer = 1;
    char yesno;

    reset();
    printGame();

    while (playing) {
        selectMove(currentPlayer);
        printGame();

        if (won(currentPlayer)) {
            printf("Player %d has won!\n", currentPlayer);
            playing = false;
        } else if (full()) {
            printf("It's a draw!\n");
            playing = false;
        } else {
            currentPlayer = nextPlayer(currentPlayer);
        }
        
        if (!playing) {
            printf("Play again? (y/n)> ");
            yesno = getch();
            printf("%c\n", yesno);

            if (yesno == 'y') {
                playing = true;
                reset();
            }
        }
    }

    return 0;
}