#pragma once

#include "BaseUI.h"
#include "GoodsListButton.h"
#include "MsgCenter.h"
#include "GoodsList_Icon.h"
#include "GoodsList.generated.h"


UCLASS()
class DBJAR_API  UGoodsList : public UBaseUI
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
	UPROPERTY()
		UButton * m_BackButton;
	UPROPERTY()
		UButton * m_FilterButton;
	UPROPERTY()
		UScrollBox * m_IconScrolBox;
	UPROPERTY()
		UGridPanel * m_IconList;
	UPROPERTY()
		UVerticalBox * m_CategoryView;
	UPROPERTY()
		TArray<UGoodsListButton*>		m_ListButtons;
	UPROPERTY()
	TArray<UGoodsList_Icon*>		m_IconArray;
	int			m_CurrentSelectId;
	int32		m_LastId;

	bool		m_IsRequest;

	

};
