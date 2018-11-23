#pragma once

#include "BaseUI.h"
#include "OrderUserInfoItem.h"

#include "OrderUserInfoUI.generated.h"


UCLASS()
class DBJ_AR_API  UOrderUserInfoUI : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Delete() override;

    UButton * m_BackButton;
	UVerticalBox * m_ViewBox;

	UOrderUserInfoItem * m_CompanyName;
	UOrderUserInfoItem * m_GetStyle;
	UOrderUserInfoItem * m_UserName;
	UOrderUserInfoItem * m_UsserPhone;
	UOrderUserInfoItem * m_GetTime;
	UOrderUserInfoItem * m_Address;
	UOrderUserInfoItem * m_DetailAddress;

	void ReView();
    void OnButtonClick(int _index);

	void SetGetStyle(FString _style);
	void SetGetTime(FString _time);
	void SetAddress(FString _address);
};
