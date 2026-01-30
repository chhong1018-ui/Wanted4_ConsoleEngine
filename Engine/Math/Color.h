#pragma once

#include "Common/Common.h"
#include <Windows.h>

namespace Wanted
{
	enum class WANTED_API Color : unsigned short
	{
		Black = 0,
		Blue = FOREGROUND_BLUE,
		Green = FOREGROUND_GREEN,
		Red = FOREGROUND_RED,
		White = Blue | Green | Red,
	};
}