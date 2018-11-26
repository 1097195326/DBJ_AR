#include "OrderInfoUI.h"
#include "UIManager.h"
#include "FileDownloadManager.h"
#include "MakeOrderUI.h"



void UOrderInfoUI::On_Init()
{
	if (UNativeWidgetHost * widget = (UNativeWidgetHost*)GetWidgetFromName("IconHost"))
	{
		m_Icon = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("GoodsName"))
	{
		m_GoodsName = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("GoodsBorder"))
	{
		m_GoodsBorder = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("CompanyName"))
	{
		m_CompanyName = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("GoodsPrice"))
	{
		m_GoodsPrice = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("GoodsNum"))
	{
		m_GoodsNum = widget;
	}
    if (UButton * widget = (UButton*)GetWidgetFromName("SubstractButton"))
    {
        m_SubButton = widget;
		UIManager::GetInstance()->RegisterButton(1, m_SubButton, this, &UOrderInfoUI::OnButtonClick);
    }
	if (UButton * widget = (UButton*)GetWidgetFromName("AddButton"))
	{
		m_AddButton = widget;
		UIManager::GetInstance()->RegisterButton(2, m_AddButton, this, &UOrderInfoUI::OnButtonClick);
	}
    
}
void UOrderInfoUI::On_Delete()
{
	UIManager::GetInstance()->UnRegisterButton(m_SubButton);
	UIManager::GetInstance()->UnRegisterButton(m_AddButton);
}
void UOrderInfoUI::OnButtonClick(int _index)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIB::OnButtonClick : "));
	UMakeOrderUI * parentUI = (UMakeOrderUI*)m_ParentUI;
	int OldNum = m_Num;
	switch (_index)
	{
	case 1:
	{
		--m_Num;
		if (m_Num <= 0)
		{
			m_Num = 0;
		}
	}break;
	case 2:
	{
		++m_Num;
	}break;
	}
	int price = m_Data->salePrice * (m_Num - OldNum);

	UE_LOG(LogTemp, Log, TEXT("zhx : order info ui price : %d"), price);
	parentUI->SetPrice(price);
	ResetNum();
}
void UOrderInfoUI::ResetNum()
{
	FString num = FString::Printf(TEXT("%d"), m_Num);
	m_GoodsNum->SetText(FText::FromString(num));
}
void UOrderInfoUI::SetData(GoodsData * _data)
{
	m_Data = _data;
	m_Num = m_Data->quantity;

	m_Icon->SetContent(SNew(SImage).Image(UFileDownloadManager::Get()->m_ImageCache.Download(*m_Data->thumbnailUrl)->Attr()));
	m_GoodsName->SetText(FText::FromString(m_Data->name));
	FString borderSting = FString::Printf(TEXT("%d*%d*%d mm"), m_Data->externalHeight, m_Data->externalLength, m_Data->externalHeight);
	m_GoodsBorder->SetText(FText::FromString(borderSting));
	m_CompanyName->SetText(FText::FromString(m_Data->supplyName));
	FString price = FString::Printf(TEXT("%d"), m_Data->salePrice);
	m_GoodsPrice->SetText(FText::FromString(price));
	
	ResetNum();
}
GoodsData *  UOrderInfoUI::GetData()
{
	m_Data->quantity = m_Num;
	return m_Data;
}
