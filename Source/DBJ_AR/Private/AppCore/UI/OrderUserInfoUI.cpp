#include "OrderUserInfoUI.h"
#include "UIManager.h"


void UOrderUserInfoUI::On_Init()
{
    if (UButton * button = (UButton*)GetWidgetFromName("BackButton"))
    {
        m_BackButton = button;
		UIManager::GetInstance()->RegisterButton(1, m_BackButton, this, &UOrderUserInfoUI::OnButtonClick);
    }
	if (UOrderUserInfoItem * widget = (UOrderUserInfoItem*)GetWidgetFromName("CompanyName"))
	{
		m_CompanyName = widget;
	}
	if (UOrderUserInfoItem * widget = (UOrderUserInfoItem*)GetWidgetFromName("GetStyle"))
	{
		m_GetStyle = widget;
		UIManager::GetInstance()->RegisterButton(2, m_GetStyle->m_DoSomethingButton, this, &UOrderUserInfoUI::OnButtonClick);
	}
	if (UOrderUserInfoItem * widget = (UOrderUserInfoItem*)GetWidgetFromName("UserName"))
	{
		m_UserName = widget;
	}
	if (UOrderUserInfoItem * widget = (UOrderUserInfoItem*)GetWidgetFromName("UserPhone"))
	{
		m_UsserPhone = widget;
	}
	if (UOrderUserInfoItem * widget = (UOrderUserInfoItem*)GetWidgetFromName("GetTime"))
	{
		m_GetTime = widget;
		UIManager::GetInstance()->RegisterButton(3, m_GetTime->m_DoSomethingButton, this, &UOrderUserInfoUI::OnButtonClick);
	}
	if (UOrderUserInfoItem * widget = (UOrderUserInfoItem*)GetWidgetFromName("Address"))
	{
		m_Address = widget;
		UIManager::GetInstance()->RegisterButton(4, m_Address->m_DoSomethingButton, this, &UOrderUserInfoUI::OnButtonClick);
	}
	if (UOrderUserInfoItem * widget = (UOrderUserInfoItem*)GetWidgetFromName("DetailAddress"))
	{
		m_DetailAddress = widget;
		//UIManager::GetInstance()->RegisterButton(5, m_DetailAddress->m_DoSomethingButton, this, &UOrderUserInfoUI::OnButtonClick);
	}
}
void UOrderUserInfoUI::On_Start()
{
	//UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(UGameplayStatics::GetPlayerController(this, 0), this);

}
void UOrderUserInfoUI::On_Delete()
{

}
void UOrderUserInfoUI::OnButtonClick(int _index)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UOrderUserInfoUI::OnButtonClick : %d"),_index);
	switch (_index)
	{
	case 1:
	{
		RemoveFromParent();
	}break;
	case 2:
	{
		UBaseUI * GetStyle = UIManager::GetInstance()->OpenUI(TEXT("GetStyleUI"),this);
		GetStyle->AddToViewport();
	}break;
	case 3:
	{
		UBaseUI * timeUI = UIManager::GetInstance()->OpenUI(TEXT("AddressAndTimeTool"), this);
		timeUI->AddToViewport();
	}break;
	case 4:
	{

	}break;
	case 5:
	{

	}break;
	default:
		break;
	}
}
void UOrderUserInfoUI::SetGetStyle(FString _style)
{
	m_GetStyle->m_ItemContent->SetText(FText::FromString(_style));
}
