#pragma once

#include "Level/Level.h"
#include "Level/SokobanLevel.h"
#include "Math/Color.h"
#include <vector>

using namespace Wanted;


struct FinishMenuItem
{
	
	using OnSelected = void (*)();

	FinishMenuItem(const char* text, OnSelected onSelected)
		: onSelected(onSelected)
	{
		//  텍스트 복사.
		size_t length = strlen(text) + 1;
		this->text = new char[length];
		strcpy_s(this->text, length, text);
	}

	~FinishMenuItem()
	{
		if (text)
		{
			delete[] text;
			text = nullptr;
		}
	}


	char* text = nullptr;

	
	OnSelected onSelected = nullptr;
};

class FinishLevel : public Level
{

	RTTI_DECLARATIONS(FinishLevel, Level)

public:
	FinishLevel();
	~FinishLevel();

	
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

private:
	
	int currentIndex = 0;

	
	Color selectedColor = Color::Green;

	
	Color unselectedColor = Color::White;

	
	std::vector<FinishMenuItem*> items;
};