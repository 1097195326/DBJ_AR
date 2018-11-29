#include "MakeOrderUI.h"
#include "UIManager.h"
#include "RuntimeRDataManager.h"
#include "UserInfo.h"
#include "OrderUserInfoUI.h"
#include "EditerARGameModule.h"

void UMakeOrderUI::On_Init()
{
	if (UButton * widget = (UButton*)GetWidgetFromName("BackButton"))
	{
		m_BackButton = widget;
		
	}
	// user info
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("CompanyName"))
	{
		m_CompanyName = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("UserInfo"))
	{
		m_UserInfo = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("AdressInfo"))
	{
		m_AddressInfo = widget;
	}
	if (UButton * widget = (UButton*)GetWidgetFromName("ToOrderInfoButton"))
	{
		m_ToOrderInfoButton = widget;
		
	}
	//main view
	if (UScrollBox * widget = (UScrollBox*)GetWidgetFromName("OrderScroll"))
	{
		m_OrderScroll = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("OrederPrice"))
	{
		m_Allprice = widget;
	}
	if (UCanvasPanel * widget = (UCanvasPanel*)GetWidgetFromName("SaveOrderPanel"))
	{
		m_SaveOrderPanel = widget;
	}
	if (UButton * widget = (UButton*)GetWidgetFromName("SaveOrderButton"))
	{
		m_SaveOrderButton = widget;
		
	}
	if (UButton * widget = (UButton*)GetWidgetFromName("CommitButton"))
	{
		m_CommitOrderButton = widget;
		
	}
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2009, this, &UMakeOrderUI::OnCommitCurrentOrder);
}
void UMakeOrderUI::On_Start()
{
	//UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(UGameplayStatics::GetPlayerController(this, 0), this);
    UIManager::GetInstance()->RegisterButton(1, m_BackButton, this, &UMakeOrderUI::OnButtonClick);
    UIManager::GetInstance()->RegisterButton(2, m_ToOrderInfoButton, this, &UMakeOrderUI::OnButtonClick);
    UIManager::GetInstance()->RegisterButton(3, m_SaveOrderButton, this, &UMakeOrderUI::OnButtonClick);
    UIManager::GetInstance()->RegisterButton(4, m_CommitOrderButton, this, &UMakeOrderUI::OnButtonClick);
    
	InitView();
}
void UMakeOrderUI::On_Delete()
{
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 2009, this);

	UIManager::GetInstance()->UnRegisterButton(m_BackButton);
	UIManager::GetInstance()->UnRegisterButton(m_ToOrderInfoButton);
	UIManager::GetInstance()->UnRegisterButton(m_SaveOrderButton);
	UIManager::GetInstance()->UnRegisterButton(m_CommitOrderButton);

	RuntimeRDataManager::GetInstance()->ClearOrder();

}
void UMakeOrderUI::InitView()
{
	ReView();
	R_Order * order = RuntimeRDataManager::GetInstance()->GetCurrentOrder();
	if (order->Status == 1)
	{
		m_SaveOrderPanel->SetVisibility(ESlateVisibility::Hidden);
		m_SaveOrderButton->SetVisibility(ESlateVisibility::Hidden);
	}else if (order->Status == 2)
	{
		m_SaveOrderPanel->SetVisibility(ESlateVisibility::Hidden);
		m_SaveOrderButton->SetVisibility(ESlateVisibility::Hidden);
		m_CommitOrderButton->SetIsEnabled(false);
	}
	TMap<int,GoodsData*> datas = RuntimeRDataManager::GetInstance()->GetOrderDatas();
	
	for (auto & item : datas)
	{
		GoodsData * data = item.Value;
		UOrderInfoUI * icon = (UOrderInfoUI*)UIManager::GetInstance()->OpenUI(TEXT("OrderInfoUI"),this);

		if (icon->IsValidLowLevel())
		{
			UScrollBoxSlot * scrollSlot = (UScrollBoxSlot*)m_OrderScroll->AddChild(icon);
			icon->SetData(data);
			scrollSlot->SetPadding(FMargin(48.f, 0.0f, 48.f, 24.f));
			allPriceI += data->quantity * data->salePrice;
			m_InfoUIList.Add(icon);
		}
	}
	SetPrice(0);
}
void UMakeOrderUI::ReView()
{
	R_Order * order = RuntimeRDataManager::GetInstance()->GetCurrentOrder();

	m_CompanyName->SetText(FText::FromString(order->ReceiverCompanyName));
	FString userInfoS = FString::Printf(TEXT("%s %s"), *order->ReceiverName, *order->ReceiverPhone);
	m_UserInfo->SetText(FText::FromString(userInfoS));
	m_AddressInfo->SetText(FText::FromString(order->Address));
}
void UMakeOrderUI::SetPrice(int num)
{
	allPriceI += num;
	UE_LOG(LogTemp, Log, TEXT("zhx  make order ui : %d,%d"), allPriceI, num);
	FString priceStr = FString::Printf(TEXT("￥%d"), allPriceI);
	m_Allprice->SetText(FText::FromString(priceStr));
}

void UMakeOrderUI::OnButtonClick(int _index)
{
	UE_LOG(LogTemp, Log, TEXT("zhx : UMakeOrderUI::OnButtonClick : "));
	switch (_index)
	{
	case 1:
	{//back button
		RemoveFromParent();
	}break;
	case 2:
	{// to order info button
		UOrderUserInfoUI * userInfoUI = (UOrderUserInfoUI*)UIManager::GetInstance()->OpenUI(TEXT("OrderUserInfoUI"),this);
		userInfoUI->AddToViewport();
	}break;
	case 3:
	{// save order button
		R_Order * order = RuntimeRDataManager::GetInstance()->GetCurrentOrder();
		order->Status = 1;
		for (int i = 0;i<m_InfoUIList.Num();i++)
		{
			order->ProductList.Add(m_InfoUIList[i]->GetData());
		}
		EditerARGameModule::GetInstance()->CommitCurrentOrder();
		
	}break;
	case 4:
	{// commit order button
		R_Order * order = RuntimeRDataManager::GetInstance()->GetCurrentOrder();
		order->Status = 2;
		for (int i = 0;i < m_InfoUIList.Num(); i++)
		{
			if (RuntimeRDataManager::GetInstance()->IsEditOrder())
			{
				m_InfoUIList[i]->GetData();
			}
			else
			{
				order->ProductList.Add(m_InfoUIList[i]->GetData());
			}
		}
		EditerARGameModule::GetInstance()->CommitCurrentOrder();
		
	}break;
	default:
		break;
	}
	
}
void UMakeOrderUI::OnCommitCurrentOrder(msg_ptr _msg)
{
	RemoveFromParent();
	UBaseUI * baseUI = UIManager::GetInstance()->OpenUI(TEXT("UserAccountUI"));
	baseUI->AddToViewport();
}
