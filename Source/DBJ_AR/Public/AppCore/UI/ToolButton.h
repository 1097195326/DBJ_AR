#pragma once
#include "BaseUI.h"
#include "ToolButton.generated.h"

struct IdData
{
	int Id;
	FString Name;
};

UCLASS()
class DBJ_AR_API  UToolButton : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;

    UButton * m_ViewButton;
	UTextBlock * m_ButtonText;
	UBorder * m_SelectBorder;


	IdData	m_Data;

	void	SetData(IdData _data);
	void	SelectButton(bool _isSelect);

    UFUNCTION()
        void OnButtonClick();
};
