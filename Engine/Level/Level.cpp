#include "Level.h"
#include "Actor/Actor.h"

namespace Wanted
{
	Level::Level()
	{
	}
	Level::~Level()
	{
		// 메모리 정리.
		for (Actor*& actor : actors)
		{
			if (actor)
			{
				delete actor;
				actor = nullptr;
			}
		}

		// 배열 초기화.
		actors.clear();
	}

	void Level::BeginPlay()
	{
		// 엑터에 이벤트 흘리기.
		for (Actor* actor : actors)
		{
			// todo: 이미 BeginPlay 호출된 액터는 건너뛰기.
			actor->BeginPlay();
		}
	}
	void Level::Tick(float deltaTime)
	{
		// 엑터에 이벤트 흘리기.
		for (Actor* actor : actors)
		{
			actor->Tick(deltaTime);
		}
	}
	void Level::Draw()
	{
		// 엑터에 이벤트 흘리기.
		for (Actor* actor : actors)
		{
			actor->Draw();
		}
	}
}