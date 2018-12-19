#pragma once
#include "BaseUI.h"
#include "DateTime.h"
#include "ToolButton.h"
#include "MsgCenter.h"
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
class DBJAR_API  UToolScrollWidget : public UBaseUI, public SelectButtonDelegate
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;
	virtual void On_Delete() override;

	UPROPERTY()
		UButton * m_ViewButton;
	UPROPERTY()
	UScrollBox * m_ScorllBox;

	int			m_Level;

	ToolScrollType m_Type;
	int		m_ParentId;
	IdData  m_CurrentData;

	TArray<UToolButton*>	m_Buttons;

	UPROPERTY()
	UToolScrollWidget * m_NextNode;
	
	void	StartRun(int _id = 0);
	void	SetType(ToolScrollType _type);
	void	SetParentId(int _id);
	void	SelectButton(UToolButton * _button);

	FString	GetName();

    UFUNCTION()
        void OnButtonClick();

	void OnGetAreasList(msg_ptr _msg);

};
