#pragma once

#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

#include <string>

class SokobanLevel
	: public Wanted::Level,
	public ICanPlayerMove
{
	RTTI_DECLARATIONS(SokobanLevel, Level)

public:
	SokobanLevel();

	// 게임 레벨 초기화 후 재시작 함수.
	void Restart();

	// 이벤트 함수 오버라이드.
	virtual void Draw() override;

	void Tick(float deltaTime) override;

	// 게임 클리어 상태를 알리는 변수
	bool isGameClear = false;
	
	const std::string& GetCurrentMapFilename() const { return currentMapFilename; } // Added getter

private:
	// 게임 내에서 필요한 리소스를 로드하는 함수.
	void LoadMap(const std::string& filename, int startX = 0, int startY = 0); // Changed to const std::string&

	//Inherited via ICanPlayerMove
	virtual bool CanMove(
		const Wanted::Vector2& playerPosition,
		const Wanted::Vector2& newtPosition) override;

	// 게임 클리어 확인 함수.
	bool CheckGameClear();

	// 게임 오버 확인 함수.
	bool CheckGameOver();

	float GameOverTimer = 2.0f;
	bool isWaitingForToggle = false;

	// 게임 오버 상태를 알리는 변수.
	bool isGameOver = false;

	int mapWidth = 0;
	int mapHeight = 0;

	std::string currentMapFilename; // Changed to std::string by value

	// 맵 크기 계산 함수.
	Wanted::Vector2 CalculateMapDimensions(const std::string& filename); // Changed to const std::string&
};