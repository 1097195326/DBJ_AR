#include "HttpMsg.h"



HttpMsg::HttpMsg()
{

}
//
HttpMsg::HttpMsg(MsgChanelId _channelID, int32 _unMsgID, TSharedPtr<FJsonObject> & _content, FString _token, FString _operator, EnumHttpRequestType _httpReqType)
{
	m_MsgChannelId = _channelID;
	m_MsgId = _unMsgID;
	m_token = _token;
	m_operator = _operator;
	m_HttpRequestType = _httpReqType;

	TSharedRef<TJsonWriter<TCHAR>> t_writer = TJsonWriterFactory<>::Create(&m_httpContent);
	FJsonSerializer::Serialize(_content.ToSharedRef(), t_writer);
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
