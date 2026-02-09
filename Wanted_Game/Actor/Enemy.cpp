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

//void Enemy::SetTarget(Player* player)
//{
//	targetPlayer = player;
//}

void Enemy::BeginPlay()
{
}

void Enemy::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	Wanted::Vector2 mapSize = EnemyMapCalculation("Map.txt");
	mapWidth = static_cast<int>(mapSize.x);
	mapHeight = static_cast<int>(mapSize.y);

	//----------

	/*if (targetPlayer == nullptr)
	{
		return;
	}*/


	// ----------

	Vector2 start = GetPosition();
	//Vector2 destination = targetPlayer->GetPosition;

	Vector2 moveDir[4] = {
		{1,0}, {-1,0}, {0, 1}, {0,-1}
	};
	//std::vector<std::vector<bool>> discovered(mapHeight, std::vector<bool>(mapWidth, false));
	//std::vector <std::vector<Vector2>> parent(mapHeight, std::vector<Vector2>(mapWidth, { -1,-1 }));

	//std::queue<Vector2> q;
	//q.push(start);
	//discovered[start.y][start.x] = true;
	//parent[start.y][start.x] = start;

	//ICanPlayerMove*
	
}

void Enemy::Draw()
{
	super::Draw();
}

Wanted::Vector2 Enemy::EnemyMapCalculation(const char* filename)
{
	// 
	int width = 0;
	int height = 0;

	char path[2048] = {};
	sprintf_s(path, 2048, "../Assets/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, path, "rt");

	if (!file)
	{
		std::cerr << "Can't read the file for enemy BFS.\n";
		__debugbreak();
	}

	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	char* data = new char[fileSize + 1];
	fread(data, sizeof(char), fileSize, file);
	data[fileSize] = '\0';

	int index = 0;
	Wanted::Vector2 position;

	while (index < fileSize)
	{
		char mapCharacter = data[index];
		++index;

		if (mapCharacter == '\n')
		{
			++position.y;
			position.x = 0;
			continue;
		}

		if (position.x + 1 > width)
		{
			width = position.x + 1;
		}
		++position.x;
	}
	height = position.y + 1;

	delete[] data;
	fclose(file);

	return Wanted::Vector2(width, height);
}
