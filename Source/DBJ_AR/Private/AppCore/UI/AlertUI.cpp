#include "AlertUI.h"

void UAlertUI::On_Init()
{
    if (UButton * widget = (UButton*)GetWidgetFromName("ViewButton"))
    {
        m_ViewButton = widget;
        m_ViewButton->OnClicked.AddDynamic(this, &UAlertUI::OnButtonClick);
    }
    
    
}
void UAlertUI::OnButtonClick()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIB::OnButtonClick : "));

}
