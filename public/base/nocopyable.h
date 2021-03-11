#pragma once

namespace base
{
    class nocopyable
    {
    protected:
        nocopyable(){}
        virtual ~nocopyable(){}
	private:
		nocopyable(const nocopyable&);
		nocopyable& operator = (const nocopyable&);
	};
}

