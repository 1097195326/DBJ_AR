//
//  MsgChannel.hpp
//  LearnOpenGL
//
//  Created by hongxing zhang on 2018/9/24.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#pragma once

#include "MsgStruct.h"

#include <list>
#include <map>
#include <functional>

typedef function<void(msg_ptr)> MsgFunction;

class MsgHeader
{
public:
    void * m_Obj;
    MsgFunction m_Fun_Header;
    
};

class MSGCORE_API MsgChannel
{
protected:

    typedef list<MsgHeader>                     Msg_Header_List;
    typedef map<int,Msg_Header_List>            Msg_Header_Map;
    
    Msg_Header_Map         m_Msg_Header_Map;
    
    MsgChanelId     m_ChannelId;
public:
    MsgChannel();
    virtual ~MsgChannel();
    
    template<typename T>
    void RegisterMsgHeader(int _msgId, T * _obj, void(T::*_func)(msg_ptr))
    {
        MsgFunction mTemFunc = bind(_func, _obj, placeholders::_1);
        
        MsgHeader mHeader;// = new MsgHeader();
        mHeader.m_Obj = _obj;
        mHeader.m_Fun_Header = mTemFunc;
        
        auto iter = m_Msg_Header_Map.find(_msgId);
        if(iter == m_Msg_Header_Map.end()) //
        {
            Msg_Header_List mList;
            mList.push_back(mHeader);
            m_Msg_Header_Map.insert(pair<int, Msg_Header_List>(_msgId,mList));
        }else
        {
            Msg_Header_List & mTemList = iter->second;
            mTemList.push_back(mHeader);
        }
		auto checkI = m_Msg_Header_Map.find(_msgId);
		UE_LOG(LogTemp, Log, TEXT("zhx : msg  register id : %d, list num : %d"), _msgId, checkI->second.size());
    }
    void RemoveMsgHeader(int _msgId,void * _obj);
    
    virtual void SendMsg(msg_ptr _msg);
    
    void SetChannelId(MsgChanelId _channelId);

	virtual void StopSendMsg();
    virtual void TickMsg();
};
