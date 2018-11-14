#pragma once

#include "BaseUI.h"
#include "GoodsListButton.h"
#include "GoodsList.generated.h"


UCLASS()
class DBJ_AR_API  UGoodsList : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;

	void InitView();

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
