#include "MsgStruct.h"


MsgStruct::MsgStruct(MsgChanelId _channelId, int _msgId,void * _msgContent)
{
    m_MsgId = _msgId;
    m_MsgContent = _msgContent;
    m_MsgChannelId = _channelId;
}
MsgStruct::~MsgStruct()
{
    
}

int MsgStruct::GetMsgId()
{
    return m_MsgId;
}
void* MsgStruct::GetMsgContent()
{
    return m_MsgContent;
}
MsgChanelId MsgStruct::GetMsgChannelId()
{
    return m_MsgChannelId;
}
char * MsgStruct::GetMsgError()
{
    return m_MsgError;
}
