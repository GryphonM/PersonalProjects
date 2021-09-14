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

// Prints a filled or not filled rectangle based on the parameter passed into it
// Params:
//   filled = tells the function whether to print a filled in rectangle or an empty rectangle
void PrintRectangle(bool filled)
{
	int x, y;
	cout << "\nEnter the rectangle's width and height values: ";
	cin >> x >> y;

	//check if incorrect values were given
	if (x <= 0)
		cout << "The width must be at least 1" << std::endl;
	else if (y <= 0)
		cout << "The height must be at least 1" << std::endl;

	if (filled)
	{
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
				cout << "*";
			cout << std::endl;
		}
	}
	else
	{
		//set i equal to 1 so it can be compared directly to y.
		//the if statement can then easily compare these values
		for (int i = 1; i <= y; i++)
		{
			/* Version that loops less using std::setw()
			if (i == 1 || i == y)
			{
				for (int j = 0; j < x; j++)
					cout << "*";
			}
			else
			{
				int width = x - 1;
				cout << "*" << std::setw(width) << "*";
			}
			cout << std::endl;*/
			
			for (int j = 1; j <= x; j++)
			{
				//these cases are when something should be printed, otherwise only a space is needed
				if (i == 1 || i == y || j == 1 || j == x)
					cout << "*";
				else
					cout << " ";
			}
			cout << std::endl;
		}
	}
}

// Prints a filled or not filled triangle based on the parameter passed into it
// Params:
//   filled = tells the function whether to print a filled in triangle or an empty triangle
void PrintTriangle(bool filled)
{
	int height;
	cout << "\nEnter the triangle's height: ";
	cin >> height;

	//check if incorrect value was given
	if (height <= 0)
		cout << "The height must be at least 1" << std::endl;

	if (filled)
	{
		for (int i = 0; i < height; i++)
		{
			int width = height - i;
			cout.width(width);
			for (int j = 0; j <= 2 * i; j++)
				cout << "*";
			cout << std::endl;
		}
	}
	else
	{
		for (int i = 0; i < height; i++)
		{
			int width = height - i;
			cout.width(width);

			/* Version that loops less using std::setw()
			if (i == 0 || i == height - 1)
			{
				for (int j = 0; j <= 2 * i; j++)
					cout << "*";
			}
			else
			{
				int width = 2 * i;
				cout << "*" << std::setw(width) << "*";
			}
			cout << std::endl;*/
			
			//these cases are when something should be printed, otherwise only a space is needed
			for (int j = 0; j <= 2 * i; j++)
			{
				if (i == 0 || i == height - 1 || j == 0 || j == 2 * i)
					cout << "*";
				else
					cout << " ";
			}
			cout << std::endl;
		}
	}
}