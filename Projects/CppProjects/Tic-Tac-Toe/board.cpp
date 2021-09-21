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
	// Private Functions:
	//------------------------------------------------------------------------------

	// Converts a tile state to board state.
	// Only called if a win was confirmed, used to determine which player won
	// Should not be called with an empty space
	// Params:
	//   state = the tilestate to convert to a board state
	// Return:
	//   A bsWIN_ONE if the given value is tsPLAYER_ONE
	//   A bsWIN_TWO if the given value is tsPLAYER_TWO
	BoardState ConvertToBoardState(TileState state);

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
		for (unsigned i = 0; i < boardLength; i++)
		{
			newBoard->data[i] = new TileState[boardLength];
			// Set values to empty
			for (unsigned j = 0; j < boardLength; j++)
				newBoard->data[i][j] = tsEMPTY;
		}

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
		// Loop through the data and print it out
		for (unsigned i = 0; i < boardLength; i++)
		{
			// Print row separator
			std::cout << "-------------" << std::endl;
			
			// Print each column
			for (unsigned j = 0; j < boardLength; j++)
			{
				// Print column separator
				std::cout << "|";

				// Determine which value to print
				switch (board.data[i][j])
				{
					case tsEMPTY:
						std::cout << "   ";
						break;
					case tsPLAYER_ONE:
						std::cout << " X ";
						break;
					case tsPLAYER_TWO:
						std::cout << " O ";
						break;
				}
			}

			// Print final column seperator and new line
			std::cout << "|" << std::endl;
		}

		// Print final row seperator
		std::cout << "-------------" << std::endl;
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
		// Determine if place is out of bounds
		if (row > 2 || column > 2)
			return prREJECTED_OUTOFBOUNDS;
		else
		{
			// Determine if place is filled, if not fill it, otherwise return error
			if (board.data[row][column] == tsEMPTY)
			{
				board.data[row][column] = value;
				return prACCEPTED;
			}
			else
				return prREJECTED_OCCUPIED;
		}
	}

	// Reset the board to an empty state.
	// Params:
	//   theBoard = A reference to the game board.
	void BoardReset(Board& board)
	{
		// Loop through board and set each value to empty
		for (unsigned i = 0; i < boardLength; i++)
		{
			for (unsigned j = 0; j < boardLength; j++)
				board.data[i][j] = tsEMPTY;
		}
	}

	// Get the current state of the board. (Is the game over?)
	// Params:
	//   theBoard = A reference to the game board.
	// Returns:
	//   The current state of the game - win, tie, or open (still going).
	BoardState BoardGetState(const Board& board)
	{
		const int totalWinConditions = 8;
		// Store all possible win conditions (3 down, 3 across, 2 diagonal)
		// Does not store a win if the values are empty
		bool winConditions[totalWinConditions] = {
			// 3 down
			(board.data[0][0] == board.data[0][1] == board.data[0][2]) && board.data[0][0] != tsEMPTY,
			(board.data[1][0] == board.data[1][1] == board.data[1][2]) && board.data[1][0] != tsEMPTY,
			(board.data[2][0] == board.data[2][1] == board.data[2][2]) && board.data[2][0] != tsEMPTY,
			// 3 across
			(board.data[0][0] == board.data[1][0] == board.data[2][0]) && board.data[0][0] != tsEMPTY,
			(board.data[0][1] == board.data[1][1] == board.data[2][1]) && board.data[0][1] != tsEMPTY,
			(board.data[0][2] == board.data[1][2] == board.data[2][2]) && board.data[0][2] != tsEMPTY,
			// 2 diagonal
			(board.data[0][0] == board.data[1][1] == board.data[2][2]) && board.data[0][0] != tsEMPTY,
			(board.data[0][2] == board.data[1][1] == board.data[2][0]) && board.data[0][2] != tsEMPTY
		};

		// Loop through winConditions to find a win
		for (int i = 0; i < totalWinConditions; i++)
		{
			if (winConditions[i])
			{
				// Convert to a board state if there is a win
				// Cases do not go up in order so similar calls to ConvertToBoardState can be grouped
				switch (i)
				{
					case 0:
					case 3:
					case 6:
						return ConvertToBoardState(board.data[0][0]);
						break;
					case 1:
						return ConvertToBoardState(board.data[1][0]);
						break;
					case 2:
						return ConvertToBoardState(board.data[2][0]);
						break;
					case 4:
						return ConvertToBoardState(board.data[0][1]);
						break;
					case 5:
					case 7:
						return ConvertToBoardState(board.data[0][2]);
						break;
				}
			}
		}

		// If we reach this point, there are no win conditions
		// Therefore we need to check if there are empty spaces
		for (unsigned i = 0; i < boardLength; i++)
		{
			for (unsigned j = 0; j < boardLength; j++)
			{
				if (board.data[i][j] == tsEMPTY)
					return bsOPEN;
			}
		}

		// If we reach this point, then the board is full and it is a tie
		return bsTIE;
	}

	//------------------------------------------------------------------------------
	// Private Function Declarations:
	//------------------------------------------------------------------------------

	// Converts a tile state to board state.
	// Only called if a win was confirmed, used to determine which player won
	// Should not be called with an empty space
	// Params:
	//   state = the tilestate to convert to a board state
	// Return:
	//   A bsWIN_ONE if the given value is tsPLAYER_ONE
	//   A bsWIN_TWO if the given value is tsPLAYER_TWO
	BoardState ConvertToBoardState(TileState state)
	{
		if (state == tsPLAYER_ONE)
			return bsWIN_ONE;
		else if (state == tsPLAYER_TWO)
			return bsWIN_TWO;
	}
}