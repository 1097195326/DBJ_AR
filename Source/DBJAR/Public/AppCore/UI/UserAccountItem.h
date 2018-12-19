#pragma once
#include "BaseUI.h"
#include "RuntimeRDataManager.h"
#include "UserAccountItem.generated.h"


UCLASS()
class DBJAR_API  UUserAccountItem : public UBaseUI
{
	GENERATED_BODY()

public:
	virtual void On_Init() override;

	UPROPERTY()
		UButton *	m_EditerOrderButton;
	UPROPERTY()
		UTextBlock * m_CompanyName;
	UPROPERTY()
		UTextBlock * m_StatusText;
	UPROPERTY()
		UScrollBox * m_IconListScroll;
	UPROPERTY()
		UTextBlock * m_CommitTime;
	UPROPERTY()
		UTextBlock * m_AllPrice;
	UPROPERTY()
		UTextBlock * m_AllNum;
	UPROPERTY()
		UImage *	m_WeiTijiaoImage;
	UPROPERTY()
		UImage *	m_YiTijiaoImage;
	UFUNCTION()
		void OnButtonClick();

	void		SetOrder(R_Order * order);
	void		ReView();
private:
	R_Order * m_Order;

};
