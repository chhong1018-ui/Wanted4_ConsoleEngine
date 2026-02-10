#include "Game.h"
#include "Core/Input.h"
#include "Level/SokobanLevel.h"
#include "Level/MenuLevel.h"
#include "Level/StartLevel.h"
#include "Level/FinishLevel.h"
#include <iostream>

Game* Game::instance = nullptr;

Game::Game()
{
	instance = this;

	
	levels.emplace_back(new SokobanLevel());
	levels.emplace_back(new MenuLevel());
	levels.emplace_back(new StartLevel());
	levels.emplace_back(new FinishLevel());

	
	state = State::startGame;


	mainLevel = levels[2];
}

Level* Game::GetCurrentLevel()
{
	return mainLevel;
}

Game::~Game()
{
	
	mainLevel = nullptr;

	for (Level*& level : levels)
	{
		delete level;
		level = nullptr;
	}


	levels.clear();
}

void Game::StartGame()
{
	system("cls");

	int stateIndex = (int)state;	// static_cast
	int nextState = 2 - stateIndex;	// one - x.
	state = (State)nextState;

	mainLevel = levels[static_cast<int>(state)];
}

// sokobanLelvel.cpp의 Restart 이용 해 게임 재시작.
void Game::Restart()
{
	system("cls");

	SokobanLevel* sokobanLevelInstance = nullptr;
	for (Level* level : levels)
	{
		if (level->IsTypeOf<SokobanLevel>())
		{
			sokobanLevelInstance = static_cast<SokobanLevel*>(level);
			break;
		}
	}

	if (sokobanLevelInstance)
	{
		sokobanLevelInstance->Restart();
		mainLevel = sokobanLevelInstance;
		state = State::GamePlay;
	}
	else
	{
		std::cerr << "SokobanLevel instance not found for restart!\n";
		__debugbreak();
	}
}

void Game::GameFinish()
{
	system("cls");

	int stateIndex = (int)state;	// static_cast
	int nextState = stateIndex + 3;	// one - x.
	state = (State)nextState;

	mainLevel = levels[static_cast<int>(state)];
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
