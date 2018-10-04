#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <time.h>
#include <stdlib.h>

using namespace std;

class Game2048
{
public:
    enum DIRECTION { LEFT, RIGHT, UP, DOWN };

    Game2048(): board() {}

    void clearBoard()
    {
        for (int row = 0; row < 4; row++)
            for (int col = 0; col < 4; col++)
                board[row][col] = 0;

        // Starting board has two 2s - one at [1,1] and the other at [2,3]
        // TODO: Randomized position?
        board[1][1] = 2;
        board[1][3] = 2;
    }

    //
    // Modify this method as you see fit
    // Things to remember:
    //    - Sliding
    //    - Merging
    //    - Spawning a new 2 (only after valid moves)
    //    - Detecting the end of the game
    //
    void PlayGame()
    {
        clearBoard();

        cout << "Start 2048" << endl;
        while (true)
        {
            // Inside of loop: a single turn takes place
            render();
            DIRECTION nextMove = getNextMove();

            // TODO: Call performAction here.
            // if the returned result is false, means there's no possible move. we can break
            if (!performAction(nextMove)) {
              break;
            }

        }
        render();
        cout << "Game over!" << endl;
    }

private:
    /**
    * Peforming actions.
    **/
    bool performAction(DIRECTION nextMove) {
      if (slideAndMerge(nextMove) ) {
          spawnNewTwo();
      }
      return checkState();
    }

    void spawnNewTwo() {
      bool found = false;
      vector<int> possiblePlaceX;
      vector<int> possiblePlaceY;

      for (int r = 0; r < length; r++) {
        for (int c = 0; c < length; c++) {
          if (board[r][c] == 0) {
            possiblePlaceX.push_back(r);
            possiblePlaceY.push_back(c);
          }
        }
      }

      int randomized = getNextRandom(0, length);

      board[possiblePlaceX[randomized]][possiblePlaceY[randomized]] = 2;
    }

    /**
    * slideAndMerge
    * Helper method to perform sliding and merging.
    **/

    bool slideAndMerge(DIRECTION nextMove) {
      bool merged = true;
      switch (nextMove){
        case UP:
          for (int c = 0; c < length; c++) {

            // first, move everything , reduce space

            for (int i = 0; i < length;i++) {
              if (board[i][c] > 0) {
                int currZeroIndex = i;
                while ( currZeroIndex > 0 && board[currZeroIndex-1][c] == 0) {
                  currZeroIndex -=1;
                }

                if (currZeroIndex != i) {
                  board[currZeroIndex][c] = board[i][c];
                  board[i][c]= 0;
                }
              }
            }


            // second, attempt to merge everything
            for (int i = 0; i < length - 1; i++) {
              //1. first condition: when front and end is the same. Then we merge
              if (board[i+1][c] == board[i][c] && board[i][c] > 0) {
                board[i][c] += board[i+1][c];
                // turns 0
                board[i+1][c] = 0;
                merged = true;
              }
              // 2. else if
              else if (board[i][c] == 0 && board[i+1][c] > 0) {
                board[i][c] = board[i+1][c];
                board[i+1][c] = 0;
              }
            }

          }


          break;

        case DOWN:
          for (int c = 0; c < length; c++) {

            // first, move everything , reduce space

            for (int i = length - 1; i >= 0 ;i--) {
              if (board[i][c] > 0) {
                int currZeroIndex = i;
                while ( currZeroIndex < length -1 && board[currZeroIndex+1][c] == 0) {
                  currZeroIndex +=1;
                }

                if (currZeroIndex != i) {
                  board[currZeroIndex][c] = board[i][c];
                  board[i][c]= 0;
                }
              }
            }


            // second, attempt to merge everything
            for (int i = length - 1; i > 0; i--) {
              //1. first condition: when front and end is the same. Then we merge
              if (board[i-1][c] == board[i][c] && board[i][c] > 0) {
                board[i][c] += board[i-1][c];
                // turns 0
                board[i-1][c] = 0;
                merged = true;
              }
              // 2. else if
              else if (board[i][c] == 0 && board[i-1][c] > 0) {
                board[i][c] = board[i-1][c];
                board[i-1][c] = 0;
              }
            }

          }

          break;

        case LEFT:

           for (int r = 0; r < length; r++) {

             // first, move everything , reduce space

             for (int i = 0; i < length;i++) {
               if (board[r][i] > 0) {
                 int currZeroIndex = i;
                 while ( currZeroIndex > 0 && board[r][currZeroIndex-1] == 0) {
                   currZeroIndex -=1;
                 }

                 if (currZeroIndex != i) {
                   board[r][currZeroIndex] = board[r][i];
                   board[r][i]= 0;
                 }
               }
             }


             // second, attempt to merge everything
             for (int i = 0; i < length - 1; i++) {
               //1. first condition: when front and end is the same. Then we merge
               if (board[r][i + 1] == board[r][i] && board[r][i] > 0) {
                 board[r][i] += board[r][i +1];
                 // turns 0
                 board[r][i +1] = 0;
                 merged = true;
               }
               // 2. else if
               else if (board[r][i] == 0 && board[r][i+1] > 0) {
                 board[r][i] = board[r][i+1];
                 board[r][i+1] = 0;
               }
             }

           }
          break;

        case RIGHT:
          for (int r = 0; r < length; r++) {

            // first, move everything , reduce space

            for (int i = length - 1; i >= 0 ;i--) {
              if (board[r][i] > 0) {
                int currZeroIndex = i;
                while ( currZeroIndex < length -1 && board[r][currZeroIndex+1] == 0) {
                  currZeroIndex +=1;
                }

                if (currZeroIndex != i) {
                  board[r][currZeroIndex] = board[r][i];
                  board[r][i]= 0;
                }
              }
            }


            // second, attempt to merge everything
            for (int i = length - 1; i > 0; i--) {
              //1. first condition: when front and end is the same. Then we merge
              if (board[r][i - 1] == board[r][i] && board[r][i] > 0) {
                board[r][i] += board[r][i -1];
                // turns 0
                board[r][i -1] = 0;
                merged = true;
              }
              // 2. else if
              else if (board[r][i] == 0 && board[r][i-1] > 0) {
                board[r][i] = board[r][i-1];
                board[r][i-1] = 0;
              }
            }

          }

          break;

        // don't think there's possibility that the switch will reach here, but anyways
        default:
          cout <<"2048: Sorry, something went wrong. Please try again :(\n";
          return merged;

      }

      return merged;
    }

