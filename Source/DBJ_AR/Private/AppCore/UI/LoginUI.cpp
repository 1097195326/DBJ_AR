﻿#include "LoginUI.h"
#include "UIManager.h"
#include "LoginGameModule.h"
#include "AppInstance.h"


void ULoginUI::On_Init()
{
	if (UCanvasPanel * widget = Cast<UCanvasPanel>(GetWidgetFromName("XieYiPanel")))
	{
		m_XieyiPanel = widget;
	}
	if (UCanvasPanel * widget = Cast<UCanvasPanel>(GetWidgetFromName("Main")))
	{
		m_MainPanel = widget;
	}

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
	if (UButton *button = Cast<UButton>(GetWidgetFromName("BackButton")))
	{
		m_BackButton = button;
		UI_M->RegisterButton(3, m_BackButton, this, &ULoginUI::On_Button_Click);
	}
	if (UButton *button = Cast<UButton>(GetWidgetFromName("Button_Open_Service_Agreement")))
	{
		m_Button_Open_Service_Agreement = button;
		UI_M->RegisterButton(4, m_Button_Open_Service_Agreement, this, &ULoginUI::On_Button_Click);
	}
	if (UEditableText * text = Cast<UEditableText>(GetWidgetFromName("PhoneBox")))
	{
		m_Phone_Text = text;
	}
	if (UEditableText * text = Cast<UEditableText>(GetWidgetFromName("VeriCodeBox")))
	{
		m_VeriCode_Text = text;
	}
	if (UTextBlock * text = Cast<UTextBlock>(GetWidgetFromName("VeriCodeText")))
	{
		m_VeriText = text;
	}
	
}
void ULoginUI::On_Start()
{
	m_VeriText->SetText(FText::FromString(TEXT("| 获取验证码")));

	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2002, this, &ULoginUI::OnGetSmsCode);
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2001, this, &ULoginUI::OnUserLogin);
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2016, this, &ULoginUI::OnAutoLogin);

	LoginGameModule::GetInstance()->AutoLogin();

}
void ULoginUI::On_Delete()
{
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 2002, this);
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 2001, this);
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 2016, this);

	if (m_Login_Button)
	{
		UI_M->UnRegisterButton(m_Login_Button);
	}
	if (m_VeriCode_Button)
	{
		UI_M->UnRegisterButton(m_VeriCode_Button);
	}
}
static int timeindex = 0;
void ULoginUI::On_Button_Click(int _index)
{
	UE_LOG(LogTemp, Log, TEXT("zhx : ULoginUI::On_Button_Click : %d"), _index);
	switch (_index)
	{
	case 1:
	{
		UE_LOG(LogTemp,Log,TEXT("zhx : msm code button click "));
		timeindex = 60;
		m_VeriCode_Button->SetIsEnabled(false);
		GetWorld()->GetTimerManager().SetTimer(m_TimeHandle, this, &ULoginUI::TimeRun, 1, true,0);
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
	case 3:
	{
		m_MainPanel->SetVisibility(ESlateVisibility::Visible);
		m_XieyiPanel->SetVisibility(ESlateVisibility::Hidden);
	}break;
	case 4:
	{
		m_MainPanel->SetVisibility(ESlateVisibility::Hidden);
		m_XieyiPanel->SetVisibility(ESlateVisibility::Visible);
	}break;
	default:
		break;
	}

}
void ULoginUI::TimeRun()
{
	timeindex--;
	FString showText = FString::Printf(TEXT("| 重新获取(%ds)"),timeindex);
	m_VeriText->SetText(FText::FromString(showText));

	if (timeindex <= 0)
	{
		m_VeriText->SetText(FText::FromString(TEXT("| 获取验证码")));
		m_VeriCode_Button->SetIsEnabled(true);
		GetWorld()->GetTimerManager().ClearTimer(m_TimeHandle);
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
	int result = _msg->GetMsgContent<int>();

    if (result == 1)
	{
        UAppInstance::GetInstance()->OpenLevel(TEXT("ARLevel"));
//        UAppInstance::GetInstance()->OpenLevel(TEXT("TestAR"));
	}
    else
    {

    }
}
void ULoginUI::OnAutoLogin(msg_ptr _msg)
{
	int result = _msg->GetMsgContent<int>();
	if (result == 1)
	{
		UAppInstance::GetInstance()->OpenLevel(TEXT("ARLevel"));
	}
	else
	{

	}
}
