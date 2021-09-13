//------------------------------------------------------------------------------
//
// File Name:	main.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 5.2.7 Assignment - Console I/O and Iteration in C++
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include <iostream>
#include <iomanip>

int main(void)
{
	using namespace std;
	
	int type;

	//ask user what kind of shape they want
	cout << "What would you like to draw?" << endl;
	cout << "1 - A Filled Rectangle" << endl;
	cout << "2 - A Non Filled Rectangle" << endl;
	cout << "3 - A Filled Triangle" << endl;
	cout << "4 - A Non Filled Triangle" << endl;
	cout << "\nYour choice is: ";
	cin >> type;

	//call appropriate function based on type selected
	switch (type)
	{
		case 1:
			PrintRectangle(true);
		case 2:
			PrintRectangle(false);
	}
}

void PrintRectangle(bool filled)
{
	int x, y;
	cout << "Enter the rectangle's width and height values: ";
	cin >> x >> y;
}