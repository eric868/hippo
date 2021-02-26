#pragma once
#include "sigslot.h"

//sigslot是对象间通信的机制
class SigSend
{
public:
	void sendmsg(int i)
	{
		signal_(i, "hello");
	}

	sigslot::signal2<int, const std::string&> signal_;
};

class SlotRecv : public sigslot::has_slots<>
{
public:
	void slot_recv(int type, const std::string& data)
	{
		std::cout << type << ": " << data << std::endl;
	}
};

class TestSigslot
{
public:
	void test()
	{
		SigSend sigsend;
		SlotRecv slotrecv;
		sigsend.signal_.connect(&slotrecv, &SlotRecv::slot_recv);

		for (int i = 0; i < 10; ++i)
			sigsend.sendmsg(i);
	}
};