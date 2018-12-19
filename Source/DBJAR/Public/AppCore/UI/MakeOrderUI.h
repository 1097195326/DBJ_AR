#pragma once

#include "BaseUI.h"
#include "OrderInfoUI.h"
#include "MsgCenter.h"
#include "MakeOrderUI.generated.h"


UCLASS()
class DBJAR_API  UMakeOrderUI : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Delete() override;

	void	InitView();
	void	ReView();

	UPROPERTY()
	TArray<UOrderInfoUI*> m_InfoUIList;

	UPROPERTY()
		UButton * m_BackButton;
	UPROPERTY()
	UTextBlock * m_TitleName;
	// user info
	UPROPERTY()
		UTextBlock * m_CompanyName;
	UPROPERTY()
		UTextBlock * m_UserInfo;
	UPROPERTY()
		UTextBlock * m_AddressInfo;
	UPROPERTY()
	UButton * m_ToOrderInfoButton;
	//main view
	UPROPERTY()
		UScrollBox * m_OrderScroll;
	UPROPERTY()
		UTextBlock * m_Allprice;
	UPROPERTY()
		UCanvasPanel * m_SaveOrderPanel;
	UPROPERTY()
		UButton * m_SaveOrderButton;
	UPROPERTY()
		UButton * m_CommitOrderButton;
	UPROPERTY()
	UTextBlock * m_CommitButtonText;

    UFUNCTION()
        void OnButtonClick(int _index);

	void SetPrice(int num);

	void OnCommitCurrentOrder(msg_ptr _msg);

private:
	int		allPriceI;
};
