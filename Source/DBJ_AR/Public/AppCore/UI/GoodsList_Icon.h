#pragma once

#include "BaseUI.h"
#include "GoodsData.h"
#include "FileDownloadManager.h"
#include "GFileManager.h"
#include "GoodsList_Icon.generated.h"


UCLASS()
class DBJ_AR_API  UGoodsList_Icon : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;
	virtual void On_Delete() override;
    virtual void On_Tick(float delta);

	void	SetData(GoodsData * _data);
	void	SetParentUI(UBaseUI * _ui);

	UFUNCTION()
		void OnButtonClick(int index);
	//UFUNCTION()
		void OnGetPakFinish(int _finish, FFileInfo _info);
private:
    UButton *	m_SelectButton;
	UButton	*	m_DownloadButton;
	UImage	*	m_Image;
    UImage  *   m_DownOKImage;
	UTextBlock * m_IconName;
	UNativeWidgetHost * m_ImageHost;
    UProgressBar * m_downloadingProgress;
    
	GoodsData * m_Data;

	bool m_IsDowning;

	UBaseUI * m_ParentUI;
};
