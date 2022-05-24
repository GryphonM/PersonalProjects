//------------------------------------------------------------------------------
//
// File Name:	GameObjectFactory.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS230 7.1.3 Assignment: Object Management
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameObjectFactory.h"
#include "GameObject.h"
#include "Component.h"
#include "SpriteSource.h"
#include "Sprite.h"
#include "FileStream.h"
#include "ColliderCircle.h"
#include "ColliderPoint.h"
#include "ColliderRectangle.h"
#include "ColliderTilemap.h"
#include "Animator.h"
#include "Sprite.h"
#include "RigidBody.h"
#include "Transform.h"

using namespace Beta;

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Register core components
GameObjectFactory::GameObjectFactory() : BetaObject("GameObjectFactory"), objectFilePath("Assets\\Objects\\")
{
	RegisterComponent<ColliderCircle>();
	RegisterComponent<ColliderPoint>();
	RegisterComponent<ColliderRectangle>();
	RegisterComponent<ColliderTilemap>();
	RegisterComponent<Animator>();
	RegisterComponent<Sprite>();
	RegisterComponent<RigidBody>();
	RegisterComponent<Transform>();
}

// Delete all registered components
GameObjectFactory::~GameObjectFactory()
{
	for (auto it = registeredComponents.begin(); it != registeredComponents.end(); it++)
	{
		delete (*it);
		(*it) = nullptr;
	}
}

// Create a single instance of the specified game object.
// Loads the object from a text file (if it exists).
// Params:
//   name = The name of the object.
//   mesh = The mesh used for the object's sprite (if any).
//   spriteSource = The sprite source used for the object's sprite (if any).
// Returns:
//	 If the object file exists and can be loaded, then return a pointer to a new instance 
//    of the specified game object type, else nullptr.
GameObject* GameObjectFactory::CreateObject(const std::string& name,
	Beta::Mesh* mesh, SpriteSource* spriteSource)
{
	GameObject* newObj = new GameObject(name);
	FileStream stream(objectFilePath + name + ".txt", std::fstream::in);
	try
	{
		newObj->Deserialize(stream);
		if (dynamic_cast<Sprite*>(newObj->GetComponent("Sprite")) != nullptr)
		{
			dynamic_cast<Sprite*>(newObj->GetComponent("Sprite"))->SetMesh(mesh);
			dynamic_cast<Sprite*>(newObj->GetComponent("Sprite"))->SetSpriteSource(spriteSource);
		}
	}
	catch (FileStreamException exc)
	{
		std::cout << exc.what() << std::endl;
		delete newObj;
		newObj = nullptr;
	};
	return newObj;
}

// Create a single instance of the specified component.
// Params:
//   name = The name of the component.
// Returns:
//	 If the component exists, then return a pointer to a new instance 
//    of the specified component, else nullptr.
Component* GameObjectFactory::CreateComponent(const std::string& name)
{
	for (auto it = registeredComponents.begin(); it != registeredComponents.end(); it++)
	{
		if (std::string(typeid(**it).name()) == name)
			return (*it)->Clone();
	}
	return nullptr;
}

// Saves an object to an archetype file so it can be loaded later.
void GameObjectFactory::SaveObjectToFile(GameObject* object)
{
	FileStream stream(objectFilePath + object->GetName() + ".txt", std::fstream::out);
	object->Serialize(stream);
	std::cout << object->GetName() << " was written to " << objectFilePath << object->GetName() << ".txt" << std::endl;
}