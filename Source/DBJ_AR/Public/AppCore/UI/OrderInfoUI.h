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
	OrderInfoData m_Data;
	int m_Num;
public:
    virtual void On_Init() override;
	virtual void On_Delete() override;

	UNativeWidgetHost * m_Icon;
	UTextBlock * m_GoodsName;
	UTextBlock * m_GoodsBorder;
	UTextBlock * m_CompanyName;
	UTextBlock * m_GoodsPrice;
	UTextBlock * m_GoodsNum;
	UButton * m_SubButton;
	UButton * m_AddButton;

	void SetData(OrderInfoData _data);
	void ResetNum();

       void OnButtonClick(int _index);
};
