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
	virtual void On_Start() override;
	virtual void On_Tick(float delta) override;
	virtual void On_Delete() override;

	UPROPERTY()
		UButton *	m_BackButton;
	UPROPERTY()
		UButton *	m_CancelButton;
	UPROPERTY()
		UButton *	m_SureButton;
	UPROPERTY()
		UScrollBox * m_ScrollBox;
	UPROPERTY()
	UGridPanel * m_GridPanel;

    void OnButtonClick(int id);

	void OnGetChangeList(msg_ptr _msg);

	void SelectChangeIcon(UGoodsList_Icon * _icon);

	void ReloadData();

	//void SetData(int _id,FString _path);
private:
	UPROPERTY()
	TArray<UGoodsList_Icon*>	m_GoodsListIcons;

	GoodsData * m_CurrentGoodsData;

	int		m_ProductId;
	/*FString		m_ModelGamePath;*/
	int32		m_LastId;
	bool		m_IsRequest;
};
