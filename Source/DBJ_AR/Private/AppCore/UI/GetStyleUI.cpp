#include "GetStyleUI.h"
#include "UIManager.h"
#include "OrderUserInfoUI.h"


void UGetStyleUI::On_Init()
{
    if (UButton * widget = (UButton*)GetWidgetFromName("BackButton"))
    {
        m_BackButton = widget;
		UIManager::GetInstance()->RegisterButton(1, m_BackButton, this, &UGetStyleUI::OnButtonClick);
    }
	if (UButton * widget = (UButton*)GetWidgetFromName("SonghuoButton"))
	{
		m_SongHuoButton = widget;
		UIManager::GetInstance()->RegisterButton(2, m_SongHuoButton, this, &UGetStyleUI::OnButtonClick);
	}
	if (UButton * widget = (UButton*)GetWidgetFromName("ZiquButton"))
	{
		m_ZiquButton = widget;
		UIManager::GetInstance()->RegisterButton(3, m_ZiquButton, this, &UGetStyleUI::OnButtonClick);
	}
	if (UCheckBox * widget = (UCheckBox*)GetWidgetFromName("CheckBox1"))
	{
		m_Box1 = widget;
	}
	if (UCheckBox * widget = (UCheckBox*)GetWidgetFromName("CheckBox2"))
	{
		m_Box2 = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("Text1"))
	{
		m_Text1 = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("Text2"))
	{
		m_Text2 = widget;
	}
}
void UGetStyleUI::On_Start()
{
	OnButtonClick(2);
}
void UGetStyleUI::OnButtonClick(int _index)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UGetStyleUI::OnButtonClick : "));
	switch (_index)
	{
	case 1:
	{
		UOrderUserInfoUI * parent = (UOrderUserInfoUI*)m_ParentUI;
		parent->SetGetStyle(m_String);
		RemoveFromParent();
	}break;
	case 2:
	{
		m_Box1->SetIsChecked(true);
		m_Box2->SetIsChecked(false);
		m_String = m_Text1->GetText().ToString();
		
	}break;
	case 3:
	{
		m_Box1->SetIsChecked(false);
		m_Box2->SetIsChecked(true);
		m_String = m_Text2->GetText().ToString();
	}break;
	default:
		break;
	}
}