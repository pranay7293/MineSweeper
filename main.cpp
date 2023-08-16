#include <iostream>

using namespace std;

#define MAXSIDE 25
#define MAXMINES 99

class MineSweeper {
private:
  int side;
  int mines;
  char myBoard[MAXSIDE][MAXSIDE];
  char realBoard[MAXSIDE][MAXSIDE];
  int mine[MAXMINES][2];

public:
  // Function for game introduction message
  void GameIntro() {
    cout << endl;
    cout << "\033[38;5;202m  █▄ ▄█ ▀█▀ █▄  █ █▀▀▀  █▀▀▀ █ ▄ █ █▀▀▀ █▀▀▀"
            " █▀▀▄ █▀▀▀ █▀▀▄\033[0m"
         << endl;
    cout << "  █ █ █  █  █ █ █ █▀▀▀  ▀▀▄▄ █ █ █ █▀▀▀ █▀▀▀ █▄▄▀ █▀▀▀ █▄▄▀"
         << endl;
    cout << "\033[32m  █   █ ▄█▄ █  ▀█ █▄▄▄  ▄▄▄█ ▀█▀█▀ █▄▄▄ █▄▄▄ █   "
            " █▄▄▄ █ ▀▄\033[0m"
         << endl;
    cout << "  ----- --- ----- ----  ---- ----- ---- ---- ---- ---- ----"
         << endl;
    cout << endl;
    cout << " RULES: " << endl;
    cout
        << " 1. Board is divided into cells with mines randomly distributed\n "
           "2. To win, you will need to open all cells without triggering the "
           "mines\n 3. Number on the cell denotes the number of mines adjacent "
           "to it\n 4. Contains 3 Gameplay modes\n 5. Have fun and enjoy!\n"
        << endl;
    cout << "_ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _\n";
    cout << " *-----*-----*-----*-----*-----*-----*-----*-----*-----*-----* ";
    cout << endl << endl;
  }

  // Function to validate user input
  bool isValid(int _row, int _col) {
    return (((_row >= 0) && (_row < side)) && (_col >= 0) && (_col < side));
  }

  // Function to validate mine at position given
  bool isMine(int _row, int _col, char board[][MAXSIDE]) {
    return board[_row][_col] == '*';
  }

  // Function to print the board
  void printBoard(char board[][MAXSIDE]) {
    cout << "   ";
    for (int i = 0; i < side; i++) {
      cout << "  " << i << " ";
    }
    cout << "\n   ";
    for (int i = 0; i < side; i++) {
      cout << "+---";
    }
    cout << "+\n";
    for (int i = 0; i < side; i++) {
      cout << " " << i << " |";
      for (int j = 0; j < side; j++) {
        cout << " " << board[i][j] << " |";
      }
      cout << "\n   ";
      for (int j = 0; j < side; j++) {
        cout << "+---";
      }
      cout << "+\n";
    }
    cout << endl;
  }

  // For choosing difficulty level
  void ChooseSideMines() {
    int level;

    do {
      cout << "\n Choose Board Size (9 <= side < 25): ";
      cin >> side;

      if (side < 9 || side >= MAXSIDE) {
        cout << "Invalid side value. Please enter a value 9 <= side < 25."
             << endl;
        cin.clear();
      }
    } while (side < 9 || side >= MAXSIDE);

    cout << endl;
    cout << "\033[38;5;202m Enter '0' for " << side << "x" << side;
    cout << " board with " << side << " mines\033[0m" << endl;
    cout << " Enter '1' for " << side << "x" << side;
    cout << " board with " << 2 * side << " mines" << endl;
    cout << "\033[32m Enter '2' for " << side << "x" << side;
    cout << " board with " << 3 * side << " mines\033[0m" << endl;
    do {
      cout << "\n Choose the Game Play mode: ";
      cin >> level;

      if (level < 0 || level > 2) {
        cout << "Invalid input. Please enter '0', '1', or '2'." << endl;
        cin.clear();
      }
    } while (level < 0 || level > 2);
    cout << endl;

    if (level == 0) {
      mines = 1 * side;
    } else if (level == 1) {
      mines = 2 * side;
    } else if (level == 2) {
      mines = 3 * side;
    }
  }

  // Function to initialize the boards
  void InitializeBoards() {
    for (int i = 0; i < side; i++) {
      for (int j = 0; j < side; j++) {
        myBoard[i][j] = realBoard[i][j] = '-';
      }
    }
  }

  // Function for placing mines
  void PlaceMines() {
    bool mark[side * side];
    for (int i = 0; i < side * side; i++) {
      mark[i] = false;
    }
    srand(time(0));

    int i = 0;
    while (i < mines) {
      int random = rand() % (side * side);
      int x = random / side;
      int y = random % side;

      if (mark[random] == false) {
        mine[i][0] = x;
        mine[i][1] = y;
        realBoard[mine[i][0]][mine[i][1]] = '*';
        mark[random] = true;
        i++;
      }
    }
  }

