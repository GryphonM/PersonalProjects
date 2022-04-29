//------------------------------------------------------------------------------
//
// File Name:	Hero.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS170 8.0.1 Assignment: Final Exam
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "Hero.h"
#include <iostream>

Hero::Hero(std::string name_, Point center_, int maxItems) : GameObject(name_, center_), items_count(maxItems)
{
    items = new int[maxItems];
    for (int i = 0; i < maxItems; i++)
        items[i] = 0;
}

Hero::Hero(const Hero& other) : GameObject(other.GetName(), other.GetCenter()), items_count(other.items_count)
{
    items = new int[items_count];
    for (int i = 0; i < items_count; i++)
        items[i] = other.items[i];
}

Hero::~Hero()
{
    delete[] items;
}

Hero& Hero::operator=(const Hero& other)
{
    SetName(other.GetName());
    SetCenter(other.GetCenter());
    items_count = other.items_count;
    delete[] items;
    items = new int[items_count];
    for (int i = 0; i < items_count; i++)
        items[i] = other.items[i];
    return *this;
}

void Hero::IncrementItem(int index_)
{
    if (index_ >= 0 && index_ < items_count)
    {
        ++items[index_];
    }
}

void Hero::Update()
{
    std::cout << "Updating The Following Hero Object: " << GetName() << std::endl;
}

void Hero::Display()
{
    std::cout << "Displaying The Following Hero Object: " << GetName() << std::endl;
    for (int i = 0; i < items_count; i++)
        std::cout << "Item " << i + 1 << ": " << items[i] << std::endl;
}
