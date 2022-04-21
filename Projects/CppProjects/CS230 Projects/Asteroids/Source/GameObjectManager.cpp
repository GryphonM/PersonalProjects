//------------------------------------------------------------------------------
//
// File Name:	Component.cpp
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
#include "Space.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Collider.h"

//------------------------------------------------------------------------------

using namespace Beta;

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Constructor(s)
GameObjectManager::GameObjectManager(Space* space) : 
	BetaObject("ObjectManager", space), 
	numObjects(0), numArchetypes(0), fixedUpdateDt(1.f/60.f), timeAccumulator(0),
	gameObjectActiveList(), gameObjectArchetypes()
{

}

// Destructor
GameObjectManager::~GameObjectManager()
{
	Shutdown();
	Unload();
}

// Update all objects in the active game objects list.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameObjectManager::Update(float dt)
{
	if (!dynamic_cast<Space*>(GetOwner())->IsPaused())
	{
		VariableUpdate(dt);
		FixedUpdate(dt);
	}
	DestroyObjects();
	Draw();
}

// Shutdown the game object manager, destroying all active objects.
void GameObjectManager::Shutdown(void)
{
	for (int i = 0; i < numObjects; i++)
	{
		delete gameObjectActiveList[i];
	}
	numObjects = 0;
}

// Unload the game object manager, destroying all object archetypes.
void GameObjectManager::Unload(void)
{
	for (int i = 0; i < numArchetypes; i++)
	{
		delete gameObjectArchetypes[i];
	}
	numArchetypes = 0;
}

// Add a game object to the active game object list.
// Params:
//	 gameObject = Reference to the game object to be added to the list.
void GameObjectManager::AddObject(GameObject& gameObject)
{
	gameObject.SetOwner(GetOwner());
	gameObject.Initialize();
	gameObjectActiveList[numObjects] = &gameObject;
	numObjects++;
}

// Add a game object to the game object archetype list.
// Params:
//	 gameObject = Reference to the game object to be added to the list.
void GameObjectManager::AddArchetype(GameObject& gameObject)
{
	gameObjectArchetypes[numArchetypes] = &gameObject;
	numArchetypes++;
}

// Returns a pointer to the first active game object matching the specified name.
// Params:
//	 objectName = The name of the object to be returned, if found.
// Returns:
//   If the named object is found,
//	   then return the pointer to the named game object,
//	   else return nullptr.
GameObject* GameObjectManager::GetObjectByName(const std::string& objectName) const
{
	for (int i = 0; i < numObjects; i++)
	{
		if (gameObjectActiveList[i]->GetName() == objectName)
		{
			return gameObjectActiveList[i];
		}
	}
	return nullptr;
}

// Returns a pointer to the first game object archetype matching the specified name.
// Params:
//	 objectName = The name of the archetype to be returned, if found.
// Returns:
//   If the named archetype is found,
//	   then return the pointer to the named game object archetype,
//	   else return nullptr.
GameObject* GameObjectManager::GetArchetypeByName(const std::string& objectName) const
{
	for (int i = 0; i < numArchetypes; i++)
	{
		if (gameObjectArchetypes[i]->GetName() == objectName)
		{
			return gameObjectArchetypes[i];
		}
	}
	return nullptr;
}

// Returns the number of active objects with the given name.
// Params:
//   objectName = The name of the objects that should be counted.
size_t GameObjectManager::GetObjectCount(const std::string& objectName) const
{
	size_t count = 0;
	for (int i = 0; i < numObjects; i++)
	{
		if (gameObjectActiveList[i]->GetName() == objectName && !gameObjectActiveList[i]->IsDestroyed())
		{
			count++;
		}
	}
	return count;
}

// Update object logic using variable timestep.
void GameObjectManager::VariableUpdate(float dt)
{
	for (int i = 0; i < numObjects; i++)
	{
		gameObjectActiveList[i]->Update(dt);
	}
}

// Update object physics using fixed timestep.
void GameObjectManager::FixedUpdate(float dt)
{
	timeAccumulator += dt;
	while (timeAccumulator >= fixedUpdateDt)
	{
		for (int i = 0; i < numObjects; i++)
		{
			gameObjectActiveList[i]->FixedUpdate(fixedUpdateDt);
		}
		CheckCollisions();
		timeAccumulator -= fixedUpdateDt;
	}
}

// Check for collisions between pairs of objects
void GameObjectManager::CheckCollisions()
{	
	for (int i = 0; i < numObjects; i++)
	{
		if (!gameObjectActiveList[i]->IsDestroyed())
		{
			Collider* col = dynamic_cast<Collider*>(gameObjectActiveList[i]->GetComponent("Collider"));
			if (col != nullptr)
			{
				if ((i + 1) != numObjects)
				{
					for (int j = i + 1; j < numObjects; j++)
					{
						Collider* col2 = dynamic_cast<Collider*>(gameObjectActiveList[j]->GetComponent("Collider"));
						if (col2 != nullptr)
						{
							col->CheckCollision(*col2);
						}
					}
				}
			}
		}
	}
}

// Destroy any objects marked for destruction.
void GameObjectManager::DestroyObjects()
{
	for (int i = 0; i < numObjects; i++)
	{
		if (gameObjectActiveList[i]->IsDestroyed())
		{
			delete gameObjectActiveList[i];
			gameObjectActiveList[i] = gameObjectActiveList[numObjects - 1];
			gameObjectActiveList[numObjects - 1] = nullptr;
			numObjects--;
		}
	}
}

// Draw all game objects in the active game object list.
void GameObjectManager::Draw(void)
{
	for (int i = 0; i < numObjects; i++)
	{
		gameObjectActiveList[i]->Draw();
	}
}