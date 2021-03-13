#pragma once
#include <atomic>

namespace base
{
    class state
    {
    public:
        // object state flag.
        enum
        {
            state_none = 0x00,
            state_ok = 0x01,

            state_a = 0x02,
            state_b = 0x04,
            state_c = 0x08,
            state_d = 0x10,
            state_e = 0x20,
            state_f = 0x40,
            state_g = 0x80,
        };

    public:
        state() : value_(state_none)
        {}

        inline void setnone()
        {
            value_ = state_none;
        }
        inline void setok()
        {
            add(state_ok);
        }

        inline bool isok() const
        {
            return has(state_ok);
        }

        inline bool isnone() const
        {
            return (value_ == state_none);
        }

    public:
        // add state.
        inline void add(const uint8_t value)
        {
            value_ |= value;
        }

        // remove state.
        inline void del(const uint8_t value)
        {
            value_ &= ~value;
        }

        // whether has dedicated state.
        inline bool has(const uint8_t value) const
        {
            return (value_ & value) > 0;
        }

        inline bool operator==(const state& other) const
        {
            return value_ == other.value_;
        }

    private:
        std::atomic<uint8_t> value_;
    };

}
