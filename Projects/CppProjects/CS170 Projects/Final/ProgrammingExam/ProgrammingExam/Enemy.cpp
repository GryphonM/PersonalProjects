//------------------------------------------------------------------------------
//
// File Name:	Enemy.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS170 8.0.1 Assignment: Final Exam
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "Enemy.h"
#include <iostream>

Enemy::Enemy(std::string name_, Point center_) : GameObject(name_, center_)
{
}

void Enemy::Update()
{
	std::cout << "Updating The Following Enemy Object: " << GetName() << std::endl;
}

void Enemy::Display()
{
	std::cout << "Displaying The Following Enemy Object: " << GetName() << std::endl;
}