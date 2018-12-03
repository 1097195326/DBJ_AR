#pragma once
#include "MsgStruct.h"
#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"


enum EnumHttpRequestType :int32
{
	Http_Post = 1,
	Http_Get,
	Http_Put,

};

class MSGCORE_API HttpMsg : public MsgStruct
{
public:
	FString m_httpUrl;
	FString m_httpContent;
	FString m_operator;
	FString m_token;
	FString m_Cookie;
	EnumHttpRequestType m_RequestType;
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
	HttpMsg(MsgChanelId _channelID, int32 _unMsgID,  TSharedPtr<FJsonObject> & _content, FString _httpUrl, EnumHttpRequestType _type = Http_Post,FString _cookie = TEXT(""), FString _token = TEXT("token"),  FString _operator = TEXT("operator"));
	HttpMsg(MsgChanelId _channelID, int32 _unMsgID, FString _httpUrl, FString _AppendUrl, EnumHttpRequestType _type = Http_Get, FString _cookie = TEXT("cookie"), FString _token = TEXT("token"), FString _operator = TEXT("operator"));

};
