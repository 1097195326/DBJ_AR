//
//  MsgStruct.hpp
//  LearnOpenGL
//
//  Created by hongxing zhang on 2018/9/24.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//
#pragma once

#include "Serialization/JsonSerializer.h"

#include <stdio.h>
#include <string>
#include <memory>

using namespace std;

enum MsgChanelId
{
    Msg_Local = 1,
    Msg_HttpRequest
};
class MSGCORE_API  MsgStruct
{
public:
	void *      m_MsgContent;  // 消息内容
	TSharedPtr<FJsonObject>		m_JsonObject;
	int         m_MsgId;  // 消息编号
	MsgChanelId         m_MsgChannelId; // 消息通道编号
protected:
	char *      m_MsgError; // 消息报错
public:
	MsgStruct();
	MsgStruct(void * _msgContent);
	MsgStruct(TSharedPtr<FJsonObject> _jsonObject);
	virtual ~MsgStruct();

	int GetMsgId();
	void * GetMsgContent();
	template<typename T>
	T GetMsgContent()
	{
		return *static_cast<T*>(m_MsgContent);
	}
	TSharedPtr<FJsonObject> GetJsonObject();
	MsgChanelId      GetMsgChannelId();
	char *      GetMsgError();

	template<typename T>
	T * SelfConvertToT()
	{
		return (T*)(this);
	}
};
//typedef shared_ptr<MsgStruct> msg_ptr;

typedef TSharedPtr<MsgStruct> msg_ptr;
