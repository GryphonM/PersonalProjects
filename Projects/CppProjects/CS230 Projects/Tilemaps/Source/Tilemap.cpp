//------------------------------------------------------------------------------
//
// File Name:	Tilemap.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 8.0.1 Assignment: Tilemaps
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "Tilemap.h"
#include "Matrix2DStudent.h"

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Create a tilemap from the given parameters.
// Params:
//   numColumns = The width of the map.
//   numRows = The height of the map.
//   data = The array containing the map data.
Tilemap::Tilemap(unsigned numColumns_, unsigned numRows_, int** data_) : 
	numColumns(numColumns_), numRows(numRows_), data(data_)
{
}

// Destructor.
Tilemap::~Tilemap()
{
	for (int i = 0; i < numRows; i++)
		delete[] data[i];
	delete[] data;
}

// Gets the width of the map (in tiles).
unsigned Tilemap::GetWidth() const
{
	return numColumns;
}

// Get the height of the map (in tiles).
unsigned Tilemap::GetHeight() const
{
	return numRows;
}

// Gets the value of the cell in the map with the given indices.
// Params:
//   column = The column of the cell.
//   row = The row of the cell.
// Returns:
//   -1 if the indices are invalid, 0 if the cell is empty, 
//   or a positive integer otherwise.
int Tilemap::GetCellValue(unsigned column, unsigned row) const
{
	if (column < 0 || column > numColumns || row < 0 || row > numRows)
		return -1;
	return data[row][column];
}

// Create a tilemap from the given file.
// Params:
//   filename = The name of the file containing the tilemap data.
Tilemap* Tilemap::CreateTilemapFromFile(const std::string& filename)
{
	std::ifstream input(filename);
	if (!input.is_open())
		return nullptr;

	int columns;
	int rows;
	if (ReadIntegerVariable(input, "width", columns))
	{
		if (ReadIntegerVariable(input, "height", rows))
		{
			int** arr = ReadArrayVariable(input, "data", columns, rows);
			return new Tilemap(columns, rows, arr);
		}
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Helper function for reading in values of integers.
// Params:
//   file = The file stream to read from.
//   name = The text to look for before reading the value.
//   variable = If the name is valid, the variable to put the value in.
// Returns:
//   True if a value with the given name was found, false otherwise.
bool Tilemap::ReadIntegerVariable(std::ifstream& file, const std::string& name, int& variable)
{
	do
	{
		std::string input;
		file >> input;
		if (input == name)
		{
			file >> variable;
			return true;
		}
	} while (!file.eof());
	return false;
}

// Helper function for reading in arrays of integers.
// Params:
//   file = The file stream to read from.
//   name = The text to look for before reading the array.
//   columns = The number of columns in the array.
//   rows = The number of rows in the array.
// Returns:
//   A pointer to the dynamically allocated array if the data is valid, nullptr otherwise.
int** Tilemap::ReadArrayVariable(std::ifstream& file, const std::string& name,
	unsigned columns, unsigned rows)
{
	std::string input;
	file >> input;
	if (input != name || columns < 0 || rows < 0)
		return nullptr;

	int** arr = new int*[rows];
	for (int i = 0; i < rows; i++)
		arr[i] = new int[columns];

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
			file >> arr[i][j];
	}
	return arr;
}