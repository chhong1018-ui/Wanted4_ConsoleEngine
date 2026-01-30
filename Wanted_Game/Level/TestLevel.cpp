#include "TestLevel.h"
#include "Actor/Player.h"

TestLevel::TestLevel()
{
	// TeslActor 액터를 레벨에 추가
	AddNewActor(new Player());
}
