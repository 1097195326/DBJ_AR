#include "LoginGameModule.h"
#include "LoginUIController.h"
#include "DataManager.h"
#include "MsgCenter.h"


LoginGameModule * LoginGameModule::GetInstance()
{
	static LoginGameModule m;
	return &m;
}
void LoginGameModule::On_Init()
{
	m_CurrentUIController = new LoginUIController();
	m_CurrentUIController->On_Init();

}
void LoginGameModule::On_Start()
{
	m_CurrentUIController->On_Start();

}
void LoginGameModule::On_Delete()
{

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
	MsgCenter::Instance()->SendMsg(mMsg);

}
