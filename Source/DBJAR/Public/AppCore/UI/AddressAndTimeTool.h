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
class DBJAR_API  UAddressAndTimeTool : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Delete() override;

	TMap<ToolScrollType, int>	m_LevelMap;

	UPROPERTY()
	TArray<UToolScrollWidget*>	m_Widgets;

	UPROPERTY()
	UHorizontalBox * m_ScrollWidgetList;

	UPROPERTY()
	UButton * m_CancelButton;
	UPROPERTY()
	UButton * m_SureButton;
	UPROPERTY()
	UTextBlock * m_TitleName;

	AddOrTimeType  m_type;

	void	SetType(AddOrTimeType _type);

        void OnButtonClick(int _index);
};
