#pragma once

#include "MsgChannel.h"

#include "HttpMsg.h"
#include "LocalMsg.h"


#include <queue>
#include <list>
#include <thread>
#include <mutex>


class MSGCORE_API HttpChannel : public MsgChannel
{
protected:
	bool				m_CanRun;
	bool				m_IsRequesting;

	std::thread			m_Thread;
	mutex				m_ThreadMutex;

	queue<msg_ptr>		m_Msg_Queue;
	list<TSharedRef<IHttpRequest>> m_HttpRequests;

	msg_ptr		m_CurrentMsg;
	
	virtual void Update();
public:
	HttpChannel();
	virtual void StopSendMsg() override;
    virtual void TickMsg() override;

	void	RerequestHttp();
	void	ContineHttp();

	virtual void SendMsg(msg_ptr _msg);

	virtual void SendMsgToHttp(msg_ptr _msg);
	virtual void OnMsgResponse(FHttpRequestPtr inReq, FHttpResponsePtr inResp, bool inSuccess);
};