    bool checkState() {
      int possibleMove = 0;
      // 1. check 0
      for (int r = 0; r < length; r++) {
        for (int c = 0; c < length; c++) {
          if (board[r][c] == 0) return true;
          // 2. check if there's possible move

          // top
          if ( (r > 0) && board[r-1][c] == board[r][c]) {
            possibleMove += 1;
          }

          // left
          if ( (c > 0) && board[r][c-1] == board[r][c]) {
            possibleMove += 1;
          }

          // right
          if ( (c < length -1) && board[r][c+1] == board[r][c]) {
            possibleMove += 1;
          }

          // down
          if ( (r < length -1) && board[r+1][c] == board[r][c]) {
            possibleMove += 1;
          }
        }
      }

      if (possibleMove > 0) return true;

      return false;
    }


    /*****************************************************************************/

    /**
     * Get a random integer between "min" and "max" (including min, excluding max)
     **/
    int getNextRandom(int min, int max)
    {
        return (rand() % (max - min)) + min;
    }

    void render()
    {
        cout << "---------------------" << endl;
        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                cout << "|" << right << setw(4) << board[row][col];
            }
            cout << "|" << endl << "---------------------" << endl;
        }
    }

    /**
    * getNextMove
    * : a helper method that gets move from user's input.
    **/
    DIRECTION getNextMove()
    {
        cout << "Where would you like to move? (l)eft, (r)ight, (u)p, or (d)own: ";
        char m = 0;
        cin >> m;
        switch (m)
        {
            case 'l': case 'L': return LEFT;
            case 'r': case 'R': return RIGHT;
            case 'u': case 'U': return UP;
            case 'd': case 'D': return DOWN;
            default: cout << "Invalid input!" << endl; return getNextMove();
        }
    }

private:
    unsigned int board[4][4];
    int length = 4;
};

void printLine(string str) {
    replace(str.begin(), str.end(), '\n', ' ');
    cout << str << endl;
}

int main(int argc, char* argv[])
{
    srand(NULL); // Seed the random number generator predictably, to give consistent results. Not actually "random"

    Game2048 b;
    b.PlayGame();

    return 0;
}
