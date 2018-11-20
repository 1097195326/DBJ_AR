#pragma once
#include "BaseUI.h"
#include "DateTime.h"
#include "ToolButton.h"
#include "ToolScrollWidget.generated.h"

enum ToolScrollType
{
	t_Sheng,
	t_Shi,
	t_Qu,
	t_Year,
	t_Month,
	t_Day,
	t_HalfDay
};
UCLASS()
class DBJ_AR_API  UToolScrollWidget : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;

    UButton * m_ViewButton;
	UScrollBox * m_ScorllBox;

	ToolScrollType m_Type;
	int		m_ParentId;
	TArray<UToolButton*>	m_Buttons;

	UToolScrollWidget * m_NextNode;
	
	void	StartRun(int _id = 0);
	void	SetType(ToolScrollType _type);
	void	SetParentId(int _id);

    UFUNCTION()
        void OnButtonClick();
};
