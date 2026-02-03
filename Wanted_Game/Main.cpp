#include <iostream>
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/SokobanLevel.h"

using namespace Wanted;

// 예시 배열.
int main()
{
	//Wanted::Engine engine;
	//engine.SetNewLevel(new SokobanLevel());
	//engine.Run();

	// 문자 배열을 한 번에 콘솔로 넘겨서 그릴 때 사용하는 함수.
	Game game;
	game.Run();
}