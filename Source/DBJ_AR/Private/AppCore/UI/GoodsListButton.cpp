#include "GoodsListButton.h"
#include "GoodsList.h"

void UGoodsListButton::On_Init()
{
    if (UButton * button = (UButton*)GetWidgetFromName("SelectButton"))
    {
        m_ViewButton = button;
        m_ViewButton->OnClicked.AddDynamic(this, &UGoodsListButton::OnButtonClick);
    }
	if (UTextBlock * text = (UTextBlock*)GetWidgetFromName("ButtonText"))
	{
		m_Text = text;
	}
    
}
void UGoodsListButton::OnButtonClick()
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
		m_Text->SetColorAndOpacity(FLinearColor(FColor::FromHex(TEXT("65FF83FF"))));
	}
	else
	{
		m_Text->SetColorAndOpacity(FLinearColor(FColor::FromHex(TEXT("000000FF"))));
	}
}