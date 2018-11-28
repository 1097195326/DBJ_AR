#include "SettingUI.h"
#include "UIManager.h"
#include "UserInfo.h"
#include "AppInstance.h"
#include "EditerARGameModule.h"
#include "UserPawn.h"

void USettingUI::On_Init()
{
    if (UButton * widget = (UButton*)GetWidgetFromName("AllowGButton"))
    {
        m_AllowGButton = widget;
		UIManager::GetInstance()->RegisterButton(1, m_AllowGButton, this, &USettingUI::OnButtonClick);
    }
	if (UButton * widget = (UButton*)GetWidgetFromName("LayoutButton"))
	{
		m_LayoutButton = widget;
		UIManager::GetInstance()->RegisterButton(2, m_LayoutButton, this, &USettingUI::OnButtonClick);
	}
	if (UButton * widget = (UButton*)GetWidgetFromName("BackButton"))
	{
		m_BackButton = widget;
		UIManager::GetInstance()->RegisterButton(3, m_BackButton, this, &USettingUI::OnButtonClick);
	}
	if (UImage * widget = (UImage*)GetWidgetFromName("SwitchOff"))
	{
		m_SwitchOff = widget;
	}
	if (UImage * widget = (UImage*)GetWidgetFromName("SwitchOn"))
	{
		m_SwitchOn = widget;
	}
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2003, this, &USettingUI::OnUserLogout);

	isOnOrOff = UserInfo::Get()->GetLocalData().Allow4G == 1 ? true : false;
	ReView();
}
void USettingUI::On_Delete()
{
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 2003, this);

}
void USettingUI::OnButtonClick(int _index)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIB::OnButtonClick : "));
	switch (_index)
	{
	case 1:
	{
		isOnOrOff = !isOnOrOff;
		int value = isOnOrOff ? 1 : 0;
		UserInfo::Get()->SaveUserData(TEXT("Allow4G"), value);
		ReView();
	}break;
	case 2:
	{
		/*AUserPawn::GetInstance()->DeleteAllARActor();
		UAppInstance::GetInstance()->OpenLevel(TEXT("LoginLevel"));*/
		EditerARGameModule::GetInstance()->UserLogout();
	}break;
	case 3:
	{
		UBaseUI * baseUI = UIManager::GetInstance()->OpenUI(TEXT("UserAccountUI"));
		baseUI->AddToViewport();
		RemoveFromParent();
	}break;
	}
}
void USettingUI::ReView()
{
	if (isOnOrOff)
	{
		m_SwitchOn->SetVisibility(ESlateVisibility::Visible);
		m_SwitchOff->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		m_SwitchOn->SetVisibility(ESlateVisibility::Hidden);
		m_SwitchOff->SetVisibility(ESlateVisibility::Visible);
	}

}
void USettingUI::OnUserLogout(msg_ptr _msg)
{
	int result =  _msg->GetMsgContent<int>();
	if (result == 1)
	{
		AUserPawn::GetInstance()->DeleteAllARActor();
		UAppInstance::GetInstance()->OpenLevel(TEXT("LoginLevel"));
	}
}