#pragma once
#include "BaseUI.h"
#include "GoodsFilterItem.h"
#include "MsgCenter.h"
#include "GoodsFilterUI.generated.h"


UCLASS()
class DBJ_AR_API  UGoodsFilterUI : public UBaseUI
{
	GENERATED_BODY()

public:
	virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Delete() override;

	UVerticalBox * m_ViewVerticalBox;
	UButton * m_CancelButton;
	UButton * m_SureButton;
	
	void OnButtonClick(int _index);

	void	OnGetInnerDiameters(msg_ptr _msg);
	void	OnGetMaterials(msg_ptr _msg);
	void	OnGetGoodsType(msg_ptr _msg);

	void	InitView();

	int			m_TypeIndex;
	int			m_InnerIndex;
	int			m_MaterialIndex;
private:
	TArray<IdData> m_TypeData;
	TArray<IdData> m_InnerData;
	TArray<IdData> m_MaterialData;

	int		m_ReceiveNum;
};
