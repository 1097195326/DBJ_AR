#pragma once

#include "MsgChannel.h"
#include "LocalMsg.h"


class MSGCORE_API LocalChannel : public MsgChannel
{
private:


public:

	virtual void SendMsg(msg_ptr _msg);
};