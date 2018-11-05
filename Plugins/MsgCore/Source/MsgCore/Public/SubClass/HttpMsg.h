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
	bool	m_IsGet;

	//EnumHttpRequestType m_HttpRequestType;

	// ��Ϣ�壬http����jsonObject��ʽ.
	TSharedPtr<FJsonObject> m_httpJsonObj;

public:
	// ��ȡhttp���ص�json����.
	TSharedPtr<FJsonObject> GetHttpContent();

	// �����л�.
	void Decode(FHttpRequestPtr & inReq, FHttpResponsePtr & inResp, bool inSuccess);

public:
	HttpMsg();
	~HttpMsg();
	HttpMsg(MsgChanelId _channelID, int32 _unMsgID,  TSharedPtr<FJsonObject> & _content, bool _IsGet = false, FString _token = TEXT("token"),  FString _operator = TEXT("operator"));
};
