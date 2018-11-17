#pragma once

#include "BaseUI.h"
#include "GoodsList_Icon.h"
#include "MsgCenter.h"
#include "GoodsChangeUI.generated.h"


UCLASS()
class DBJ_AR_API  UGoodsChangeUI : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;
	virtual void On_Delete() override;

	UButton *	m_BackButton;
    UButton *	m_CancelButton;
	UButton *	m_SureButton;
	UScrollBox * m_ScrollBox;
	UGridPanel * m_GridPanel;

    void OnButtonClick(int id);

	void OnGetChangeList(msg_ptr _msg);

	void SelectChangeIcon(UGoodsList_Icon * _icon);

	//void SetData(int _id,FString _path);
private:
	TArray<UGoodsList_Icon*>	m_GoodsListIcons;

	GoodsData * m_CurrentGoodsData;

	int		m_ProductId;
	/*FString		m_ModelGamePath;*/
};
