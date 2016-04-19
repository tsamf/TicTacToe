// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>



//prototypes
void PlayGame();
void SetCursorPosition(int Column, int Row);
void DisplayGameBoard(int Board[3][3]);
void PrintGrid();
int ReturnGameState(int Board[3][3]);
bool TakeTurn(int Board[3][3], int Player);
bool MakeMove(int Board[3][3], int Move,int Player);
COORD TranslateMove(int Move);
void ClearBoard(int Board[3][3]);
void RefreshUserInterface(int Board[3][3]);


int main()
{
	PlayGame();

	return 0;
}

void PlayGame()
{
	//Possible states returned by game_state()
	enum State { in_progress, player_one_wins, player_two_wins, draw };


	//Tic Tac Toe board
	int Board[3][3] =
	{
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 }
	};


	bool Playing = true;

	PrintGrid();

	//Tic Tac Toe repeats until told to exit
	while (Playing)
	{
		//Players take turns
		while (ReturnGameState(Board) == State::in_progress)
		{
			//Player one's turn loops until valid input is given
			while (!TakeTurn(Board, 1))
			{
				RefreshUserInterface(Board);
			};

			//Update Board to refelct player Ones Move
			RefreshUserInterface(Board);

			//If player one wins break the loop here
			if (ReturnGameState(Board) != State::in_progress)
				break;

			//Player two's turn loops until valid input is given
			while (!TakeTurn(Board, 2))
			{
				RefreshUserInterface(Board);
			};

			RefreshUserInterface(Board);
		}

		//Clear the window, display board, and the end of game condition.
		//DisplayGameBoard(Board);
		
		RefreshUserInterface(Board);
		
		

		int s = ReturnGameState(Board);


		switch (s)
		{
		case State::in_progress:
			std::cout << "You shouldn't be here!" << std::endl;
			break;
		case State::player_one_wins:
			std::cout << "Player 1 Wins!" << std::endl;
			break;
		case State::player_two_wins:
			std::cout << "Player 2 Wins!" << std::endl;
			break;
		case State::draw:
			std::cout << "The game is a draw!" << std::endl;
			break;
		}

		//Do the players want to play again?
		char play = 'Y';
		std::cout << "Do you want to play again Y/N" << std::endl;
		std::cin >> play;

		//if yes clear the board and start the game over
		if (play == 'Y' || play == 'y')
		{
			Playing = true;
			ClearBoard(Board);
			RefreshUserInterface(Board);

		}
		else
		{
			Playing = false;
		}
	}
}

//Sends the console cursor to an (x,y) coordinate
void SetCursorPosition(int Row, int Column)
{
	COORD coord;
	coord.X = Column;
	coord.Y = Row;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Print the grid
void PrintGrid()
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


//Displays the board and the current moves
void DisplayGameBoard(int Board[3][3])
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
			if (Board[r][c] == 1)
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
			else if (Board[r][c] == 2)
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

void RefreshUserInterface(int Board[3][3])
{
	system("cls");
	PrintGrid();
	DisplayGameBoard(Board);
}

//Updates game state based on current moves 
int ReturnGameState(int Board[3][3])
{
	for (int r = 0; r < 3; r++)
	{
		//Check for horizontal win
		if (Board[r][0] == Board[r][1] && Board[r][0] == Board[r][2] && Board[r][0] != 0)
		{
			return Board[r][0];
		}
		//Check for vertical win
		else if (Board[0][r] == Board[1][r] && Board[0][r] == Board[2][r] && Board[0][r] != 0)
		{
			return Board[0][r];
		}
	}


	//check for diagonal win
	if (Board[0][0] == Board[1][1] && Board[0][0] == Board[2][2] && Board[0][0] != 0)
	{
		return Board[0][0];
	}

	if (Board[0][2] == Board[1][1] && Board[0][2] == Board[2][0] && Board[0][2] != 0)
	{
		return Board[0][2];
	}


	//check for a full board
	int Blanks = 0;
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			if (Board[r][c] == 0)
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

//Players move
bool MakeMove(int Board[3][3], int Move,int Player)
{
	COORD TranslatedMove = TranslateMove(Move);

	//Checks for valid moves if the input is taken or out of range it returns a false value
	if (Board[TranslatedMove.X][TranslatedMove.Y] != 0 || TranslatedMove.X == -1)
	{
		return false;
	}
	else
	{
		//Valid move is recorded and true is returned 
		Board[TranslatedMove.X][TranslatedMove.Y] = Player;
		return true;
	}

}

//Translate players move choice into array position
COORD TranslateMove(int Move)
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

//Player Turn
bool TakeTurn(int Board[3][3], int Player)
{
	std::cout << "Make a move player "<< Player << "!" << std::endl;
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
	return MakeMove(Board, Move, Player);
}

//Clears the board of all moves
void ClearBoard(int Board[3][3])
{
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			Board[r][c] = 0;
		}
	}
}


 