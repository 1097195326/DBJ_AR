#include "EditStringUI.h"


void UEditStringUI::On_Init()
{
    if (UButton * widget = (UButton*)GetWidgetFromName("ViewButton"))
    {
        m_ViewButton = widget;
        m_ViewButton->OnClicked.AddDynamic(this, &UEditStringUI::OnButtonClick);
    }
    
    
}
void UEditStringUI::OnButtonClick()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIB::OnButtonClick : "));

}
