#include "GoodsFilterItem.h"
#include "GoodsFilterUI.h"
#include "UIManager.h"

void UGoodsFilterItem::On_Init()
{
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("TitleName"))
	{
		m_TitleName = widget;
	}
	if (UGridPanel * widget = (UGridPanel*)GetWidgetFromName("ContentGridPanel"))
	{
		m_ContentGridPanel = widget;
	}

	m_SelectButton = nullptr;
}

void UGoodsFilterItem::SetData(const int & _type, const TArray<IdData> & _data,int _index)
{
	m_type = _type;
	m_Data = _data;
	m_SelectIndex = _index;
	
	switch (m_type)
	{
	case 1:
	{
		m_TitleName->SetText(FText::FromString(TEXT("类型")));
	}break;
	case 2:
	{
		m_TitleName->SetText(FText::FromString(TEXT("材质")));
	}break;
	case 3:
	{
		m_TitleName->SetText(FText::FromString(TEXT("尺寸")));
	}break;
	default:
		break;
	}

	for (int i = 0; i< m_Data.Num(); i++)
	{
		UToolButton * button = (UToolButton*)UIManager::GetInstance()->OpenUI(TEXT("GoodsFilterButton"),this);
		UGridSlot * slot = m_ContentGridPanel->AddChildToGrid(button);
		//button->SetShowBorder(true);
		button->SetData(m_Data[i],this);
		slot->SetColumn(i % 3);
		slot->SetRow(i / 3);
		slot->SetPadding(FMargin(0.f, 0.f, 40.f, 40.f));
		m_Buttons.Add(button);
	}
	SelectButton(m_SelectIndex);

}
void UGoodsFilterItem::SelectButton(UToolButton * _button)
{
	if (m_SelectButton && m_SelectButton == _button)
	{
		m_SelectButton->SelectButton(false);
		m_SelectButton = nullptr;
		m_SelectIndex = 0;
		return;
	}
	for (UToolButton * button : m_Buttons)
	{
		if (button == _button)
		{
			button->SelectButton(true);
			m_SelectButton = button;
			m_SelectIndex = button->m_Data.Id;
			UGoodsFilterUI * parentUI = (UGoodsFilterUI*)m_ParentUI;
			switch (m_type)
			{
			case 1:
			{
				parentUI->m_TypeIndex = m_SelectIndex;
			}break;
			case 2:
			{
				parentUI->m_MaterialIndex = m_SelectIndex;
			}break;
			case 3:
			{
				parentUI->m_InnerIndex = m_SelectIndex;
			}break;
			default:
				break;
			}
		}
		else
		{
			button->SelectButton(false);
		}
	}
}
void UGoodsFilterItem::SelectButton(int _index)
{
	for (UToolButton * button : m_Buttons)
	{
		if (_index == button->m_Data.Id)
		{
			button->SelectButton(true);
			m_SelectButton = button;
		}
		else
		{
			button->SelectButton(false);
		}
	}
}