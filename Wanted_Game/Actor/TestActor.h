#pragma once

#include "Actor/Actor.h"
#include "Common/Common.h"

class TestActor : public Wanted::Actor
{
//public:
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;
};

