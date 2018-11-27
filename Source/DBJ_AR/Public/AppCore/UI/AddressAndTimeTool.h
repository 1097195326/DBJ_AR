#pragma once

#include "BaseUI.h"
#include "ToolScrollWidget.h"
#include "AddressAndTimeTool.generated.h"

enum AddOrTimeType
{
	t_Time,
	t_Address
};

UCLASS()
class DBJ_AR_API  UAddressAndTimeTool : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Delete() override;
	
	TMap<ToolScrollType, int>	m_LevelMap;

	TArray<UToolScrollWidget*>	m_Widgets;

	UHorizontalBox * m_ScrollWidgetList;

    UButton * m_CancelButton;
	UButton * m_SureButton;
	UTextBlock * m_TitleName;

	AddOrTimeType  m_type;

	void	SetType(AddOrTimeType _type);

        void OnButtonClick(int _index);
};
