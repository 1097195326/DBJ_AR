//
//  MsgCenter.cpp
//  LearnOpenGL
//
//  Created by hongxing zhang on 2018/9/24.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#include "MsgCenter.h"


MsgCenter::MsgCenter()
{
    
}
MsgCenter::~MsgCenter()
{
    
}
MsgCenter * MsgCenter::Instance()
{
    static MsgCenter m;
    return &m;
}
void MsgCenter::RemoveMsgHeader(MsgChanelId _channelId, int _msgId,void * _obj)
{
    auto iter = m_Channel_Map.find(_channelId);
    if (iter != m_Channel_Map.end())
    {
        MsgChannel * channel = iter->second;
        channel->RemoveMsgHeader(_msgId, _obj);
    }
}
void MsgCenter::SendMsg(_msg_ptr _msg)
{
    auto iter = m_Channel_Map.find(_msg->GetMsgChannelId());
    if (iter != m_Channel_Map.end())
    {
        MsgChannel * channel = iter->second;
        channel->SendMsg(_msg);
    }
}
