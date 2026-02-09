#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Level/Level.h"
#include "Level/SokobanLevel.h"

#include "Game/Game.h"

#include "Interface/ICanPlayerMove.h"

#include <iostream>
#include <Windows.h>

using namespace Wanted;

Player::Player(const Vector2& position)
	: super("P", position, Color::Green)
{
	sortingOrder = 10;
}

void Player::BeginPlay()
{
	// 상위함수 호출.
	// c++는 부모 함수 가리키는 포인터가 없음.
	Actor::BeginPlay();

	//std::cout << "TestActor::BeginPlay().\n";
}

void Player::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);
	// vk -> virtual key.
	if (Wanted::Input::Get().GetKeyDown(VK_ESCAPE))
	{
		// esc로 레벨 이동(Menu<->Game)
		Game::Get().ToggleMenu();
		return;
	}

	if (Wanted::Input::Get().GetKeyDown('Q'))
	{
		// Q를 눌러 게임 종료.
		Wanted::Engine::Get().QuitEngine();
	}

	// 인터페이스 확인.
	static ICanPlayerMove* canPlayerMoveInterface = nullptr;

	// 오너십 확인 (null 확인).
	if (!canPlayerMoveInterface && GetOwner())
	{
		// 인터페이스로 형 변환.
		canPlayerMoveInterface = dynamic_cast<ICanPlayerMove*>(GetOwner());
	}


	// 오른쪽으로 이동하는 키.
	if (Input::Get().GetKey(VK_RIGHT) && GetPosition().x < 120)
	{
		// 이동 가능 여부 판단.
		Vector2 newPosition(GetPosition().x + 1, GetPosition().y);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}

		//Vector2 newPosition = GetPosition();
		//newPosition.x += 1;
		//SetPosition(newPosition);
	}

	// 왼쪽으로 이동하는 키.
	if (Input::Get().GetKey(VK_LEFT) && GetPosition().x > 0)
	{
		Vector2 newPosition(GetPosition().x - 1, GetPosition().y);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}

		//Vector2 newPosition = GetPosition();
		//newPosition.x -= 1
		//SetPosition(newPosition);
	}

	// 위로 이동하는 키.
	if (Input::Get().GetKey(VK_UP) && GetPosition().y > 0)
	{
		Vector2 newPosition(GetPosition().x, GetPosition().y - 1);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}

		//Vector2 newPosition = GetPosition();
		//newPosition.y -= 1;
		//SetPosition(newPosition);
	}

	// 아래로 이동하는 키.
	if (Input::Get().GetKey(VK_DOWN) && GetPosition().y < 30)
	{
		Vector2 newPosition(GetPosition().x, GetPosition().y + 1);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}

		//Vector2 newPosition = GetPosition();
		//newPosition.y += 1;
		//SetPosition(newPosition);
	}
}

void Player::Draw()
{
	Actor::Draw();
}