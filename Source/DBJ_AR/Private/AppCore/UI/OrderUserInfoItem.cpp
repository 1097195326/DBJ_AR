#include "OrderUserInfoItem.h"



void UOrderUserInfoItem::On_Init()
{
    if (UButton * button = (UButton*)GetWidgetFromName("DoSomethingButton"))
    {
		m_DoSomethingButton = button;
    }
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("ItemName"))
	{
		m_ItemName = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("ItemContent"))
	{
		m_ItemContent = widget;
	}
	if (UEditableText * widget = (UEditableText*)GetWidgetFromName("EditerItem"))
	{
		m_EditText = widget;
	}
    
}
void UOrderUserInfoItem::On_Start()
{
	m_ItemName->SetText(FText::FromString(m_ItemNameS));
	if (m_IsEdit)
	{
		m_EditText->SetHintText(FText::FromString(TEXT("SDFADF")));
		m_EditText->SetVisibility(ESlateVisibility::Visible);
		m_ItemContent->SetVisibility(ESlateVisibility::Hidden);
		m_DoSomethingButton->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		m_EditText->SetVisibility(ESlateVisibility::Hidden);
		m_ItemContent->SetVisibility(ESlateVisibility::Visible);
		m_DoSomethingButton->SetVisibility(ESlateVisibility::Visible);
	}
}
void UOrderUserInfoItem::On_Delete()
{

}