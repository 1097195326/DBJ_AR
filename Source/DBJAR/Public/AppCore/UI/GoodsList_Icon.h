#pragma once

#include "BaseUI.h"
#include "GoodsData.h"
#include "FileDownloadManager.h"
#include "GFileManager.h"
#include "GoodsList_Icon.generated.h"

UCLASS()
class DBJAR_API  UGoodsList_Icon : public UBaseUI
{
    GENERATED_BODY()

public:
	virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Delete() override;
    virtual void On_Tick(float delta);

	void	SetData(GoodsData * _data, bool _isChange = false);
	GoodsData * GetData() { return m_Data; }
	void	ShowSelectIcon(bool _isSelect);

	UFUNCTION()
		void OnButtonClick(int index);
	//UFUNCTION()
		void OnGetPakFinish(int _finish, FFileInfo _info);
		void CheckPak();


		static bool CanDownPak;

private:
	UPROPERTY()
    UButton *	m_IconButton;
	UPROPERTY()
	UButton	*	m_DownloadButton;
	UPROPERTY()
	UImage	*	m_Image;
	UPROPERTY()
    UImage  *   m_DownOKImage;
	UPROPERTY()
	UImage  *   m_SelectIcon;
	UPROPERTY()
	UTextBlock * m_IconName;
	UPROPERTY()
	UNativeWidgetHost * m_ImageHost;
	UPROPERTY()
    UProgressBar * m_downloadingProgress;
    
	GoodsData * m_Data;
	bool		m_IsChange;

	bool m_IsDowning;
	FDelegateHandle m_DelegateHandle;

	TArray<FFileInfo>	m_DownFiles;
	int		m_DownIndex;
	bool GetDownFiles();
	void DownFiles(int _index);
};
