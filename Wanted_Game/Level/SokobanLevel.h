#pragma once

#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

class SokobanLevel 
	: public Wanted::Level,
	public ICanPlayerMove
{
	RTTI_DECLARATIONS(SokobanLevel, Level)

public:
	SokobanLevel();

	// 이벤트 함수 오버라이드.
	virtual void Draw() override;

	void Tick(float deltaTime) override;

	void SetMoveChecker(ICanPlayerMove* checker);

private:
	// 게임 내에서 필요한 리소스를 로드하는 함수.
	void LoadMap(const char* filename, int startX = 0, int startY = 0);

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

private:
	// 클리어해야 하는 목표 점수.
	int targetScore = 0;

	// 게임 클리어 상태를 알리는 변수
	bool isGameClear = false;

	// 게임 오버 상태를 알리는 변수.
	bool isGameOver = false;

	int mapWidth = 0;
	int mapHeight = 0;

	const char* currentMapFilename = nullptr;

public: // Added public access specifier for getter methods
    int GetMapWidth() const { return mapWidth; }
    int GetMapHeight() const { return mapHeight; }


private:
	// 맵 크기 계산 함수.
	Wanted::Vector2 CalculateMapDimensions(const char* filename);

	ICanPlayerMove* moveChecker = nullptr;
};