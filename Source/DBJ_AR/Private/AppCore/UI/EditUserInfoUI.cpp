#include "EditUserInfoUI.h"
#include "UIManager.h"
#include "UserInfo.h"
#include "EditerARGameModule.h"



void UEditUserInfoUI::On_Init()
{
    if (UButton * widget = (UButton*)GetWidgetFromName("BackButton"))
    {
		m_BackButton = widget;
    }
	if (UButton * widget = (UButton*)GetWidgetFromName("ChangeUserImage"))
	{
		m_ChangeUserImage = widget;
	}
	if (UButton * widget = (UButton*)GetWidgetFromName("EditUserNameButton"))
	{
		m_EditUerNameButton = widget;
	}
	if (UImage * widget = (UImage*)GetWidgetFromName("UserImage"))
	{
		m_UserImage = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("UserName"))
	{
		m_UserName = widget;

	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("UserPhone"))
	{
		m_UserPhone = widget;
	}

}
void UEditUserInfoUI::On_Start()
{
	UIManager::GetInstance()->RegisterButton(1, m_BackButton, this, &UEditUserInfoUI::OnButtonClick);
	UIManager::GetInstance()->RegisterButton(2, m_ChangeUserImage, this, &UEditUserInfoUI::OnButtonClick);
	UIManager::GetInstance()->RegisterButton(3, m_EditUerNameButton, this, &UEditUserInfoUI::OnButtonClick);

	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2015, this, &UEditUserInfoUI::OnEditString);

	m_UserName->SetText(FText::FromString(UserInfo::Get()->GetLocalData().renterName));
	m_UserPhone->SetText(FText::FromString(UserInfo::Get()->GetLocalData().phone));

}
void UEditUserInfoUI::On_Delete()
{
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 2015, this);

	UIManager::GetInstance()->UnRegisterButton(m_BackButton);
	UIManager::GetInstance()->UnRegisterButton(m_ChangeUserImage);
	UIManager::GetInstance()->UnRegisterButton(m_EditUerNameButton);

}
void UEditUserInfoUI::OnButtonClick(int _index)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UEditUserInfoUI::OnButtonClick : "));
	switch (_index)
	{
	case 1:
	{
		UBaseUI * baseUI = UIManager::GetInstance()->OpenUI(TEXT("UserAccountUI"));
		baseUI->AddToViewport();
		RemoveFromParent();
	}break;
	case 2:
	{
        UBaseUI * baseUI = UIManager::GetInstance()->OpenUI(TEXT("PhotoPage"));
        baseUI->AddToViewport();
	}break;
	case 3:
	{
		UEditStringUI * baseUI = (UEditStringUI*)UIManager::GetInstance()->OpenUI(TEXT("EditStringUI"));
		baseUI->SetDelegate(this,TEXT("用户名"), UserInfo::Get()->GetLocalData().renterName);
		baseUI->AddToViewport();
	}break;
	}

}
void UEditUserInfoUI::OnEditString(msg_ptr _msg)
{
	UE_LOG(LogTemp, Log, TEXT("zhx : edit user info text changed"));
	UserInfo::Get()->SetUserName(m_Wto_UserName);
	m_UserName->SetText(FText::FromString(m_Wto_UserName));
}
void UEditUserInfoUI::EditString(const FString & text)
{
	m_Wto_UserName = text;

	EditerARGameModule::GetInstance()->UpdateUserName(text);

}