#include "LocalChannel.h"


void LocalChannel::SendMsg(msg_ptr _msg)
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