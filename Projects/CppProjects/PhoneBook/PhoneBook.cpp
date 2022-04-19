//------------------------------------------------------------------------------
//
// File Name:	PhoneBook.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 8.3.8 Assignment: Phone Book
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "PhoneBook.h"
#include <fstream>
#include <iostream>
#include <algorithm>

//------------------------------------------------------------------------------
// Phone Book Functions:
//------------------------------------------------------------------------------
bool Sort(const PhoneEntry* lhs, const PhoneEntry* rhs)
{
    return lhs->name < rhs->name;
}

//------------------------------------------------------------------------------
// Phone Entry Functions:
//------------------------------------------------------------------------------
// Constructor for a single phone entry with all the values passed in.
PhoneEntry::PhoneEntry(std::string name_, std::string last_name_,
    std::string email_, int region_, int number_) : 
    name(name_), last_name(last_name_), email(email_), region(region_), number(number_)
{
}

//------------------------------------------------------------------------------
// Phone Book Functions:
//------------------------------------------------------------------------------

// Constructor for a full phonebook with initial value found in passed in file.
PhoneBook::PhoneBook(std::string filename_)
{
    std::ifstream inFile(filename_);

    if (!inFile.is_open())
        std::cout << "Can't open file" << std::endl;
    else
    {
        while (!inFile.eof())
        {
            // Name
            std::string name;
            std::string last_name;
            inFile >> name;
            if (name == "")
                continue;
            inFile >> last_name;

            // Email
            std::string email;
            inFile >> email;

            // Number
            int region;
            int number;
            inFile >> region;
            char cbuffer;
            inFile.get(cbuffer);
            inFile >> number;

            // Clear *
            std::string buffer;
            inFile >> buffer;

            // Add Entry
            PhoneEntry* newEntry = new PhoneEntry(name, last_name, email, region, number);
            entries.push_back(newEntry);
        }
    }
}

// Copy Constructor
PhoneBook::PhoneBook(const PhoneBook& copy_)
{
    for (auto it = copy_.entries.begin(); it != copy_.entries.end(); it++)
        AddEntry((*it)->name, (*it)->last_name, (*it)->email, (*it)->region, (*it)->number);
}

// Overloads the assignment operator
// Params:
//   rhs_ = The value to apply to this array
// Return:
//   Reference to this object
PhoneBook& PhoneBook::operator=(const PhoneBook& rhs_)
{
    // Empty Array
    for (auto it = entries.begin(); it != entries.end(); it++)
        delete (*it);
    entries.clear();

    // Assign Array
    for (auto it = rhs_.entries.begin(); it != rhs_.entries.end(); it++)
        AddEntry((*it)->name, (*it)->last_name, (*it)->email, (*it)->region, (*it)->number);

    return *this;
}

// Saves the contents of the PhoneBook to the given file
// Params:
//   filename_ = the file to save the PhoneBook to
void PhoneBook::Save(std::string filename_) const
{
    std::ofstream outFile;
    outFile.open(filename_);

    if (outFile.is_open())
        outFile << *this;
    else
        std::cout << "Couldn't Output to File" << std::endl;

    outFile.close();
}

// Adds an entry to the end of the phone book
// Params:
//   The values of the new entry
void PhoneBook::AddEntry(const std::string& name_, const std::string& last_name_, const std::string& email_, int region_, int number_)
{
    PhoneEntry* newEntry = new PhoneEntry(name_, last_name_, email_, region_, number_);
    entries.push_back(newEntry);
}

// Sorts the entries of the phone book by first name
void PhoneBook::SortByName()
{
    std::sort(entries.begin(), entries.end(), Sort);
}

// Removes the first occurence of a first name with the given substring
// Params:
//   subString_ = the substring to look for in the first name
void PhoneBook::RemoveEntriesByName(std::string subString_)
{
    for (auto it = entries.begin(); it != entries.end();)
    {
        if ((*it)->name.find(subString_) != std::string::npos)
        {
            delete (*it);
            it = entries.erase(it);
        }
        else
            it++;
    }
}

// Overloads the output operator to print out the full phone book
// Params:
//   os_ = the stream to output to
//   phonebook_ = the object to print
// Return:
//   reference to the stream that was output
std::ostream& operator<<(std::ostream& os_, const PhoneBook& phonebook_)
{
    for (auto entry = phonebook_.entries.begin(); entry != phonebook_.entries.end(); entry++)
    {
        os_ << (*entry)->name << " " << (*entry)->last_name << "\n";
        os_ << (*entry)->email << "\n";
        os_ << (*entry)->region << "-" << (*entry)->number << "\n";
        os_ << "*" << std::endl;
    }

    return os_;
}

// Destructor, deletes the dynamically allocated entries.
PhoneBook::~PhoneBook() 
{
    for (auto it = entries.begin(); it != entries.end(); it++)
    {
        delete (*it);
    }
}