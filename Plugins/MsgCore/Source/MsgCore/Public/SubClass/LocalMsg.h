#pragma once

#include "MsgStruct.h"


class MSGCORE_API LocalMsg : public MsgStruct
{
public:
	LocalMsg(MsgChanelId _channelId, int _msgId, void * _msgContent);
};