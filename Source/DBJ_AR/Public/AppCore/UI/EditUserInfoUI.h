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
	UEditableText * m_EditUserName;
	UEditableText * m_EditUserPhone;

    void OnButtonClick(int _index);
};