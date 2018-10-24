//
//  MsgCenter.hpp
//  LearnOpenGL
//
//  Created by hongxing zhang on 2018/9/24.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#pragma once

#include "MsgChannel.h"


class MsgCenter
{
private:
    map<MsgChanelId,MsgChannel*>    m_Channel_Map;
    
public:
    MsgCenter();
    virtual ~MsgCenter();
    
    static MsgCenter * Instance();
    
    template<typename T>
    void RegisterMsgHeader(MsgChanelId _channelId, int _msgId, T * _obj, void(T::*_func)(_msg_ptr))
    {
        auto ChannelIter = m_Channel_Map.find(_channelId);
        if (ChannelIter == m_Channel_Map.end())
        {
            MsgChannel * channel = new MsgChannel();
            channel->SetChannelId(_channelId);
            channel->RegisterMsgHeader(_msgId, _obj, _func);
            
            m_Channel_Map.insert(pair<MsgChanelId, MsgChannel*>(_channelId,channel));
        }else
        {
            MsgChannel * channel = ChannelIter->second;
            channel->RegisterMsgHeader(_msgId, _obj, _func);
        }
    }
    void RemoveMsgHeader(MsgChanelId _channelId, int _msgId,void * _obj);
    
    void SendMsg(_msg_ptr _msg);
    
};
