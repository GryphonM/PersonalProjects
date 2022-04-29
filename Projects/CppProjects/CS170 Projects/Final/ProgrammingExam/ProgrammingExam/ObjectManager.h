//------------------------------------------------------------------------------
//
// File Name:	ObjectManager.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS170 8.0.1 Assignment: Final Exam
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#pragma once
#include "GameObject.h"
#include <vector>

class ObjectManager
{
public:
    // Adds an object to the list of objects
    // Params:
    //   object_ = the object to add
    void AddObject(GameObject *object_);

    // Removes the first occurence of an object with the given name
    // Params:
    //   name_ = the name of the object to remove
    void RemoveObjectByName(std::string name_);

    // Removes all occurences of an object with the given name
    // Params:
    //   name_ = the name of the object to remove
    void RemoveAllObjectsByName(std::string name_);

    // Updates all objects in the array
    void Update();

    // Displays all objects in the array
    void Display();

    // Removes all objects in the array
    void Clear();

    // Destructor
    ~ObjectManager();

private:
    std::vector<GameObject *>objects;
};