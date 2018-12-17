#pragma once
#include "BaseUI.h"
#include "ToolButton.h"
#include "GoodsFilterItem.generated.h"


UCLASS()
class DBJ_AR_API  UGoodsFilterItem : public UBaseUI,public SelectButtonDelegate
{
	GENERATED_BODY()

public:
	virtual void On_Init() override;

	UPROPERTY()
		UTextBlock * m_TitleName;
	UPROPERTY()
	UGridPanel * m_ContentGridPanel;

	void SetData(const int & _type, const TArray<IdData> & _data,int _index);
	void SelectButton(UToolButton * _button);
	void SelectButton(int _index);

private:
	TArray<IdData> m_Data;
	int		m_type;

	UToolButton * m_SelectButton;
	int	m_SelectIndex;
	UPROPERTY()
	TArray<UToolButton*> m_Buttons;
};
