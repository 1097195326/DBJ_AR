#pragma once

#include "MsgStruct.h"


class MSGCORE_API LocalMsg : public MsgStruct
{
public:
	LocalMsg(MsgChanelId _channelId, int _msgId, void * _msgContent);
	LocalMsg(MsgChanelId _channelId, int _msgId, TSharedPtr<FJsonObject>& _data);
};