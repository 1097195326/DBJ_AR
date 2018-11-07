#pragma once

#include "BaseUI.h"
#include "GoodsData.h"
#include "FileDownloadManager.h"
#include "GoodsList_Icon.generated.h"


UCLASS()
class DBJ_AR_API  UGoodsList_Icon : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;
	virtual void On_Delete() override;

	void	SetData(GoodsData * _data);

	UFUNCTION()
		void OnButtonClick(int index);
	//UFUNCTION()
		void OnGetPakFinish(int _finish, FFileInfo _info);
private:
    UButton *	m_SelectButton;
	UButton	*	m_DownloadButton;
	UImage	*	m_Image;
	UTextBlock * m_IconName;
	UNativeWidgetHost * m_ImageHost;
	GoodsData * m_Data;
    
	bool m_IsDowning;
};
