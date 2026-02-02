#pragma once

#include "Level/Level.h"
#include "Math/Color.h"
#include <vector>

using namespace Wanted;

// 메뉴 아이템 구조체.
struct MenuItem
{
	// 메뉴 선택됐을 때 실행 될 함수의 타입
	using OnSelected = void (*)();

	MenuItem(const char* text, OnSelected onSelected)
		: onSelected(onSelected)
	{
		//  xprtmxm qhrtk
		size_t length = strlen(text) + 1;
		this->text = new char[length];
		strcpy_s(this->text, length, text);
	}

	~MenuItem()
	{
		if (text)
		{
			delete[] text;
			text = nullptr;
		}
	}

	// 메뉴 텍스트.
	char* text = nullptr;

	// 메뉴 선택됐을 때 실행 될 로직(함수).
	OnSelected onSelected = nullptr;
};

class MenuLevel : public Level
{

	RTTI_DECLARATIONS(MenuLevel, Level)

public:
	MenuLevel();
	~MenuLevel();

	// 이벤트 함수 오버라이드
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

private:
	// 현재 활성화 된 매뉴 아이템 인덱스
	int currentIndex = 0;

	// 선택 된 아이템의 색상.
	Color selectedColor = Color::Green;

	// 선택되지 않은 아이템의 색상.
	Color unselectedColor = Color::White;

	// 매뉴 아이템 배열.
	std::vector<MenuItem*> items;
};