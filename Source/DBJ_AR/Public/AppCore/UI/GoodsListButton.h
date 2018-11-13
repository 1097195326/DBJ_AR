#pragma once
#pragma once

#include "BaseUI.h"
#include "GoodsListButton.generated.h"


UCLASS()
class DBJ_AR_API  UGoodsListButton : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;

    UButton * m_ViewButton;
	UTextBlock * m_Text;

    UFUNCTION()
        void OnButtonClick();

	void SetData(int _id, FString _name,UBaseUI * parent);

	void SetButtonSelect(bool _select);

	int		m_Id;
	FString m_Name;
	UBaseUI * m_Parent;
private:
	

};