
#include "MsgStruct.h"



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
