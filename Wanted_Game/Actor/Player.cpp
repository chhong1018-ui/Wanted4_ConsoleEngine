#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Actor/Box.h"
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
	// �׸��� �켱���� ���� ����.
	sortingOrder = 10;
}

void Player::BeginPlay()
{
	// ���� �Լ� ȣ��.
	// C++�� �θ��Լ� ����Ű�� �����Ͱ� ����.
	Actor::BeginPlay();

	//std::cout << "TestActor::BeginPlay().\n";
}

void Player::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);
	if (Wanted::Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();
		return;
	}

	// QŰ ����.
	if (Wanted::Input::Get().GetKeyDown('Q'))
	{
		// ���� ���� ���� ��û.
		Wanted::Engine::Get().QuitEngine();
	}

	// �����̽��� �ڽ� ����.
	// vk -> virtual key.
	if (Input::Get().GetKeyDown(VK_SPACE))
	{
		// �ڽ� ����.
		if (owner)
		{
			owner->AddNewActor(new Box(GetPosition()));
		}
	}

	// �������̽� Ȯ��.
	static ICanPlayerMove* canPlayerMoveInterface = nullptr;

	// ���ʽ� Ȯ�� (null Ȯ��).
	if (!canPlayerMoveInterface && GetOwner())
	{
		// �������̽��� ����ȯ.
		canPlayerMoveInterface = dynamic_cast<ICanPlayerMove*>(GetOwner());
	}


	// �̵�.
	if (Input::Get().GetKey(VK_RIGHT) && GetPosition().x < 200)
	{
		// �̵� ���� ���� �Ǵ�.
		Vector2 newPosition(GetPosition().x + 1, GetPosition().y);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}

		//Vector2 newPosition = GetPosition();
		//newPosition.x += 1;
		//SetPosition(newPosition);
	}

	// �̵� ���� ���� �Ǵ�.
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

	// �̵� ���� ���� �Ǵ�.
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

	// �̵� ���� ���� �Ǵ�.
	if (Input::Get().GetKey(VK_DOWN) && GetPosition().y < 200)
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