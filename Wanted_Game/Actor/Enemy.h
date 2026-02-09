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
	bool bMapInitialized = false;

	// 이동 속도 조절용 멤버 (초 단위)
	float moveInterval = 0.2f; // 몇 초마다 한 칸 이동할지
	float moveTimer = 0.0f;    // 다음 이동까지 남은 시간

	bool FindPlayerPosition(Vector2& outPlayerPos) const;
	bool IsWalkable(const Vector2& pos) const;
	bool FindNextStepToPlayer(const Vector2& playerPos, Vector2& outNextPos);
};