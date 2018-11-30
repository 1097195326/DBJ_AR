#pragma once

#include "BaseUI.h"
#include "EditStringUI.generated.h"


UCLASS()
class DBJ_AR_API  UEditStringUI : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;

    UButton * m_ViewButton;

    UFUNCTION()
        void OnButtonClick();
};
