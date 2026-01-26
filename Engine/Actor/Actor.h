#pragma once

namespace Wanted
{
	class Actor
	{
	public:
		Actor();
		virtual ~Actor();

		// 게임 플레이 이벤트.
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		// Getter
		inline bool HasBeganPlay() const { return hasBeganPlay; }
		bool IsActive() const
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
	};
}