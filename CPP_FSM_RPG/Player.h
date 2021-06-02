#pragma once
#include "BaseGameEntity.h"
#include "Locations.h"

#define MAX_GOLD            3
#define COMFORT_LEVEL       5
#define TIREDNESS_THRESHOLD 5
#define THIRST_LEVEL        5

class Player;
class State
{
public:
	virtual ~State() {}

	virtual void Enter(Player*) abstract;
	virtual void Execute(Player*) abstract;
	virtual void Exit(Player*) abstract;
};

class Player : public BaseGameEntity
{
};

