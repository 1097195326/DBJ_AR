#include "TestUIA.h"


void UTestUIA::On_Init()
{
    if(UButton * button = (UButton*)GetWidgetFromName("ViewButton"))
    {
        m_ViewButton = button;
        m_ViewButton->OnClicked.AddDynamic(this, &UTestUIA::OnButtonClick);
    }
    
    
    
}
void UTestUIA::OnButtonClick()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIA::OnButtonClick : "));

}
