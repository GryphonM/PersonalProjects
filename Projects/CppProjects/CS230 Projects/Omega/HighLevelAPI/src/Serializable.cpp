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
#include "Serializable.h"

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
// Loads object data from a file.
// Params:
//   stream = The stream for the file we want to read from.
void Serializable::Deserialize(FileStream& stream)
{
	UNREFERENCED_PARAMETER(stream);
}

// Saves object data to a file.
// Params:
//   stream = The stream for the file we want to write to.
void Serializable::Serialize(FileStream& stream) const
{
	UNREFERENCED_PARAMETER(stream);
}