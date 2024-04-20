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
    bool hasPieces;
    int hasKing;
    string letter;
    int blackPieces[7] = {0, 0, 0, 0, 0, 0, 0};
    int whitePieces[7] = {0, 0, 0, 0, 0, 0, 0};
    string grid[9][9] = {{"\x1b[31m L \x1b[0m", "\x1b[31m N \x1b[0m", "\x1b[31m S \x1b[0m", "\x1b[31m G \x1b[0m", "\x1b[31m K \x1b[0m", "\x1b[31m G \x1b[0m", "\x1b[31m S \x1b[0m", "\x1b[31m N \x1b[0m", "\x1b[31m L \x1b[0m"},
                         {"   ", "\x1b[31m R \x1b[0m", "   ", "   ", "   ", "   ", "   ", "\x1b[31m B \x1b[0m", "   "},
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
        cout << "|-----------------------|" << endl;
        cout << "|         SHOGI         |" << endl;
        cout << "|                       |" << endl;
        cout << "|         Play (p)      |" << endl;
        cout << "|         Rules(r)      |" << endl;
        cout << "|                       |" << endl;
        cout << "|-----------------------|" << endl
             << endl;
        do
        {
            cout << "Please enter a letter of the option" << endl;
            getline(cin, letter);
            for (int i = 0; i < letter.length(); i++)
            {
                letter.at(i) = tolower(letter.at(i));
            }
            if (letter == "r")
            {
                cout << "Shogi is a 2 player game whom one wins by capturing the opponent's king" << endl;
                cout << "The player playing blue will start first, while the player with the red pieces goes second" << endl;
                cout << "The following description are what the pieces can do when not promoted and promoted:" << endl << endl;
                cout << "These are how the pieces move when not promoted:" << endl;
                cout << "Name          Symbol          Description" << endl;
                cout << "Pawn           (P):           Can only move 1 space forward" << endl;
                cout << "Lance          (L):           Can only move vertically" << endl;
                cout << "Knight         (N):           Can only move 2 spaces forward and 1 space to the left or right" << endl;
                cout << "Silver General (S):           Can only move 1 spot diagonally or 1 spot forward:" << endl;
                cout << "Gold General   (G):           Can only move 1 spot around itself except the diagonals behind it" << endl;
                cout << "Bishop         (B):           Can only move diagonally" << endl;
                cout << "Rook           (R):           Can move vertically and horizontally" << endl;
                cout << "King           (K):           Can only move one space around itself" << endl;
                cout << endl;
                cout << "These are how pieces move when promoted: " << endl;
                cout << "Name          Symbol        Description" << endl;
                cout << "Rook           (R):         Can move vertically, horizontally and one step diagonally" << endl;
                cout << "Bishop         (B):         Can move diagonally and 1 step horizontally or vertically" << endl;
                cout << "All the other pieces except the King (K) and the Gold general (G) can be promoted to Gold Generals" << endl;
            }
            else if (letter == "p")
            {
                cout << "Player 1, please enter your name." << endl;
                getline(cin, player1Name);
                cout << "Player 2, please enter your name." << endl;
                getline(cin, player2Name);
            }
        } while (letter != "p");
    }
    void prompt()
    {
        cout << endl;
        do
        {
            askMovement(turn);
            turn = "white";
            if (checkKing(turn) == 1)
            {
                askMovement(turn);
                turn = "black";
            }
        } while (checkKing(turn) == 1);
        if (turn == "black")
        {
            cout << "Congratulations, " << player2Name << "! You have won!" << endl;
        }
        else
        {
            cout << "Congratulations, " << player1Name << "! You have won!" << endl;
        }
    }
    bool checkKing(string turn)
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (turn == "white")
                {
                    if (grid[i][j] == "\x1b[31m K \x1b[0m")
                    {
                        return 1;
                    }
                }
                else
                {
                    if (grid[i][j] == "\x1b[34m K \x1b[0m")
                    {
                        return 1;
                    }
                }
            }
        }
        return 0;
    }
    void askMovement(string turn)
    {
        correctWord = true;
        bool extra = false;
        bool move = false;
        do
        {
            printBoard();
            if (turn == "black")
            {
                cout << "It is your turn now, " << player1Name << endl;
            }
            else
            {
                cout << "It is your turn now, " << player2Name << endl;
            }
            for (int i = 0; i < 7; i++)
            {
                if (turn == "black")
                {
                    if (blackPieces[i] == 0)
                    {
                        extra = false;
                    }
                    else
                    {
                        extra = true;
                        break;
                    }
                }
                else
                {
                    if (whitePieces[i] == 0)
                    {
                        extra = false;
                    }
                    else
                    {
                        extra = true;
                        break;
                    }
                }
            }
            if (extra)
            {
                while (extra)
                {
                    printBoard();
                    cout << "Would you like to use your captured pieces? (Y/N)" << endl;
                    cin >> letter;
                    for (int i = 0; i < letter.length(); i++)
                    {
                        letter.at(i) = tolower(letter.at(i));
                    }
                    if (letter == "y")
                    {
                        do
                        {
                            cout << "Which piece would you like to use?" << endl;
                            cin >> piece;
                            for (int i = 0; i < piece.size(); i++)
                            {
                                tolower(piece.at(i));
                            }
                            if (piece != "pawn" && piece != "rook" && piece != "bishop" && piece != "king" && piece != "lance" && piece != "knight" && piece != "silver" && piece != "gold")
                            {
                                correctWord = false;
                            }
                            else
                            {
                                correctWord = true;
                            }
                            if (!correctWord)
                            {
                                cout << "That is not a correct piece name.  Please try again" << endl;
                            }
                        } while (!correctWord);
                        bool inRange = true;
                        if (turn == "black")
                        {
                            if (piece == "pawn")
                            {
                                if (blackPieces[0] >= 1)
                                {
                                    hasPieces = true;
                                    blackPieces[0] -= 1;
                                }
                            }
                            else if (piece == "lance")
                            {
                                if (blackPieces[1] >= 1)
                                {
                                    hasPieces = true;
                                    blackPieces[1] -= 1;
                                }
                            }
                            else if (piece == "knight")
                            {
                                if (blackPieces[2] >= 1)
                                {
                                    hasPieces = true;
                                    blackPieces[2] -= 1;
                                }
                            }
                            else if (piece == "silver")
                            {
                                if (blackPieces[3] >= 1)
                                {
                                    hasPieces = true;
                                    blackPieces[3] -= 1;
                                }
                            }
                            else if (piece == "gold")
                            {
                                if (blackPieces[4] >= 1)
                                {
                                    hasPieces = true;
                                    blackPieces[4] -= 1;
                                }
                            }
                            else if (piece == "bishop")
                            {
                                if (blackPieces[5] >= 1)
                                {
                                    hasPieces = true;
                                    blackPieces[5] -= 1;
                                }
                            }
                            else if (piece == "rook")
                            {
                                if (blackPieces[6] >= 1)
                                {
                                    hasPieces = true;
                                    blackPieces[6] -= 1;
                                }
                            }
                        }
                        else
                        {
                            if (piece == "pawn")
                            {
                                if (whitePieces[0] >= 1)
                                {
                                    hasPieces = true;
                                    whitePieces[0] -= 1;
                                }
                            }
                            else if (piece == "lance")
                            {
                                if (whitePieces[1] >= 1)
                                {
                                    hasPieces = true;
                                    whitePieces[1] -= 1;
                                }
                            }
                            else if (piece == "knight")
                            {
                                if (whitePieces[2] >= 1)
                                {
                                    hasPieces = true;
                                    whitePieces[2] -= 1;
                                }
                            }
                            else if (piece == "silver")
                            {
                                if (whitePieces[3] >= 1)
                                {
                                    hasPieces = true;
                                    whitePieces[3] -= 1;
                                }
                            }
                            else if (piece == "gold")
                            {
                                if (whitePieces[4] >= 1)
                                {
                                    hasPieces = true;
                                    whitePieces[4] -= 1;
                                }
                            }
                            else if (piece == "bishop")
                            {
                                if (whitePieces[5] >= 1)
                                {
                                    hasPieces = true;
                                    whitePieces[5] -= 1;
                                }
                            }
                            else if (piece == "rook")
                            {
                                if (whitePieces[6] >= 1)
                                {
                                    hasPieces = true;
                                    whitePieces[6] -= 1;
                                }
                            }
                        }
                        if (hasPieces)
                        {
                            do
                            {
                                cout << "Where would you like to place the " << piece << "? (Row, Col)" << endl;
                                cin >> row >> col;
                                row = fixRow(row);
                                col = fixCol(col);
                                if (grid[row][col] != "   ")
                                {
                                    if (turn == "black")
                                    {
                                        if (piece == "knight")
                                        {
                                            inRange = false;
                                        }
                                        else if (piece == "pawn")
                                        {
                                            for (int i = 8; i > 0; i ++)
                                            {
                                                if (grid[i][col] == "\x1b[34m P \x1b[0m")
                                                {
                                                    inRange = false;
                                                    break;
                                                }
                                                else
                                                {
                                                    inRange = true;
                                                }
                                            }
                                            if (row == 0)
                                            {
                                                inRange = false;
                                            }
                                        }
                                        else if (piece == "lance")
                                        {
                                            if (row == 0)
                                            {
                                                inRange = false;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if (piece == "knight")
                                        {
                                            inRange = false;
                                        }
                                        else if (piece == "pawn")
                                        {
                                            for (int i = 8; i > 0; i++)
                                            {
                                                if (grid[i][col] == "\x1b[31m P \x1b[0m")
                                                {
                                                    inRange = false;
                                                    break;
                                                }
                                                else
                                                {
                                                    inRange = true;
                                                }
                                            }
                                            if (row == 8)
                                            {
                                                inRange = false;
                                            }
                                        }
                                        else if (piece == "lance")
                                        {
                                            if (row == 8)
                                            {
                                                inRange = false;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    inRange = true;
                                }
                                if (row > 9 || row < 1 || col > 9 || col < 1)
                                {
                                    inRange = false;
                                }
                                if (!inRange)
                                {
                                    cout << "(" << row << ", " << col << ") is not a valid place. Please try again" << endl;
                                }
                            } while(!inRange);
                            if (turn == "black")
                            {
                                if (piece == "pawn")
                                {
                                    grid[row][col] = "\x1b[34m P \x1b[0m";
                                }
                                else if (piece == "lance")
                                {
                                    grid[row][col] = "\x1b[34m L \x1b[0m";
                                }
                                else if (piece == "knight")
                                {
                                    grid[row][col] = "\x1b[34m K \x1b[0m";
                                }
                                else if (piece == "silver")
                                {
                                    grid[row][col] = "\x1b[34m S \x1b[0m";
                                }
                                else if (piece == "gold")
                                {
                                    grid[row][col] = "\x1b[34m G \x1b[0m";
                                }
                                else if (piece == "bishop")
                                {
                                    grid[row][col] = "\x1b[34m B \x1b[0m";
                                }
                                else if (piece == "rook")
                                {
                                    grid[row][col] = "\x1b[34m R \x1b[0m";
                                }
                            }
                            else
                            {
                                if (piece == "pawn")
                                {
                                    grid[row][col] = "\x1b[31m P \x1b[0m";
                                }
                                else if (piece == "lance")
                                {
                                    grid[row][col] = "\x1b[31m L \x1b[0m";
                                }
                                else if (piece == "knight")
                                {
                                    grid[row][col] = "\x1b[31m K \x1b[0m";
                                }
                                else if (piece == "silver")
                                {
                                    grid[row][col] = "\x1b[31m S \x1b[0m";
                                }
                                else if (piece == "gold")
                                {
                                    grid[row][col] = "\x1b[31m G \x1b[0m";
                                }
                                else if (piece == "bishop")
                                {
                                    grid[row][col] = "\x1b[31m B \x1b[0m";
                                }
                                else if (piece == "rook")
                                {
                                    grid[row][col] = "\x1b[31m R \x1b[0m";
                                }
                            }
                        }
                    }
                    extra = false;
                }
            }
            else
            {
                piece = whichPiece(piece);
                movement();
                move = canMove(piece, row, col, moveRow, moveCol);
                changeCoor();
                if (turn == "black")
                {
                    if (row < 3)
                    {
                        while (letter != "y" && letter != "n")
                        {
                            if (grid[row][col].at(3) != '5')
                            {
                                cout << player1Name << ", would you like to promote your " << piece << "? (Y/N)" << endl;
                                cin >> letter;
                            }
                            for (int i = 0; i < letter.length(); i ++)
                            {
                                letter.at(i) = tolower(letter.at(i));
                            }
                            if (letter == "y")
                            {
                                grid[row][col].at(3) = '5';
                            }
                        } 
                        letter = "";
                    }
                }
                else
                {
                    if (row > 6)
                    {
                        while (letter != "y" && letter != "n")
                        {
                            if (grid[row][col].at(3) != '2')
                            {
                            cout << player2Name << ", would you like to promote your " << piece << "? (Y/N)" << endl;
                            cin >> letter;
                            }
                            for (int i = 0; i < letter.length(); i++)
                            {
                                letter.at(i) = tolower(letter.at(i));
                            }
                            if (letter == "y")
                            {
                                grid[row][col].at(3) = '2';
                            }
                        }
                        letter = "";
                    }
                }
            }
        } while (!move);
        cout << endl;
    }
    string whichPiece(string piece)
    {
        do
        {
            cout << "What piece would you like to move?" << endl;
            cin >> piece;
            for (int i = 0; i < piece.size(); i++)
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
            if (!correctWord)
            {
                cout << "That is not a correct piece name.  Please try again" << endl;
            }
        } while (!correctWord); // Finding what piece the user wants to move
        return piece;
    }
    void movement()
    {
        bool inRange = true;
        do
        {
            cout << "Where is the " << piece << "? (Row, Column)" << endl;
            cin >> row >> col;
            if (grid[row - 1][col - 1] != "   ")
            {
                if ((row >= 1 && row <= 9) && (col >= 1 && col <= 9))
                {
                    row = fixRow(row);
                    col = fixCol(col);
                    if (turn == "white")
                    {
                        if (grid[row][col].at(3) == '1')
                        {
                            inRange = true;
                        }
                    }
                    else
                    {
                        if (grid[row][col].at(3) == '4')
                        {
                            inRange = true;
                        }
                    }
                }
                else
                {
                    inRange = false;
                }
            }
            else
            {
                inRange = false;
                do
                {
                    cout << "(" << row << ", " << col << ") is not where the " << piece << " is" << endl;
                    cout << "What piece would you like to move?" << endl;
                    cin >> piece;
                    for (int i = 0; i < piece.size(); i++)
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
            }
        } while (!inRange); // Finding where the piece is
        do
        {
            inRange = true;
            cout << "Where would you like to move the " << piece << "? (Row, Column)" << endl;
            cin >> moveRow >> moveCol;
            string moveLocation = "";
            if ((moveRow >= 1 && moveRow <= 9) && (moveCol >= 1 && moveCol <= 9))
            {
                moveRow = fixMoveRow(moveRow);
                moveCol = fixMoveCol(moveCol);
                moveLocation = grid[moveRow][moveCol];
                if (moveLocation == "   ")
                {
                    inRange = true;
                }
                else
                {
                    if (turn == "white")
                    {
                        if (moveLocation.at(3) == '4')
                        {
                            inRange = true;
                            char piece = moveLocation.at(6);
                            if (piece == 'L')
                            {
                                whitePieces[1] += 1;
                            }
                            else if (piece == 'P')
                            {
                                whitePieces[0] += 1;
                            }
                            else if (piece == 'N')
                            {
                                whitePieces[2] += 1;
                            }
                            else if (piece == 'S')
                            {
                                whitePieces[3] += 1;
                            }
                            else if (piece == 'G')
                            {
                                whitePieces[4] += 1;
                            }
                            else if (piece == 'B')
                            {
                                whitePieces[5] += 1;
                            }
                            else if (piece == 'R')
                            {
                                whitePieces[6] += 1;
                            }
                        }
                    }
                    else
                    {
                        if (moveLocation.at(3) == '1')
                        {
                            inRange = true;
                            char piece = moveLocation.at(6);
                            if (piece == 'L')
                            {
                                blackPieces[1] += 1;
                            }
                            else if (piece == 'P')
                            {
                                blackPieces[0] += 1;
                            }
                            else if (piece == 'N')
                            {
                                blackPieces[2] += 1;
                            }
                            else if (piece == 'S')
                            {
                                blackPieces[3] += 1;
                            }
                            else if (piece == 'G')
                            {
                                blackPieces[4] += 1;
                            }
                            else if (piece == 'B')
                            {
                                blackPieces[5] += 1;
                            }
                            else if (piece == 'R')
                            {
                                blackPieces[6] += 1;
                            }
                        }
                    }
                }
            }
            else
            {
                inRange = false;
                piece = whichPiece(piece);
                do
                {
                    cout << "Where is the " << piece << "? (Row, Column)" << endl;
                    cin >> row >> col;
                    if (grid[row - 1][col - 1] != "   ")
                    {
                        if ((row >= 1 && row <= 9) && (col >= 1 && col <= 9))
                        {
                            row = fixRow(row);
                            col = fixCol(col);
                            if (turn == "white")
                            {
                                if (grid[row][col].at(3) == '1')
                                {
                                    inRange = true;
                                }
                            }
                            else
                            {
                                if (grid[row][col].at(3) == '4')
                                {
                                    inRange = true;
                                }
                            }
                        }
                        else
                        {
                            inRange = false;
                        }
                    }
                    else
                    {
                        inRange = false;
                        do
                        {
                            cout << "(" << row << ", " << col << ") is not where the " << piece << " is" << endl;
                            cout << "What piece would you like to move?" << endl;
                            cin >> piece;
                            for (int i = 0; i < piece.size(); i++)
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
                    }
                } while (!inRange);
            }
        } while (!inRange); // Moving to a new Space and capturing pieces
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
                    if (row == moveRow + 1)
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
                else if (grid[row][col] == "\x1b[35m G \x1b[0m")
                {
                    if (row - 1 == moveRow && (col - 1 == moveCol || col == moveCol || col + 1 == moveCol))
                    {
                        grid[moveRow][moveCol] = "\x1b[35m G \x1b[0m";
                        grid[row][col] = "   ";
                        return true;
                    }
                    else if (row + 1 == moveRow && col == moveCol)
                    {
                        grid[moveRow][moveCol] = "\x1b[35m G \x1b[0m";
                        grid[row][col] = "   ";
                        return true;
                    }
                    else if (row == moveRow && (col - 1 == moveCol || col + 1 == moveCol))
                    {
                        grid[moveRow][moveCol] = "\x1b[35m G \x1b[0m";
                        grid[row][col] = "   ";
                        return true;
                    }
                }
                else if (grid[row][col] == "\x1b[31m G \x1b[0m")
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
                else if (grid[row][col] == "\x1b[32m G \x1b[0m")
                {
                    if (row + 1 == moveRow && (col - 1 == moveCol || col == moveCol || col + 1 == moveCol))
                    {
                        grid[moveRow][moveCol] = "\x1b[32m S \x1b[0m";
                        grid[row][col] = "   ";
                        return true;
                    }
                    else if (row - 1 == moveRow && col == moveCol)
                    {
                        grid[moveRow][moveCol] = "\x1b[32m S \x1b[0m";
                        grid[row][col] = "   ";
                        return true;
                    }
                    else if (row == moveRow && (col - 1 == moveCol || col + 1 == moveCol))
                    {
                        grid[moveRow][moveCol] = "\x1b[32m G \x1b[0m";
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
                if (row - 1 == moveRow && col - 1 == moveCol)
                {
                    if (grid[row][col].at(3) == '2' || grid[row][col].at(3) == '5')
                    {
                        if (turn == "black")
                        {
                            grid[moveRow][moveCol] = "\x1b[35m R \x1b[0m";
                        }
                        else
                        {
                            grid[moveRow][moveCol] = "\x1b[32m R \x1b[0m";
                        }
                        grid[row][col] = "   ";
                        return true;
                    }
                }
                else if (row + 1 == moveRow && col - 1 == moveCol)
                {
                    if (grid[row][col].at(3) == '2' || grid[row][col].at(3) == '5')
                    {
                        if (turn == "black")
                        {
                            grid[moveRow][moveCol] = "\x1b[35m R \x1b[0m";
                        }
                        else
                        {
                            grid[moveRow][moveCol] = "\x1b[32m R \x1b[0m";
                        }
                        grid[row][col] = "   ";
                        return true;
                    }
                }
                else if (row - 1 == moveRow && moveCol + 1 == moveCol)
                {
                    if (grid[row][col].at(3) == '2' || grid[row][col].at(3) == '5')
                    {
                        if (turn == "black")
                        {
                            grid[moveRow][moveCol] = "\x1b[35m R \x1b[0m";
                        }
                        else
                        {
                            grid[moveRow][moveCol] = "\x1b[32m R \x1b[0m";
                        }
                        grid[row][col] = "   ";
                        return true;
                    }
                }
                else if (row + 1 == moveRow && moveCol + 1 == moveCol)
                {
                    if (grid[row][col].at(3) == '2' || grid[row][col].at(3) == '5')
                    {
                        if (turn == "black")
                        {
                            grid[moveRow][moveCol] = "\x1b[35m R \x1b[0m";
                        }
                        else
                        {
                            grid[moveRow][moveCol] = "\x1b[32m R \x1b[0m";
                        }
                        grid[row][col] = "   ";
                        return true;
                    }
                }
                else
                {
                    if (turn == "black")
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
                                    else if (grid[row][i].at(3) == '4' || grid[row][i].at(3) == '5')
                                    {
                                        notObstacles = false;
                                        break;
                                    }
                                    else if (grid[row][i].at(3) == '1' || grid[row][i].at(3) == '2')
                                    {
                                        if (i == moveCol)
                                        {
                                            if (grid[row][col].at(3) == '4')
                                                grid[moveRow][moveCol] = "\x1b[34m R \x1b[0m";
                                            else if (grid[row][col].at(3) == '5')
                                                grid[moveRow][moveCol] = "\x1b[35m R \x1b[0m";
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
                                    else if (grid[row][i].at(3) == '4' || grid[row][i].at(3) == '5')
                                    {
                                        notObstacles = false;
                                        break;
                                    }
                                    else if (grid[row][i].at(3) == '1' || grid[row][i].at(3) == '2')
                                    {
                                        if (i == moveCol)
                                        {
                                            if (grid[row][col].at(3) == '4')
                                                grid[moveRow][moveCol] = "\x1b[34m R \x1b[0m";
                                            else if (grid[row][col].at(3) == '5')
                                                grid[moveRow][moveCol] = "\x1b[35m R \x1b[0m";
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
                        else if (col == moveCol)
                        {
                            if (moveRow > row)
                            {
                                for (int i = row + 1; i <= moveRow; i++)
                                {
                                    if (grid[i][col] == "   ")
                                    {
                                        notObstacles = true;
                                    }
                                    else if (grid[i][col].at(3) == '4' || grid[row][i].at(3) == '5')
                                    {
                                        notObstacles = false;
                                        break;
                                    }
                                    else if (grid[i][col].at(3) == '1' || grid[i][col].at(3) == '2')
                                    {
                                        if (i == moveRow)
                                        {
                                            if (grid[row][col].at(3) == '4')
                                                grid[moveRow][moveCol] = "\x1b[34m R \x1b[0m";
                                            else if (grid[row][col].at(3) == '5')
                                                grid[moveRow][moveCol] = "\x1b[35m R \x1b[0m";
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
                                for (int i = row - 1; i >= moveRow; i--)
                                {
                                
                                    if (grid[i][col] == "   ")
                                    {
                                        notObstacles = true;
                                    }
                                    else if (grid[i][col].at(3) == '4' || grid[i][col].at(3) == '5')
                                    {
                                        notObstacles = false;
                                        break;
                                    }
                                    else if (grid[i][col].at(3) == '1' || grid[i][col].at(3) == '2')
                                    {
                                        if (i == moveRow)
                                        {     
                                            if (grid[row][col].at(3) == '4')
                                                grid[moveRow][moveCol] = "\x1b[34m R \x1b[0m";
                                            else if (grid[row][col].at(3) == '5')
                                                grid[moveRow][moveCol] = "\x1b[35m R \x1b[0m";
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
                    }
                    else
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
                                    else if (grid[row][i].at(3) == '1' || grid[row][i].at(3) == '2')
                                    {
                                        notObstacles = false;
                                        break;
                                    }
                                    else if (grid[row][i].at(3) == '4' || grid[row][i].at(3) == '5')
                                    {
                                        if (i == moveCol)
                                        {
                                            if (grid[row][col].at(3) == '1')
                                                grid[moveRow][moveCol] = "\x1b[31m R \x1b[0m";
                                            else if (grid[row][col].at(3) == '2')
                                                grid[moveRow][moveCol] = "\x1b[32m R \x1b[0m";
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
                                    else if (grid[row][i].at(3) == '1' || grid[row][i].at(3) == '2')
                                    {
                                        notObstacles = false;
                                        break;
                                    }
                                    else if (grid[row][i].at(3) == '4' || grid[row][i].at(3) == '5')
                                    {
                                        if (i == moveCol)
                                        {
                                            if (grid[row][col].at(3) == '1')
                                                grid[moveRow][moveCol] = "\x1b[34m R \x1b[0m";
                                            else if (grid[row][col].at(3) == '1')
                                                grid[moveRow][moveCol] = "\x1b[35m R \x1b[0m";
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
                        else if (col == moveCol)
                        {
                            if (moveRow > row)
                            {
                                for (int i = row + 1; i <= moveRow; i++)
                                {
                                    if (grid[i][col] == "   ")
                                    {
                                        notObstacles = true;
                                    }
                                    else if (grid[i][col].at(3) == '1' || grid[row][i].at(3) == '2')
                                    {
                                        notObstacles = false;
                                        break;
                                    }
                                    else if (grid[i][col].at(3) == '4' || grid[i][col].at(3) == '5')
                                    {
                                        if (i == moveRow)
                                        {
                                            if (grid[row][col].at(3) == '1')
                                                grid[moveRow][moveCol] = "\x1b[31m R \x1b[0m";
                                            else if (grid[row][col].at(3) == '2')
                                                grid[moveRow][moveCol] = "\x1b[32m R \x1b[0m";
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
                                for (int i = row - 1; i >= moveRow; i--)
                                {
                                    if (grid[i][col] == "   ")
                                    {
                                        notObstacles = true;
                                    }
                                    else if (grid[i][col].at(3) == '1' || grid[i][col].at(3) == '2')
                                    {
                                        notObstacles = false;
                                        break;
                                    }
                                    else if (grid[i][col].at(3) == '4' || grid[i][col].at(3) == '5')
                                    {
                                        if (i == moveRow)
                                        {
                                            if (grid[row][col].at(3) == '1')
                                                grid[moveRow][moveCol] = "\x1b[31m R \x1b[0m";
                                            else if (grid[row][col].at(3) == '2')
                                                grid[moveRow][moveCol] = "\x1b[32m R \x1b[0m";
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
                    }
                    if (notObstacles)
                    {
                        if (turn == "black")
                        {
                            if (grid[row][col].at(3) == '4')
                                grid[moveRow][moveCol] = "\x1b[34m R \x1b[0m";
                            else if (grid[row][col].at(3) == '5')
                                grid[moveRow][moveCol] = "\x1b[35m R \x1b[0m";
                        }
                        else
                        {
                            if (grid[row][col].at(3) == '1')
                                grid[moveRow][moveCol] = "\x1b[31m R \x1b[0m";
                            else if (grid[row][col].at(3) == '2')
                                grid[moveRow][moveCol] = "\x1b[32m R \x1b[0m";
                        }
                        grid[row][col] = "   ";
                        return true;
                    }
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
        return false;
    }
    void changeCoor()
    {
        row = moveRow;
        col = moveCol;
    }
    bool checkBishopBounds(int row, int col, int moveRow, int movecol)
    {
        if (row == moveRow + 1 || row == moveRow - 1 || col == moveCol - 1 || col == moveCol + 1)
        {
            if (grid[row][col].at(3) == '2' || grid[row][col].at(3) == '5')
            {
                if (turn == "black")
                {
                    grid[moveRow][moveCol] = "\x1b[35m B \x1b[0m";
                }
                else
                {
                    grid[moveRow][moveCol] = "\x1b[32m B \x1b[0m";
                }
                grid[row][col] = "   ";
                return true;
            }
        }
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
        for (int i = 0; i < 9; i++)
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
            for (int j = 0; j < 9; j++)
            {
                cout << "|" << grid[i][j];
            }
            cout << "|" << endl;
        }
        cout << "  ";
        for (int i = 0; i < 9; i++)
        {
            cout << "|---";
        }
        cout << "|" << endl;
        cout << "    ";
        for (int i = 1; i <= 9; i++)
        {
            cout << i << "   ";
        }
        cout << endl;
        cout << player1Name << endl
             << endl;
        cout << player1Name << "'s extendable pieces: ";
        cout << endl;
        for (int i = 0; i < 7; i++)
        {
            cout << blackPieces[i];
            if (i == 0)
            {
                cout << " Pawns   ";
            }
            else if (i == 1)
            {
                cout << " Lances  ";
            }
            else if (i == 2)
            {
                cout << " Knights  ";
            }
            else if (i == 3)
            {
                cout << " Silver Generals  ";
            }
            else if (i == 4)
            {
                cout << " Gold Generals  ";
            }
            else if (i == 5)
            {
                cout << " Bishops  ";
            }
            else
            {
                cout << " Rooks";
            }
        }
        cout << endl;
        cout << player2Name << "'s extendable pieces: ";
        cout << endl;
        for (int i = 0; i < 7; i++)
        {
            cout << whitePieces[i];
            if (i == 0)
            {
                cout << " Pawns   ";
            }
            else if (i == 1)
            {
                cout << " Lances  ";
            }
            else if (i == 2)
            {
                cout << " Knights  ";
            }
            else if (i == 3)
            {
                cout << " Silver Generals  ";
            }
            else if (i == 4)
            {
                cout << " Gold Generals  ";
            }
            else if (i == 5)
            {
                cout << " Bishops  ";
            }
            else
            {
                cout << " Rooks";
            }
        }
        cout << endl;
    }
};
int main()
{
    Shogi game;
    game.prompt();
    return 0;
}