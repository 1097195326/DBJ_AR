#pragma once

#include "BaseUI.h"
#include "OrderInfoUI.h"
#include "MakeOrderUI.generated.h"


UCLASS()
class DBJ_AR_API  UMakeOrderUI : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Delete() override;

	void	InitView();
	void	ReView();

	TArray<UOrderInfoUI*> m_InfoUIList;

    UButton * m_BackButton;
	// user info
	UTextBlock * m_CompanyName;
	UTextBlock * m_UserInfo;
	UTextBlock * m_AddressInfo;
	UButton * m_ToOrderInfoButton;
	//main view
	UScrollBox * m_OrderScroll;
	UTextBlock * m_Allprice;
	UButton * m_SaveOrderButton;
	UButton * m_CommitOrderButton;

    UFUNCTION()
        void OnButtonClick(int _index);

	void SetPrice(int num);

private:
	int		allPriceI;
};
