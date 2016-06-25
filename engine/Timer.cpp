#include "Timer.h"

Timer::Timer()
{
	reset();
}

Timer::~Timer()
{
}

double Timer::getDeltaTimeSeconds()
{
	auto newTime = std::chrono::high_resolution_clock::now();
	auto delta = std::chrono::duration_cast<std::chrono::nanoseconds>(newTime - _past).count();
	_past = newTime;
	return delta / 1000000000.0;
}

void Timer::reset()
{
    _past = std::chrono::high_resolution_clock::now();
}

