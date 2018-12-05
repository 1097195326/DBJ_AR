#pragma once
#include "BaseUI.h"
#include "RuntimeRDataManager.h"
#include "UserAccountItem.generated.h"


UCLASS()
class DBJ_AR_API  UUserAccountItem : public UBaseUI
{
	GENERATED_BODY()

public:
	virtual void On_Init() override;

	UButton *	m_EditerOrderButton;
	UTextBlock * m_CompanyName;
	UTextBlock * m_StatusText;
	UScrollBox * m_IconListScroll;
	UTextBlock * m_CommitTime;
	UTextBlock * m_AllPrice;
	UTextBlock * m_AllNum;
	UImage *	m_WeiTijiaoImage;
	UImage *	m_YiTijiaoImage;

	UFUNCTION()
		void OnButtonClick();

	void		SetOrder(R_Order * order);
	void		ReView();
private:
	R_Order * m_Order;

};
