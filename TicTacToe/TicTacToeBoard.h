#pragma once
#include <Windows.h>
#include <iostream>

class TicTacToeBoard
{

public:
	TicTacToeBoard();
	TicTacToeBoard(int Size);
	~TicTacToeBoard();
	
	void ClearBoard();
	void RefreshUserInterface();
	bool TakeTurn(int Player);
	int ReturnBoardState();

private:

	int** board;
	const int boardSize;

	void SetCursorPosition(int Row, int Column);
	void DisplayGameBoard();
	void PrintGrid();
	void PrintAvaliableMoves();
	COORD TranslateMove(int Move);
	bool MakeMove(int Move, int Player);

	//Undefined Copy constructor and assignment operator
	TicTacToeBoard& operator= (const TicTacToeBoard& other);
	TicTacToeBoard(const TicTacToeBoard& other);
};