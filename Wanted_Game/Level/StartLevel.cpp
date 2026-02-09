#include "StartLevel.h"
#include "Game/Game.h"
#include "Core/Input.h"
#include "Util/Util.h"
#include "Render/Renderer.h"
#include <iostream>

StartLevel::StartLevel()
{
	// 메뉴 아이템 생성
	items.emplace_back(new StartMenuItem(
		"Start Game",
		[]()
		{
			// 메뉴 토글 함수 호출.
			Game::Get().StartGame();
		}
	));

	items.emplace_back(new StartMenuItem(
		"Quit Game",
		[]()
		{
			// 게임 종료.
			Game::Get().QuitEngine();
		}
	));
}

StartLevel::~StartLevel()
{
	for (StartMenuItem*& item : items)
	{
		{
			delete item;
			item = nullptr;
		}
		items.clear();
	}
}

void StartLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	static int length = static_cast<int>(items.size());
	// 입력 처리(방향키 위/아래, 엔터키, ESC키).
	if (Input::Get().GetKeyDown(VK_UP))
	{
		// 인덱스 돌리기 (위 방향으로).
		currentIndex = (currentIndex - 1 + length) % length;
	}

	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		// 인덱스 돌리기 (아래 방향으로).
		currentIndex = (currentIndex + 1) % length;
	}

	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		items[currentIndex]->onSelected();
	}
}

void StartLevel::Draw()
{
	// 메뉴 제목 출력.
	//Util::SetConsolePosition(Vector2::Zero);
	//Util::SetConsoleTextColor(Color::White);

	//std::cout << "Sokoban Game\n\n";

	Renderer::Get().SubmitCentered("Maze Runner", -2);

	// 메뉴 아이템 y좌표에 사용함.
	int y_offset = 0;

	// 메뉴 아이템 출력
	for (int ix = 0; ix < static_cast<int>(items.size()); ++ix)
	{
		Color textColor =
			(ix == currentIndex) ? selectedColor : unselectedColor;

		Renderer::Get().SubmitCentered(
			items[ix]->text,
			y_offset,
			textColor);

		// 메뉴 아이템 출력 후 줄바꿈.
		y_offset++;
	}
}
