#include "Enemy.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Player.h"
#include "Wall.h"
#include "Level/Level.h"
#include "Level/SokobanLevel.h"

#include "Game/Game.h"

#include "Interface/ICanPlayerMove.h"

#include <iostream>
#include <Windows.h>
#include <queue>
#include <vector>


namespace
{
	const int MAP_OFFSET_X = 16;
	const int MAP_OFFSET_Y = 0;
}

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
	super::Tick(deltaTime);

	Level* level = GetOwner();
	if (level != nullptr)
	{
		// *게임 클리어 시 Enemy 정지를 위해 다운캐스팅 사용.
		SokobanLevel* sokobanLevel = dynamic_cast<SokobanLevel*>(level);
		if (sokobanLevel != nullptr && sokobanLevel->isGameClear)
		{
			// 게임이 클리어되면 적은 움직이지 않습니다.
			return;
		}

		if (!bMapInitialized)
		{
			if (sokobanLevel != nullptr)
			{
				enemyMapFilename = sokobanLevel->GetCurrentMapFilename();
				Wanted::Vector2 mapSize = EnemyMapCalculation(enemyMapFilename);
				mapWidth = static_cast<int>(mapSize.x);
				mapHeight = static_cast<int>(mapSize.y);
				bMapInitialized = true;
			}
		}
	}

	// 이동 쿨타임 감소
	moveTimer -= deltaTime;
	if (moveTimer > 0.0f)
	{
		// 아직 다음 이동까지 시간이 남았으면 이번 프레임에는 이동하지 않음.
		return;
	}

	// 플레이어 위치 찾기 실패 시 아무 것도 하지 않음.
	Vector2 playerPos;
	if (!FindPlayerPosition(playerPos))
	{
		return;
	}

	// BFS로 플레이어까지의 최단 경로 중 다음 한 칸 계산.
	Vector2 nextPos;
	if (FindNextStepToPlayer(playerPos, nextPos))
	{
		SetPosition(nextPos);
		// 이동에 성공했다면 쿨타임 리셋.
		moveTimer = moveInterval;
	}
}

bool Enemy::FindPlayerPosition(Vector2& outPlayerPos) const
{
	Level* level = GetOwner();
	if (level == nullptr)
	{
		return false;
	}

	const std::vector<Actor*>& actors = level->GetActors();
	for (Actor* actor : actors)
	{
		if (actor != nullptr && actor->IsTypeOf<Player>())
		{
			outPlayerPos = actor->GetPosition();
			return true;
		}
	}

	return false;
}

bool Enemy::IsWalkable(const Vector2& pos) const
{
	// 맵 범위 밖이면 이동 불가.
	if (pos.x < MAP_OFFSET_X || pos.x >= MAP_OFFSET_X + mapWidth ||
		pos.y < MAP_OFFSET_Y || pos.y >= MAP_OFFSET_Y + mapHeight)
	{
		return false;
	}

	Level* level = GetOwner();
	if (level == nullptr)
	{
		return false;
	}

	const std::vector<Actor*>& actors = level->GetActors();
	for (Actor* actor : actors)
	{
		if (actor == nullptr)
		{
			continue;
		}

		if (actor->GetPosition() == pos)
		{
			// 벽이 있는 타일은 통과 불가.
			if (actor->IsTypeOf<Wall>())
			{
				return false;
			}
		}
	}

	return true;
}

bool Enemy::FindNextStepToPlayer(const Vector2& playerPos, Vector2& outNextPos)
{
	Vector2 startPos = GetPosition();

	// 이미 같은 칸이면 이동할 필요 없음.
	if (startPos == playerPos)
	{
		return false;
	}

	// 맵 크기가 유효하지 않으면 BFS 수행 불가.
	if (mapWidth <= 0 || mapHeight <= 0)
	{
		return false;
	}

	Level* level = GetOwner();


	// 월드 좌표를 맵 로컬 좌표로 변환.
	int sx = startPos.x - MAP_OFFSET_X;
	int sy = startPos.y - MAP_OFFSET_Y;

	// Enemy가 맵 영역 밖에 있으면 BFS 수행 안 함.
	if (sx < 0 || sx >= mapWidth || sy < 0 || sy >= mapHeight)
	{
		return false;
	}

	std::vector<std::vector<bool>> visited(
		static_cast<size_t>(mapHeight),
		std::vector<bool>(static_cast<size_t>(mapWidth), false));
	std::vector<std::vector<Vector2>> parent(
		static_cast<size_t>(mapHeight),
		std::vector<Vector2>(static_cast<size_t>(mapWidth), Vector2(-1, -1)));

	std::queue<Vector2> q;
	q.push(startPos);
	visited[sy][sx] = true;

	const Vector2 moveDir[4] =
	{
		Vector2(1, 0),
		Vector2(-1, 0),
		Vector2(0, 1),
		Vector2(0, -1)
	};

	bool found = false;

	while (!q.empty())
	{
		Vector2 cur = q.front();
		q.pop();

		if (cur == playerPos)
		{
			found = true;
			break;
		}

		for (int i = 0; i < 4; ++i)
		{
			int nx = cur.x + moveDir[i].x;
			int ny = cur.y + moveDir[i].y;

			Vector2 nextWorld(nx, ny);

			// 월드 좌표 기준으로 이동 가능 여부 체크.
			if (!IsWalkable(nextWorld))
			{
				continue;
			}

			// 맵 로컬 좌표로 변환 후 visited/parent 인덱싱.
			int lx = nx - MAP_OFFSET_X;
			int ly = ny - MAP_OFFSET_Y;

			if (lx < 0 || lx >= mapWidth || ly < 0 || ly >= mapHeight)
			{
				continue;
			}

			if (visited[ly][lx])
			{
				continue;
			}

			visited[ly][lx] = true;
			// parent에는 월드 좌표 저장.
			parent[ly][lx] = cur; 
			q.push(nextWorld);
		}
	}

	if (!found)
	{
		// 플레이어까지 가는 길이 없으면 이동하지 않음.
		return false;
	}

	// playerPos에서 startPos까지 parent를 역추적해서
	// startPos 바로 다음 칸을 outNextPos로 설정.
	Vector2 cur = playerPos;
	while (true)
	{
		int cx = cur.x - MAP_OFFSET_X;
		int cy = cur.y - MAP_OFFSET_Y;

		// 안전장치: 인덱스가 범위를 벗어나면 실패 처리.
		if (cx < 0 || cx >= mapWidth || cy < 0 || cy >= mapHeight)
		{
			return false;
		}

		if (parent[cy][cx] == startPos)
		{
			break;
		}

		cur = parent[cy][cx];
	}

	outNextPos = cur;
	return true;
}

void Enemy::Draw()
{
	super::Draw();
}

Wanted::Vector2 Enemy::EnemyMapCalculation(const std::string& filename)
{
	int width = 0;
	int height = 0;

	char path[2048] = {};
	sprintf_s(path, 2048, "../Assets/%s", filename.c_str());

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
	data = nullptr;
	fclose(file);

	return Wanted::Vector2(width, height);
}
