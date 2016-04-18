// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>



//prototypes
void gotoxy(int column, int row);
void display_board(int board[3][3]);
int game_state(int board[3][3]);
bool turn(int board[3][3], int player);
bool make_move(int board[3][3], int move,int player);
COORD translate_move(int move);
void clear_board(int board[3][3]);

int main()
{
	//Possible states returned by game_state()
	enum state{in_progress,player_one_wins,player_two_wins,draw};
	
	
	//Tic Tac Toe board
	int board[3][3] =
	{
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 }
	};

	
	bool playing = true;

	//Tic Tac Toe repeats until told to exit
	while (playing)
	{

		//Players take turns
		while (game_state(board) == state::in_progress)
		{
			//Player one's turn loops until valid input is given
			while (!turn(board, 1));

			//If player one wins break the loop here
			if (game_state(board) != state::in_progress)
				break;
			
			//Player two's turn loops until valid input is given
			while (!turn(board, 2));
		}

		//Clear the window, display board, and the end of game condition.
		system("cls");
		display_board(board);
		int s = game_state(board);

		switch (s)
		{
		case state::in_progress:
			std::cout << "You shouldn't be here!" << std::endl;
			break;
		case state::player_one_wins:
			std::cout << "Player 1 Wins!" << std::endl;
			break;
		case state::player_two_wins:
			std::cout << "Player 2 Wins!" << std::endl;
			break;
		case state::draw:
			std::cout << "The game is a draw!" << std::endl;
			break;
		}
		
		//Do the players want to play again?
		char play = 'Y';
		std::cout << "Do you want to play again Y/N"<<std::endl;
		std::cin >> play;

		//if yes clear the board and start the game over
		if (play == 'Y' || play == 'y')
		{
			playing = true;
			clear_board(board);
			
		}
		else
		{
			playing = false;
		}
	}

	return 0;
}

//Sends the console cursor to an (x,y) coordinate
void gotoxy(int row, int column)
{
	COORD coord;
	coord.X = column;
	coord.Y = row;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Displays the board and the current moves
void display_board(int board[3][3])
{
	//How big a move is on the display 
	int move_size = 3;
	//Offsets the game board when it prints by 1
	int grid_offset = 1;

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

	//Define x move
	char x[3][3] =
	{
		{ 'X', ' ', 'X' },
		{ ' ','X',' ' },
		{ 'X', ' ', 'X' }
	};
	
	//Define o move
	char y[3][3] =
	{
		{ 'O', 'O', 'O' },
		{ 'O', ' ', 'O' },
		{ 'O', 'O', 'O' }
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

	//Print moves
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			//Calculate Coordinate for move
			COORD coord;
			coord.X = r* move_size + grid_offset + r;
			coord.Y = c* move_size + grid_offset + c;

			//Set cursor to coordinate
			gotoxy(coord.X, coord.Y);

			//If the move is an X print an X in the space
			if (board[r][c] == 1)
			{
				for (int i = 0; i < 3; i++)
				{
					gotoxy(coord.X + i, coord.Y);
					for (int j = 0; j < 3; j++)
					{
						std::cout << x[i][j];
					}
				}
			}
			//If the move is an O print an O in the space
			else if (board[r][c] == 2)
			{
				for (int i = 0; i < 3; i++)
				{
					gotoxy(coord.X + i, coord.Y);
					for (int j = 0; j < 3; j++)
					{
						std::cout << y[i][j];
					}
				}
			}
		}
	}

	//Set cursor to line after the board
	gotoxy(13, 0);
}

//Updates game state based on current moves 
int game_state(int board[3][3])
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
	int blanks = 0;
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			if (board[r][c] == 0)
			{
				blanks++;
			}
		}
	}

	//Full board return 3
	if (blanks == 0)
	{
		return 3;
	}

	//No winner or draw yet return 0
	return 0;
}

//Players move
bool make_move(int board[3][3], int move,int player)
{
	COORD t_move = translate_move(move);

	//Checks for valid moves if the input is taken or out of range it returns a false value
	if (board[t_move.X][t_move.Y] != 0 || t_move.X == -1)
	{
		return false;
	}
	else
	{
		//Valid move is recorded and true is returned 
		board[t_move.X][t_move.Y] = player;
		return true;
	}

}

//Translate players move choice into array position
COORD translate_move(int move)
{
	COORD result;

	switch (move)
	{
	case 1:
		result.X = 0;
		result.Y = 0;
		break;
	case 2:
		result.X = 0;
		result.Y = 1;
		break;
	case 3:
		result.X = 0;
		result.Y = 2;
		break;
	case 4:
		result.X = 1;
		result.Y = 0;
		break;
	case 5:
		result.X = 1;
		result.Y = 1;
		break;
	case 6:
		result.X = 1;
		result.Y = 2;
		break;
	case 7:
		result.X = 2;
		result.Y = 0;
		break;
	case 8:
		result.X = 2;
		result.Y = 1;
		break;
	case 9:
		result.X = 2;
		result.Y = 2;
		break;
	default:
		result.X = -1;
		result.Y = -1;
	}

	return result;
}

//Player Turn
bool turn(int board[3][3], int player)
{
	system("cls");
	display_board(board);
	std::cout << "Make a move player "<< player << "!" << std::endl;
	int move = 0;
	std::cin >> move;
	
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
	return make_move(board, move, player);
}

//Clears the board of all moves
void clear_board(int board[3][3])
{
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			board[r][c] = 0;
		}
	}
}


