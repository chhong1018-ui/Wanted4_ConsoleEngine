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

private:
	// 게임에서 사용할 맵을 로드하는 함수.
	void LoadMap(const char* filename);

	virtual bool CanMove(
		const Wanted::Vector2& playerPosition,
		const Wanted::Vector2& newtPosition) override;
};