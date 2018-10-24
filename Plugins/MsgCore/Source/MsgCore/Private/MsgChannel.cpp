//
//  MsgChannel.cpp
//  LearnOpenGL
//
//  Created by hongxing zhang on 2018/9/24.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#include "MsgChannel.h"


MsgChannel::MsgChannel()
{
    
}
MsgChannel::~MsgChannel()
{
    
}
void MsgChannel::RemoveMsgHeader(int _msgId,void * _obj)
{
    auto iter = m_Msg_Header_Map.find(_msgId);
    if (iter != m_Msg_Header_Map.end())
    {
        Msg_Header_List msgList = iter->second;
        
        list<MsgHeader>::iterator lIter;
        for (lIter = msgList.begin(); lIter != msgList.end(); lIter++)
        {
            MsgHeader header = *lIter;
            if (lIter->m_Obj == _obj)
            {
                msgList.erase(lIter);
                break;
            }
        }
    }
}
void MsgChannel::SendMsg(_msg_ptr _msg)
{
    auto iter = m_Msg_Header_Map.find(_msg->GetMsgId());
    if (iter != m_Msg_Header_Map.end())
    {
        Msg_Header_List msgList = iter->second;
        list<MsgHeader>::iterator lIter;
        for (lIter = msgList.begin(); lIter != msgList.end(); lIter++)
        {
            lIter->m_Fun_Header(_msg);
        }
    }
}
void MsgChannel::SetChannelId(MsgChanelId _channelId)
{
    m_ChannelId = _channelId;
}
