#pragma once
#include "BaseUI.h"
#include "ToolButton.generated.h"

struct IdData
{
	int Id;
	FString Name;
};
class UToolButton;
class SelectButtonDelegate
{
public:
	virtual void SelectButton(UToolButton * _button) = 0;
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

	virtual void	SetData(const IdData & _data, SelectButtonDelegate * _delegate);
	virtual void	SelectButton(bool _isSelect);

    UFUNCTION()
        void OnButtonClick();

protected:
	SelectButtonDelegate * m_Delegate;
};
