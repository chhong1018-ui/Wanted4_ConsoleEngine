#include <iostream>
#include "Engine/Engine.h"
#include "Level/TestLevel.h"
#include "Actor/TestActor.h"
//#include "Level/Level.h"
//#include "Actor/Actor.h"

using namespace Wanted;

int main()
{
	//Wanted::Engine engine;
	//engine.SetNewLevel(new TestLevel());
	//engine.Run();

	TestLevel* level = new TestLevel();
	Actor* actor = new Actor();
	TestActor* testActor = new TestActor();

	//if (testActor->Is(actor))
	//{
	//	std::cout << "actor is TestActor type/\n";
	//}
	//else
	//{
	//	std::cout << "actor is not TestActor type/\n";
	//}

	//TestActor* testActor2 = dynamic_cast<TestActor*>(actor);
	TestActor* testActor = actor->As<TestActor>();
	if (testActor)
	{
		std::cout << "actor is TestActor type/\n";
	}
	else
	{
		std::cout << "actor is not TestActor type/\n";
	}
}