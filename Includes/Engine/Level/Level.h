#pragma once
#pragma warning(disable: 4251) // 미봉책(방법이 없음).

// STL(	Standard Template Library) - C++에서 기본 제공.
// 크기가 알아서 변경되는 배열.
#include <vector>
#include "Common/Common.h"

namespace Wanted
{
	// 전방 선언.
	class Actor;

	//
	class WANTED_API Level
	{
	public:
		Level();
		virtual ~Level();

		// 게임 플레이 이벤트
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		// 액터 추가 함수.
		void AddNewActor(Actor* newActor);

	protected:
		std::vector<Actor*> actors;

	};
}