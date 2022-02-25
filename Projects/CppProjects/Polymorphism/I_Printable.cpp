//------------------------------------------------------------------------------
//
// File Name:	I_Printable.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.2.9 Practice - Account Class with Polymorphism
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "I_Printable.h"

// Overrides the output operator for all children of this class
// Params:
//   os = stream to output to
//   obj = object to output
// Return:
//   Reference to the output stream
std::ostream& operator<<(std::ostream& os, const I_Printable& obj)
{
	obj.print(os);
	return os;
}