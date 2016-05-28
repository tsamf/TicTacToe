#pragma once
#include <Windows.h>
#include <iostream>

class TicTacToeBoard
{

public:
	TicTacToeBoard();
	void ClearBoard();
	void RefreshUserInterface();
	bool TakeTurn(int Player);
	int ReturnBoardState();

private:
	int board[3][3];
	void SetCursorPosition(int Row, int Column);
	void DisplayGameBoard();
	void PrintGrid();
	COORD TranslateMove(int Move);
	bool MakeMove(int Move, int Player);

};