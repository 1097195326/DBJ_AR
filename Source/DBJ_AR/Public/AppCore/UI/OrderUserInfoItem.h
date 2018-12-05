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
		bool m_IsEdit;
	UPROPERTY(EditAnywhere)
		bool m_ShowBorder;

	UImage * m_ShowGoImage;
    UButton * m_DoSomethingButton;
	UTextBlock *  m_ItemName;
	UEditableText * m_EditText;
	UTextBlock *  m_ItemContent;
	UBorder *	m_BottomBorder;

	
};
