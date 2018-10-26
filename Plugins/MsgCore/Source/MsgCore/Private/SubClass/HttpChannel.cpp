#include "HttpChannel.h"




HttpChannel::HttpChannel():m_CanRun(true)
{
	m_IsRequesting = false;
	m_Thread = thread(std::bind(&HttpChannel::Update, this));
	m_Thread.detach();
}
void HttpChannel::SendMsg(msg_ptr _msg)
{
	m_Msg_Queue.push(_msg);
}
void HttpChannel::Update()
{
	while (m_CanRun)
	{
		m_ThreadMutex.lock();
		if (!m_IsRequesting && !m_Msg_Queue.empty())
		{
			m_CurrentMsg = m_Msg_Queue.front();
			SendMsgToHttp(m_CurrentMsg);
		}
		m_ThreadMutex.unlock();
	}
}
void HttpChannel::SendMsgToHttp(msg_ptr _msg)
{
	m_IsRequesting = true;
	HttpMsg *mHttpMsg = _msg->ConvertToT<HttpMsg>();

	FHttpModule::Get().SetHttpTimeout(60);

	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));

	HttpRequest->SetHeader(TEXT("token"), mHttpMsg->m_token);

	HttpRequest->SetHeader(TEXT("operator"), mHttpMsg->m_operator);

	HttpRequest->SetURL(mHttpMsg->m_httpUrl);

	const FString verb = TEXT("POST");
	HttpRequest->SetVerb(verb);

	HttpRequest->SetContentAsString(mHttpMsg->m_httpContent);

	HttpRequest->OnProcessRequestComplete() = FHttpRequestCompleteDelegate::CreateRaw(this, &HttpChannel::OnMsgResponse);

	UE_LOG(LogTemp, Log, TEXT("zhx : url(%s),parameter:%s"),*mHttpMsg->m_httpUrl,*mHttpMsg->m_httpContent);

	HttpRequest->ProcessRequest();

	m_HttpRequests.push_back(HttpRequest);
}
void HttpChannel::OnMsgResponse(FHttpRequestPtr inReq, FHttpResponsePtr inResp, bool isSuccess)
{
	
	if (isSuccess && inResp.IsValid())
	{
		FString mResponseMsg = inResp->GetContentAsString();
		UE_LOG(LogTemp, Log, TEXT("zhx : response : %s"), *mResponseMsg);
		/*if (!mResponseMsg.IsEmpty())
		{
			TSharedPtr<FJsonObject> mJsonObject;
			TSharedRef<TJsonReader<>> t_reader = TJsonReaderFactory<>::Create(mResponseMsg);
			if (FJsonSerializer::Deserialize(t_reader, mJsonObject))
			{
				int32 code = mJsonObject->GetIntegerField(TEXT("code"));
				FString sMsg = mJsonObject->GetStringField(TEXT("message"));
			}
		}*/
		// detach msg
		/*auto iter = m_Msg_Header_Map.find(m_CurrentMsg->GetMsgId());
		if (iter != m_Msg_Header_Map.end())
		{
		Msg_Header_List msgList = iter->second;
		list<MsgHeader>::iterator lIter;
		for (lIter = msgList.begin(); lIter != msgList.end(); lIter++)
		{
			msg_ptr msg(new LocalMsg());
			
			lIter->m_Fun_Header(msg);
		}
		}*/
	}

	m_Msg_Queue.pop();
	m_CurrentMsg = nullptr;
	m_IsRequesting = false;
	
}
void HttpChannel::StopSendMsg()
{
	m_CanRun = false;
	
}