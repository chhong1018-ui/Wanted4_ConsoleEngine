#include "SokobanLevel.h"
#include "Actor/Player.h"
#include "Actor/Enemy.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/box.h"
#include "Actor/Enemy.h"
#include "Actor/Target.h"
#include "Util/Util.h"
#include "Render/Renderer.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/MenuLevel.h"
#include "Core/Input.h"
#include <iostream>

/*
#: 벽(Wall)
.: 바닥(Ground)
p: 플레이어(Player)
b: 박스(Box)
t: 타겟(Target)
*/

using namespace Wanted;

SokobanLevel::SokobanLevel()
{
	// 맵 크기 계산.
	Wanted::Vector2 mapSize = CalculateMapDimensions("Map.txt");
	mapWidth = static_cast<int>(mapSize.x);
	mapHeight = static_cast<int>(mapSize.y);

	// 화면 크기 가져오기.
	Wanted::Vector2 screenSize = Renderer::Get().GetScreenSize();

	// 중앙 정렬 오프셋 계산.
	int startX = (screenSize.x - mapWidth) / 2;
	int startY = (screenSize.y - mapHeight) / 2;

	// 맵 로드.
	LoadMap("Map.txt", 16,0);
}

void SokobanLevel::Draw()
{
	super::Draw();

	// 게임 클리어인 경우. 메시지 출력.
	if (isGameClear)
	{
		/*
		Util::SetConsolePosition(Vector2(30, 0));
		Util::SetConsoleTextColor(Color::White);
		std::cout << "Game Clear!" << std::endl;
		*/
		// "Game Clear!"가 Renderer의 버퍼에 안들어가 있어 화면에 안보이는 문제 발생.
		// Renderer/Renderer.h 추가하고 std::cout에서 Renderer::Get().Submit으로 변경해 렌더러에서 출력하도록 변경함.

		// Vector2(30, 0)으로 실행 시 "Game Clear"로 느낌표가 잘려 출력 됨.
		// "Game Clear!" 이미지까지 모두 프레임 내부에 출력되도록 최종으로 X 위치를 29로 변경.
		Renderer::Get().SubmitCentered(
			"           Game Clear!            ",
			-2,
			Color::Green
		);
		Renderer::Get().SubmitCentered(
			"                                  ",
			-1,
			Color::Black
		);
		Renderer::Get().SubmitCentered(
			" Press ESC to return to the menu. ",
			0,
			Color::Green
		);
		Renderer::Get().SubmitCentered(
			"                                  ",
			1,
			Color::Black
		);
		Renderer::Get().SubmitCentered(
			"        Press 'Q' to Quit.        ",
			2,
			Color::Green
		);
	}

	if (isGameOver)
	{
		Renderer::Get().SubmitCentered(
			" Game Over. Returning to Menu in 2s... ",
			-1,
			Color::Red
		);
		Renderer::Get().SubmitCentered(
			"                                       ",
			0,
			Color::Black
		);
		Renderer::Get().SubmitCentered(
			"   Or you can press 'Q' to Quit Game.  ",
			1,
			Color::Red
		);

		// 게임 오버 시 타이머 처리는 Tick 함수에서 수행됩니다.
	}
}

void SokobanLevel::Tick(float deltaTime)
{
	Level::Tick(deltaTime);
	
	isGameClear = CheckGameClear();

	isGameOver = CheckGameOver();

	// 게임 오버 상태가 되었고, 아직 타이머가 시작되지 않았다면 타이머 시작
	if (isGameOver != isWaitingForToggle)
	{
		isWaitingForToggle = true;
		GameOverTimer = 2.0f; // 2초 대기 시간 설정
	}

	// 타이머가 활성화된 경우 시간 감소
	if (isWaitingForToggle)
	{
		GameOverTimer -= deltaTime;

		// 타이머가 만료되면 메뉴로 전환
		if (GameOverTimer <= 0.0f)
		{
			Game::Get().ToggleMenu();
			isWaitingForToggle = false; // 타이머 비활성화
		}
	}
}

void SokobanLevel::SetMoveChecker(ICanPlayerMove* checker)
{
	moveChecker = checker;
}

