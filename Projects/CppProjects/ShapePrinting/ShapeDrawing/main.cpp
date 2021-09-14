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

//include files
#include <iostream>
#include <iomanip>

//function prototypes
void PrintRectangle(bool filled);
void PrintTriangle(bool filled);

//using statements
using std::cout;
using std::cin;

int main(void)
{
	int type;
	bool exit = false;

	while (!exit)
	{
		//ask user what kind of shape they want
		cout << "What would you like to draw?" << std::endl;
		cout << "1 - A Filled Rectangle" << std::endl;
		cout << "2 - A Non Filled Rectangle" << std::endl;
		cout << "3 - A Filled Triangle" << std::endl;
		cout << "4 - A Non Filled Triangle" << std::endl;
		cout << "Any Other Number - Exit" << std::endl;
		cout << "\nYour choice is: ";
		cin >> type;

		//call appropriate function based on type selected
		switch (type)
		{
		case 1:
			PrintRectangle(true);
			cout << std::endl;
			break;
		case 2:
			PrintRectangle(false);
			cout << std::endl;
			break;
		case 3:
			PrintTriangle(true);
			cout << std::endl;
			break;
		case 4:
			PrintTriangle(false);
			cout << std::endl;
			break;
		default:
			exit = true;
			cout << "Thank You for using our application!" << std::endl;
			break;
		}
	}
}

void PrintRectangle(bool filled)
{
	int x, y;
	cout << "Enter the rectangle's width and height values: ";
	cin >> x >> y;

	if (filled)
	{
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
			{
				cout << "*";
			}
			cout << std::endl;
		}
	}
	else
	{

	}
}

void PrintTriangle(bool filled)
{
	int x;
	std::cout << "Enter the triangle's height: ";
	std::cin >> x;

	if (filled)
	{

	}
	else
	{

	}
}