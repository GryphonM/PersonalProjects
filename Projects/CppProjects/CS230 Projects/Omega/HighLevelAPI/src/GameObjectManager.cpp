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
	for (auto it = gameObjectActiveList.begin(); it != gameObjectActiveList.end(); it++)
	{
		delete (*it);
		(*it) = nullptr;
	}
	gameObjectActiveList.clear();
	numObjects = 0;
}

// Unload the game object manager, destroying all object archetypes.
void GameObjectManager::Unload(void)
{
	for (auto it = gameObjectArchetypes.begin(); it != gameObjectArchetypes.end(); it++)
	{
		delete (*it);
		(*it) = nullptr;
	}
	gameObjectArchetypes.clear();
	numArchetypes = 0;
}

// Add a game object to the active game object list.
// Params:
//	 gameObject = Reference to the game object to be added to the list.
void GameObjectManager::AddObject(GameObject& gameObject)
{
	gameObject.SetOwner(GetOwner());
	gameObject.Initialize();
	gameObjectActiveList.push_back(&gameObject);
	numObjects++;
}

// Add a game object to the game object archetype list.
// Params:
//	 gameObject = Reference to the game object to be added to the list.
void GameObjectManager::AddArchetype(GameObject& gameObject)
{
	gameObjectArchetypes.push_back(&gameObject);
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
	for (auto it = gameObjectActiveList.begin(); it != gameObjectActiveList.end(); it++)
	{
		if ((*it)->GetName() == objectName)
		{
			return *it;
		}
	}
	return nullptr;
}

// Returns a pointer to all the active game objects matching the specified name.
// Params:
//	 objectName = The name of the object to be returned, if found.
// Returns:
//   If the named object is found,
//	   then return the pointer to an array of objects
//	   else return nullptr.
void GameObjectManager::GetObjectsByName(const std::string& objectName, std::vector<GameObject*>& out) const
{
	for (auto it = gameObjectActiveList.begin(); it != gameObjectActiveList.end(); it++)
	{
		if ((*it)->GetName() == objectName)
			out.push_back(*it);
	}
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
	for (auto it = gameObjectArchetypes.begin(); it != gameObjectArchetypes.end(); it++)
	{
		if ((*it)->GetName() == objectName)
		{
			return (*it);
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
	for (auto it = gameObjectActiveList.begin(); it != gameObjectActiveList.end(); it++)
	{
		if ((*it)->GetName() == objectName && !(*it)->IsDestroyed())
		{
			count++;
		}
	}
	return count;
}

// Update object logic using variable timestep.
void GameObjectManager::VariableUpdate(float dt)
{
	if (EngineGetModule(Input)->CheckTriggered(' '))
		dt = 1 * dt;
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
			Collider* col = dynamic_cast<Collider*>(gameObjectActiveList[i]->GetComponent<Collider>());
			if (col != nullptr)
			{
				if (i + 1 != numObjects)
				{
					for (int j = i + 1; j < numObjects; j++)
					{
						Collider* col2 = dynamic_cast<Collider*>(gameObjectActiveList[j]->GetComponent<Collider>());
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
	for (auto it = gameObjectActiveList.begin(); it != gameObjectActiveList.end();)
	{
		if ((*it)->IsDestroyed())
		{
			delete (*it);
			(*it) = nullptr;
			it = gameObjectActiveList.erase(it);
			numObjects--;
		}
		else
			it++;
	}
}

// Draw all game objects in the active game object list.
void GameObjectManager::Draw(void)
{
	for (auto it = gameObjectActiveList.begin(); it != gameObjectActiveList.end(); it++)
	{
		(*it)->Draw();
	}
}