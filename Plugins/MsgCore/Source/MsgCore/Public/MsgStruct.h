//
//  MsgStruct.hpp
//  LearnOpenGL
//
//  Created by hongxing zhang on 2018/9/24.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//
#pragma once


#include <stdio.h>
#include <string>
#include <memory>

using namespace std;

enum MsgChanelId
{
    Msg_Local = 1,
    Msg_HttpRequest,
    Msg_HttpRespose
};
class MsgStruct
{
private:
	void *      m_MsgContent;  // 消息内容
	int         m_MsgId;  // 消息编号
	MsgChanelId         m_MsgChannelId; // 消息通道编号
protected:
	char *      m_MsgError; // 消息报错
public:
	MsgStruct(MsgChanelId _channelId, int _msgId, void * _msgContent);
	virtual ~MsgStruct();

	int GetMsgId();
	void * GetMsgContent();
	MsgChanelId      GetMsgChannelId();
	char *      GetMsgError();

	template<typename T>
	T * ContentToT()
	{
		return (T*)(m_MsgContent);
	}
};
typedef shared_ptr<MsgStruct> _msg_ptr;

