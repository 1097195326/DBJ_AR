#include "LoginUI.h"
#include "UIManager.h"
#include "LoginGameModule.h"
#include "AppInstance.h"


void ULoginUI::On_Init()
{
	if (UButton *button = Cast<UButton>(GetWidgetFromName("VeriCodeButton")))
	{
		m_VeriCode_Button = button;
		UI_M->RegisterButton(1, m_VeriCode_Button, this, &ULoginUI::On_Button_Click);
	}
	if (UButton *button = Cast<UButton>(GetWidgetFromName("LoginButton")))
	{
		m_Login_Button = button;
		UI_M->RegisterButton(2, m_Login_Button, this, &ULoginUI::On_Button_Click);
	}
	if (UEditableText * text = Cast<UEditableText>(GetWidgetFromName("PhoneBox")))
	{
		m_Phone_Text = text;
	}
	if (UEditableText * text = Cast<UEditableText>(GetWidgetFromName("VeriCodeBox")))
	{
		m_VeriCode_Text = text;
	}
	
}
void ULoginUI::On_Start()
{
	
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2002, this, &ULoginUI::OnGetSmsCode);
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2001, this, &ULoginUI::OnUserLogin);
}
void ULoginUI::On_Delete()
{
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 2002, this);
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 2001, this);

	if (m_Login_Button)
	{
		UI_M->UnRegisterButton(m_Login_Button);
	}
	if (m_VeriCode_Button)
	{
		UI_M->UnRegisterButton(m_VeriCode_Button);
	}
}
void ULoginUI::On_Button_Click(int _index)
{
	UE_LOG(LogTemp, Log, TEXT("zhx : ULoginUI::On_Button_Click : %d"), _index);
	switch (_index)
	{
	case 1:
	{
		UE_LOG(LogTemp,Log,TEXT("zhx : msm code button click "));
		FString phoneNum = m_Phone_Text->GetText().ToString();
		LoginGameModule::GetInstance()->GetSmsCodeToLogin(phoneNum);
		break;
	}
	case 2:
	{
		
		FString phoneNum = m_Phone_Text->GetText().ToString();
		FString veriCodeNum = m_VeriCode_Text->GetText().ToString();
        LoginGameModule::GetInstance()->UserLogin(phoneNum, veriCodeNum);
//        UAppInstance::GetInstance()->OpenLevel(TEXT("TestAR"));
        //UAppInstance::GetInstance()->OpenLevel(TEXT("ARLevel"));
        
		break;
	}
	default:
		break;
	}

}
void ULoginUI::OnGetSmsCode(msg_ptr _msg)
{
	UE_LOG(LogTemp, Log, TEXT("zhx : ULoginUI::OnGetSmsCode : "));
	int code = *((int*)(_msg->GetMsgContent()));
	if (code == 200)
	{

	}
	else
	{

	}
}
void ULoginUI::OnUserLogin(msg_ptr _msg)
{
	UE_LOG(LogTemp, Log, TEXT("zhx : ULoginUI::OnUserLogin : "));
	int code  = *((int *)_msg->GetMsgContent());

	if (code == 200)
	{
		UAppInstance::GetInstance()->OpenLevel(TEXT("ARLevel"));
	}
	else
	{

	}
   


}
