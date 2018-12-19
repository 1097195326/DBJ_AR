#pragma once
#include "BaseUI.h"
#include "EditStringUI.h"
#include "MsgCenter.h"
#include "EditUserInfoUI.generated.h"


UCLASS()
class DBJAR_API  UEditUserInfoUI: public UBaseUI, public EditStringDelegate
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Delete() override;

	UPROPERTY()
		UButton * m_BackButton;
	UPROPERTY()
		UButton * m_EditUerNameButton;
	UPROPERTY()
		UImage * m_UserImage;
	UPROPERTY()
		UButton * m_ChangeUserImage;
	UPROPERTY()
		UTextBlock * m_UserName;
	UPROPERTY()
	UTextBlock * m_UserPhone;

    void OnButtonClick(int _index);

	void EditString(const FString & text);

	void OnEditString(msg_ptr _msg);
private:
	FString	m_Wto_UserName;

    void OnSelectPicture(bool isSuccess, FString inIconFilePath, FString inFilePath, FVector2D inDPI, FVector2D inRes);
};
