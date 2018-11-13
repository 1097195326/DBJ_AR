#pragma once

#include "BaseUI.h"
#include "GoodsList_Icon.h"
#include "GoodsChangeUI.generated.h"


UCLASS()
class DBJ_AR_API  UGoodsChangeUI : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;

    UButton * m_ViewButton;
	UScrollBox * m_ScrollBox;
	UGridPanel * m_GridPanel;


    UFUNCTION()
        void OnButtonClick();
private:
	TArray<UGoodsList_Icon*>	m_GoodsListIcons;


};
