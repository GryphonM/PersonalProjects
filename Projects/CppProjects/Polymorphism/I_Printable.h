//------------------------------------------------------------------------------
//
// File Name:	I_Printable.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.2.9 Practice - Account Class with Polymorphism
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include <ostream>

#pragma once
class I_Printable
{
    // Overrides the output operator for all children of this class
    // Params:
    //   os = stream to output to
    //   obj = object to output
    // Return:
    //   Reference to the output stream
    friend std::ostream& operator<<(std::ostream& os, const I_Printable& obj);
public:
    // Ensure all children create a print function so
    // the overloaded output operator works
    virtual void print(std::ostream& os) const = 0;
    virtual ~I_Printable() = default;
};

