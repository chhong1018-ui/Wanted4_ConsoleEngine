#include "TestActor.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include <iostream>
#include <Windows.h>

using namespace Wanted;

TestActor::TestActor()
	: Actor('T', Wanted::Vector2(5, 5))
{
}

void TestActor::BeginPlay()
{
	// 상위 함수 호출.
	// C++는 부모함수 가리키는 포인터가 없음.
	Actor::BeginPlay();

	//std::cout << "TestActor::BeginPlay().\n";
}

void TestActor::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);

	// Q키 종료.
	if (Wanted::Input::Get().GetKeyDown('Q'))
	{
		// todo: 게임 엔진 종료 요청.
		Wanted::Engine::Get().QuitEngine();
	}

	// 오른쪽 방향키가 눌리고, x위치가 20번째 칸을 안 넘어갔으면,
	if (Input::Get().GetKey(VK_RIGHT) && GetPosition().x < 20)
	{
		// 현재 위치 가져오기.
		Vector2 newPosition = GetPosition();

		// x 위치 오른쪽으로 한칸 이동.
		newPosition.x += 1;

		// 새로운 위치 설정.
		SetPosition(newPosition);
	}

	// 왼쪽 방향키가 눌리고, x위치가 0번째 칸보다 오른쪽에 있으면,
	if (Input::Get().GetKey(VK_LEFT) && GetPosition().x > 0)
	{
		// 현재 위치 가져오기.
		Vector2 newPosition = GetPosition();

		// x 위치 왼쪽으로 한칸 이동.
		newPosition.x -= 1;

		// 새로운 위치 설정.
		SetPosition(newPosition);
	}

	// 위쪽 방향키가 눌리고, y위치가 0번째 칸보다 왼쪽에 있으면,
	if (Input::Get().GetKey(VK_UP) && GetPosition().y > 0)
	{
		// 현재 위치 가져오기.
		Vector2 newPosition = GetPosition();

		// x 위치 왼쪽으로 한칸 이동.
		newPosition.y -= 1;

		// 새로운 위치 설정.
		SetPosition(newPosition);
	}

	// 아래쪽 방향키가 눌리고, y위치가 20번째 칸을 안 넘어갔으면,
	if (Input::Get().GetKey(VK_DOWN) && GetPosition().y < 20)
	{
		// 현재 위치 가져오기.
		Vector2 newPosition = GetPosition();

		// x 위치 오른쪽으로 한칸 이동.
		newPosition.y += 1;

		// 새로운 위치 설정.
		SetPosition(newPosition);
	}

	//std::cout << "TestActor::Tick().deltaTime : " << deltaTime << ", FPS : " << (1.0f / deltaTime) << "\n";
}

void TestActor::Draw()
{
	Actor::Draw();
}
