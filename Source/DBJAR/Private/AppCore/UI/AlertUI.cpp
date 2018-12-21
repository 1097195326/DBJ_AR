#include "AlertUI.h"
#include "UIManager.h"


void UAlertUI::On_Init()
{
    if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("ContentText"))
    {
        m_ContentText = widget;
    }
	if (UButton * widget = (UButton*)GetWidgetFromName("CancelButton"))
	{
		m_CancelButton = widget;
		UIManager::GetInstance()->RegisterButton(1, m_CancelButton, this, &UAlertUI::OnButtonClick);
	}
	if (UButton * widget = (UButton*)GetWidgetFromName("SureButton"))
	{
		m_SureButton = widget;
		UIManager::GetInstance()->RegisterButton(2, m_SureButton, this, &UAlertUI::OnButtonClick);
	}
	if (UButton * widget = (UButton*)GetWidgetFromName("OnlySureButton"))
	{
		m_OnlySureButton = widget;
		UIManager::GetInstance()->RegisterButton(3, m_OnlySureButton, this, &UAlertUI::OnButtonClick);
	}
	if (UCanvasPanel * widget = (UCanvasPanel*)GetWidgetFromName("OnlyPanel"))
	{
		m_OnlyPanel = widget;
		m_OnlyPanel->SetVisibility(ESlateVisibility::Hidden);
	}
	if (UCanvasPanel * widget = (UCanvasPanel*)GetWidgetFromName("ShowPanel"))
	{
		m_ShowPanel = widget;
	}
    
	CancelFunctionDelegate = nullptr;
	SureFunctionDelegate = nullptr;
	OnlySureFunctionDelegate = nullptr;
}
void UAlertUI::On_Delete()
{
	if (m_CancelButton)
	{
		UIManager::GetInstance()->UnRegisterButton(m_CancelButton);
	}
	if (m_SureButton)
	{
		UIManager::GetInstance()->UnRegisterButton(m_SureButton);
	}
	if (m_OnlySureButton)
	{
		UIManager::GetInstance()->UnRegisterButton(m_OnlySureButton);
	}

	CancelFunctionDelegate = nullptr;
	SureFunctionDelegate = nullptr;
	OnlySureFunctionDelegate = nullptr;
}
void UAlertUI::OnlyButtonShow(bool _show)
{
	if (_show)
	{
		if (m_OnlyPanel)
		{
			m_OnlyPanel->SetVisibility(ESlateVisibility::Visible);
		}
		if (m_ShowPanel)
		{
			m_ShowPanel->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	else
	{
		if (m_OnlyPanel)
		{
			m_OnlyPanel->SetVisibility(ESlateVisibility::Hidden);
		}
		if (m_ShowPanel)
		{
			m_ShowPanel->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
void UAlertUI::SetContentText(const FString & _content)
{
	FString Content = _content;
	int index = Content.Len() / 16;
	for (int i = index; i > 0; i--)
	{
		Content.InsertAt(16 * i, TEXT("\n"));
	}
	if (m_ContentText)
	{
		m_ContentText->SetText(FText::FromString(Content));
	}
}
void UAlertUI::OnButtonClick(int _index)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UAlertUI::OnButtonClick : "));
	switch (_index)
	{
	case 1:
	{
		if (CancelFunctionDelegate)
		{
			CancelFunctionDelegate();
		}
	}break;
	case 2:
	{
		if (SureFunctionDelegate)
		{
			SureFunctionDelegate();
		}
	}break;
	case 3:
	{
		if (OnlySureFunctionDelegate)
		{
			OnlySureFunctionDelegate();
		}
	}break;
	default:
		break;
	}

	RemoveFromParent();
}
