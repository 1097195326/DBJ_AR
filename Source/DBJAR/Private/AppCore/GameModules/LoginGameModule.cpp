#include "LoginGameModule.h"
#include "LoginUIController.h"
#include "DataManager.h"
#include "UserInfo.h"


LoginGameModule * LoginGameModule::GetInstance()
{
	static LoginGameModule m;
	return &m;
}
LoginGameModule::LoginGameModule()
{
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_HttpRequest, 1002, this, &LoginGameModule::OnGetSmsCode);
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_HttpRequest, 1001, this, &LoginGameModule::OnUserLogin);
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_HttpRequest, 1016, this, &LoginGameModule::OnAutoLogin);
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_HttpRequest, 1017, this, &LoginGameModule::OnUpdateRentDay);
}
void LoginGameModule::On_Init()
{
	UserInfo::Get()->ReadLocalData();

	FString token = UserInfo::Get()->GetLocalData().token;
	UE_LOG(LogTemp, Log, TEXT("zhx : LoginGameModule::On_Init : token = %s"), *token);

	m_CurrentUIController = new LoginUIController();
	m_CurrentUIController->On_Init();

}
void LoginGameModule::On_Start()
{
	m_CurrentUIController->On_Start();

}
void LoginGameModule::On_Delete()
{
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_HttpRequest, 1002, this);
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_HttpRequest, 1001, this);
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_HttpRequest, 1016, this);
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_HttpRequest, 1017, this);

	if (m_CurrentUIController != nullptr)
	{
		delete m_CurrentUIController;
	}
}
void LoginGameModule::GetSmsCodeToLogin(FString _phoneNum)
{
	TSharedPtr<FJsonObject> t_jsonObject = MakeShareable(new FJsonObject);

	t_jsonObject->SetStringField(TEXT("phone"), _phoneNum);

	FString httpUrl = Data_M->GetURL(1002);
	HttpMsg * msg = new HttpMsg(Msg_HttpRequest, 1002, t_jsonObject, httpUrl,Http_Post);
	
	msg_ptr mMsg(msg); //
	
	// 3.通过消息系统发送消息.
	MsgCenter::GetInstance()->SendMsg(mMsg);

}
void LoginGameModule::OnGetSmsCode(msg_ptr _msg)
{
	UE_LOG(LogTemp, Log, TEXT("zhx : LoginGameModule::OnGetSmsCode : "));
	int result = 0;
	TSharedPtr<FJsonObject> jsonData = _msg->GetJsonObject();
	if (jsonData->GetIntegerField(TEXT("code")) == 200)
	{
		result = 1;

	}
	msg_ptr msg(new LocalMsg(Msg_Local, 2002,&result));
	MsgCenter::GetInstance()->SendMsg(msg);
}
void LoginGameModule::UserLogin(FString _phoneNum, FString _smsCodeNum)
{
	/*msg_ptr msg(new LocalMsg(Msg_Local, 2001,nullptr));
	MsgCenter::GetInstance()->SendMsg(msg);*/

	TSharedPtr<FJsonObject> t_jsonObject = MakeShareable(new FJsonObject);

	t_jsonObject->SetStringField(TEXT("phone"), _phoneNum);
	t_jsonObject->SetStringField(TEXT("smsCode"), _smsCodeNum);

	FString httpUrl = Data_M->GetURL(1001);
	HttpMsg * msg = new HttpMsg(Msg_HttpRequest, 1001, t_jsonObject,httpUrl,Http_Post);
	msg_ptr mMsg(msg); //

					   // 3.通过消息系统发送消息.
	MsgCenter::GetInstance()->SendMsg(mMsg);
}
void LoginGameModule::OnUserLogin(msg_ptr _msg)
{
	UE_LOG(LogTemp, Log, TEXT("zhx : LoginGameModule::OnUserLogin : "));
	
	TSharedPtr<FJsonObject> jsonData = _msg->GetJsonObject();
	if (jsonData->GetIntegerField(TEXT("code")) == 200)
	{
		TSharedPtr<FJsonObject> jsonObj = jsonData->GetObjectField(TEXT("data"));
		FString token = jsonObj->GetStringField(TEXT("token"));
		TSharedPtr<FJsonObject> userData = jsonObj->GetObjectField(TEXT("userRentVO"));

		userData->SetStringField(TEXT("token"), token);
		UserInfo::Get()->SaveToLocal(userData);
		UpdateRentDay();
	}
	
	msg_ptr msg(new LocalMsg(Msg_Local, 2001, jsonData));
	MsgCenter::GetInstance()->SendMsg(msg);
}
void LoginGameModule::AutoLogin()
{
	FString cookie = UserInfo::Get()->GetCookie();
	FString token = UserInfo::Get()->GetToken();
	if (!token.IsEmpty())
	{
		FString httpUrl = Data_M->GetURL(1016);
		msg_ptr mMsg(new HttpMsg(Msg_HttpRequest, 1016, httpUrl, TEXT(""), Http_Get, cookie, token));

		MsgCenter::GetInstance()->SendMsg(mMsg);
	}
}
void LoginGameModule::OnAutoLogin(msg_ptr _msg)
{
	TSharedPtr<FJsonObject> jsonData = _msg->GetJsonObject();
	if (jsonData->GetIntegerField(TEXT("code")) == 200)
	{
		TSharedPtr<FJsonObject> jsonObj = jsonData->GetObjectField(TEXT("data"));
		jsonObj->SetStringField(TEXT("token"), UserInfo::Get()->GetToken());
		UserInfo::Get()->SaveToLocal(jsonObj);
		UpdateRentDay();
	}
	msg_ptr msg(new LocalMsg(Msg_Local, 2016, jsonData));
	MsgCenter::GetInstance()->SendMsg(msg);
}
void LoginGameModule::UpdateRentDay()
{
	FString cookie = UserInfo::Get()->GetCookie();
	FString token = UserInfo::Get()->GetToken();
	if (!token.IsEmpty())
	{
		FString httpUrl = Data_M->GetURL(1017);
		msg_ptr mMsg(new HttpMsg(Msg_HttpRequest, 1017, httpUrl, TEXT(""), Http_Put, cookie, token));
		MsgCenter::GetInstance()->SendMsg(mMsg);
	}
}
void LoginGameModule::OnUpdateRentDay(msg_ptr _msg)
{
	/*TSharedPtr<FJsonObject> jsonData = _msg->GetJsonObject();
	if (jsonData->GetIntegerField(TEXT("code")) == 200)
	{

	}*/
}