#include "Game.h"
#include <iostream>
#include "Level/SokobanLevel.h"
#include "Level/MenuLevel.h"

Game* Game::instance = nullptr;

Game::Game()
{
	instance = this;

	// �� ���� ���� �� �迭�� �߰�
	levels.emplace_back(new SokobanLevel());
	levels.emplace_back(new MenuLevel());

	// ���� ����(����) ����.
	state = State::Menu;

	// ���� ���� �� Ȱ��ȭ �� ���� ����.
	mainLevel = levels[1];
}

Level* Game::GetCurrentLevel()
{
	return mainLevel;
}

Game::~Game()
{
	// �ߺ� ���� ����.
	mainLevel = nullptr;

	// ��� ���� ����.
	for (Level*& level : levels)
	{
		delete level;
		level = nullptr;
	}

	// �迭 ����.
	levels.clear();
}

// todo: ���Ӻ��� �޴��� ���� ������, ���� �޴� �߰�.
void Game::StartGame()
{

}

void Game::ToggleMenu()
{
	// cls -> clear screen.
	system("cls");

	int stateIndex = (int)state;	// static_cast
	int nextState = 1 - stateIndex;	// one - x.
	state = (State)nextState;	

	mainLevel = levels[static_cast<int>(state)];
}

Game& Game::Get()
{
	if (!instance)
	{
		std::cerr << "Game::Get() - instance is null\n";
		__debugbreak();
	}

	return *instance;
}
