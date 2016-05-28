#include "stdafx.h"
#include "TicTacToeBoard.h"

TicTacToeBoard::TicTacToeBoard()
{
	ClearBoard();
}

void TicTacToeBoard::ClearBoard()
{
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			board[r][c] = 0;
		}
	}
}

void TicTacToeBoard::DisplayGameBoard()
{
	//How big a move is on the display 
	int MoveSize = 3;
	//Offsets the game board when it prints by 1
	int GridOffset = 1;

	//Define x move
	char XMove[3][3] =
	{
		{ 'X', ' ', 'X' },
		{ ' ','X',' ' },
		{ 'X', ' ', 'X' }
	};

	//Define o move
	char YMove[3][3] =
	{
		{ 'O', 'O', 'O' },
		{ 'O', ' ', 'O' },
		{ 'O', 'O', 'O' }
	};

	//Print moves
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			//Calculate Coordinate for move
			COORD Coord;
			Coord.X = r* MoveSize + GridOffset + r;
			Coord.Y = c* MoveSize + GridOffset + c;

			//Set cursor to coordinate
			SetCursorPosition(Coord.X, Coord.Y);

			//If the move is an X print an X in the space
			if (board[r][c] == 1)
			{
				for (int i = 0; i < 3; i++)
				{
					SetCursorPosition(Coord.X + i, Coord.Y);
					for (int j = 0; j < 3; j++)
					{
						std::cout << XMove[i][j];
					}
				}
			}
			//If the move is an O print an O in the space
			else if (board[r][c] == 2)
			{
				for (int i = 0; i < 3; i++)
				{
					SetCursorPosition(Coord.X + i, Coord.Y);
					for (int j = 0; j < 3; j++)
					{
						std::cout << YMove[i][j];
					}
				}
			}
		}
	}

	//Set cursor to line after the board
	SetCursorPosition(13, 0);
}

void TicTacToeBoard::SetCursorPosition(int Row, int Column)
{
	COORD coord;
	coord.X = Column;
	coord.Y = Row;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void TicTacToeBoard::RefreshUserInterface()
{
	system("cls");
	PrintGrid();
	DisplayGameBoard();
}

void TicTacToeBoard::PrintGrid()
{
	//Define game grid
	char grid[12][12] =
	{
		{ ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' },
		{ ' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ' },
		{ ' ',' ','1',' ','|',' ','2',' ','|',' ','3',' ' },
		{ ' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ' },
		{ ' ','-','-','-','+','-','-','-','+','-','-','-' },
		{ ' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ' },
		{ ' ',' ','4',' ','|',' ','5',' ','|',' ','6',' ' },
		{ ' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ' },
		{ ' ','-','-','-','+','-','-','-','+','-','-','-' },
		{ ' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ' },
		{ ' ',' ','7',' ','|',' ','8',' ','|',' ','9',' ' },
		{ ' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ' },
	};



	//Print grid
	for (int r = 0; r < 12; r++)
	{
		for (int c = 0; c < 12; c++)
		{
			std::cout << grid[r][c];
		}
		std::cout << std::endl;
	}
}

bool TicTacToeBoard::MakeMove(int Move, int Player)
{
	COORD TranslatedMove = TranslateMove(Move);

	//Checks for valid moves if the input is taken or out of range it returns a false value
	if (board[TranslatedMove.X][TranslatedMove.Y] != 0 || TranslatedMove.X == -1)
	{
		return false;
	}
	else
	{
		//Valid move is recorded and true is returned 
		board[TranslatedMove.X][TranslatedMove.Y] = Player;
		return true;
	}

}

COORD TicTacToeBoard::TranslateMove(int Move)
{
	COORD Result;

	switch (Move)
	{
	case 1:
		Result.X = 0;
		Result.Y = 0;
		break;
	case 2:
		Result.X = 0;
		Result.Y = 1;
		break;
	case 3:
		Result.X = 0;
		Result.Y = 2;
		break;
	case 4:
		Result.X = 1;
		Result.Y = 0;
		break;
	case 5:
		Result.X = 1;
		Result.Y = 1;
		break;
	case 6:
		Result.X = 1;
		Result.Y = 2;
		break;
	case 7:
		Result.X = 2;
		Result.Y = 0;
		break;
	case 8:
		Result.X = 2;
		Result.Y = 1;
		break;
	case 9:
		Result.X = 2;
		Result.Y = 2;
		break;
	default:
		Result.X = -1;
		Result.Y = -1;
	}

	return Result;
}

bool TicTacToeBoard::TakeTurn(int Player)
{
	std::cout << "Make a move player " << Player << "!" << std::endl;
	int Move = 0;
	std::cin >> Move;

	//If we get a bad input return false
	if (std::cin.fail()) {
		//Clear cin error flag
		std::cin.clear();
		//Ignore bad input
		std::cin.ignore(INT_MAX, '\n');
		//Start turn over
		return false;
	}

	//Make the move and return true if successful
	return MakeMove(Move, Player);
}

int TicTacToeBoard::ReturnBoardState()
{
	for (int r = 0; r < 3; r++)
	{
		//Check for horizontal win
		if (board[r][0] == board[r][1] && board[r][0] == board[r][2] && board[r][0] != 0)
		{
			return board[r][0];
		}
		//Check for vertical win
		else if (board[0][r] == board[1][r] && board[0][r] == board[2][r] && board[0][r] != 0)
		{
			return board[0][r];
		}
	}


	//check for diagonal win
	if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != 0)
	{
		return board[0][0];
	}

	if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != 0)
	{
		return board[0][2];
	}


	//check for a full board
	int Blanks = 0;
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			if (board[r][c] == 0)
			{
				Blanks++;
			}
		}
	}

	//Full board return 3
	if (Blanks == 0)
	{
		return 3;
	}

	//No winner or draw yet return 0
	return 0;
}
