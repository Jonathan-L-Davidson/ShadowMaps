#include "Timer.h"

Timer::Timer() {
	_lastFrame = std::chrono::steady_clock::now();
}

float Timer::GetDelta() {
	return duration<float>(steady_clock::now() - _lastFrame).count();
}

void Timer::Tick() {
	_lastFrame = std::chrono::steady_clock::now();
}