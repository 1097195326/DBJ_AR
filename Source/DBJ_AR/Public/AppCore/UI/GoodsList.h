#pragma once

#include "BaseUI.h"
#include "GoodsListButton.h"
#include "MsgCenter.h"
#include "GoodsList_Icon.h"
#include "GoodsList.generated.h"


UCLASS()
class DBJ_AR_API  UGoodsList : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;
    virtual void On_Start() override;
	virtual void On_Tick(float delta) override;
	virtual void On_Delete() override;

	void InitView();
	void OnGetProductList(msg_ptr _msg);
	void SelectCategoryButton(int _id);
	void ReloadData(bool _clear = false);
    void OnButtonClick(int _index);

	int			m_TypeIndex;
	int			m_InnerIndex;
	int			m_MaterialIndex;
private:
	UButton * m_BackButton;
	UButton * m_FilterButton;
	UScrollBox * m_IconScrolBox;
	UGridPanel * m_IconList;
	UVerticalBox * m_CategoryView;
	TArray<UGoodsListButton*>		m_ListButtons;
	TArray<UGoodsList_Icon*>		m_IconArray;
	int			m_CurrentSelectId;
	int32		m_LastId;

	bool		m_IsRequest;

	

};
