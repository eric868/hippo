#pragma once 

#define DECLARE_MESSAGE_TYPE(name, id) \
    const int name = id;\
    const int type##id = id;

namespace common
{
///////////////////////////////////////////////////////////////////////////////
//heartbeat client
DECLARE_MESSAGE_TYPE(TYPE_SYSTEM_HEARTBEAT_CLIENT, 1)
//heartbeat server
DECLARE_MESSAGE_TYPE(TYPE_SYSTEM_HEARTBEAT_SERVER, 2)
}

