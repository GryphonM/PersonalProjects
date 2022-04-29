//------------------------------------------------------------------------------
//
// File Name:	ObjectManager.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS170 8.0.1 Assignment: Final Exam
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "ObjectManager.h"

void ObjectManager::AddObject(GameObject *object_)
{
	objects.push_back(object_);
}

void ObjectManager::RemoveObjectByName(std::string name_)
{
    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        if ((*it)->GetName().find(name_) != std::string::npos)
        {
            delete (*it);
            it = objects.erase(it);
            return;
        }
    }
}

void ObjectManager::RemoveAllObjectsByName(std::string name_)
{
    for (auto it = objects.begin(); it != objects.end();)
    {
        if ((*it)->GetName().find(name_) != std::string::npos)
        {
            delete (*it);
            it = objects.erase(it);
        }
        else
            it++;
    }
}

void ObjectManager::Update()
{
    for (auto it = objects.begin(); it != objects.end(); it++)
        (*it)->Update();
}

void ObjectManager::Display()
{
    for (auto it = objects.begin(); it != objects.end(); it++)
        (*it)->Display();
}

void ObjectManager::Clear()
{
    for (auto it = objects.begin(); it != objects.end(); it++)
        delete (*it);
    objects.clear();
}

ObjectManager::~ObjectManager()
{
    Clear();
}