  // Function for counting adjacent mines
  int CountAdjacentMines(int row, int col) {
    int count = 0;

    if (isValid(row, col - 1)) {
      if (isMine(row, col - 1, realBoard)) {
        count++;
      }
    }
    if (isValid(row, col + 1)) {
      if (isMine(row, col + 1, realBoard)) {
        count++;
      }
    }
    if (isValid(row + 1, col)) {
      if (isMine(row + 1, col, realBoard)) {
        count++;
      }
    }
    if (isValid(row - 1, col)) {
      if (isMine(row - 1, col, realBoard)) {
        count++;
      }
    }
    if (isValid(row - 1, col - 1)) {
      if (isMine(row - 1, col - 1, realBoard)) {
        count++;
      }
    }
    if (isValid(row + 1, col + 1)) {
      if (isMine(row + 1, col + 1, realBoard)) {
        count++;
      }
    }
    if (isValid(row + 1, col - 1)) {
      if (isMine(row + 1, col - 1, realBoard)) {
        count++;
      }
    }
    if (isValid(row - 1, col + 1)) {
      if (isMine(row - 1, col + 1, realBoard)) {
        count++;
      }
    }
    return count;
  }

  // Function for gameloop
  bool Gameloop(int row, int col, int *movesLeft) {
    // Base case
    if (myBoard[row][col] != '-')
      return false;

    if (realBoard[row][col] == '*') {
      myBoard[row][col] = '*';

      for (int i = 0; i < mines; i++) {
        myBoard[mine[i][0]][mine[i][1]] = '*';
      }

      printBoard(myBoard);

      cout << "        YOU HIT A MINE..!" << endl << endl;
      cout << "   █▄█ █▀█ █ █  █   █▀█ █▀▀ ▀█▀ \n";
      cout << "    █  █▄█ █▄█  █▄▄ █▄█ ▄▄█  █  ▄ ▄ ▄ \n";
      cout << endl;
      return true;
    } else {
      int count = CountAdjacentMines(row, col);
      (*movesLeft)--;

      myBoard[row][col] = count + '0';

      // If no mines are nearby, we recur for all adjacent 8 cells
      if (!count) {

        if (isValid(row, col - 1)) {
          if (isMine(row, col, realBoard) == false) {
            Gameloop(row, col - 1, movesLeft);
          }
        }
        if (isValid(row, col + 1)) {
          if (isMine(row, col + 1, realBoard) == false) {
            Gameloop(row, col + 1, movesLeft);
          }
        }
        if (isValid(row + 1, col)) {
          if (isMine(row + 1, col, realBoard) == false) {
            Gameloop(row + 1, col, movesLeft);
          }
        }
        if (isValid(row - 1, col)) {
          if (isMine(row - 1, col, realBoard) == false) {
            Gameloop(row - 1, col, movesLeft);
          }
        }
        if (isValid(row - 1, col + 1)) {
          if (isMine(row - 1, col + 1, realBoard) == false) {
            Gameloop(row - 1, col + 1, movesLeft);
          }
        }
        if (isValid(row - 1, col - 1)) {
          if (isMine(row - 1, col - 1, realBoard) == false) {
            Gameloop(row - 1, col - 1, movesLeft);
          }
        }
        if (isValid(row + 1, col - 1)) {
          if (isMine(row + 1, col - 1, realBoard) == false) {
            Gameloop(row + 1, col - 1, movesLeft);
          }
        }
        if (isValid(row + 1, col + 1)) {
          if (isMine(row + 1, col + 1, realBoard) == false) {
            Gameloop(row + 1, col + 1, movesLeft);
          }
        }
      }
      return false;
    }
  }

  // Function to make a move
  void MakeAMove(int *x, int *y) {
    cout << " Enter the x and y values: ";
    cin >> *x >> *y;
    cout << endl;
    cout << "_ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _\n";
    cout << " *-----*-----*-----*-----*-----*-----*-----*-----*-----*-----* ";
    cout << endl << endl;
  }

  // Function to find mine index
  int FindMineIndex(int row, int col) {
    for (int i = 0; i < mines; i++) {
      if (mine[i][0] == row && mine[i][1] == col)
        return i;
    }
  }

  // Function to replace mine
  void ReplaceMine(int row, int col) {
    for (int i = 0; i < side; i++) {
      for (int j = 0; j < side; j++) {
        if (realBoard[i][j] != '*') {
          realBoard[i][j] = '*';
          int mineIndex = FindMineIndex(row, col);
          mine[mineIndex][0] = i;
          mine[mineIndex][1] = j;
          realBoard[row][col] = '-';
          return;
        }
      }
    }
  }
  // Function for gameplay
  void PlayMineSweeper() {
    bool gameOver = false;

    int movesLeft = side * side - mines;
    int x, y;

    InitializeBoards();

    PlaceMines();

    int moveIndex = 0;
    while (!gameOver) {
      cout << " Current board status: " << endl;
      printBoard(myBoard);
      MakeAMove(&x, &y);

      // If the first move is a mine
      if (moveIndex == 0 && isMine(x, y, realBoard))
        ReplaceMine(x, y);

      moveIndex++;

      gameOver = Gameloop(x, y, &movesLeft);

      if (!gameOver && movesLeft == 0) {
        cout << "        CONGRATULATIONS..!" << endl << endl;
        cout << "   █▄█ █▀█ █ █   █ █ █ █▀█ █▄ █ \n";
        cout << "    █  █▄█ █▄█   ▀▄▀▄▀ █▄█ █ ▀█ ▄ ▄ ▄\n";
        cout << endl;
        gameOver = true;
      }
    }
  }
};
int main() {
  MineSweeper game;
  game.GameIntro();
  game.ChooseSideMines();
  game.PlayMineSweeper();
  return 0;
}
