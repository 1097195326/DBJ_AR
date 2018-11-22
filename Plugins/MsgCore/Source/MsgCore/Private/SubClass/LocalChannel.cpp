#include "LocalChannel.h"


void LocalChannel::SendMsg(msg_ptr _msg)
{
	auto iter = m_Msg_Header_Map.find(_msg->GetMsgId());
	if (iter != m_Msg_Header_Map.end())
	{
		Msg_Header_List msgList = iter->second;
        //std::printf("zhx : msg local list num:%d\n",(int)msgList.size());
		list<MsgHeader>::iterator lIter;
		for (lIter = msgList.begin(); lIter != msgList.end(); lIter++)
		{
            //std::printf("zhx : msg local msgid:%d,obj:%ld\n",(int)_msg->GetMsgId(),(long)lIter->m_Obj);
            UE_LOG(LogTemp,Log,TEXT("zhx : zhx : send local msgid:%d,size:%d"),_msg->GetMsgId(),msgList.size());
			lIter->m_Fun_Header(_msg);
		}
	}
}
