#pragma once
#include "BaseUI.h"
#include "GoodsFilterItem.h"
#include "MsgCenter.h"
#include "GoodsFilterUI.generated.h"


UCLASS()
class DBJAR_API  UGoodsFilterUI : public UBaseUI
{
	GENERATED_BODY()

public:
	virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Delete() override;

	UPROPERTY()
		UVerticalBox * m_ViewVerticalBox;
    UPROPERTY()
    UButton * m_BackButton;
	UPROPERTY()
		UButton * m_CancelButton;
	UPROPERTY()
	UButton * m_SureButton;
	
	void OnButtonClick(int _index);

	void	OnGetInnerDiameters(msg_ptr _msg);
	void	OnGetMaterials(msg_ptr _msg);
	void	OnGetGoodsType(msg_ptr _msg);

	void	InitView();

	int			m_TypeIndex;
	int			m_InnerIndex;
	int			m_MaterialIndex;

	void	ReviewByType(int type);
private:
	TArray<IdData> m_TypeData;
	TArray<IdData> m_InnerData;
	TArray<IdData> m_MaterialData;
	UPROPERTY()
	UGoodsFilterItem * m_TypeItem;
	UPROPERTY()
	UGoodsFilterItem * m_MaterialItem;
	UPROPERTY()
	UGoodsFilterItem * m_InnerItem;

	int		m_ReceiveNum;
};
