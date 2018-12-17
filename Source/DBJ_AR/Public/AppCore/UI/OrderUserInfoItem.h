#pragma once
#include "BaseUI.h"
#include "OrderUserInfoItem.generated.h"


UCLASS()
class DBJ_AR_API  UOrderUserInfoItem : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Delete() override;

	UPROPERTY(EditAnywhere)
		FString m_ItemNameS;
	UPROPERTY(EditAnywhere)
		FString m_ItemContentS;
	UPROPERTY(EditAnywhere)
		bool m_IsEdit;
	UPROPERTY(EditAnywhere)
		bool m_ShowBorder;

	UPROPERTY()
		UImage * m_ShowGoImage;
	UPROPERTY()
		UButton * m_DoSomethingButton;
	UPROPERTY()
		UTextBlock *  m_ItemName;
	UPROPERTY()
		UEditableText * m_EditText;
	UPROPERTY()
	UBorder *	m_BottomBorder;

    void SetOnlyShow();
};
