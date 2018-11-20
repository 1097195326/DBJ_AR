#include "ToolScrollWidget.h"
#include "UIManager.h"
#include "AddressAndTimeTool.h"


void UToolScrollWidget::On_Init()
{
    if (UButton * widget = (UButton*)GetWidgetFromName("ViewButton"))
    {
        m_ViewButton = widget;
        m_ViewButton->OnClicked.AddDynamic(this, &UToolScrollWidget::OnButtonClick);
    }
	if (UScrollBox * widget = (UScrollBox*)GetWidgetFromName("ViewButton"))
	{
		m_ScorllBox = widget;
	}
    
}
void UToolScrollWidget::OnButtonClick()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIB::OnButtonClick : "));

}
void UToolScrollWidget::SetType(ToolScrollType _type)
{
	m_Type = _type;
}
void UToolScrollWidget::SetParentId(int _id)
{
	m_ParentId = _id;
	UAddressAndTimeTool * parentUI = nullptr;
	switch (m_Type)
	{
	case t_Month:
	{
		bool isFirst = true;
		for (int i = 1; i<= 12;i++)
		{
			if (FDateTime::Validate(m_ParentId,i,1,0,0,0,0))
			{
				IdData data;
				data.Id = i;
				data.Name = FString::Printf(TEXT("%d"), i);
				if (isFirst)
				{
					isFirst = false;
					parentUI = (UAddressAndTimeTool*)m_ParentUI;
					parentUI->m_LevelMap[m_Type] = data.Id;
					m_NextNode->SetParentId(data.Id);
				}
				UToolButton * button = (UToolButton*)UIManager::GetInstance()->OpenUI(TEXT("ToolButton"));
				button->SetData(data);
				m_Buttons.Add(button);
				m_ScorllBox->AddChild(button);
			}
		}
	}break;
	case t_Day:
	{
		parentUI = (UAddressAndTimeTool*)m_ParentUI;
		int year = parentUI->m_LevelMap[t_Year];

		bool isFirst = true;
		for (int i = 1; i <= FDateTime::DaysInMonth(year,m_ParentId);i++)
		{
			if (FDateTime::Validate(year, m_ParentId, i,0,0,0,0))
			{
				IdData data;
				data.Id = i;
				data.Name = FString::Printf(TEXT("%d"), i);
				if (isFirst)
				{
					isFirst = false;
					parentUI->m_LevelMap[m_Type] = data.Id;
					m_NextNode->SetParentId(data.Id);
				}
				UToolButton * button = (UToolButton*)UIManager::GetInstance()->OpenUI(TEXT("ToolButton"));
				button->SetData(data);
				m_Buttons.Add(button);
				m_ScorllBox->AddChild(button);
			}
		}
	}break;
	case t_HalfDay:
	{
		parentUI = (UAddressAndTimeTool*)m_ParentUI;
		int year = parentUI->m_LevelMap[t_Year];
		int month = parentUI->m_LevelMap[t_Year];

		bool isFirst = true;
		for (int i = 0; i < 24;i++)
		{
			if (FDateTime::Validate(year, month, m_ParentId,i,0,0,0))
			{
				IdData data;
				data.Id = i;
				data.Name = FString::Printf(TEXT("%d"), i);
				if (isFirst)
				{
					isFirst = false;
					parentUI->m_LevelMap[m_Type] = data.Id;
					m_NextNode->SetParentId(data.Id);
				}
				UToolButton * button = (UToolButton*)UIManager::GetInstance()->OpenUI(TEXT("ToolButton"));
				button->SetData(data);
				m_Buttons.Add(button);
				m_ScorllBox->AddChild(button);
			}
		}
	}break;
	case t_Shi:
	{

	}break;
	case t_Qu:
	{

	}break;
	}
}
void UToolScrollWidget::StartRun(int _id)
{
	switch (m_Type)
	{
	case t_Year:
	{
		FDateTime time = FDateTime::Now();
		int nowYear = time.GetYear();
		for (int i = 0;i < 3;i++)
		{
			IdData data;
			data.Id = nowYear + i;
			data.Name = FString::Printf(TEXT("%d"),nowYear+i);
			if (i == 0)
			{
				UAddressAndTimeTool * parent = (UAddressAndTimeTool*)m_ParentUI;
				parent->m_LevelMap[m_Type] = data.Id;
				m_NextNode->SetParentId(data.Id);
			}
			UToolButton * button = (UToolButton*)UIManager::GetInstance()->OpenUI(TEXT("ToolButton"));
			button->SetData(data);
			m_Buttons.Add(button);
			m_ScorllBox->AddChild(button);
		}
	}break;
	case t_Sheng:
	{

	}break;
	default:
		break;
	}
}

