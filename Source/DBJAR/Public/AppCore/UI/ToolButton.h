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
class DBJAR_API  UToolButton : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;

	UPROPERTY()
		UButton * m_ViewButton;
	UPROPERTY()
		UTextBlock * m_ButtonText;
	UPROPERTY()
	UBorder * m_SelectBorder;

	IdData	m_Data;

	virtual void	SetData(const IdData & _data, SelectButtonDelegate * _delegate);
	virtual void	SelectButton(bool _isSelect);

    UFUNCTION()
        void OnButtonClick();

protected:
	SelectButtonDelegate * m_Delegate;
};
