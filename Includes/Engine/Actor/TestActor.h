#pragma once

#include "Actor.h"
#include "Common/Common.h"

class WANTED_API TestActor : public Wanted::Actor
{
//public:
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;
};

