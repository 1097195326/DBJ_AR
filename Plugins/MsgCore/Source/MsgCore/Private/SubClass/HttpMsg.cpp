#include "HttpMsg.h"



HttpMsg::HttpMsg()
{

}
//
HttpMsg::HttpMsg(MsgChanelId _channelID, int32 _unMsgID, TSharedPtr<FJsonObject> & _content, FString _httpUrl, EnumHttpRequestType _type, FString _cookie, FString _token, FString _operator)
{
	m_MsgChannelId = _channelID;
	m_MsgId = _unMsgID;
	m_httpUrl = _httpUrl;
	m_Cookie = _cookie;
	m_token = _token;
	m_operator = _operator;
	m_RequestType = _type;

	TSharedRef<TJsonWriter<TCHAR>> t_writer = TJsonWriterFactory<>::Create(&m_httpContent);
	FJsonSerializer::Serialize(_content.ToSharedRef(), t_writer);
}
HttpMsg::HttpMsg(MsgChanelId _channelID, int32 _unMsgID, FString _httpUrl, FString _AppendUrl, EnumHttpRequestType _type, FString _cookie, FString _token, FString _operator)
{
	m_MsgChannelId = _channelID;
	m_MsgId = _unMsgID;
	m_httpUrl = _httpUrl;
	m_Cookie = _cookie;
	m_token = _token;
	m_operator = _operator;
	m_RequestType = _type;
	m_AppendUrl = _AppendUrl;
}
HttpMsg::~HttpMsg()
{
	//m_httpJsonObj = nullptr;
	UE_LOG(LogTemp, Error, TEXT("HttpMsg released~~~~~~~~~~~~~~~~~\n"));

}
void HttpMsg::Decode(FHttpRequestPtr & inReq, FHttpResponsePtr & inResp, bool inSuccess)
{
	if (inSuccess)
	{
		if (inResp.IsValid())
		{
			// 解析json获取msgid，并放入消息队列里.
			/*FString mResponseMsg = inResp->GetContentAsString();
			UE_LOG(LogTemp, Error, TEXT("~~~~~~~~~~~~~~~~~~%s"), *mResponseMsg);
			if (!mResponseMsg.IsEmpty())
			{
				TSharedPtr<FJsonObject> mJsonObject;
				TSharedRef<TJsonReader<>> t_reader = TJsonReaderFactory<>::Create(mResponseMsg);
				if (FJsonSerializer::Deserialize(t_reader, mJsonObject))
				{
					int32 code = mJsonObject->GetIntegerField(TEXT("code"));
					FString sMsg = mJsonObject->GetStringField(TEXT("message"));
					m_httpJsonObj = mJsonObject;
				}
			}*/
		}
	}
}

TSharedPtr<FJsonObject> HttpMsg::GetHttpContent()
{
	return m_httpJsonObj;
}
