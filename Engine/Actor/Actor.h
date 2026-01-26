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

	protected:

	};
}
class Actor
{
};

