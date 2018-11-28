#include "EditUserInfoUI.h"
#include "UIManager.h"

void UEditUserInfoUI::On_Init()
{
    if (UButton * widget = (UButton*)GetWidgetFromName("BackButton"))
    {
		m_BackButton = widget;
		UIManager::GetInstance()->RegisterButton(1, m_BackButton, this, &UEditUserInfoUI::OnButtonClick);
    }
	if (UButton * widget = (UButton*)GetWidgetFromName("ChangeUserImage"))
	{
		m_ChangeUserImage = widget;
		UIManager::GetInstance()->RegisterButton(2, m_ChangeUserImage, this, &UEditUserInfoUI::OnButtonClick);
	}
	if (UImage * widget = (UImage*)GetWidgetFromName("UserImage"))
	{
		m_UserImage = widget;
	}
	if (UEditableText * widget = (UEditableText*)GetWidgetFromName("EditUserName"))
	{
		m_EditUserName = widget;
	}
	if (UEditableText * widget = (UEditableText*)GetWidgetFromName("EditUserPhone"))
	{
		m_EditUserPhone = widget;
	}

}
void UEditUserInfoUI::OnButtonClick(int _index)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIB::OnButtonClick : "));
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

	}break;
	}

}