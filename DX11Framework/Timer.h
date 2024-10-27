#pragma once
#include <chrono>

class Timer
{
	public:
		Timer();

		float GetDelta();
		void Tick();

	private: 
		std::chrono::steady_clock::time_point _lastFrame;
};

