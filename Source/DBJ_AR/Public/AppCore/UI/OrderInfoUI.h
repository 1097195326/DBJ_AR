#pragma once

#include "BaseUI.h"
#include "GoodsData.h"
#include "RuntimeRDataManager.h"
#include "OrderInfoUI.generated.h"


UCLASS()
class DBJ_AR_API  UOrderInfoUI : public UBaseUI
{
    GENERATED_BODY()

private:
	GoodsData * m_Data;
	int m_Num;
public:
    virtual void On_Init() override;
	virtual void On_Delete() override;

	UPROPERTY()
		UNativeWidgetHost * m_Icon;
	UPROPERTY()
		UTextBlock * m_GoodsName;
	UPROPERTY()
		UTextBlock * m_GoodsBorder;
	UPROPERTY()
		UTextBlock * m_CompanyName;
	UPROPERTY()
		UTextBlock * m_GoodsPrice;
	UPROPERTY()
		UTextBlock * m_GoodsNum;
	UPROPERTY()
		UButton * m_SubButton;
	UPROPERTY()
	UButton * m_AddButton;

	void SetData(GoodsData * _data);
	GoodsData * GetData();

	void ResetNum();

       void OnButtonClick(int _index);
};
