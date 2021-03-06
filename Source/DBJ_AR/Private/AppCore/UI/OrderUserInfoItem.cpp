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
	if (UEditableText * widget = (UEditableText*)GetWidgetFromName("EditerItem"))
	{
		m_EditText = widget;
	}
	if (UImage * widget = (UImage*)GetWidgetFromName("ShowGoImage"))
	{
		m_ShowGoImage = widget;
	}
	if (UBorder * widget = (UBorder*)GetWidgetFromName("BottomBorder"))
	{
		m_BottomBorder = widget;
	}
}
void UOrderUserInfoItem::On_Start()
{
	m_ItemName->SetText(FText::FromString(m_ItemNameS));
	m_EditText->SetHintText(FText::FromString(m_ItemContentS));

	if (m_IsEdit)
	{
		m_DoSomethingButton->SetVisibility(ESlateVisibility::Hidden);
		m_ShowGoImage->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		m_EditText->SetIsReadOnly(true);
		m_DoSomethingButton->SetVisibility(ESlateVisibility::Visible);
		m_ShowGoImage->SetVisibility(ESlateVisibility::Visible);
	}
	if (m_ShowBorder)
	{
		m_BottomBorder->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		m_BottomBorder->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UOrderUserInfoItem::On_Delete()
{

}
void UOrderUserInfoItem::SetOnlyShow()
{
    if (true)
    {
        m_EditText->SetVisibility(ESlateVisibility::Visible);
		m_EditText->SetIsReadOnly(true);
        m_DoSomethingButton->SetVisibility(ESlateVisibility::Hidden);
        m_ShowGoImage->SetVisibility(ESlateVisibility::Hidden);
    }
}
