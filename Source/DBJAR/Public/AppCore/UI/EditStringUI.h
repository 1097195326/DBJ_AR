#pragma once

#include "BaseUI.h"
#include "EditStringUI.generated.h"

class EditStringDelegate
{
public:
	virtual void EditString(const FString & text) = 0;
};
UCLASS()
class DBJAR_API  UEditStringUI : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Delete() override;

	void	SetDelegate(EditStringDelegate * _delegate,FString _titleName,FString _hintS);

	UPROPERTY()
		UButton * m_CancelButton;
	UPROPERTY()
		UButton * m_SureButton;
	UPROPERTY()
		UTextBlock * m_TitleName;
	UPROPERTY()
	UEditableText * m_EditString;

    void OnButtonClick(int _index);
private:
	EditStringDelegate * m_Delegate;
	FString		m_TitleNameS;
	FString		m_EditHintS;
};
