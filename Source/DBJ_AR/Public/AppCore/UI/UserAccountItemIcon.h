#pragma once
#include "BaseUI.h"
#include "UserAccountItemIcon.generated.h"


UCLASS()
class DBJ_AR_API  UUserAccountItemIcon : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;

    UImage * m_ShowImage;

	void SetImageUrl(FString _url);
};
