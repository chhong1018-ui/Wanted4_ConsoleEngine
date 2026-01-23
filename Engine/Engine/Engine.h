#pragma once

namespace Wanted
{
	//Main game engine class.
	class Engine
	{
		// 데이터.
		//
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

		void QuitEngine();

		// 입력 확인 함수.
		bool GetKeyDown(int keyCode);

		bool GetKeyUp(int keyCode);
		
		bool GetKey(int keyCode);

	private:
		// 입력 처리 함수
		void processInput();

		// 업데이트 함수.
		void Tick(float deltaTime);
		//그리기 함수 (draw/render).
		void Draw();


	private:
		// 엔진 종료 플래그.
		bool isQuit = false;

		//키 상태 저장용 배열.
		KeyState keyStates[255] = { };
	};
}



