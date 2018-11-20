#include "ToolButton.h"



void UToolButton::On_Init()
{
    if (UButton * button = (UButton*)GetWidgetFromName("ViewButton"))
    {
        m_ViewButton = button;
        m_ViewButton->OnClicked.AddDynamic(this, &UToolButton::OnButtonClick);
    }
    
    
}
void UToolButton::OnButtonClick()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIB::OnButtonClick : "));

}
void UToolButton::SetData(IdData _data)
{
	m_Data = _data;
}
