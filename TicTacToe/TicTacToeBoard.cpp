#include "stdafx.h"
#include "TicTacToeBoard.h"
#include <string>

TicTacToeBoard::TicTacToeBoard() :TicTacToeBoard(3) {}

TicTacToeBoard::TicTacToeBoard(int Size) : boardSize(Size)
{
	board = new int*[Size];

	for (int i = 0; i < Size; i++)
	{
		board[i] = new int[Size];
	}

	ClearBoard();
}

TicTacToeBoard::~TicTacToeBoard()
{
	for (int i = 0; i < boardSize; i++)
	{
		delete board[i];
	}

	delete board;
}

void TicTacToeBoard::ClearBoard()
{
	for (int r = 0; r < boardSize; r++)
	{
		for (int c = 0; c < boardSize; c++)
		{
			board[r][c] = 0;
		}
	}
}

void TicTacToeBoard::DisplayGameBoard()
{
	//How big a move is on the display 
	const int MoveDisplaySize = 3;
	//Offsets the game board when it prints by 1
	const int GridOffset = 1;

	//Define x move
	char XMove[MoveDisplaySize][MoveDisplaySize] =
	{
		{ 'X', ' ', 'X' },
		{ ' ', 'X', ' ' },
		{ 'X', ' ', 'X' }
	};

	//Define o move
	char YMove[MoveDisplaySize][MoveDisplaySize] =
	{
		{ 'O', 'O', 'O' },
		{ 'O', ' ', 'O' },
		{ 'O', 'O', 'O' }
	};

	//Print moves
	for (int r = 0; r < boardSize; r++)
	{
		for (int c = 0; c < boardSize; c++)
		{
			//Calculate Coordinate for move
			COORD Coord;
			Coord.X = r* MoveDisplaySize + GridOffset + r;
			Coord.Y = c* MoveDisplaySize + GridOffset + c;

			//Set cursor to coordinate
			SetCursorPosition(Coord.X, Coord.Y);

			//If the move is an X print an X in the space
			if (board[r][c] == 1)
			{
				for (int i = 0; i < MoveDisplaySize; i++)
				{
					SetCursorPosition(Coord.X + i, Coord.Y);
					for (int j = 0; j < MoveDisplaySize; j++)
					{
						std::cout << XMove[i][j];
					}
				}
			}
			//If the move is an O print an O in the space
			else if (board[r][c] == 2)
			{
				for (int i = 0; i < MoveDisplaySize; i++)
				{
					SetCursorPosition(Coord.X + i, Coord.Y);
					for (int j = 0; j < MoveDisplaySize; j++)
					{
						std::cout << YMove[i][j];
					}
				}
			}
		}
	}

	//Set cursor to line after the board
	int boardOffset = boardSize * MoveDisplaySize + boardSize + 1;

	SetCursorPosition(boardOffset, 0);
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
	PrintAvaliableMoves();
	DisplayGameBoard();
}

void TicTacToeBoard::PrintGrid()
{
	//build first line 
	std::string line = " ";
	for (int i = 1; i <= boardSize; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			line += ' ';
		}

		if (i < boardSize)
			line += ' ';
	}
	std::cout << line << std::endl;
	line = " ";

	//Board
	for (int b = 1; b <= boardSize; b++)
	{
		//Row
		for (int a = 0; a < 3; a++)
		{
			//Builds Line
			std::string line = " ";
			for (int i = 1; i <= boardSize; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					line += ' ';
				}

				if (i < boardSize)
					line += '|';
			}
			std::cout << line << std::endl;
			line = " ";
		}

		//row divider
		if (b != boardSize)
		{
			std::string line = " ";
			for (int i = 1; i <= boardSize; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					line += '-';
				}

				if (i < boardSize)
					line += '+';
			}
			std::cout << line << std::endl;
			line = "";
		}
	}
}

void TicTacToeBoard::PrintAvaliableMoves()
{
	int Offset = 2;

	for (int r = 0; r < boardSize; r++)
	{
		for (int c = 0; c < boardSize; c++)
		{
			//We can skip the moves that have been taken
			if (board[r][c] != 0)
			{
				continue;
			}
			
			//Caculate coordinate to print
			int x = Offset + r * 4;
			int y = Offset + c * 4;

			SetCursorPosition(x, y);

			//Calcuate Move Number
			int MoveNumber = r * boardSize + (c + 1);

			//Print Move Number
			std::cout << MoveNumber;
		}
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

	Result.X = (Move - 1) / boardSize;
	Result.Y = (Move - 1) % boardSize;

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

//TODO Update Diagonal to accept other board sizes
int TicTacToeBoard::ReturnBoardState()
{
	for (int r = 0; r < boardSize; r++)
	{
		for (int i = 0; i + 2 < boardSize; i++)
		{
			//Check for horizontal win
			if (board[r][i] == board[r][i+1] && board[r][i] == board[r][i+2] && board[r][i] != 0)
			{
				return board[r][i];
			}
			//Check for vertical win
			else if (board[i][r] == board[i+1][r] && board[i][r] == board[i+2][r] && board[i][r] != 0)
			{
				return board[i][r];
			}
		}
	}

	//check for diagonal win
	
	for (int r = 0; r+2 < boardSize; r++)
	{
		for (int c = 0; c + 2 < boardSize; c++)
		{
			if (board[0+r][0+c] == board[1+r][1+c] && board[0+r][0+c] == board[2+r][2+c] && board[0+r][0+c] != 0)
			{
				return board[0+r][0+c];
			}

			if (board[0+r][2+c] == board[1+r][1+c] && board[0+r][2+c] == board[2+r][0+c] && board[0+r][2+c] != 0)
			{
				return board[0+r][2+c];
			}
		}
	}


	//check for a full board
	int Blanks = 0;
	for (int r = 0; r < boardSize; r++)
	{
		for (int c = 0; c < boardSize; c++)
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

