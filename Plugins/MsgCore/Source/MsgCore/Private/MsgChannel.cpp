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
        Msg_Header_List & msgList = iter->second;
        
        list<MsgHeader>::iterator lIter;
        for (lIter = msgList.begin(); lIter != msgList.end(); lIter++)
        {
//            MsgHeader * header = *lIter;
            if (lIter->m_Obj == _obj)
            {
                msgList.erase(lIter);
               /* std::printf("zhx : msg remove register msg msgid:%d,obj:%ld\n",_msgId,(long)_obj);
                std::printf("zhx : msg remove register list num:%d\n",(int)msgList.size());*/
				UE_LOG(LogTemp, Log, TEXT("zhx : msg remove register id : %d, list num : %d"), _msgId, msgList.size());
                break;
            }
        }
		/*if(msgList.size() == 0)
		{
			m_Msg_Header_Map.erase(iter);
		}*/
    }
}
void MsgChannel::SendMsg(msg_ptr _msg)
{
	
}
void MsgChannel::SetChannelId(MsgChanelId _channelId)
{
    m_ChannelId = _channelId;
}
void MsgChannel::StopSendMsg()
{
	
}
void MsgChannel::TickMsg()
{
    
}
