#pragma once
#include "BaseUI.h"
#include "EditUserInfoUI.generated.h"


UCLASS()
class DBJ_AR_API  UEditUserInfoUI: public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;

	UButton * m_BackButton;
	UImage * m_UserImage;
    UButton * m_ChangeUserImage;
	UTextBlock * m_EditUserName;
	UTextBlock * m_EditUserPhone;

    void OnButtonClick(int _index);

	void OnTextChanged(const FText & text);

};