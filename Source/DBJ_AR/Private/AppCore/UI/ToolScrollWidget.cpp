#include "ToolScrollWidget.h"
#include "UIManager.h"
#include "AddressAndTimeTool.h"
#include "EditerARGameModule.h"

void UToolScrollWidget::On_Init()
{
    if (UButton * widget = (UButton*)GetWidgetFromName("ViewButton"))
    {
        m_ViewButton = widget;
        m_ViewButton->OnClicked.AddDynamic(this, &UToolScrollWidget::OnButtonClick);
    }
	if (UScrollBox * widget = (UScrollBox*)GetWidgetFromName("ScrollView"))
	{
		m_ScorllBox = widget;
	}
	m_ParentUI = nullptr;
	m_ParentId = -1;

	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2014, this, &UToolScrollWidget::OnGetAreasList);
}
void UToolScrollWidget::On_Delete()
{
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 2014, this);

}
void UToolScrollWidget::OnButtonClick()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIB::OnButtonClick : "));

}
void UToolScrollWidget::SetType(ToolScrollType _type)
{
	m_Type = _type;
	switch (m_Type)
	{
	case t_Sheng:
	{
		m_Level = 1;
	}break;
	case t_Shi:
	{
		m_Level = 2;
	}break;
	case t_Qu:
	{
		m_Level = 3;
	}break;
	}
}
void UToolScrollWidget::SetParentId(int _id)
{
	m_ParentId = _id;
	UAddressAndTimeTool * parentUI = nullptr;
	if (m_Buttons.Num())
	{
		m_Buttons.Empty();
		m_ScorllBox->ClearChildren();
		m_ScorllBox->ScrollToStart();
	}
	switch (m_Type)
	{
	case t_Month:
	{
		bool isFirst = true;
		for (int i = 1; i<= 12;i++)
		{
			FDateTime now = FDateTime::Now();
			FDateTime time(m_ParentId, i, now.GetDay(),now.GetHour(),now.GetMinute(),now.GetSecond());
			if (time.ToUnixTimestamp() >= now.ToUnixTimestamp())
			{
				IdData data;
				data.Id = i;
				data.Name = FString::Printf(TEXT("%d月"), i);
				
				UToolButton * button = (UToolButton*)UIManager::GetInstance()->OpenUI(TEXT("ToolButton"),this);
				button->SetData(data);
				m_Buttons.Add(button);
				m_ScorllBox->AddChild(button);
				if (isFirst)
				{
					isFirst = false;
					SelectButton(button);
				}
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
			FDateTime now = FDateTime::Now();
			FDateTime time(year, m_ParentId, i);
			if (time.ToUnixTimestamp() >= now.ToUnixTimestamp())
			{
				IdData data;
				data.Id = i;
				data.Name = FString::Printf(TEXT("%d日"), i);
				
				UToolButton * button = (UToolButton*)UIManager::GetInstance()->OpenUI(TEXT("ToolButton"),this);
				button->SetData(data);
				m_Buttons.Add(button);
				m_ScorllBox->AddChild(button);
				if (isFirst)
				{
					SelectButton(button);
					isFirst = false;
				}
			}
		}
	}break;
	case t_HalfDay:
	{
		for (int i = 1; i < 3;i++)
		{
			IdData data;
			data.Id = i;
			if (i == 1)
			{
				data.Name = FString(TEXT("上午"));
			}
			else
			{
				data.Name = TEXT("下午");
			}
			UToolButton * button = (UToolButton*)UIManager::GetInstance()->OpenUI(TEXT("ToolButton"),this);
			button->SetData(data);
			m_Buttons.Add(button);
			m_ScorllBox->AddChild(button);
			if (i == 1)
			{
				SelectButton(button);
			}
		}
	}break;
	case t_Shi:
	{
		EditerARGameModule::GetInstance()->GetAreaList(m_ParentId,2);
	}break;
	case t_Qu:
	{
		EditerARGameModule::GetInstance()->GetAreaList(m_ParentId,3);
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
			data.Name = FString::Printf(TEXT("%d年"),nowYear+i);
			
			UToolButton * button = (UToolButton*)UIManager::GetInstance()->OpenUI(TEXT("ToolButton"),this);
			button->SetData(data);
			m_Buttons.Add(button);
			m_ScorllBox->AddChild(button);

			if (i == 0)
			{
				SelectButton(button);
			}
			
		}
	}break;
	case t_Sheng:
	{
		m_ParentId = _id;
		EditerARGameModule::GetInstance()->GetAreaList(m_ParentId,1);
	}break;
	default:
		break;
	}
}
void UToolScrollWidget::OnGetAreasList(msg_ptr _msg)
{
	//UE_LOG(LogTemp, Log, TEXT("zhx : UToolScrollWidget::OnGetAreasList : %d"), pid);
	int level = _msg->GetMsgContent<int>();

	if (m_Level == level)
	{
		/*if (m_Buttons.Num() > 0)
		{
			m_Buttons.Empty();
			m_ScorllBox->ClearChildren();
			m_ScorllBox->ScrollToStart();
		}*/
		TSharedPtr<FJsonObject> jsonObject = _msg->GetJsonObject();
		TArray<TSharedPtr<FJsonValue>> dataList = jsonObject->GetArrayField(TEXT("data"));
		for (int i = 0; i < dataList.Num(); i++)
		{
			TSharedPtr<FJsonObject> value = dataList[i]->AsObject();
			IdData data;
			data.Id = value->GetNumberField(TEXT("id"));
			data.Name = value->GetStringField(TEXT("name"));

			UToolButton * button = (UToolButton*)UIManager::GetInstance()->OpenUI(TEXT("ToolButton"), this);
			button->SetData(data);
			m_Buttons.Add(button);
			m_ScorllBox->AddChild(button);

		}
		SelectButton(m_Buttons[0]);
	}
}
void UToolScrollWidget::SelectButton(UToolButton * _button)
{
	m_CurrentData = _button->m_Data;
	UAddressAndTimeTool * parent = (UAddressAndTimeTool*)m_ParentUI;
	parent->m_LevelMap[m_Type] = m_CurrentData.Id;

	if (m_NextNode)
	{
		m_NextNode->SetParentId(m_CurrentData.Id);
	}
	for (int i = 0; i < m_Buttons.Num(); i++)
	{
		if(m_Buttons[i] ==_button)
		{
			m_Buttons[i]->SelectButton(true);
		}else
		{
			m_Buttons[i]->SelectButton(false);
		}
	}
}
FString UToolScrollWidget::GetName()
{
	return m_CurrentData.Name;
}
