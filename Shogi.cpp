#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <stdio.h>
using namespace std;
/*
  To compile: g++ Shogi.cpp
  To run: ./a.out
*/
class Shogi
{
    public:
    
        int row;
        int col;
        int moveRow;
        int moveCol;
        int count1;
        int count2;
        int index;
        string piece;
        string turn;
        string player1Name;
        string player2Name;
        bool checkmate;
        bool notObstacles;
        bool correctWord;
        list<string> blackPieces;
        list<string> whitePieces;

        string grid[9][9] = {{"\x1b[31m L \x1b[0m", "\x1b[31m N \x1b[0m", "\x1b[31m S \x1b[0m", "\x1b[31m G \x1b[0m", "\x1b[31m K \x1b[0m", "\x1b[31m G \x1b[0m", "\x1b[31m S \x1b[0m", "\x1b[31m N \x1b[0m", "\x1b[31m L \x1b[0m"},
                             {"   ", "\x1b[31m B \x1b[0m", "   ", "   ", "   ", "   ", "   ", "\x1b[31m R \x1b[0m", "   "},
                             {"\x1b[31m P \x1b[0m", "\x1b[31m P \x1b[0m", "\x1b[31m P \x1b[0m", "\x1b[31m P \x1b[0m", "\x1b[31m P\x1b[0m ", "\x1b[31m P \x1b[0m", "\x1b[31m P \x1b[0m", "\x1b[31m P \x1b[0m", "\x1b[31m P \x1b[0m"},
                             {"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   "},
                             {"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   "},
                             {"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   "},
                             {"\x1b[34m P \x1b[0m", "\x1b[34m P \x1b[0m", "\x1b[34m P \x1b[0m", "\x1b[34m P \x1b[0m", "\x1b[34m P\x1b[0m ", "\x1b[34m P \x1b[0m", "\x1b[34m P \x1b[0m", "\x1b[34m P \x1b[0m", "\x1b[34m P \x1b[0m"},
                             {"   ", "\x1b[34m B \x1b[0m", "   ", "   ", "   ", "   ", "   ", "\x1b[34m R \x1b[0m", "   "},
                             {"\x1b[34m L \x1b[0m", "\x1b[34m N \x1b[0m", "\x1b[34m S \x1b[0m", "\x1b[34m G \x1b[0m", "\x1b[34m K \x1b[0m", "\x1b[34m G \x1b[0m", "\x1b[34m S \x1b[0m", "\x1b[34m N \x1b[0m", "\x1b[34m L \x1b[0m"}};

