#pragma once

#include "Level/Level.h"
#include "Level/SokobanLevel.h"
#include "Math/Color.h"
#include <vector>

using namespace Wanted;

// �޴� ������ ����ü.
struct MenuItem
{
	// �޴� ���õ��� �� ���� �� �Լ��� Ÿ��
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

	// �޴� �ؽ�Ʈ.
	char* text = nullptr;

	// �޴� ���õ��� �� ���� �� ����(�Լ�).
	OnSelected onSelected = nullptr;
};

class MenuLevel : public Level
{

	RTTI_DECLARATIONS(MenuLevel, Level)

public:
	MenuLevel();
	~MenuLevel();

	// �̺�Ʈ �Լ� �������̵�
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

private:
	// ���� Ȱ��ȭ �� �Ŵ� ������ �ε���
	int currentIndex = 0;

	// ���� �� �������� ����.
	Color selectedColor = Color::Green;

	// ���õ��� ���� �������� ����.
	Color unselectedColor = Color::White;

	// �Ŵ� ������ �迭.
	std::vector<MenuItem*> items;
};