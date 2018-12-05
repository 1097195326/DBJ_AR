#pragma once

#include "BaseUI.h"
#include "MsgCenter.h"
#include "LoginUI.generated.h"

UCLASS()
class ULoginUI : public UBaseUI
{
	GENERATED_BODY()

public:
	UButton * m_Login_Button;
	UButton * m_VeriCode_Button;

	UEditableText * m_Phone_Text;
	UEditableText * m_VeriCode_Text;
public:
	virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Delete() override;

	void On_Button_Click(int _index);

	void OnGetSmsCode(msg_ptr _msg);
	void OnUserLogin(msg_ptr _msg);
	void OnAutoLogin(msg_ptr _msg);

private:
    FString m_sms;
    FString m_IphoneNum;
};
