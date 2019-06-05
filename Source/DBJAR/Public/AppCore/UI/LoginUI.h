#pragma once

#include "BaseUI.h"
#include "MsgCenter.h"
#include "LoginUI.generated.h"

UCLASS()
class ULoginUI : public UBaseUI
{
	GENERATED_BODY()

public:
	UPROPERTY()
		UCanvasPanel * m_XieyiPanel;
	UPROPERTY()
		UCanvasPanel * m_MainPanel;
	UPROPERTY()
		UButton * m_BackButton;
	UPROPERTY()
		UButton * m_Login_Button;
	UPROPERTY()
		UButton * m_VeriCode_Button;
	UPROPERTY()
		UButton * m_Visitor_Button;
	UPROPERTY()
	UButton * m_Button_Open_Service_Agreement;

	UPROPERTY()
		UEditableText * m_Phone_Text;
	UPROPERTY()
		UEditableText * m_VeriCode_Text;
	UPROPERTY()
		UTextBlock *  m_VeriText;

public:
	virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Delete() override;

	void On_Button_Click(int _index);

	void OnGetSmsCode(msg_ptr _msg);
	void OnUserLogin(msg_ptr _msg);
	void OnAutoLogin(msg_ptr _msg);
	void OnRequestLogin(msg_ptr _msg);

private:
    FString m_sms;
    FString m_IphoneNum;

	FTimerHandle m_TimeHandle;
	void	TimeRun();

	void CheckRemainDays();
	void OnAlertButtonClick();

};
