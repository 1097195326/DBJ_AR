#pragma once

#include "BaseUI.h"
#include "GoodsList.generated.h"


UCLASS()
class DBJ_AR_API  UGoodsList : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;

	void InitView();

    UFUNCTION()
        void OnButtonClick();
private:
	UButton * m_ViewButton;
	UScrollBox * m_IconScrolBox;
	UGridPanel * m_IconList;

};
