#include "UserAccountItem.h"
#include "MakeOrderUI.h"
#include "UIManager.h"
#include "UserAccountItemIcon.h"

void UUserAccountItem::On_Init()
{
    if (UButton * widget = (UButton*)GetWidgetFromName("EditerOrderButton"))
    {
		m_EditerOrderButton = widget;
		m_EditerOrderButton->OnClicked.AddDynamic(this, &UUserAccountItem::OnButtonClick);
    }
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("CompanyName"))
	{
		m_CompanyName = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("StatusText"))
	{
		m_StatusText = widget;
	}
	if (UScrollBox * widget = (UScrollBox*)GetWidgetFromName("IconListScroll"))
	{
		m_IconListScroll = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("CommitTime"))
	{
		m_CommitTime = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("AllPrice"))
	{
		m_AllPrice = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("AllNum"))
	{
		m_AllNum = widget;
	}
	if (UImage * widget = (UImage*)GetWidgetFromName("WeiTijiaoImage"))
	{
		m_WeiTijiaoImage = widget;
	}
	if (UImage * widget = (UImage*)GetWidgetFromName("YiTijiaoImage"))
	{
		m_YiTijiaoImage = widget;
	}
    
}
void UUserAccountItem::OnButtonClick()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIB::OnButtonClick : "));
	RuntimeRDataManager::GetInstance()->EditOrder(m_Order);
	m_ParentUI->RemoveFromParent();
	UMakeOrderUI * baseUI = (UMakeOrderUI*)UIManager::GetInstance()->OpenUI(TEXT("MakeOrderUI"));
	baseUI->AddToViewport();
}
void UUserAccountItem::SetOrder(R_Order * order)
{
	m_Order = order;
	ReView();
}
void UUserAccountItem::ReView()
{
	FString price = FString::Printf(TEXT("合计: ￥%d"), m_Order->totalPrice);
	FString quantity = FString::Printf(TEXT("共%d件商品"), m_Order->totalQuantity);
	m_CompanyName->SetText(FText::FromString(m_Order->CommitTime));
	m_AllPrice->SetText(FText::FromString(price));
	m_AllNum->SetText(FText::FromString(quantity));
	m_CommitTime->SetText(FText::FromString(m_Order->CommitTime));
	if (m_Order->Status == 1)
	{
		m_WeiTijiaoImage->SetVisibility(ESlateVisibility::Visible);
		m_YiTijiaoImage->SetVisibility(ESlateVisibility::Hidden);
		m_StatusText->SetText(FText::FromString(TEXT("未提交")));
	}
	else
	{
		m_WeiTijiaoImage->SetVisibility(ESlateVisibility::Hidden);
		m_YiTijiaoImage->SetVisibility(ESlateVisibility::Visible);
		m_StatusText->SetText(FText::FromString(TEXT("已提交")));
	}

	for (int i = 0; i < m_Order->ProductList.Num(); i++)
	{
		GoodsData * goodsData = m_Order->ProductList[i];
		UUserAccountItemIcon * icon = (UUserAccountItemIcon*)UIManager::GetInstance()->OpenUI(TEXT("UserAccountItemIcon"));
		UScrollBoxSlot * slot = (UScrollBoxSlot*)m_IconListScroll->AddChild(icon);
		icon->SetImageUrl(goodsData->thumbnailUrl);
		if (i == 0)
		{
			slot->SetPadding(FMargin(40.f,0.f,0.f,0.f));
		}
		else
		{
			slot->SetPadding(FMargin(16.f, 0.f, 0.f, 0.f));
		}
	}

}