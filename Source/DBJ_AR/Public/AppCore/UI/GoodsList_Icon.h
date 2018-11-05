#pragma once

#include "BaseUI.h"
#include "GoodsList_Icon.generated.h"


UCLASS()
class DBJ_AR_API  UGoodsList_Icon : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;

    UButton * m_ViewButton;

    UFUNCTION()
        void OnButtonClick();
};
