#pragma once

#include "BaseUI.h"
#include "MsgCenter.h"
#include "LoginUI.generated.h"

UCLASS()
class ULoginUI : public UBaseUI
{
	GENERATED_BODY()

public:
	UCanvasPanel * m_XieyiPanel;
	UCanvasPanel * m_MainPanel;

	UButton * m_BackButton;
	UButton * m_Login_Button;
	UButton * m_VeriCode_Button;
	UButton * m_Button_Open_Service_Agreement;

	UEditableText * m_Phone_Text;
	UEditableText * m_VeriCode_Text;
	UTextBlock *  m_VeriText;

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

	FTimerHandle m_TimeHandle;
	void	TimeRun();
};
