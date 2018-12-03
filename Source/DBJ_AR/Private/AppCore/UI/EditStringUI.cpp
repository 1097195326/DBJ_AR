#include "EditStringUI.h"
#include "UIManager.h"

void UEditStringUI::On_Init()
{
    if (UButton * widget = (UButton*)GetWidgetFromName("CancelButton"))
    {
        m_CancelButton = widget;
		UIManager::GetInstance()->RegisterButton(1, m_CancelButton, this, &UEditStringUI::OnButtonClick);
    }
	if (UButton * widget = (UButton*)GetWidgetFromName("SureButton"))
	{
		m_SureButton = widget;
		UIManager::GetInstance()->RegisterButton(2, m_SureButton, this, &UEditStringUI::OnButtonClick);
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("TitleName"))
	{
		m_TitleName = widget;
	}
	if (UEditableText * widget = (UEditableText*)GetWidgetFromName("EditString"))
	{
		m_EditString = widget;
	}
    
}
void UEditStringUI::On_Start()
{
	m_TitleName->SetText(FText::FromString(m_TitleNameS));
	m_EditString->SetHintText(FText::FromString(m_EditHintS));
}
void UEditStringUI::On_Delete()
{
	UIManager::GetInstance()->UnRegisterButton(m_CancelButton);
	UIManager::GetInstance()->UnRegisterButton(m_SureButton);
}
void UEditStringUI::OnButtonClick(int _index)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIB::OnButtonClick : "));
	switch (_index)
	{
	case 1:
	{
		RemoveFromParent();
	}break;
	case 2:
	{
		m_Delegate->EditString(m_EditString->GetText().ToString());
		RemoveFromParent();
	}break;
	default:
		break;
	}
}
void UEditStringUI::SetDelegate(EditStringDelegate * _delegate, FString _titleName, FString _hintS)
{
	m_Delegate = _delegate;
	m_TitleNameS = _titleName;
	m_EditHintS = _hintS;
}