#include "GoodsList_Icon.h"



void UGoodsList_Icon::On_Init()
{
    if (UButton * button = (UButton*)GetWidgetFromName("ViewButton"))
    {
        m_ViewButton = button;
        m_ViewButton->OnClicked.AddDynamic(this, &UGoodsList_Icon::OnButtonClick);
    }
    
    
}
void UGoodsList_Icon::OnButtonClick()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIB::OnButtonClick : "));

}
