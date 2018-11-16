#pragma once

#include "BaseUI.h"
#include "GoodsListButton.h"
#include "MsgCenter.h"
#include "GoodsList.generated.h"


UCLASS()
class DBJ_AR_API  UGoodsList : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;
    virtual void On_Start() override;
	virtual void On_Delete() override;

	void InitView();

	void OnGetProductList(msg_ptr _msg);

	void SelectCategoryButton(int _id);

    UFUNCTION()
        void OnButtonClick();
private:
	UButton * m_BackButton;
	UScrollBox * m_IconScrolBox;
	UGridPanel * m_IconList;
	UVerticalBox * m_CategoryView;
	TArray<UGoodsListButton*>		m_ListButtons;
};
