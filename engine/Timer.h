#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
public:
	Timer();
	virtual ~Timer();
	
	void reset();	
	double getDeltaTimeSeconds();

private:
	std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<long long int, std::ratio<1ll, 1000000000ll> > > _past;
};

#endif // TIMER_H
