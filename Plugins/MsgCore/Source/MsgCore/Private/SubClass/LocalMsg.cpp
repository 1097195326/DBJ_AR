#include "LocalMsg.h"

LocalMsg::LocalMsg(MsgChanelId _channelId, int _msgId, void * _msgContent)
{
	m_MsgId = _msgId;
	m_MsgContent = _msgContent;
	m_MsgChannelId = _channelId;
}
LocalMsg::LocalMsg(MsgChanelId _channelId, int _msgId, TSharedPtr<FJsonObject>& _data)
{
	m_MsgId = _msgId;
	m_JsonObject = _data;
	m_MsgChannelId = _channelId;
}