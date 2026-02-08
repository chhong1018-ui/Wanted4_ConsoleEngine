#include "MenuLevel.h"
#include "Game/Game.h"
#include "Core/Input.h"
#include "Util/Util.h"
#include "Render/Renderer.h"
#include <iostream>

MenuLevel::MenuLevel()
{
	// 메뉴 아이템 생성
	items.emplace_back(new MenuItem(
		"Resume Game",
		[]()
		{
			// 메뉴 토글 함수 호출.
			Game::Get().ToggleMenu();
		}
	));

	items.emplace_back(new MenuItem(
		"Quit Game",
		[]()
		{
			// 게임 종료.
			Game::Get().QuitEngine();
		}
	));
}

MenuLevel::~MenuLevel()
{
	for (MenuItem*& item : items)
	{
		{
			delete item;
			item = nullptr;
		}
		items.clear();
	}
}

void MenuLevel::Tick(float deltaTime)
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

	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();

		currentIndex = 0;
	}
}

void MenuLevel::Draw()
{
	// 메뉴 제목 출력.
	//Util::SetConsolePosition(Vector2::Zero);
	//Util::SetConsoleTextColor(Color::White);

	//std::cout << "Sokoban Game\n\n";

	Renderer::Get().SubmitCentered("Maze Runner", 0);

	// 메뉴 아이템 출력
	for (int ix = 0; ix < static_cast<int>(items.size()); ++ix)
	{
		Color textColor =
			(ix == currentIndex) ? selectedColor : unselectedColor;

		Renderer::Get().SubmitCentered(
			items[ix]->text,
			2,
			textColor);

		//Util::SetConsoleTextColor(textColor);

		//std::cout << items[ix]->text << "\n";
	}
}
