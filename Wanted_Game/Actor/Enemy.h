#pragma once

#include "Math/Vector.h"
#include "Actor/Actor.h"

#include <queue>
#include <vector>
#include <stack>

using namespace Wanted;


class Enemy : public Actor
{
	RTTI_DECLARATIONS(Enemy, Actor)

public:
	Enemy(const Vector2& position);

	//void SetTarget(Player* player);

	virtual void Tick(float deltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void Draw() override;

	//void SetMoveChecker(ICanPlayerMove* c);

private:
	//Player* targetPlayer = nullptr;

	Wanted::Vector2 EnemyMapCalculation(const char* filename);

	int mapWidth = 0;
	int mapHeight = 0;
};