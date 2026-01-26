#include <iostream>
#include "Engine/Engine.h"
#include "Level/TestLevel.h"

int main()
{
	Wanted::Engine engine;
	engine.SetNewLevel(new TestLevel());
	engine.Run();
}