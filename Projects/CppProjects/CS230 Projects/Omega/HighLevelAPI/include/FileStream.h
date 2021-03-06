//------------------------------------------------------------------------------
//
// File Name:	FileStream.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		CS230
//
// Copyright ? 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include <exception>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

namespace Beta
{
	class Vector2D;
}

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// Exception class for problems encountered while reading/writing from files
class FileStreamException : public std::exception
{
public:
	// Constructor
	// Params:
	//   fileName = The name of file that the stream was trying to read or write.
	//   errorDetails = The specific details of the error that occurred.
	FileStreamException(const std::string& fileName, const std::string& errorDetails);
};

// FileStream class - reads/writes data object data to/from files
// You are free to change the contents of this structure as long as you do not
// modify the public interface (function prototypes) declared in the header.
class FileStream
{
public:
	// Opens a file for loading.
	// Params:
	//   filename = The name of the file to open.
	//   mode = Whether to open the file for reading/writing, etc.
	FileStream(const std::string& filename, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out);

	// Closes the currently open file.
	~FileStream();

	// Begins a new scope when writing to a file.
	// Outputs a curly brace and increases the tab count.
	void BeginScope();

	// Ends the current scope when writing to a file.
	// Outputs an end curly brace and decreases tab count.
	void EndScope();

	// Writes a variable name and value to the currently open file.
	// Params:
	//   name = The name of the variable that will be written to the file.
	//   variable =  The value of the variable that will be written to the file.
	template<typename T>
	void WriteVariable(const std::string& name, const T& variable)
	{
		for (unsigned i = 0; i < indentLevel; i++)
			stream << tab;
		stream << name << " : " << variable << std::endl;
	}

	// Writes a value to the currently open file.
	// Params:
	//   value =  The value that will be written to the file.
	template<typename T>
	void WriteValue(const T& value)
	{
		for (unsigned i = 0; i < indentLevel; i++)
			stream << tab;
		stream << value << std::endl;
	}

	// Reads the value of a variable with the given name from the currently open file.
	// Params:
	//   name = The name of the variable that should be read from the file.
	//   variable = The variable that should hold the value from the file.
	template<typename T>
	void ReadVariable(const std::string& name, T& variable)
	{
		std::string word;
		stream >> word;
		if (word != name)
			throw FileStreamException(filename, name + " was not found");

		ReadSkip(':');
		stream >> variable;
	}

	// Reads the next value from the currently open file.
	// Params:
	//   value = The variable that should hold the value from the file.
	template<typename T>
	void ReadValue(T& value)
	{
		stream >> value;
	}

	// Reads a piece of text from the currently open file
	// and skips to the next word afterwards.
	// Params:
	//   text = The text to search for in the file.
	void ReadSkip(const std::string& text);

	// Skips characters in the stream up until the next
	// occurrence of the given delimiter.
	//    delimiter = The delimiter to search for in the file.
	void ReadSkip(char delimiter);

private:
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Checks if the file was opened correctly. If not, throws an exception.
	void CheckFileOpen();

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	std::fstream stream;	// The actual file stream
	std::string filename;	// File that was opened by the stream
	unsigned indentLevel;	// Number of tabs to print
	const char* tab = "  ";	// String to use for tabs
};
