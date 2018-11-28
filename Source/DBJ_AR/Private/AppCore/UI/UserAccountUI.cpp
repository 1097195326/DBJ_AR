#include "UserAccountUI.h"
#include "UIManager.h"
#include "UserInfo.h"
#include "EditerARGameModule.h"
#include "RuntimeCDataManager.h"
#include "UserAccountItem.h"

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
		UIManager::GetInstance()->RegisterButton(2, m_SettingButton, this, &UUserAccountUI::OnButtonClick);
	}
	if (UButton * widget = (UButton*)GetWidgetFromName("ToUserInfoButton"))
	{
		m_ToUserInfoButton = widget;
		UIManager::GetInstance()->RegisterButton(3, m_ToUserInfoButton, this, &UUserAccountUI::OnButtonClick);
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
	if (UScrollBox * widget = (UScrollBox*)GetWidgetFromName("OrderListScroll"))
	{
		m_OrderListScroll = widget;
	}
	
}
void UUserAccountUI::On_Start()
{
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2010, this, &UUserAccountUI::OnGetAccountOrder);

	FString companyName = UserInfo::Get()->GetLocalData().companyName;
	FString userName = UserInfo::Get()->GetLocalData().renterName;
	FString userPhone = UserInfo::Get()->GetLocalData().phone;
	m_CompanyName->SetText(FText::FromString(companyName));
	m_UserName->SetText(FText::FromString(FString::Printf(TEXT("%s %s"),*userName,*userPhone)));
	
	EditerARGameModule::GetInstance()->GetAccountOrder();
}
void UUserAccountUI::On_Delete()
{
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 2010, this);
}
void UUserAccountUI::OnButtonClick(int _index)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIB::OnButtonClick : "));
	switch (_index)
	{
	case 1:
	{// remove
		RemoveFromParent();
	}break;
	case 2:
	{// setting
		//EditerARGameModule::GetInstance()->GetAccountOrder();
		UBaseUI * baseUI = UIManager::GetInstance()->OpenUI(TEXT("SettingUI"));
		baseUI->AddToViewport();
		RemoveFromParent();
	}break;
	case 3:
	{// to edit user info
		UBaseUI * baseUI = UIManager::GetInstance()->OpenUI(TEXT("EditUserInfoUI"));
		baseUI->AddToViewport();
		RemoveFromParent();
	}break;
	}
}
void UUserAccountUI::OnGetAccountOrder(msg_ptr _msg)
{
	m_OrderListScroll->ClearChildren();
	m_OrderListScroll->ScrollToStart();
	TArray<R_Order*> OrderList = RuntimeCDataManager::GetInstance()->GetAccountOrderList();

	for (int i = 0; i < OrderList.Num(); i++)
	{
		UUserAccountItem * item = (UUserAccountItem*)UIManager::GetInstance()->OpenUI(TEXT("UserAccountItem"),this);
		
		UScrollBoxSlot * slot = (UScrollBoxSlot*)m_OrderListScroll->AddChild(item);
		slot->SetPadding(FMargin(0.f,28.f,0.f,0.f));
		item->SetOrder(OrderList[i]);
	}
}