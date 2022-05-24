//------------------------------------------------------------------------------
//
// File Name:	GameObject.cpp
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
#include "Component.h"
#include "Space.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "FileStream.h"

//------------------------------------------------------------------------------

using namespace Beta;

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

	// Create a new game object.
	// Params:
	//	 name = The name of the game object being created.
GameObject::GameObject(const std::string& name) : 
	components(), numComponents(0), isDestroyed(false), BetaObject(name)
{
}

// Clone a game object from another game object.
// Params:
//	 other = A reference to the object being cloned.
GameObject::GameObject(const GameObject& other) : 
	numComponents(other.numComponents), isDestroyed(other.isDestroyed), BetaObject(other.GetName())
{
	for (unsigned int i = 0; i < numComponents; i++)
	{
		components[i] = other.components[i]->Clone();
		components[i]->SetOwner(this);
	}
}

// Free the memory associated with a game object.
GameObject::~GameObject()
{
	for (unsigned int i = 0; i < numComponents; i++)
	{
		delete components[i];
	}
}

// Initialize this object's components and set it to active.
void GameObject::Initialize()
{
	for (unsigned int i = 0; i < numComponents; i++)
	{
		components[i]->Initialize();
	}
}

// Update any components attached to the game object.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameObject::Update(float dt)
{
	if (isDestroyed)
		return;

	for (unsigned int i = 0; i < numComponents; i++)
	{
		components[i]->Update(dt);
	}
}

// Updates components using a fixed timestep (usually just physics)
// Params:
//	 dt = A fixed change in time, usually 1/60th of a second.
void GameObject::FixedUpdate(float dt)
{
	if (isDestroyed)
		return;

	for (unsigned int i = 0; i < numComponents; i++)
	{
		components[i]->FixedUpdate(dt);
	}
}

// Draw any visible components attached to the game object.
void GameObject::Draw()
{
	for (unsigned int i = 0; i < numComponents; i++)
	{
		components[i]->Draw();
	}
}

// Adds a component to the object.
void GameObject::AddComponent(Component* component)
{
	component->SetOwner(this);
	components[numComponents] = component;
	numComponents++;
}

// Retrieves the component with the given name if it exists.
// Params:
//   name = The name of the component to find.
Component* GameObject::GetComponent(const std::string& name_)
{
	for (unsigned int i = 0; i < numComponents; i++)
	{
		if (components[i]->GetName() == name_)
		{
			return components[i];
		}
	}

	return nullptr;
}

// Mark an object for destruction.
void GameObject::Destroy()
{
	isDestroyed = true;
}

// Whether the object has been marked for destruction.
// Returns:
//		True if the object will be destroyed, false otherwise.
bool GameObject::IsDestroyed() const
{
	return isDestroyed;
}

// Get the space that contains this object.
Space* GameObject::GetSpace() const
{
	return dynamic_cast<Space*>(GetOwner());
}

// Loads object data from a file.
// Params:
//   stream = The stream for the file we want to read from.
void GameObject::Deserialize(FileStream& stream)
{
	try
	{
		stream.ReadSkip(GetName());
		stream.ReadSkip('{');
		unsigned components;
		stream.ReadVariable("numComponents", components);
		for (unsigned i = 0; i < components; i++)
		{
			std::string componentName;
			stream.ReadValue(componentName);
			Component* newComponent = EngineCore::GetInstance().GetModule<GameObjectFactory>()->CreateComponent(componentName);
			if (newComponent == nullptr)
				throw FileStreamException(componentName, "could not be found");
			AddComponent(newComponent);
			stream.ReadSkip('{');
			newComponent->Deserialize(stream);
			stream.ReadSkip('}');
		}
		stream.ReadSkip('}');
	}
	catch (FileStreamException exc)
	{
		std::cout << exc.what() << std::endl;
	};
}

// Saves object data to a file.
// Params:
//   stream = The stream for the file we want to write to.
void GameObject::Serialize(FileStream& stream) const
{
	stream.WriteValue(GetName());
	stream.BeginScope();
	stream.WriteVariable("numComponents", numComponents);
	for (unsigned i = 0; i < numComponents; i++)
	{
		stream.WriteValue(std::string(typeid(*components[i]).name()).substr(6));
		stream.BeginScope();
		components[i]->Serialize(stream);
		stream.EndScope();
	}
	stream.EndScope();
}