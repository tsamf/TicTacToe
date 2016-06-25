// ConsoleApplication1.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include "TicTacToeBoard.h"

//prototypes
void PlayGame();

int main()
{
	PlayGame();

	return 0;
}

void PlayGame()
{
	//Possible states returned by game_state()
	enum State { in_progress, player_one_wins, player_two_wins, draw };

	TicTacToeBoard board(5);

	bool Playing = true;

	board.RefreshUserInterface();

	//Tic Tac Toe repeats until told to exit
	while (Playing)
	{
		//Players take turns
		while (board.ReturnBoardState() == State::in_progress)
		{
			//Player one's turn loops until valid input is given
			while (!board.TakeTurn(1))
			{
				board.RefreshUserInterface();
			};

			//Update Board to refelct player Ones Move
			board.RefreshUserInterface();

			//If player one wins break the loop here
			if (board.ReturnBoardState() != State::in_progress)
				break;

			//Player two's turn loops until valid input is given
			while (!board.TakeTurn(2))
			{
				board.RefreshUserInterface();
			};

			board.RefreshUserInterface();
		}

		//Clear the window, display board, and the end of game condition.
		board.RefreshUserInterface();

		int s = board.ReturnBoardState();

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
			board.ClearBoard();
			board.RefreshUserInterface();

		}
		else
		{
			Playing = false;
		}
	}
}
