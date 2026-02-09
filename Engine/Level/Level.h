#pragma once
#pragma warning(disable: 4251) // �̺�å(����� ����).

#include "Common/RTTI.h"

// STL(	Standard Template Library) - C++���� �⺻ ����.
// ũ�Ⱑ �˾Ƽ� ����Ǵ� �迭.
#include <vector>

namespace Wanted
{
	// ���� ����.
	class Actor;

	// ��� �ӹ�: ������ �ִ� ��� ����(��ü) ����.
	class WANTED_API Level : public RTTI
	{
		// RTTI �ڵ� �߰�.
		RTTI_DECLARATIONS(Level, RTTI)

	public:
		Level();
		virtual ~Level();

		// ���� �÷��� �̺�Ʈ.
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		// ���� �߰� �Լ�.
		void AddNewActor(Actor* newActor);

		void ProcessAddAndDestroyActors();

		const std::vector<Actor*>& GetActors() const { return actors; }

	protected:
		// ���� �迭.
		std::vector<Actor*> actors;

		// ���� �߿� �߰� ��û�� ������ �迭
		std::vector<Actor*> addRequestedActors;

	};
}