#pragma once

#include "Actor/Actor.h"

class TestActor : public Wanted::Actor
{
	RTTI_DECLARATIONS(TestActor, Actor)

		//public:
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;
};