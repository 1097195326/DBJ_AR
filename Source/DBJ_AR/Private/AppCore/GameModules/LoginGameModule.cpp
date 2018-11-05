#include "LoginGameModule.h"
#include "LoginUIController.h"
#include "DataManager.h"
#include "UserInfo.h"


LoginGameModule * LoginGameModule::GetInstance()
{
	static LoginGameModule m;
	return &m;
}
void LoginGameModule::On_Init()
{
	m_CurrentUIController = new LoginUIController();
	m_CurrentUIController->On_Init();

	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_HttpRequest, 1002, this, &LoginGameModule::OnGetSmsCode);
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_HttpRequest, 1001, this, &LoginGameModule::OnUserLogin);

}
void LoginGameModule::On_Start()
{
	m_CurrentUIController->On_Start();

}
void LoginGameModule::On_Delete()
{
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_HttpRequest, 1002, this);
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_HttpRequest, 1001, this);

	if (m_CurrentUIController != nullptr)
	{
		delete m_CurrentUIController;
	}
}
void LoginGameModule::GetSmsCodeToLogin(FString _phoneNum)
{
	TSharedPtr<FJsonObject> t_jsonObject = MakeShareable(new FJsonObject);

	t_jsonObject->SetStringField(TEXT("phone"), _phoneNum);

	HttpMsg * msg = new HttpMsg(Msg_HttpRequest, 1002, t_jsonObject);
	msg->m_httpUrl = Data_M->GetURL(msg->m_MsgId);
	msg_ptr mMsg(msg); //
	
	// 3.通过消息系统发送消息.
	MsgCenter::GetInstance()->SendMsg(mMsg);

}
void LoginGameModule::OnGetSmsCode(msg_ptr _msg)
{
	UE_LOG(LogTemp, Log, TEXT("zhx : LoginGameModule::OnGetSmsCode : "));

}
void LoginGameModule::UserLogin(FString _phoneNum, FString _smsCodeNum)
{
	msg_ptr msg(new LocalMsg(Msg_Local, 2001,nullptr));
	MsgCenter::GetInstance()->SendMsg(msg);

	//TSharedPtr<FJsonObject> t_jsonObject = MakeShareable(new FJsonObject);

	//t_jsonObject->SetStringField(TEXT("phone"), _phoneNum);
	//t_jsonObject->SetStringField(TEXT("smsCode"), _smsCodeNum);

	//HttpMsg * msg = new HttpMsg(Msg_HttpRequest, 1001, t_jsonObject);
	//msg->m_httpUrl = Data_M->GetURL(msg->m_MsgId);
	//msg_ptr mMsg(msg); //

	//				   // 3.通过消息系统发送消息.
	//MsgCenter::GetInstance()->SendMsg(mMsg);
}
void LoginGameModule::OnUserLogin(msg_ptr _msg)
{
	UE_LOG(LogTemp, Log, TEXT("zhx : LoginGameModule::OnUserLogin : "));
	TSharedPtr<FJsonObject> jsonData = _msg->GetJsonObject();

	UserInfo::Get()->SaveToLocal(&jsonData);

	msg_ptr msg(new LocalMsg(Msg_Local,2001,jsonData));
	MsgCenter::GetInstance()->SendMsg(msg);

}
