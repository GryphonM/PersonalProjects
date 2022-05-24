//------------------------------------------------------------------------------
//
// File Name:	GameObjectFactory.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include <BetaObject.h>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class GameObject;
class Component;
class SpriteSource;

namespace Beta
{
	class Mesh;
}

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class GameObjectFactory : public Beta::BetaObject
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Register core components
	GameObjectFactory();

	// Delete all registered components
	~GameObjectFactory();

	// Create a single instance of the specified game object.
	// Loads the object from a text file (if it exists).
	// Params:
	//   name = The name of the object.
	//   mesh = The mesh used for the object's sprite (if any).
	//   spriteSource = The sprite source used for the object's sprite (if any).
	// Returns:
	//	 If the object file exists and can be loaded, then return a pointer to a new instance 
	//    of the specified game object type, else nullptr.
	GameObject* CreateObject(const std::string& name, 
		Beta::Mesh* mesh = nullptr, SpriteSource* spriteSource = nullptr);

	// Create a single instance of the specified component.
	// Params:
	//   name = The name of the component.
	// Returns:
	//	 If the component exists, then return a pointer to a new instance 
	//    of the specified component, else nullptr.
	Component* CreateComponent(const std::string& name);

	// Saves an object to an archetype file so it can be loaded later.
	void SaveObjectToFile(GameObject* object);

	// Register a component so it can be created on the fly.
	// Template parameters:
	//   ComponentType = The type of the component to be registered.
	template <class ComponentType>
	void RegisterComponent()
	{
		registeredComponents.push_back(new ComponentType());
	}

private:
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Disable copy and assign to prevent accidental copies
	GameObjectFactory(const GameObjectFactory&) = delete;
	GameObjectFactory& operator=(const GameObjectFactory&) = delete;

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Array containing all components used by objects.
	std::vector<Component*> registeredComponents;

	std::string objectFilePath;
};

//------------------------------------------------------------------------------
