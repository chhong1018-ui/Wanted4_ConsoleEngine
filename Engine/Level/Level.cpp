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
			// 같은 위치에 다른 애거터가 있는지 확인하기 위함.
			Actor* search = nullptr;
			for (Actor* otherActor : actors)
			{
				// 같은 액터는 비교 안함.
				if (actor == otherActor)
				{
					continue;
				}

				// 위치 비교.
				if (actor->GetPosition() == otherActor->GetPosition())
				{ 
					search = otherActor;
					break;
				}
			}

			// 같은 위치에 다른 액터가 없으면 그림.
			if (!search)
			{
				actor->Draw();
				continue;
			}

			//같은 위치에 다른 액터가 있는데 우선 순위가 높으면 그림.
			if (search &&
				(actor->GetSortingOrder() > search->GetSortingOrder()))
			{
				actor->Draw();
			}
		}
	}

	void Level::AddNewActor(Actor* newActor)
	{
		// 나중에 추가를 위해 임시 배열에 저장
		addRequestedActors.emplace_back(newActor);

		// 오너십 설정.
		newActor->SetOwner(this);
	}
	void Level::ProcessAddAndDestroyActors()
	{
		// 제거 처리.
		for (int ix = 0; ix < static_cast<int>(actors.size()); )
		{
			// 제거 요청된 액터가 있는지 확인.
			if (actors[ix]->DestroyRequested())
			{
				// 삭제 처리.
				delete actors[ix];
				actors.erase(actors.begin() + ix);
				continue;
			}

			++ix;
		}

		// 추가 처리.
		if (addRequestedActors.size() == 0)
		{
			return;
		}

		for (Actor* const actor : addRequestedActors)
		{
			actors.emplace_back(actor);
		}

		// 처리가 끝났으면 배열 초기화.
		addRequestedActors.clear();
	}
}