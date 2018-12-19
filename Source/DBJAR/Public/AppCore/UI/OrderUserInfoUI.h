#pragma once

#include "BaseUI.h"
#include "OrderUserInfoItem.h"

#include "OrderUserInfoUI.generated.h"


UCLASS()
class DBJAR_API  UOrderUserInfoUI : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Delete() override;

	UPROPERTY()
		UButton * m_BackButton;
	UPROPERTY()
		UButton * m_SaveButton;
	UPROPERTY()
	UVerticalBox * m_ViewBox;

	UPROPERTY()
		UOrderUserInfoItem * m_CompanyName;
	UPROPERTY()
		UOrderUserInfoItem * m_GetStyle;
	UPROPERTY()
		UOrderUserInfoItem * m_UserName;
	UPROPERTY()
		UOrderUserInfoItem * m_UsserPhone;
	UPROPERTY()
		UOrderUserInfoItem * m_GetTime;
	UPROPERTY()
		UOrderUserInfoItem * m_Address;
	UPROPERTY()
	UOrderUserInfoItem * m_DetailAddress;

	void ReView();
    void OnButtonClick(int _index);

	void SetGetStyle(FString _style);
	void SetGetTime(FString _time);
	void SetAddress(FString _address);
};
