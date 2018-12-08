#include "OrderUserInfoUI.h"
#include "UIManager.h"
#include "AddressAndTimeTool.h"
#include "RuntimeRDataManager.h"
#include "MakeOrderUI.h"


void UOrderUserInfoUI::On_Init()
{
    if (UButton * widget = (UButton*)GetWidgetFromName("BackButton"))
    {
        m_BackButton = widget;
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
	R_Order * order = RuntimeRDataManager::GetInstance()->GetCurrentOrder();
	if(order->Status == 2)
    {
        m_CompanyName->SetOnlyShow();
        m_GetStyle->SetOnlyShow();
        m_UsserPhone->SetOnlyShow();
        m_Address->SetOnlyShow();
        m_DetailAddress->SetOnlyShow();
        m_GetTime->SetOnlyShow();
        
        m_CompanyName->m_ItemContent->SetText(FText::FromString(order->ReceiverCompanyName));
        if (order->DeliverType == 1)
        {
            m_GetStyle->m_ItemContent->SetText(FText::FromString(TEXT("送货上门")));
            m_Address->SetVisibility(ESlateVisibility::Visible);
            m_DetailAddress->SetVisibility(ESlateVisibility::Visible);
        }else
        {
            m_GetStyle->m_ItemContent->SetText(FText::FromString(TEXT("自取")));
            m_Address->SetVisibility(ESlateVisibility::Hidden);
            m_DetailAddress->SetVisibility(ESlateVisibility::Hidden);
        }
        m_UserName->m_ItemContent->SetText(FText::FromString(order->ReceiverName));
        m_UsserPhone->m_ItemContent->SetText(FText::FromString(order->ReceiverPhone));
        m_Address->m_ItemContent->SetText(FText::FromString(order->Address));
        m_DetailAddress->m_ItemContent->SetText(FText::FromString(order->DetailAddress));
        m_GetTime->m_ItemContent->SetText(FText::FromString(order->ReceiveTime));
    }else
    {
        m_CompanyName->m_EditText->SetText(FText::FromString(order->ReceiverCompanyName));
        if (order->DeliverType == 1)
        {
            m_GetStyle->m_ItemContent->SetText(FText::FromString(TEXT("送货上门")));
        }else
        {
            m_GetStyle->m_ItemContent->SetText(FText::FromString(TEXT("自取")));
        }
        m_UserName->m_EditText->SetText(FText::FromString(order->ReceiverName));
        m_UsserPhone->m_EditText->SetText(FText::FromString(order->ReceiverPhone));
        m_Address->m_ItemContent->SetText(FText::FromString(order->Address));
        m_DetailAddress->m_EditText->SetText(FText::FromString(order->DetailAddress));
        m_GetTime->m_ItemContent->SetText(FText::FromString(order->ReceiveTime));
    }
	
}
void UOrderUserInfoUI::On_Delete()
{
	UIManager::GetInstance()->UnRegisterButton(m_BackButton);
	UIManager::GetInstance()->UnRegisterButton(m_GetStyle->m_DoSomethingButton);
	UIManager::GetInstance()->UnRegisterButton(m_GetTime->m_DoSomethingButton);
	UIManager::GetInstance()->UnRegisterButton(m_Address->m_DoSomethingButton);

}
void UOrderUserInfoUI::ReView()
{
	R_Order * order = RuntimeRDataManager::GetInstance()->GetCurrentOrder();
	if (order->DeliverType == 1)
	{
		m_Address->SetVisibility(ESlateVisibility::Visible);
		m_DetailAddress->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		m_Address->SetVisibility(ESlateVisibility::Hidden);
		m_DetailAddress->SetVisibility(ESlateVisibility::Hidden);
	}
}
void UOrderUserInfoUI::OnButtonClick(int _index)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UOrderUserInfoUI::OnButtonClick : %d"),_index);
	switch (_index)
	{
	case 1:
	{
		R_Order * order = RuntimeRDataManager::GetInstance()->GetCurrentOrder();
		order->ReceiverCompanyName = m_CompanyName->m_EditText->GetText().ToString();
		order->ReceiverName = m_UserName->m_EditText->GetText().ToString();
		order->ReceiverPhone = m_UsserPhone->m_EditText->GetText().ToString();
		order->Address = m_DetailAddress->m_EditText->GetText().ToString();
		UMakeOrderUI * parentUI = (UMakeOrderUI*)m_ParentUI;
		parentUI->ReView();
		RemoveFromParent();
	}break;
	case 2:
	{
		UBaseUI * GetStyle = UIManager::GetInstance()->OpenUI(TEXT("GetStyleUI"),this);
		GetStyle->AddToViewport();
	}break;
	case 3:
	{
		UAddressAndTimeTool * timeUI = (UAddressAndTimeTool*)UIManager::GetInstance()->OpenUI(TEXT("AddressAndTimeTool"), this);
		
		timeUI->AddToViewport();
		timeUI->SetType(t_Time);
	}break;
	case 4:
	{
		UAddressAndTimeTool * addressUI = (UAddressAndTimeTool*)UIManager::GetInstance()->OpenUI(TEXT("AddressAndTimeTool"), this);
		
		addressUI->AddToViewport();
		addressUI->SetType(t_Address);
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
void UOrderUserInfoUI::SetGetTime(FString _time)
{
	R_Order * order = RuntimeRDataManager::GetInstance()->GetCurrentOrder();
	order->ReceiveTime = _time;
	m_GetTime->m_ItemContent->SetText(FText::FromString(_time));
}
void UOrderUserInfoUI::SetAddress(FString _address)
{
	R_Order * order = RuntimeRDataManager::GetInstance()->GetCurrentOrder();
	order->Address = _address;
	m_Address->m_ItemContent->SetText(FText::FromString(_address));
}
