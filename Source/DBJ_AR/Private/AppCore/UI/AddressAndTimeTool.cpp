#include "AddressAndTimeTool.h"
#include "DateTime.h"
#include "UIManager.h"
#include "OrderUserInfoUI.h"
#include "RuntimeRDataManager.h"

void UAddressAndTimeTool::On_Init()
{
    if (UButton * widget = (UButton*)GetWidgetFromName("CancelButton"))
    {
        m_CancelButton = widget;
		UIManager::GetInstance()->RegisterButton(1, m_CancelButton, this, &UAddressAndTimeTool::OnButtonClick);
    }
	if (UButton * widget = (UButton*)GetWidgetFromName("SureButton"))
	{
		m_SureButton = widget;
		UIManager::GetInstance()->RegisterButton(2, m_SureButton, this, &UAddressAndTimeTool::OnButtonClick);

	}
	if (UHorizontalBox * widget = (UHorizontalBox*)GetWidgetFromName("ScrollWidgetList"))
	{
		m_ScrollWidgetList = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("TitleName"))
	{
		m_TitleName = widget;
	}
	//IdData data1,data2,data3,data4,data5,data6,data7;
	m_LevelMap.Add(t_Sheng, 0);
	m_LevelMap.Add(t_Shi, 0);
	m_LevelMap.Add(t_Qu, 0);
	m_LevelMap.Add(t_Year, 0);
	m_LevelMap.Add(t_Month, 0);
	m_LevelMap.Add(t_Day, 0);
	m_LevelMap.Add(t_HalfDay, 0);
}
void UAddressAndTimeTool::On_Start()
{	
	
}
void UAddressAndTimeTool::On_Delete()
{
	UIManager::GetInstance()->UnRegisterButton(m_CancelButton);
	UIManager::GetInstance()->UnRegisterButton(m_SureButton);

}
void UAddressAndTimeTool::OnButtonClick(int _index)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UAddressAndTimeTool::OnButtonClick : %d"),_index);
	switch (_index)
	{
	case 1:
	{
		RemoveFromParent();
	}break;
	case 2:
	{
		R_Order * order = RuntimeRDataManager::GetInstance()->GetCurrentOrder();
		UOrderUserInfoUI * parentUI = (UOrderUserInfoUI*)m_ParentUI;
		FString setS;
		switch (m_type)
		{
		case t_Time:
		{
			FString year = m_Widgets[0]->m_CurrentData.Name;
			FString month = m_Widgets[1]->m_CurrentData.Name;
			FString day = m_Widgets[2]->m_CurrentData.Name;
			FString halfDay = m_Widgets[3]->m_CurrentData.Name;
			setS = FString::Printf(TEXT("%s%s%s%s"), *year, *month, *day, *halfDay);
			parentUI->SetGetTime(setS);
			FDateTime expTime(m_Widgets[0]->m_CurrentData.Id, m_Widgets[1]->m_CurrentData.Id, m_Widgets[2]->m_CurrentData.Id);
			order->ExpectReceiveTime = expTime.ToUnixTimestamp() * 1000;
			order->Morning = m_Widgets[3]->m_CurrentData.Id == 1 ? true : false;

		}break;
		case t_Address:
		{
			FString sheng = m_Widgets[0]->m_CurrentData.Name;
			FString shi = m_Widgets[1]->m_CurrentData.Name;
			FString qu = m_Widgets[2]->m_CurrentData.Name;
			setS = FString::Printf(TEXT("%s%s%s"), *sheng, *shi, *qu);
			parentUI->SetAddress(setS);
			order->ProvinceId = m_Widgets[0]->m_CurrentData.Id;
			order->CityId = m_Widgets[1]->m_CurrentData.Id;
			order->DistrictId = m_Widgets[2]->m_CurrentData.Id;
		}break;
		default:
			break;
		}
		RemoveFromParent();
	}break;
	}
}
void UAddressAndTimeTool::SetType(AddOrTimeType _type)
{
	m_type = _type;

	switch (m_type)
	{
	case t_Address:
	{
		m_TitleName->SetText(FText::FromString(TEXT("选择地点")));

		UToolScrollWidget * qu = (UToolScrollWidget*)UIManager::GetInstance()->OpenUI(TEXT("ToolScrollWidget"), this);
		qu->SetType(t_Qu);
		UToolScrollWidget * shi = (UToolScrollWidget*)UIManager::GetInstance()->OpenUI(TEXT("ToolScrollWidget"), this);
		shi->m_NextNode = qu;
		shi->SetType(t_Shi);
		UToolScrollWidget * sheng = (UToolScrollWidget*)UIManager::GetInstance()->OpenUI(TEXT("ToolScrollWidget"), this);
		sheng->m_NextNode = shi;
		sheng->SetType(t_Sheng);

		m_ScrollWidgetList->AddChild(sheng);
		m_ScrollWidgetList->AddChild(shi);
		m_ScrollWidgetList->AddChild(qu);

		m_Widgets.Add(sheng);
		m_Widgets.Add(shi);
		m_Widgets.Add(qu);

		sheng->StartRun();
	}break;
	case t_Time:
	{
		m_TitleName->SetText(FText::FromString(TEXT("选择日期")));

		UToolScrollWidget * halfDay = (UToolScrollWidget*)UIManager::GetInstance()->OpenUI(TEXT("ToolScrollWidget"), this);
		halfDay->SetType(t_HalfDay);
		UToolScrollWidget * Day = (UToolScrollWidget*)UIManager::GetInstance()->OpenUI(TEXT("ToolScrollWidget"), this);
		Day->m_NextNode = halfDay;
		Day->SetType(t_Day);
		UToolScrollWidget * Month = (UToolScrollWidget*)UIManager::GetInstance()->OpenUI(TEXT("ToolScrollWidget"), this);
		Month->m_NextNode = Day;
		Month->SetType(t_Month);
		UToolScrollWidget * Year = (UToolScrollWidget*)UIManager::GetInstance()->OpenUI(TEXT("ToolScrollWidget"), this);
		Year->m_NextNode = Month;
		Year->SetType(t_Year);

		m_ScrollWidgetList->AddChild(Year);
		m_ScrollWidgetList->AddChild(Month);
		m_ScrollWidgetList->AddChild(Day);
		m_ScrollWidgetList->AddChild(halfDay);

		m_Widgets.Add(Year);
		m_Widgets.Add(Month);
		m_Widgets.Add(Day);
		m_Widgets.Add(halfDay);

		Year->StartRun();
	}break;
	}
}
