#include "GoodsChangeIcon.h"


void UGoodsChangeIcon::On_Init()
{
    if (UButton * button = (UButton*)GetWidgetFromName("ViewButton"))
    {
        m_ViewButton = button;
        m_ViewButton->OnClicked.AddDynamic(this, &UGoodsChangeIcon::OnButtonClick);
    }
    
    
}
void UGoodsChangeIcon::OnButtonClick()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIB::OnButtonClick : "));

}
