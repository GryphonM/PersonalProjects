//------------------------------------------------------------------------------
//
// File Name:	FileName.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS230 8.2.5 Assignment: Serialization
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "FileStream.h"

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Constructor
// Params:
//   fileName = The name of file that the stream was trying to read or write.
//   errorDetails = The specific details of the error that occurred.
FileStreamException::FileStreamException(const std::string& fileName, const std::string& errorDetails) : 
	std::exception(("Error reading file " + fileName + ". " + errorDetails).c_str())
{
}

// Opens a file for loading.
// Params:
//   filename = The name of the file to open.
//   mode = Whether to open the file for reading/writing, etc.
FileStream::FileStream(const std::string& filename_, std::ios_base::openmode mode) : 
	stream(filename_.c_str(), mode), filename(filename_), indentLevel(0)
{
}

// Closes the currently open file.
FileStream::~FileStream()
{
	stream.close();
}

// Begins a new scope when writing to a file.
// Outputs a curly brace and increases the tab count.
void FileStream::BeginScope()
{
	try
	{
		CheckFileOpen();
		for (unsigned i = 0; i < indentLevel; i++)
			stream << tab;
		stream << "{" << std::endl;
		indentLevel++;
	}
	catch (FileStreamException exc)
	{
		std::cout << exc.what() << std::endl;
	}
}

// Ends the current scope when writing to a file.
// Outputs an end curly brace and decreases tab count.
void FileStream::EndScope()
{
	try
	{
		CheckFileOpen();
		indentLevel--;
		for (unsigned i = 0; i < indentLevel; i++)
			stream << tab;
		stream << "}" << std::endl;
	}
	catch (FileStreamException exc)
	{
		std::cout << exc.what() << std::endl;
	}
}

// Reads a piece of text from the currently open file
// and skips to the next word afterwards.
// Params:
//   text = The text to search for in the file.
void FileStream::ReadSkip(const std::string& text)
{
	try
	{
		CheckFileOpen();
		std::string input;
		stream >> input;
		if (input != text)
			throw FileStreamException(filename, text + "could not be found");
	}
	catch (FileStreamException exc)
	{
		std::cout << exc.what() << std::endl;
	}
}

// Skips characters in the stream up until the next
// occurrence of the given delimiter.
//    delimiter = The delimiter to search for in the file.
void FileStream::ReadSkip(char delimiter)
{
	try
	{
		CheckFileOpen();
		while (!stream.eof() || stream.get() != delimiter)
			stream.ignore();

		stream.ignore();
	}
	catch (FileStreamException exc)
	{
		std::cout << exc.what() << std::endl;
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Checks if the file was opened correctly. If not, throws an exception.
void FileStream::CheckFileOpen()
{
	if (!stream.is_open())
		throw FileStreamException(filename, "File was not open");
}