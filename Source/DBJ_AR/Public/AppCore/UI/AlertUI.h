#pragma once

#include "BaseUI.h"
#include "AlertUI.generated.h"


UCLASS()
class DBJ_AR_API  UAlertUI : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;

    UButton * m_ViewButton;

    UFUNCTION()
        void OnButtonClick();
};
