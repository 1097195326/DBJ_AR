#pragma once

#include "BaseUI.h"
#include "MsgCenter.h"
#include "EditerARUI.generated.h"

UCLASS()
class UEditerARUI : public UBaseUI
{
    GENERATED_BODY()
    
public:
    UButton * m_ProductListButton;
    
public:
    virtual void On_Init() override;
    virtual void On_Start() override;
    virtual void On_Delete() override;
    
    void On_Button_Click(int _index);
    
};
