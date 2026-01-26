#pragma once

namespace Wanted
{
	// Main game engine class.
	class Engine
	{
		// 데이터.
		// Down/Up/Key.
		struct KeyState
		{
			// 현재 키가 눌렸는지.
			bool isKeyDown = false;

			// 이전에 키가 눌렸는지.
			bool wasKeyDown = false;
		};

	public:
		Engine();
		~Engine();

		// 엔진 루프(게임 루프)
		void Run();

		// 엔진 종료 함수.
		void QuitEngine();

		// 입력 확인 함수.
		// 이전에 입력이 안됐는데, 현재 입력이 됐으면 1번 호출.
		bool GetKeyDown(int keyCode);

		// 이전에 입력이 됐는데, 현재 입력이 취소됐으면 1번 호출.
		bool GetKeyUp(int keyCode);
		
		// 현재 눌려있으면 반복 호출.
		bool GetKey(int keyCode);

		// 새 레벨을 추가(설정)하는 함수.
		void SetNewLevel(class Level* newLevel);

	private:
		// 입력 처리 함수
		void ProcessInput();

		// 게임 플레이 시작 함수.
		void BeginPlay();

		// 업데이트 함수.
		void Tick(float deltaTime);

		//그리기 함수 (draw/render).
		void Draw();

	private:
		// 엔진 종료 플래그.
		bool isQuit = false;

		//키 상태 저장용 배열.
		KeyState keyStates[255] = { };

		//메인 레벨.
		class Level* mainLevel = nullptr;
	};
}