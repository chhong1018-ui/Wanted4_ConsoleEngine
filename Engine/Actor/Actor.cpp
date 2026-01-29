#include "Actor.h"
#include <iostream>
#include <Windows.h>

namespace Wanted
{
	Actor::Actor(const char image, const Vector2& position)
		: image(image), position(position)
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
		COORD coord = {};
		coord.X = static_cast<short>(position.x);
		coord.Y = static_cast<short>(position.y);
		SetConsoleCursorPosition(
			GetStdHandle(STD_OUTPUT_HANDLE),
			coord
		);

		std::cout << image;
	}

	void Actor::SetPosition(const Vector2& newPosition)
	{
		COORD coord = {};
		coord.X = static_cast<short>(position.x);
		coord.Y = static_cast<short>(position.y);
		SetConsoleCursorPosition(
			GetStdHandle(STD_OUTPUT_HANDLE),
			coord
		);

		std::cout << ' ';

		position = newPosition;
	}
}