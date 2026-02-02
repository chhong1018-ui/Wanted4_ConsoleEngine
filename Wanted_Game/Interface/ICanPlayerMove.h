#pragma once

#include "Math/Vector.h"

// 플레이어가 이동할 위치를 판단해주는 인터페이스.
// c++ 인터페이스 = 순수 가상함수를 가지는 클래스.
class ICanPlayerMove
{
public:
	// 플레이어가 이동가능한지 문의할 때 사용할 함수.
	// playerPosition: 플레이어의 현재 위치.
	// newtPosition: 플레이어가 이동하려는 위치.
	virtual bool CanMove(
		const Wanted::Vector2& playerPosition,
		const Wanted::Vector2& newtPosition
	) = 0;
};