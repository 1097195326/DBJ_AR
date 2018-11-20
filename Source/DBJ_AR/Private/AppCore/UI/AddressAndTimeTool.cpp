#include "AddressAndTimeTool.h"
#include "DateTime.h"
#include "UIManager.h"


void UAddressAndTimeTool::On_Init()
{
    if (UButton * widget = (UButton*)GetWidgetFromName("ViewButton"))
    {
        m_ViewButton = widget;
        m_ViewButton->OnClicked.AddDynamic(this, &UAddressAndTimeTool::OnButtonClick);
    }
	if (UHorizontalBox * widget = (UHorizontalBox*)GetWidgetFromName("ScrollWidgetList"))
	{
		m_ScrollWidgetList = widget;
	}
	FDateTime time = FDateTime::Now();
	UE_LOG(LogTemp, Log, TEXT("zhx : time Y : %d, M : %d, D : %d"), time.GetYear(),time.GetMonth(),time.GetDay());

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
	switch (m_type)
	{
	case t_Address:
	{
		UToolScrollWidget * qu = (UToolScrollWidget*)UIManager::GetInstance()->OpenUI(TEXT("ToolScrollWidget"),this);
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

		sheng->StartRun();
	}break;
	case t_Time:
	{
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

		Year->StartRun();
	}break;
	}
}
void UAddressAndTimeTool::On_Delete()
{

}
void UAddressAndTimeTool::OnButtonClick()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UAddressAndTimeTool::OnButtonClick : "));

}
void UAddressAndTimeTool::SetType(AddOrTimeType _type)
{
	m_type = _type;
}