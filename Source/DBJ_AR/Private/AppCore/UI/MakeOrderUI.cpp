#include "MakeOrderUI.h"
#include "UIManager.h"
#include "RuntimeRDataManager.h"
#include "UserInfo.h"
#include "OrderUserInfoUI.h"

void UMakeOrderUI::On_Init()
{
	if (UButton * widget = (UButton*)GetWidgetFromName("BackButton"))
	{
		m_BackButton = widget;
		UIManager::GetInstance()->RegisterButton(1, m_BackButton, this, &UMakeOrderUI::OnButtonClick);
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
		UIManager::GetInstance()->RegisterButton(2, m_ToOrderInfoButton, this, &UMakeOrderUI::OnButtonClick);
	}
	//main view
	if (UScrollBox * widget = (UScrollBox*)GetWidgetFromName("OrderScroll"))
	{
		m_OrderScroll = widget;
	}
	if (UGridPanel * widget = (UGridPanel*)GetWidgetFromName("OrderGridePanel"))
	{
		m_OrderGirdePanel = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("OrederPrice"))
	{
		m_Allprice = widget;
	}
	if (UButton * widget = (UButton*)GetWidgetFromName("SaveOrderButton"))
	{
		m_SaveOrderButton = widget;
		UIManager::GetInstance()->RegisterButton(3, m_SaveOrderButton, this, &UMakeOrderUI::OnButtonClick);
	}
	if (UButton * widget = (UButton*)GetWidgetFromName("CommitButton"))
	{
		m_CommitOrderButton = widget;
		UIManager::GetInstance()->RegisterButton(4, m_CommitOrderButton, this, &UMakeOrderUI::OnButtonClick);
	}

}
void UMakeOrderUI::On_Start()
{
	//UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(UGameplayStatics::GetPlayerController(this, 0), this);

	InitView();
}
void UMakeOrderUI::InitView()
{
	FSaveUserData userData = UserInfo::Get()->GetLocalData();
	m_CompanyName->SetText(FText::FromString(userData.companyName));
	FString userInfoS = FString::Printf(TEXT("%s %s"),*userData.renterName,*userData.phone);
	m_UserInfo->SetText(FText::FromString(userInfoS));
	FString userAddress = FString::Printf(TEXT("%s%s"), *userData.address, *userData.detailAddress);
	m_AddressInfo->SetText(FText::FromString(userData.address));

	TMap<int,OrderInfoData> datas = RuntimeRDataManager::GetInstance()->GetOrderDatas();
	int index = 0;
	for (auto & item : datas)
	{
		OrderInfoData data = item.Value;
		UOrderInfoUI * icon = (UOrderInfoUI*)UIManager::GetInstance()->OpenUI(TEXT("OrderInfoUI"),this);

		if (icon->IsValidLowLevel())
		{
			UGridSlot * mGridSlot = m_OrderGirdePanel->AddChildToGrid(icon);
			mGridSlot->SetRow(index);
			icon->SetData(data);
			mGridSlot->SetPadding(FMargin(0.f, 24.0f, 0.f, 0.f));
			allPriceI += data.Num * data.goodsData->salePrice;
			++index;
		}
	}
	SetPrice(0);
}
void UMakeOrderUI::SetPrice(int num)
{
	allPriceI += num;
	UE_LOG(LogTemp, Log, TEXT("zhx  make order ui : %d,%d"), allPriceI, num);
	FString priceStr = FString::Printf(TEXT("%d"), allPriceI);
	m_Allprice->SetText(FText::FromString(priceStr));
}
void UMakeOrderUI::On_Delete()
{
	UIManager::GetInstance()->UnRegisterButton(m_BackButton);
	UIManager::GetInstance()->UnRegisterButton(m_ToOrderInfoButton);
	UIManager::GetInstance()->UnRegisterButton(m_SaveOrderButton);
	UIManager::GetInstance()->UnRegisterButton(m_CommitOrderButton);

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
		UOrderUserInfoUI * userInfoUI = (UOrderUserInfoUI*)UIManager::GetInstance()->OpenUI(TEXT("OrderUserInfoUI"));
		userInfoUI->AddToViewport();
	}break;
	case 3:
	{// save order button

	}break;
	case 4:
	{// commit order button

	}break;
	default:
		break;
	}
	
}
