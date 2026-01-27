#include "Actor.h"

namespace Wanted
{
	Wanted::Actor::Actor()
	{

	}

	Wanted::Actor::~Actor()
	{

	}

	void Actor::BeginPlay()
	{
		// 이벤트를 받은 후에는 플래그 설정.
		hasBeganPlay = true;
	}
	void Actor::Tick(float deltaTime)
	{

	}
	void Actor::Draw()
	{

	}
}