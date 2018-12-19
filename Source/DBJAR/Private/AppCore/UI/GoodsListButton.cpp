#include "GoodsListButton.h"
#include "GoodsList.h"
#include "UIManager.h"


void UGoodsListButton::On_Init()
{
    if (UButton * button = (UButton*)GetWidgetFromName("SelectButton"))
    {
        m_ViewButton = button;
		UIManager::GetInstance()->RegisterButton(1, m_ViewButton, this, &UGoodsListButton::OnButtonClick);
    }
	if (UTextBlock * text = (UTextBlock*)GetWidgetFromName("ButtonText"))
	{
		m_Text = text;
	}
	if (UBorder * widget = (UBorder*)GetWidgetFromName("SelectBorder"))
	{
		m_Border = widget;
	}
    
}
void UGoodsListButton::On_Delete()
{
	UIManager::GetInstance()->UnRegisterButton(m_ViewButton);

}
void UGoodsListButton::OnButtonClick(int index)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIB::OnButtonClick : "));
	UGoodsList * parent = (UGoodsList*)m_Parent;
	parent->SelectCategoryButton(m_Id);
}
void UGoodsListButton::SetData(int _id, FString _name, UBaseUI * _parent)
{
	m_Id = _id;
	m_Name = _name;
	m_Parent = _parent;
	m_Text->SetText(FText::FromString(m_Name));

}
void UGoodsListButton::SetButtonSelect(bool _select)
{
	if (_select)
	{
		m_Text->SetColorAndOpacity(FLinearColor(FColor::FromHex(TEXT("29CF81"))));
		m_Border->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		m_Text->SetColorAndOpacity(FLinearColor(FColor::FromHex(TEXT("666666"))));
		m_Border->SetVisibility(ESlateVisibility::Hidden);
	}
}
