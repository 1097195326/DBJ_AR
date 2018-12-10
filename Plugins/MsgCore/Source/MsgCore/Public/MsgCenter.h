//
//  MsgCenter.hpp
//  LearnOpenGL
//
//  Created by hongxing zhang on 2018/9/24.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#pragma once

#include "LocalChannel.h"
#include "HttpChannel.h"

class MSGCORE_API MsgCenter
{
private:
    map<MsgChanelId,MsgChannel*>    m_Channel_Map;
    
public:
    MsgCenter();
    virtual ~MsgCenter();
    
    static MsgCenter * GetInstance();
    
    template<typename T>
    void RegisterMsgHeader(MsgChanelId _channelId, int _msgId, T * _obj, void(T::*_func)(msg_ptr))
    {
        auto ChannelIter = m_Channel_Map.find(_channelId);
        if (ChannelIter == m_Channel_Map.end())
        {
			MsgChannel * channel = nullptr;
			switch (_channelId)
			{
			case Msg_Local:
			{
				channel = new LocalChannel();
				break;
			}
			case Msg_HttpRequest:
			{
				channel = new HttpChannel();
				break;
			}
			default:
				return;
			}
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
    
    void SendMsg(msg_ptr _msg);
    
	void StopSendMsg();
    
	void RerequestHttp();
	void ContineHttp();

    void TickMsg();
};
