#pragma once
#include "BaseUI.h"
#include "EditStringUI.h"
#include "MsgCenter.h"
#include "EditUserInfoUI.generated.h"


UCLASS()
class DBJ_AR_API  UEditUserInfoUI: public UBaseUI, public EditStringDelegate
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Delete() override;

	UButton * m_BackButton;
	UButton * m_EditUerNameButton;
	UImage * m_UserImage;
    UButton * m_ChangeUserImage;
	UTextBlock * m_UserName;
	UTextBlock * m_UserPhone;

    void OnButtonClick(int _index);

	void EditString(const FString & text);

	void OnEditString(msg_ptr _msg);
private:
	FString	m_Wto_UserName;

    void OnSelectPicture(bool isSuccess, FString inIconFilePath, FString inFilePath, FVector2D inDPI, FVector2D inRes);
};