void SokobanLevel::LoadMap(const char* filename, int startX, int startY)
{
	mapWidth = 0;
	mapHeight = 0;

	// 파일 로드.
	// 최종 파일 경로 만들기. ("../Assets/filename")
	char path[2048] = {};
	sprintf_s(path, 2048, "../Assets/%s", filename);

	// 파일 열기.
	FILE* file = nullptr;
	fopen_s(&file, path, "rt");

	// 예외 처리.
	if (!file)
	{
		// 표준 오류 콘솔 활용.
		std::cerr << "Failed to open map file.\n";

		// 디버그 모드에서 중단점으로 중단해주는 기능.
		__debugbreak();
	}

	// 맵 읽기.
	// 맵 크기 파악: File Position 포인터를 파일의 끝으로 이동.
	fseek(file, 0, SEEK_END);

	// 이 위치 읽기.
	size_t fileSize = ftell(file);

	// File Position 처음으로 되돌리기.
	rewind(file);

	// 파일에서 데이터를 읽어올 버퍼 생성.
	char* data = new char[fileSize + 1];

	// 데이터 읽기.
	size_t readSize = fread(data, sizeof(char), fileSize, file);

	// 읽어온 문자열을 분석(파싱-Parsing)해서 출력.
	// 인덱스를 사용해 한문자씩 읽기.
	int index = 0;

	// 객체를 생성할 위치 값.
	Wanted::Vector2 position;

	while (true)
	{
		// 종료 조건.
		if (index >= fileSize)
		{
			break;
		}

		// 캐릭터 읽기.
		char mapCharacter = data[index];
		++index;

		// 개행 문자 처리.
		if (mapCharacter == '\n')
		{
			//std::cout << "\n";
			// y좌표는 하나 늘리고, x 좌표 초기화.
			++position.y;
			position.x = 0;
			continue;
		}

		/*
		#: 벽(Wall)
		.: 바닥(Ground)
		p: 플레이어(Player)
		b: 박스(Box)
		t: 타겟(Target)
		*/
		// 한문자씩 처리.
		switch (mapCharacter)
		{
		case '#':
			//std::cout << "#";
			AddNewActor(new Wall(Vector2(position.x + startX, position.y + startY)));
			break;
		case '.':
			//std::cout << " ";
			AddNewActor(new Ground(Vector2(position.x + startX, position.y + startY)));
			break;
		case 'p':
			//std::cout << "P";
			// 플레이어도 이동 가능함.
			// 플레이어 밑에 땅이 있어야 함.
			//player = new Player(Vector2(position.x + startX, position.y + startY));
			//AddNewActor(player);
			AddNewActor(new Player(Vector2(position.x + startX, position.y + startY)));
			AddNewActor(new Ground(Vector2(position.x + startX, position.y + startY)));
			break;
		case 'b':
			//std::cout << "B";
			// 박스는 이동 가능함.
			// 박스가 옮겨졌을 때 그 밑에 땅이 있어야 함.
			AddNewActor(new Box(Vector2(position.x + startX, position.y + startY)));
			AddNewActor(new Ground(Vector2(position.x + startX, position.y + startY)));
			break;
		case 't':
			//std::cout << "T";
			AddNewActor(new Target(Vector2(position.x + startX, position.y + startY)));
			break;
		case 'e':
			// Enemy는 이동 가능함.
			// Enemy가 옮겨졌을 때 그 밑에 땅이 있어야 함.
			Enemy * enemy = new Enemy(Vector2(position.x + startX, position.y + startY));
			//enemy->SetTarget(player);                // 플레이어 연결
			//enemy->SetMoveChecker(this);

			AddNewActor(enemy);
			AddNewActor(new Ground(Vector2(position.x + startX, position.y + startY)));
			break;
		}

		// x 좌표 증가 처리.
		if (position.x + 1 > mapWidth)
		{
			mapWidth = position.x + 1;
		}
		++position.x;
	}

	mapHeight = position.y + 1; // After the loop, position.y holds the last row index.

	// 사용한 버퍼 해제.
	delete[] data;

	// 파일이 정상적으로 열렸으면 닫기.
	fclose(file);
}

bool SokobanLevel::CanMove(
	const Wanted::Vector2& playerPosition,
	const Wanted::Vector2& nextPosition)
{
	// 게임 클리어인 경우 플레이어 방향조작 중단.
	if (isGameClear)
	{
		return false;
	}

	if (isGameOver)
	{
		return false;
	}

	// -> 이동하려는 곳에 있는 액터가 벽이 아니면 이동 가능.
	for (Actor* const actor : actors)
	{
		// 먼저, 이동하려는 위치에 있는 액터 검색.
		if (actor->GetPosition() == nextPosition)
		{
			// 이 액터가 벽인지 확인.
			if (actor->IsTypeOf<Wall>())
			{
				return false;
			}

			// 그라운드 또는 타겟.
			return true;
		}
	}

	// 에러.
	return false;
}

bool SokobanLevel::CheckGameClear()
{
	for (Actor* const actor : actors)
	{
		if (!actor->IsTypeOf<Player>())
			continue;

		Vector2 playerPosition = actor->GetPosition();

		for (Actor* const other : actors)
		{
			if (!other->IsTypeOf<Target>())
				continue;

			if (playerPosition == other->GetPosition())
			{
				return true;   // 즉시 클리어
			}
		}
	}

	return false;
}


//게임 오버 판정
bool SokobanLevel::CheckGameOver()
{
	for (Actor* const actor : actors)
	{
		if (!actor->IsTypeOf<Player>())
			continue;

		Vector2 playerPosition = actor->GetPosition();

		for (Actor* const other : actors)
		{
			if (!other->IsTypeOf<Enemy>())
				continue;

			// enemy와 player의 위치가 같다면 게임 오버.
			if (playerPosition == other->GetPosition())
			{
				return true;
			}
		}
	}

	return false;
}

Wanted::Vector2 SokobanLevel::CalculateMapDimensions(const char* filename)
{
	int width = 0;
	int height = 0;

	char path[2048] = {};
	sprintf_s(path, 2048, "../Assets/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, path, "rt");

	if (!file)
	{
		std::cerr << "Failed to open map file for dimension calculation.\n";
		__debugbreak();
	}

	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	char* data = new char[fileSize + 1];
	fread(data, sizeof(char), fileSize, file);
	data[fileSize] = '\0'; // Null-terminate the string

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