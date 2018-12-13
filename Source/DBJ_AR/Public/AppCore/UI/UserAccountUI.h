#pragma once

#include "BaseUI.h"
#include "MsgCenter.h"
#include "UserAccountUI.generated.h"


UCLASS()
class DBJ_AR_API  UUserAccountUI : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Tick(float delta) override;
	virtual void On_Delete() override;


    UButton * m_BackButton;
	UButton * m_SettingButton;
	UImage *  m_UserImage;
	UTextBlock * m_CompanyName;
	UTextBlock * m_UserName;
	UTextBlock * m_AccountTypeText;
	UButton * m_ToUserInfoButton;

	UScrollBox * m_OrderListScroll;

    void OnButtonClick(int _index);

	void OnGetAccountOrder(msg_ptr _msg);

	void ReloadData();

private:
	int32		m_LastId;
	bool		m_IsRequest;

};
