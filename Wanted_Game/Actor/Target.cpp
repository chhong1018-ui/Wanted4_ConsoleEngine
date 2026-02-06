#include "Target.h"

Target::Target(const Vector2& position)
	: super("O", position, Color::Green)
{
	sortingOrder = 3;
}