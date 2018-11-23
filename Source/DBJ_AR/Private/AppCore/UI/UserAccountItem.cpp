#include "UserAccountItem.h"



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
    
}
void UUserAccountItem::OnButtonClick()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIB::OnButtonClick : "));

}
