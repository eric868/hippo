#pragma once
#include "alarm.h"
#include "sigslot.h"
#include <memory>
#include <time.h>

class TestAlarm : public sigslot::has_slots<>
{
public:
	TestAlarm()
	{
		alarm_ = std::make_unique<base::alarm>(9, 57, 0);
	}
	void test()
	{
		alarm_->signal_alarm_.connect(this, &TestAlarm::alarm_callback);
		alarm_->turn_on();
	}

protected:
	void alarm_callback(base::alarm_info& alarminfo, struct tm* t)
	{
		std::cout << alarminfo.hour << ":" << alarminfo.minute << ":" << alarminfo.second << std::endl;
		char buf[30] = { 0 };
		strftime(buf, 30, "%Y-%m-%d %H:%M:%S", t);
		std::cout << buf << std::endl;
	}

private:
	sigslot::signal2<base::alarm_info&, struct tm*> signal_alarm_;
	std::unique_ptr<base::alarm> alarm_;
};