// Level1.h
#pragma once

#include "BetaObject.h"

class Level1 : public Beta::BetaObject
{
public:
	Level1();

	void Initialize();
	void Update(float dt);
	void Shutdown();
};