//------------------------------------------------------------------------------
//
// File Name:	Board.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 5.5.6 Assignment - Tic-Tac-Toe
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "Board.h"
#include <iostream>
#include <cstdlib>

namespace CS170
{
	//------------------------------------------------------------------------------
	// Struct Definitions:
	//------------------------------------------------------------------------------

	struct Board
	{
		TileState** data;
	};

	//------------------------------------------------------------------------------
	// Function Declarations:
	//------------------------------------------------------------------------------

	// Allocate memory for a tic-tac-toe board.
		// Returns:
		//   A pointer to the created board struct.
	Board* BoardCreate()
	{
		Board *newBoard = new Board;

		// Allocate Tile State data
		newBoard->data = new TileState * [boardLength];
		for (int i = 0; i < (int)boardLength; i++)
			newBoard->data[i] = new TileState[boardLength];

		return newBoard;
	}

	// Free memory for the tic-tac-toe board.
	// Params:
	//   theBoard = A reference to the pointer to the board.
	void BoardFree(Board*& theBoard)
	{
		// Loop through the data and free the other arrays
		for (unsigned i = 0; i < boardLength; i++)
		{
			delete[] theBoard->data[i];
			theBoard->data[i] = NULL;
		}

		// Free the overhead array
		delete[] theBoard->data;
		theBoard->data = NULL;

		// Free the structure
		delete theBoard;
		theBoard = NULL;
	}

	// Display the contents of the board using the standard output stream.
	// Params:
	//   theBoard = A reference to the game board.
	void BoardDisplay(const Board& board)
	{
		if (board.data[0][0] == tsEMPTY)
			std::cout << "UNREFERENCED_PARAMETER";
	}

	// Place a token on the board at a specific position.
	// Params:
	//   theBoard = A reference to the game board.
	//   row = The row of the board on which to place the token.
	//   column = The column of the board on which to place the token.
	//   value = The value to place in the specified tile.
	// Returns:
	//   Whether the token was able to be placed.
	PlaceResult BoardPlaceToken(Board& board, unsigned row, unsigned column, TileState value)
	{
		PlaceResult result = prREJECTED_OCCUPIED;
		
		if (board.data[0][0] == value || row == column)
			return result;
		return result;
	}

	// Reset the board to an empty state.
	// Params:
	//   theBoard = A reference to the game board.
	void BoardReset(Board& board)
	{
		if (board.data[0][0] == tsEMPTY)
			std::cout << "UNREFERENCED_PARAMETER";
	}

	// Get the current state of the board. (Is the game over?)
	// Params:
	//   theBoard = A reference to the game board.
	// Returns:
	//   The current state of the game - win, tie, or open (still going).
	BoardState BoardGetState(const Board& board)
	{
		BoardState state = bsOPEN;

		if (board.data[0][0] == tsEMPTY)
			return state;
		return state;
	}
}