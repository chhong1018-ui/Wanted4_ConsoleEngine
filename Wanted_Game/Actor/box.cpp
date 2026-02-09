#include "box.h"

//todo: bfs 구현하고 box 없어도 될 난이도면 삭제하기
Box::Box(const Vector2& newPosition)
	: super("B", newPosition, Color::Blue)
{
	sortingOrder = 5;
}