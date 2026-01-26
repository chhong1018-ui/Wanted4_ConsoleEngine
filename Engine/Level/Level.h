#pragma once

// STL(	Standard Template Library) - C++에서 기본 제공.
// 크기가 알아서 변경되는 배열.
#include <vector>

namespace Wanted
{
	// 전방 선언.
	class Actor;


	class Level
	{
	public:
		Level();
		virtual ~Level();

		// 게임 플레이 이벤트
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

	protected:
		std::vector<Actor*> actors;
	
	};
}

