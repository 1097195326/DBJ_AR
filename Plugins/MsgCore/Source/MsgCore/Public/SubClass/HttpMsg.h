#pragma once
#include "MsgStruct.h"
#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"


enum EnumHttpRequestType :int32
{
	Http_Post = 0,
	Http_Get,
	Http_Put,
	Http_Delete,

};

class MSGCORE_API HttpMsg : public MsgStruct
{
public:
	FString m_httpUrl;
	FString m_httpContent;
	FString m_operator;
	FString m_token;
	FString m_Cookie;
	bool	m_IsGet;
	FString	m_AppendUrl;

	//EnumHttpRequestType m_HttpRequestType;

	// 消息体，http内容jsonObject格式.
	TSharedPtr<FJsonObject> m_httpJsonObj;

public:
	// 获取http返回的json对象.
	TSharedPtr<FJsonObject> GetHttpContent();

	// 反序列化.
	void Decode(FHttpRequestPtr & inReq, FHttpResponsePtr & inResp, bool inSuccess);

public:
	HttpMsg();
	~HttpMsg();
	HttpMsg(MsgChanelId _channelID, int32 _unMsgID,  TSharedPtr<FJsonObject> & _content, FString _httpUrl, bool _IsGet = false,FString _cookie = TEXT(""), FString _token = TEXT("token"),  FString _operator = TEXT("operator"));
	HttpMsg(MsgChanelId _channelID, int32 _unMsgID, FString _httpUrl, FString _AppendUrl, bool _IsGet = true, FString _cookie = TEXT("cookie"), FString _token = TEXT("token"), FString _operator = TEXT("operator"));

};
