#include "Timer.h"

Timer::Timer() {
	_lastFrame = std::chrono::steady_clock::now();
}

float Timer::GetDelta() {
	return std::chrono::duration<float>(std::chrono::steady_clock::now() - _lastFrame).count();
}

void Timer::Tick() {
	_lastFrame = std::chrono::steady_clock::now();
}