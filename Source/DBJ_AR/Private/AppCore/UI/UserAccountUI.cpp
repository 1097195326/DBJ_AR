#include "UserAccountUI.h"
#include "UIManager.h"

void UUserAccountUI::On_Init()
{
    if (UButton * widget = (UButton*)GetWidgetFromName("BackButton"))
    {
		m_BackButton = widget;
		UIManager::GetInstance()->RegisterButton(1, m_BackButton, this, &UUserAccountUI::OnButtonClick);
    }
	if (UButton * widget = (UButton*)GetWidgetFromName("SettingButton"))
	{
		m_SettingButton = widget;
		UIManager::GetInstance()->RegisterButton(1, m_SettingButton, this, &UUserAccountUI::OnButtonClick);
	}
	if (UButton * widget = (UButton*)GetWidgetFromName("ToUserInfoButton"))
	{
		m_ToUserInfoButton = widget;
		UIManager::GetInstance()->RegisterButton(1, m_ToUserInfoButton, this, &UUserAccountUI::OnButtonClick);
	}
	if (UNativeWidgetHost * widget = (UNativeWidgetHost*)GetWidgetFromName("UserImage"))
	{
		m_UserImage = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("CompanyName"))
	{
		m_CompanyName = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("UserName"))
	{
		m_UserName = widget;
	}
}
void UUserAccountUI::On_Start()
{

}
void UUserAccountUI::On_Delete()
{

}
void UUserAccountUI::OnButtonClick(int _index)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIB::OnButtonClick : "));

}
