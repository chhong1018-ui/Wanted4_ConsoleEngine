#pragma once

#include "Common/RTTI.h"
#include "Math/Vector.h"

namespace Wanted
{
	class WANTED_API Actor : public RTTI
	{
		// RTTI 코드 추가.
		RTTI_DECLARATIONS(Actor, RTTI)

	public:
		Actor(const char image = ' ', const Vector2& position = Vector2::Zero);
		virtual ~Actor();

		// 게임 플레이 이벤트.
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		// 위치변경 및 읽기 함수.
		void SetPosition(const Vector2& newPosition);
		inline Vector2 GetPosition() const { return position; }

		// Getter
		inline bool HasBeganPlay() const { return hasBeganPlay; }
		inline bool IsActive() const
		{
			return isActive && !destroyRequested;
		}

	protected:
		// 이미 beginPlay 이벤트를 받았는지 여부.
		bool hasBeganPlay = false;

		// 활성화 상태 여부.
		bool isActive = true;

		//현재 프레임에 삭제 요청 받았는지 여부.
		bool destroyRequested = false;

		char image = ' ';

	private:
		// 위치.
		Vector2 position;
	};
}