        Shogi()
        {
            row = 0;
            col = 0;
            moveRow = 0;
            moveCol = 0;
            count1 = 0;
            count2 = 0;
            index = 0;
            turn = "black";
            piece = "";
            notObstacles = false;
            checkmate = false;
            correctWord = true;
            cout << "Player 1, please enter your name." << endl;
            cin >> player1Name;

            cout << "Player 2, please enter your name." << endl;
            cin >> player2Name;
            
        }
        void prompt()
        {
            cout << endl;

            if (turn == "black")
            {
                cout << "It is your turn now, " << player1Name << endl;
            }
            else
            {
                cout << "It is your turn now, " << player2Name << endl;
            }
          

            correctWord = true;
            do
            {
                cout << "What piece would you like to move?" << endl;
                cin >> piece;
                for (int i = 0; i < piece.size(); i ++)
                {
                    tolower(piece.at(i));
                }
                if (piece != "pawn" && piece != "rook" && piece != "bishop" && piece != "king" && piece != "lance" && piece != "knight" && piece != "silver" && piece != "silver general" && piece != "gold" && piece != "gold general")
                {
                    correctWord = false;
                }
                else
                {
                    correctWord = true;
                }
            } while (!correctWord);
            bool inRange = true;
            do
            {
                cout << "Where is the " << piece << "? (Row, Column)" << endl;
                cin >> row >> col;
                if ((row >= 1 && row <= 9) && (col >= 1 && col <= 9))
                {
                    inRange = true;
                }
                else
                {
                    inRange = false;
                }
            } while (!inRange);
            inRange = true;
            do
            {
                cout << "Where would you like to move the " << piece << "? (Row, Column)" << endl;
                cin >> moveRow >> moveCol;
                if ((moveRow >= 1 && moveRow <= 9) && (moveCol >= 1 && moveCol <= 9))
                {
                    inRange = true;
                }
                else
                {
                    inRange = false;
                }
            } while (!inRange);
            row = fixRow(row);
            col = fixCol(col);
            moveRow = fixMoveRow(moveRow);
            moveCol = fixMoveCol(moveCol);
            while (!canMove(piece, row, col, moveRow, moveCol))
            {
                cout << "(" << moveRow + 1 << ", " << moveCol + 1 << ") is not a valid move. Please enter another coordinate." << endl;
                cin >> moveRow >> moveCol;
            }
            printBoard();
        }
        int fixRow(int row)
        {
            return row - 1;
            
        }
        int fixCol(int col)
        {
            return col - 1;
        }
        int fixMoveRow(int row)
        {
            return row - 1;
        }
        int fixMoveCol(int col)
        {
            return col - 1;
        }
        bool canMove(string piece, int row, int col, int moveRow, int moveCol)
        {
            if (grid[moveRow][moveCol] != "   ")
            {
                if (turn == "black" && grid[moveRow][moveCol].at(3) == '4')
                {
                    return false;
                }
                if (turn == "white" && grid[moveRow][moveCol].at(3) == '1')
                {
                    return false;
                }
            }
            if (grid[row][col] != "   ")
            {
                if (piece == "lance")
                {
                    if (grid[row][col] == "\x1b[31m L \x1b[0m")
                    {
                        for (int i = row + 1; i <= moveRow; i++)
                        {
                            if (grid[i][col] == ("   "))
                            {
                                notObstacles = true;
                            }
                            else
                            {
                                notObstacles = false;
                                break;
                            }
                        }
                        if (notObstacles && grid[moveRow][moveCol].find("\x1b[31m") == false)
                        {
                            grid[moveRow][moveCol] = "\x1b[31m L \x1b[0m";
                            grid[row][col] = "   ";
                            return true;
                        }
                    }
                    else if (grid[row][col] == "\x1b[34m L \x1b[0m")
                    {
                        for (int i = row - 1; i >= moveRow; i--)
                        {
                            cout << grid[i][col];
                            if (grid[i][col] == ("   "))
                            {
                                notObstacles = true;
                            }
                            else
                            {
                                notObstacles = false;
                                break;
                            }
                        }
                        if (notObstacles)
                        {
                            grid[moveRow][moveCol] = "\x1b[34m L \x1b[0m";
                            grid[row][col] = "   ";
                            return true;
                        }
                    }
                }
                else if (piece == "pawn")
                {
                    if (grid[row][col] == "\x1b[31m P \x1b[0m")
                    {
                        if (row == moveRow - 1)
                        {
                            grid[moveRow][moveCol] = "\x1b[31m P \x1b[0m";
                            grid[row][col] = "   ";
                            return true;
                        }
                    }
                    else if (grid[row][col] == "\x1b[34m P \x1b[0m")
                    {
                        if (row == moveRow +  1)
                        {
                            grid[moveRow][moveCol] = "\x1b[34m P \x1b[0m";
                            grid[row][col] = "   ";
                            return true;
                        }
                    }
                }
                else if (piece == "knight")
                {
                    if (grid[row][col] == "\x1b[34m N \x1b[0m")
                    {
                        if (row - 2 == moveRow && (col + 1 == moveCol || col - 1 == moveCol))
                        {
                            if (grid[row][col].at(3) == '4')
                            {
                                grid[moveRow][moveCol] = "\x1b[34m N \x1b[0m";
                                grid[row][col] = "   ";
                                return true;
                            }
                        }
                    }
                    else if (grid[row][col] == "\x1b[31m N \x1b[0m")
                    {
                        if (row + 2 == moveRow && (col + 1 == moveCol || col - 1 == moveCol))
                        {
                            if (grid[row][col].at(3) == '2')
                            {
                                grid[moveRow][moveCol] = "\x1b[31m N \x1b[0m";
                                grid[row][col] = "   ";
                            }
                            return true;
                        }
                    }
                }
                else if (piece == ("silver") || piece == ("silver general"))
                {
                    if (grid[row][col] == "\x1b[34m S \x1b[0m")
                    {

                        if (row - 1 == moveRow && (col - 1 == moveCol || col == moveCol || col + 1 == moveCol))
                        {
                            grid[moveRow][moveCol] = "\x1b[34m S \x1b[0m";
                            grid[row][col] = "   ";
                            return true;
                        }
                        else if (row + 1 == moveRow && (col - 1 == moveCol || col + 1 == moveCol))
                        {
                            grid[moveRow][moveCol] = "\x1b[34m S \x1b[0m";
                            grid[row][col] = "   ";
                            return true;
                        }
                    }
                    else if (grid[row][col] == "\x1b[31m S \x1b[0m")
                    {

                        if (row + 1 == moveRow && (col - 1 == moveCol || col == moveCol || col + 1 == moveCol))
                        {
                            grid[moveRow][moveCol] = "\x1b[31m S \x1b[0m";
                            grid[row][col] = "   ";
                            return true;
                        }
                        else if (row - 1 == moveRow && (col - 1 == moveCol || col + 1 == moveCol))
                        {
                            grid[moveRow][moveCol] = "\x1b[31m S \x1b[0m";
                            grid[row][col] = "   ";
                            return true;
                        }
                    }
                }
                else if (piece == ("gold") || piece == ("gold general"))
                {
                    if (grid[row][col] == "\x1b[34m G \x1b[0m")
                    {
                        if (row - 1 == moveRow && (col - 1 == moveCol || col == moveCol || col + 1 == moveCol))
                        {
                            grid[moveRow][moveCol] = "\x1b[34m G \x1b[0m";
                            grid[row][col] = "   ";
                            return true;
                        }
                        else if (row + 1 == moveRow && col == moveCol)
                        {
                            grid[moveRow][moveCol] = "\x1b[34m G \x1b[0m";
                            grid[row][col] = "   ";
                            return true;
                        }
                        else if (row == moveRow && (col - 1 == moveCol || col + 1 == moveCol))
                        {
                            grid[moveRow][moveCol] = "\x1b[34m G \x1b[0m";
                            grid[row][col] = "   ";
                            return true;
                        }
                    }
                    else if (grid[row][col] == "\x1b[34m G \x1b[0m")
                    {
                        if (row + 1 == moveRow && (col - 1 == moveCol || col == moveCol || col + 1 == moveCol))
                        {
                            grid[moveRow][moveCol] = "\x1b[31m S \x1b[0m";
                            grid[row][col] = "   ";
                            return true;
                        }
                        else if (row - 1 == moveRow && col == moveCol)
                        {
                            grid[moveRow][moveCol] = "\x1b[31m S \x1b[0m";
                            grid[row][col] = "   ";
                            return true;
                        }
                        else if (row == moveRow && (col - 1 == moveCol || col + 1 == moveCol))
                        {
                            grid[moveRow][moveCol] = "\x1b[31m G \x1b[0m";
                            grid[row][col] = "   ";
                            return true;
                        }
                    }
                }
                else if (piece == ("king"))
                {
                    if (grid[row][col] == "\x1b[34m K \x1b[0m")
                    {
                        grid[moveRow][moveCol] = "\x1b[34m K \x1b[0m";
                        grid[row][col] = "   ";
                        return true;
                    }
                    else if (grid[row][col] == "\x1b[31m K \x1b[0m")
                    {
                        grid[moveRow][moveCol] = "\x1b[31m K \x1b[0m";
                        grid[row][col] = "   ";
                        return true;
                    }
                }
                else if (piece == ("rook"))
                {
                    if (row == moveRow)
                    {
                        if (moveCol > col)
                        {
                            for (int i = col + 1; i <= moveCol; i++)
                            {
                                if (grid[row][i] == "   ")
                                {
                                    notObstacles = true;
                                }
                                else if (grid[row][i].at(3) == '4')
                                {
                                    notObstacles = false;
                                    break;
                                }
                                else if (grid[row][i].at(3) == '1')
                                {
                                    if (i == moveCol)
                                    {
                                        if (turn == "black")
                                            grid[moveRow][moveCol] = "\x1b[34m R \x1b[0m";
                                        else
                                            grid[moveRow][moveCol] = "\x1b[31m R \x1b[0m";
                                        grid[row][col] = "   ";
                                        return true;
                                    }
                                    else
                                    {
                                        return false;
                                    }
                                }
                            }
                        }
                        else if (moveCol < col)
                        {
                            for (int i = col - 1; i >= moveCol; i--)
                            {
                                if (grid[row][i] == "   ")
                                {
                                    notObstacles = true;
                                }
                                else if (grid[row][i].at(3) == '4')
                                {
                                    notObstacles = false;
                                    break;
                                }
                                else if (grid[row][i].at(3) == '1')
                                {
                                    if (i == moveCol)
                                    {
                                        if (turn == "black")
                                            grid[moveRow][moveCol] = "\x1b[34m R \x1b[0m";
                                        else
                                            grid[moveRow][moveCol] = "\x1b[31m R \x1b[0m";
                                        grid[row][col] = "   ";
                                        return true;
                                    }
                                    else
                                    {
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        if (moveRow > row)
                        {
                            for (int i = row + 1; i <= moveRow; i++)
                            {
                                if (grid[i][col] == "   ")
                                {
                                    notObstacles = true;
                                }
                                else if (grid[i][col].at(3) == '4')
                                {
                                    notObstacles = false;
                                    break;
                                }
                                else if (grid[i][col].at(3) == '1')
                                {
                                    if (i == moveRow)
                                    {
                                        if (turn == "black")
                                            grid[moveRow][moveCol] = "\x1b[34m R \x1b[0m";
                                        else
                                            grid[moveRow][moveCol] = "\x1b[31m R \x1b[0m";
                                        grid[row][col] = "   ";
                                        return true;
                                    }
                                    else
                                    {
                                        return false;
                                    }
                                }
                            }
                        }
                        else if (moveRow < row)
                        {
                            for (int i = row; i >= moveRow; i--)
                            {
                                if (grid[row][i] == "   ")
                                {
                                    notObstacles = true;
                                }
                                else if (grid[row][i].at(3) == '4')
                                {
                                    notObstacles = false;
                                    break;
                                }
                                else if (grid[row][i].at(3) == '1')
                                {
                                    if (i == moveCol)
                                    {
                                        if (turn == "black")
                                            grid[moveRow][moveCol] = "\x1b[34m R \x1b[0m";
                                        else
                                            grid[moveRow][moveCol] = "\x1b[31m R \x1b[0m";
                                        grid[row][col] = "   ";
                                        return true;
                                    }
                                    else
                                    {
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                    cout << notObstacles;
                    if (notObstacles)
                    {
                        if (turn == "black")
                            grid[moveRow][moveCol] = "\x1b[34m R \x1b[0m";
                        else
                            grid[moveRow][moveCol] = "\x1b[31m R \x1b[0m";
                        grid[row][col] = "   ";
                        return true;
                    }
                }
                else if (piece == ("bishop"))
                {
                    notObstacles = checkBishopBounds(row, col, moveRow, moveCol);
                    if (grid[row][col] == "\x1b[34m B \x1b[0m")
                    {
                        if (notObstacles)
                        {
                            grid[moveRow][moveCol] = "\x1b[34m B \x1b[0m";
                            grid[row][col] = "   ";
                            return true;
                        }
                    }
                    else if (grid[row][col] == "\x1b[31m B \x1b[0m")
                    {
                        if (notObstacles)
                        {
                            grid[moveRow][moveCol] = "\x1b[31m B \x1b[0m";
                            grid[row][col] = "   ";
                            return true;
                        }
                    }
                }
                
            }
            if (turn == "black")
            {
                turn = "white";
            }
            else
            {
                turn = "black";
            }
            return false;
        }
        bool checkBishopBounds (int row, int col, int moveRow, int movecol)
        {
            if (moveRow >= 0 && moveCol >= 0 && moveRow < row && moveCol < col)
            {
                while (count1 != moveRow && count2 != moveCol)
                {
                    count1 = row - 1;
                    count2 = col - 1;
                    if (grid[count1][count2] == "   ")
                    {
                        notObstacles = true;
                    }
                    else
                    {
                        notObstacles = false;
                        break;
                    }
                    if (notObstacles)
                    {
                        return true;
                    }
                }
            }
            else if (moveRow >= 0 && moveCol < 9 && moveRow < row && moveCol > col)
            {
                while (count1 != moveRow && count2 != moveCol)
                {
                    count1 = row - 1;
                    count2 = col + 1;
                   if (grid[count1][count2] == "   ")
                    {
                        notObstacles = true;
                    }
                    else
                    {
                        notObstacles = false;
                        break;
                    }
                    if (notObstacles)
                    {
                        return true;
                    }
                }
            }
            else if (moveRow < 9 && moveCol >= 0 && moveRow > row && moveCol < col)
            {
                while (count1 != moveRow && count2 != moveCol)
                {
                    count1 = row + 1;
                    count2 = col - 1;
                    if (grid[count1][count2] == "   ")
                    {
                        notObstacles = true;
                    }
                    else
                    {
                        notObstacles = false;
                        break;
                    }
                    if (notObstacles)
                    {
                        return true;
                    }
                }
            }
            else if (moveRow < 9 && moveCol < 9 && moveRow > row && moveCol > col)
            {
                while (count1 != moveRow && count2 != moveCol)
                {
                    count1 = row + 1;
                    count2 = col + 1;
                    if (grid[count1][count2] == "   ")
                    {
                        notObstacles = true;
                    }
                    else
                    {
                        notObstacles = false;
                        break;
                    }
                    if (notObstacles)
                    {
                        return true;
                    }
                }
            }
            return false;
        }
        void printBoard()
        {
            cout << endl << player2Name << endl;
            for (int i = 0; i < 9; i ++)
            {
                cout << "  ";
                for (int j = 0; j < 9; j++)
                {
                    if ((i == 3 || i == 6) && (j == 3 || j == 6))
                    {
                        cout << "*---";
                    }
                    else
                    {
                       cout << "|---";
                    }
                }
                cout << "|" << endl;
                cout << i + 1 << " ";
                for (int j = 0; j < 9; j ++)
                {
                    cout << "|" << grid[i][j];
                }
                cout << "|" << endl;
            }
            cout << "  ";
            for (int i = 0; i < 9; i ++)
            {
                cout << "|---";
            }
            cout << "|" << endl;
            cout << "    ";
            for (int i = 1; i <= 9; i ++)
            {
                cout << i << "   ";
            }
            cout << endl;
            cout << player1Name << endl;
        }
};

int main()
{
    Shogi game;
    
    game.printBoard();
    game.prompt();
    
    return 0;
}