#include "Actor.h"
#include "Core/Renderer.h"
#include "Util/Util.h"

#include <iostream>
#include <Windows.h>

namespace Wanted
{
	Actor::Actor(
		const char image, 
		const Vector2& position,
		Color color)
		: image(image), position(position), color(color)
	{
	}

	Actor::~Actor()
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
		// 렌더러에 그리기 요청.
		Renderer::Draw(position, color, image);
	}

	void Actor::SetPosition(const Vector2& newPosition)
	{
		Renderer::Draw(position, ' ');

		position = newPosition;
	}
}