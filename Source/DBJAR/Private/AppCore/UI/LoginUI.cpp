#include "LoginUI.h"
#include "UIManager.h"
#include "LoginGameModule.h"
#include "AppInstance.h"
#include "AlertUI.h"
#include "UserInfo.h"

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
		FString phoneNum = m_Phone_Text->GetText().ToString();
		if (UAppInstance::CheckPhone(phoneNum))
		{
			timeindex = 60;
			m_VeriCode_Button->SetIsEnabled(false);
			GetWorld()->GetTimerManager().SetTimer(m_TimeHandle, this, &ULoginUI::TimeRun, 1, true, 0);
			LoginGameModule::GetInstance()->GetSmsCodeToLogin(phoneNum);
		}
		else
		{
			UIManager::GetInstance()->TopHintText(TEXT("请输入正确的手机号"),1);
		}
		
	}break;
	case 2:
	{
		FString phoneNum = m_Phone_Text->GetText().ToString();
		FString veriCodeNum = m_VeriCode_Text->GetText().ToString();
		if (UAppInstance::CheckPhone(phoneNum))
		{
			if (!veriCodeNum.IsEmpty())
			{
				LoginGameModule::GetInstance()->UserLogin(phoneNum, veriCodeNum);
			}
			else
			{
				UIManager::GetInstance()->TopHintText(TEXT("验证码不能为空"), 1);
			}
		}
		else
		{
			UIManager::GetInstance()->TopHintText(TEXT("请输入正确的手机号"), 1);
		}
	}break;
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
	int result = *((int*)(_msg->GetMsgContent()));
	if (result == 1)
	{
		UIManager::GetInstance()->TopHintText(TEXT("发送验证码成功"),1.f);
	}
	else
	{
		UIManager::GetInstance()->TopHintText(TEXT("发送验证码失败"),1.f);
	}
}
void ULoginUI::OnUserLogin(msg_ptr _msg)
{
	UE_LOG(LogTemp, Log, TEXT("zhx : ULoginUI::OnUserLogin : "));
	TSharedPtr<FJsonObject> jsonObj = _msg->GetJsonObject();

	if (jsonObj->GetIntegerField(TEXT("code")) == 200)
	{
		CheckRemainDays();
	}
    else
    {
		FString msg = jsonObj->GetStringField(TEXT("msg"));
		UIManager::GetInstance()->TopHintText(msg, 3.f);
    }
}
void ULoginUI::OnAutoLogin(msg_ptr _msg)
{
	TSharedPtr<FJsonObject> jsonObj = _msg->GetJsonObject();

	if (jsonObj->GetIntegerField(TEXT("code")) == 200)
	{
		CheckRemainDays();
	}
	else
	{
		FString msg = jsonObj->GetStringField(TEXT("msg"));
		UIManager::GetInstance()->TopHintText(msg, 3.f);
	}
}
void ULoginUI::CheckRemainDays()
{
	if (UserInfo::Get()->GetLocalData().Tips)
	{
		UAlertUI * alertUI = (UAlertUI*)UIManager::GetInstance()->OpenUI(TEXT("AlertUI"));
		alertUI->SetContentText(UserInfo::Get()->GetLocalData().TipMessage);
		alertUI->OnlyButtonShow(true);
		alertUI->BindOnlySureFunctionCall(this, &ULoginUI::OnAlertButtonClick);
		alertUI->AddToViewport(99);
	}
}
void ULoginUI::OnAlertButtonClick()
{
	if (UserInfo::Get()->GetLocalData().RemainingDays > 0)
	{
		UAppInstance::GetInstance()->OpenLevel(TEXT("ARLevel"));

	}
}