#pragma once
#include "thread.h"
#include "lock.h"
#include "event.h"
#include <vector>

namespace base
{

typedef void(*timer_callback)(void* obj, void* param);
class timer
{
	friend class dispatch_scheduler;

public:
	timer();
	~timer();

public:
	/*
	 * set timer params
	 * @param obj the obj that will be passed back to the timer_callback
	 * @param cb timer timeout callback function
	 * @param param the param that will be passed back to the timer_callback
	 * @param timeout timer timeout-period, in milliseconds
	 * @param repeat
	 */
	void set_timer(void* obj, timer_callback cb, void* param, int timeout, bool repeat = false);
	bool start();
	void fire();
	void reset();

protected:
	void* obj_;
	timer_callback cb_;
	void* param_;
	int timeout_;
	bool repeat_;
	long next_fire_time_;
};

}

