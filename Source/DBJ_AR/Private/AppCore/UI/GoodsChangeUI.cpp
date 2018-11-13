#include "GoodsChangeUI.h"


void UGoodsChangeUI::On_Init()
{
    if (UButton * button = (UButton*)GetWidgetFromName("ViewButton"))
    {
        m_ViewButton = button;
        m_ViewButton->OnClicked.AddDynamic(this, &UGoodsChangeUI::OnButtonClick);
    }
	if (UScrollBox * widget = (UScrollBox*)GetWidgetFromName("UScrollBox"))
	{
		m_ScrollBox = widget;
	}
	if (UGridPanel * widget = (UGridPanel*)GetWidgetFromName("ChangeGridPanel"))
	{
		m_GridPanel = widget;
	}
    
}
void UGoodsChangeUI::OnButtonClick()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIB::OnButtonClick : "));

}
