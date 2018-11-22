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
	UToolScrollWidget * parentUI = (UToolScrollWidget*)m_ParentUI;
	parentUI->SelectButton(this);
}
void UToolButton::SetData(IdData _data)
{
	m_Data = _data;
	m_ButtonText->SetText(FText::FromString(m_Data.Name));
}
void UToolButton::SelectButton(bool _isSelect)
{
	if (_isSelect)
	{
		m_SelectBorder->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		m_SelectBorder->SetVisibility(ESlateVisibility::Hidden);
	}

}