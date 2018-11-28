#pragma once

#include "BaseUI.h"
#include "MsgCenter.h"
#include "SettingUI.generated.h"


UCLASS()
class DBJ_AR_API  USettingUI : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;
	virtual void On_Delete() override;

    UButton * m_AllowGButton;
	UButton * m_LayoutButton;
	UButton * m_BackButton;
	UImage *  m_SwitchOff;
	UImage *  m_SwitchOn;

	void OnButtonClick(int _index);
	void ReView();

	void	OnUserLogout(msg_ptr _msg);
private:
	bool isOnOrOff;
};
