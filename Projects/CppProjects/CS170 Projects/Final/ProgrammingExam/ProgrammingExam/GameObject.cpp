//------------------------------------------------------------------------------
//
// File Name:	GameObject.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS170 8.0.1 Assignment: Final Exam
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "GameObject.h"

GameObject::GameObject(std::string name_, Point center_) :
    name(name_), center(center_)
{
}

void GameObject::SetName(std::string name_)
{
    name = name_;
}

std::string GameObject::GetName() const
{
    return name;
}

void GameObject::SetCenter(Point center_)
{
    center = center_;
}

void GameObject::SetCenter(int x, int y)
{
    center.x = x;
    center.y = y;
}

Point GameObject::GetCenter() const
{
    return center;
}