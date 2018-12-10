#include "HttpChannel.h"
#include "MsgCenter.h"



HttpChannel::HttpChannel():m_CanRun(true)
{
	m_IsRequesting = false;
    m_Thread = thread(std::bind(&HttpChannel::Update, this));
    m_Thread.detach();
}
void HttpChannel::SendMsg(msg_ptr _msg)
{
	m_Msg_Queue.push(_msg);
	/*m_CurrentMsg = m_Msg_Queue.front();
	SendMsgToHttp(m_CurrentMsg);*/
}
void HttpChannel::TickMsg()
{
    Update();
}
void HttpChannel::Update()
{
    while (m_CanRun)
//    if(m_CanRun)
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
	HttpMsg *mHttpMsg = _msg->SelfConvertToT<HttpMsg>();

	FHttpModule::Get().SetHttpTimeout(60);

	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));

	HttpRequest->SetHeader(TEXT("token"), mHttpMsg->m_token);
	HttpRequest->SetHeader(TEXT("Cookie"), mHttpMsg->m_Cookie);

    UE_LOG(LogTemp, Log, TEXT("zhx : token(%s),Cookie:%s"),*mHttpMsg->m_token,*mHttpMsg->m_Cookie);
    
	HttpRequest->SetHeader(TEXT("operator"), mHttpMsg->m_operator);

	FString httpUrl;
	if (!mHttpMsg->m_AppendUrl.IsEmpty() && !mHttpMsg->m_AppendUrl.Equals(""))
	{
		httpUrl = FString::Printf(TEXT("%s?%s"), *mHttpMsg->m_httpUrl, *mHttpMsg->m_AppendUrl);
	}
	else
	{
		httpUrl = mHttpMsg->m_httpUrl;
	}
	httpUrl.RemoveSpacesInline();
	HttpRequest->SetURL(httpUrl);
	
	switch (mHttpMsg->m_RequestType)
	{
	case Http_Post:
	{
		HttpRequest->SetVerb(TEXT("POST"));
	}break;
	case  Http_Get:
	{
		HttpRequest->SetVerb(TEXT("GET"));
	}break;
	case  Http_Put:
	{
		HttpRequest->SetVerb(TEXT("PUT"));
	}break;
	}
	/*const FString verb = mHttpMsg->m_IsGet ? TEXT("GET") : TEXT("POST");
	HttpRequest->SetVerb(verb);*/

	HttpRequest->SetContentAsString(mHttpMsg->m_httpContent);

	HttpRequest->OnProcessRequestComplete() = FHttpRequestCompleteDelegate::CreateRaw(this, &HttpChannel::OnMsgResponse);

	UE_LOG(LogTemp, Log, TEXT("zhx : url(%s),parameter:%s"),*httpUrl,*mHttpMsg->m_httpContent);

	HttpRequest->ProcessRequest();

	m_HttpRequests.push_back(HttpRequest);
}
void HttpChannel::OnMsgResponse(FHttpRequestPtr inReq, FHttpResponsePtr inResp, bool isSuccess)
{
	
	if (isSuccess && inResp.IsValid())
	{
		FString mResponseMsg = inResp->GetContentAsString();
		UE_LOG(LogTemp, Error, TEXT("zhx : response : %s"), *mResponseMsg);
		if (!mResponseMsg.IsEmpty())
		{
			TSharedPtr<FJsonObject> mJsonObject;
			TSharedRef<TJsonReader<>> t_reader = TJsonReaderFactory<>::Create(mResponseMsg);
			if (FJsonSerializer::Deserialize(t_reader, mJsonObject))
			{
				FString msgContent;
				TSharedRef<TJsonWriter<TCHAR>> t_writer = TJsonWriterFactory<>::Create(&msgContent);
				FJsonSerializer::Serialize(mJsonObject.ToSharedRef(), t_writer);
				UE_LOG(LogTemp, Error, TEXT("zhx : response : %s"), *msgContent);
				// detach msg
				auto iter = m_Msg_Header_Map.find(m_CurrentMsg->GetMsgId());
				if (iter != m_Msg_Header_Map.end())
				{
					Msg_Header_List msgList = iter->second;
					list<MsgHeader>::iterator lIter;
					for (lIter = msgList.begin(); lIter != msgList.end(); lIter++)
					{
						msg_ptr msg(new MsgStruct(mJsonObject));
						lIter->m_Fun_Header(msg);
					}
				}
			}
		}

		m_Msg_Queue.pop();
		m_CurrentMsg = nullptr;
		m_IsRequesting = false;
	}
	else
	{
		msg_ptr msg(new LocalMsg(Msg_Local, 110, nullptr));
		MsgCenter::GetInstance()->SendMsg(msg);
	}
}

void HttpChannel::StopSendMsg()
{
	m_CanRun = false;
	
}
void HttpChannel::RerequestHttp()
{
	m_CurrentMsg = nullptr;
	m_IsRequesting = false;
}
void HttpChannel::ContineHttp()
{
	m_Msg_Queue.pop();
	m_CurrentMsg = nullptr;
	m_IsRequesting = false;
}