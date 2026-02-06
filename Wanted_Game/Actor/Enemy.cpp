#include "Enemy.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Actor/Box.h"
#include "Level/Level.h"
#include "Level/SokobanLevel.h"

#include "Game/Game.h"

#include "Interface/ICanPlayerMove.h"

#include <iostream>
#include <Windows.h>

Enemy::Enemy(const Vector2& position)
	: super("E", position, Color::Red)
{
	// 그리기 우선순위 높게 설정.
	sortingOrder = 11;
}

void Enemy::BeginPlay()
{
}

void Enemy::Tick(float deltaTime)
{
}

void Enemy::Draw()
{
	super::Draw();
}
