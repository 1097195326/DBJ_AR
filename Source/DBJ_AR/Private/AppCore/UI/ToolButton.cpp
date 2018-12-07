#include "ToolButton.h"
#include "ToolScrollWidget.h"


void UToolButton::On_Init()
{
    if (UButton * widget = (UButton*)GetWidgetFromName("Button1"))
    {
        m_ViewButton = widget;
        m_ViewButton->OnClicked.AddDynamic(this, &UToolButton::OnButtonClick);
    }
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("ButtonText"))
	{
		m_ButtonText = widget;
	}
	if (UBorder * widget = (UBorder*)GetWidgetFromName("SelectBorder"))
	{
		m_SelectBorder = widget;
		m_SelectBorder->SetVisibility(ESlateVisibility::Hidden);
	}

}
void UToolButton::OnButtonClick()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UToolButton::OnButtonClick : "));
	m_Delegate->SelectButton(this);
}
void UToolButton::SetData(const IdData & _data, SelectButtonDelegate * _delegate)
{
	m_Data = _data;
	m_Delegate = _delegate;

	m_ButtonText->SetText(FText::FromString(m_Data.Name));
}
void UToolButton::SelectButton(bool _isSelect)
{
	if (_isSelect)
	{
		m_ButtonText->SetColorAndOpacity(FLinearColor(FColor::FromHex(TEXT("333333"))));
		if (m_IsShowBorder)
		{
			m_SelectBorder->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		m_ButtonText->SetColorAndOpacity(FLinearColor(FColor::FromHex(TEXT("999999"))));
		if (m_IsShowBorder)
		{
			m_SelectBorder->SetVisibility(ESlateVisibility::Hidden);
		}
	}

}
void UToolButton::SetShowBorder(bool _show)
{
	m_IsShowBorder = _show;
}