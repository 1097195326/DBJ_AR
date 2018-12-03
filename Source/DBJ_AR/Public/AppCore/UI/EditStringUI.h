#pragma once

#include "BaseUI.h"
#include "EditStringUI.generated.h"

class EditStringDelegate
{
public:
	virtual void EditString(const FString & text) = 0;
};
UCLASS()
class DBJ_AR_API  UEditStringUI : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Delete() override;

	void	SetDelegate(EditStringDelegate * _delegate,FString _titleName,FString _hintS);

    UButton * m_CancelButton;
	UButton * m_SureButton;
	UTextBlock * m_TitleName;
	UEditableText * m_EditString;

    void OnButtonClick(int _index);
private:
	EditStringDelegate * m_Delegate;
	FString		m_TitleNameS;
	FString		m_EditHintS;
};
