#pragma once

#include "BaseUI.h"
#include "MsgCenter.h"
#include "SettingUI.generated.h"


UCLASS()
class DBJAR_API  USettingUI : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;
    virtual void On_Start() override;
	virtual void On_Delete() override;

	UPROPERTY()
		UButton * m_AllowGButton;
	UPROPERTY()
		UButton * m_LayoutButton;
	UPROPERTY()
		UButton * m_BackButton;
	UPROPERTY()
		UImage *  m_SwitchOff;
	UPROPERTY()
		UImage *  m_SwitchOn;

	void OnButtonClick(int _index);
	void SureLayout();

	void ReView();

	void	OnUserLogout(msg_ptr _msg);
private:
	bool isOnOrOff;
};
