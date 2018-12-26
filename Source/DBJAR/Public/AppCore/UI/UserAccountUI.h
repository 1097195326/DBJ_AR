#pragma once

#include "BaseUI.h"
#include "MsgCenter.h"
#include "UserAccountUI.generated.h"


UCLASS()
class DBJAR_API  UUserAccountUI : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Tick(float delta) override;
	virtual void On_Delete() override;

	UPROPERTY()
    UButton * m_BackButton;
	UPROPERTY()
	UButton * m_SettingButton;
	UPROPERTY()
	UImage *  m_UserImage;
	UPROPERTY()
		UTextBlock * m_CompanyName;
	UPROPERTY()
		UTextBlock * m_UserName;
	UPROPERTY()
		UTextBlock * m_AccountTypeText;
	UPROPERTY()
	UButton * m_ToUserInfoButton;

	UPROPERTY()
	UScrollBox * m_OrderListScroll;
	UPROPERTY()
		UCanvasPanel * m_ContentEmptyPanel;
    void OnButtonClick(int _index);

	void OnGetAccountOrder(msg_ptr _msg);

	void ReloadData();

private:
	int32		m_LastId;
	bool		m_IsRequest;

};
