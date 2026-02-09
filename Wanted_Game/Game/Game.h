#pragma once

#include "Engine/Engine.h"
#include <vector>

using namespace Wanted;

// ���� ������ ����� ������
enum class State
{
	//None = -1,
	GamePlay = 0,
	Menu = 1,
	startGame = 2,
	Length
};

class Game : public Wanted::Engine
{
public:
	Game();
	~Game();

	void StartGame();

	void ToggleMenu();

	Level* GetCurrentLevel();

	static Game& Get();

private:
	//
	std::vector<Level*> levels;

	// ���� Ȱ��ȭ �� 
	State state = State::GamePlay;

	// �̱��� ������ ���� �Լ�.
	static Game* instance;
};

