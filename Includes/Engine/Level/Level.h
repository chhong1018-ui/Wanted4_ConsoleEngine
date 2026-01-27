#pragma once
#pragma warning(disable: 4251) // 미봉책(방법이 없음).

#include "Common/Common.h"

// STL(	Standard Template Library) - C++에서 기본 제공.
// 크기가 알아서 변경되는 배열.
#include <vector>

namespace Wanted
{
	// 전방 선언.
	class Actor;

	// 담당 임무: 레벨에 있는 모든 엑터(물체) 관리.
	class WANTED_API Level
	{
	public:
		Level();
		virtual ~Level();

		// 게임 플레이 이벤트.
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		// 액터 추가 함수.
		void AddNewActor(Actor* newActor);

	protected:
		// 엑터 배열.
		std::vector<Actor*> actors;
	};
}