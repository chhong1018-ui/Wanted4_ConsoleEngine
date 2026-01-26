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
			// 액터 객체 메모리 해제.
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
			// 이미 BeginPlay 호출된 액터는 건너뛰기.
			if (actor->HasBeganPlay())
			{
				continue;
			}

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
	void Level::AddNewActor(Actor* newActor)
	{
		// todo: 나중에 프레임 처리 고려해서 따로 추가 작업 해야함.
		//actors.push_back(newActor);
		actors.emplace_back(newActor);
	}
}