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
MsgCenter * MsgCenter::GetInstance()
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
void MsgCenter::SendMsg(msg_ptr _msg)
{
    auto iter = m_Channel_Map.find(_msg->GetMsgChannelId());
    if (iter != m_Channel_Map.end())
    {
        MsgChannel * channel = iter->second;
        channel->SendMsg(_msg);
	}
	else
	{
		MsgChannel * channel = nullptr;
		MsgChanelId channelID = _msg->m_MsgChannelId;
		switch (channelID)
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
		channel->SetChannelId(channelID);
		m_Channel_Map.insert(pair<MsgChanelId, MsgChannel*>(channelID, channel));
		channel->SendMsg(_msg);
	}
}
void MsgCenter::StopSendMsg()
{
	for (auto channel : m_Channel_Map)
	{
		channel.second->StopSendMsg();
	}
}
void MsgCenter::TickMsg()
{
    for (auto channel : m_Channel_Map)
    {
        channel.second->TickMsg();
    }
}
void MsgCenter::RerequestHttp()
{
	auto iter = m_Channel_Map.find(Msg_HttpRequest);
	if (iter != m_Channel_Map.end())
	{
		HttpChannel * channel = (HttpChannel*)iter->second;
		channel->RerequestHttp();
	}
}
void MsgCenter::ContineHttp()
{
	auto iter = m_Channel_Map.find(Msg_HttpRequest);
	if (iter != m_Channel_Map.end())
	{
		HttpChannel * channel = (HttpChannel*)iter->second;
		channel->ContineHttp();
	}
}