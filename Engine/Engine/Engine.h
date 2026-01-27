#pragma once

#include "Common/Common.h"

namespace Wanted
{
	class Input;

	// Main game engine class.
	class WANTED_API Engine
	{
	public:
		Engine();
		~Engine();

		// 엔진 루프(게임 루프)
		void Run();

		// 엔진 종료 함수.
		void QuitEngine();

		// 새 레벨을 추가(설정)하는 함수.
		void SetNewLevel(class Level* newLevel);

		// 전역 접근 함수.
		static Engine& Get();

	private:

		// 게임 플레이 시작 함수.
		// Unity의 경우: Start/Awake.
		void BeginPlay();

		// 업데이트 함수.
		void Tick(float deltaTime);

		//그리기 함수 (draw/render).
		void Draw();

	private:
		// 엔진 종료 플래그.
		bool isQuit = false;

		// 입력 관리자.
		Input* input = nullptr;

		//메인 레벨.
		class Level* mainLevel = nullptr;

		// 전역 변수.
		static Engine* instance;
	};
}