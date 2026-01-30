#pragma once

#include "Actor/Actor.h"

class Player : public Wanted::Actor
{
	RTTI_DECLARATIONS(Player, Actor)

public:
	Player();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;
};