//------------------------------------------------------------------------------
//
// File Name:	Enemy.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS170 8.0.1 Assignment: Final Exam
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
public:
    // Non-default constructor
    Enemy(std::string name_, Point center_);

    // Updates the object
    virtual void Update() override;

    // Displays the object
    virtual void Display() override;
};