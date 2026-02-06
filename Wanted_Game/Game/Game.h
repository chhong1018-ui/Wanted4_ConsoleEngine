#pragma once

#include "Engine/Engine.h"
#include <vector>

using namespace Wanted;

// 레벨 관리에 사용할 열거형
enum class State
{
	//None = -1,
	GamePlay = 0,
	Menu = 1, 
	Length
};

class Game : public Wanted::Engine
{
public:
	Game();
	~Game();

	void StartGame();

	void ToggleMenu();

	static Game& Get();

private:
	//
	std::vector<Level*> levels;

	// 현재 활성화 된 
	State state = State::GamePlay;

	// 싱글톤 구현을 위한 함수.
	static Game* instance;
};

