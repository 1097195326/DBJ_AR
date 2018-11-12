#include "GoodsList_Icon.h"
#include "UserPawn.h"
#include "UIManager.h"

void UGoodsList_Icon::On_Init()
{
    if (UButton * button = (UButton*)GetWidgetFromName("IconButton"))
    {
        m_SelectButton = button;
		UI_M->RegisterButton(1, m_SelectButton, this, &UGoodsList_Icon::OnButtonClick);
    }
	if (UButton * button = (UButton*)GetWidgetFromName("DownButton"))
	{
		m_DownloadButton = button;
		UI_M->RegisterButton(2, m_DownloadButton, this, &UGoodsList_Icon::OnButtonClick);
	}
	if (UImage * image = (UImage*)GetWidgetFromName("IconImage"))
	{
		m_Image = image;	
	}
    
    if (UProgressBar * bar = (UProgressBar*)GetWidgetFromName("downloadingProgress"))
    {
        m_downloadingProgress = bar;
    }
    if (UImage * image = (UImage*)GetWidgetFromName("DownOKImage"))
    {
        m_DownOKImage = image;
    }
	if (UNativeWidgetHost * host = (UNativeWidgetHost*)GetWidgetFromName("ImageHost"))
	{
		m_ImageHost = host;
	}
	if (UTextBlock * text = (UTextBlock*)GetWidgetFromName("IconName"))
	{
		m_IconName = text;
	}
    
    
}
void UGoodsList_Icon::On_Delete()
{
	UI_M->UnRegisterButton(m_SelectButton);
	UI_M->UnRegisterButton(m_DownloadButton);

}
void UGoodsList_Icon::On_Tick(float delta)
{
    if(m_IsDowning)
    {
        int progess = UFileDownloadManager::Get()->GetDownloadProgress(m_Data->modelId);
        UE_LOG(LogTemp,Log,TEXT("zhx : pregess : %d"),progess);
        
        float pbar = progess / 100.0f;
        m_downloadingProgress->SetPercent(pbar);
    }
}
void UGoodsList_Icon::OnButtonClick(int index)
{
    if (m_IsDowning)
    {
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("zhx : UGoodsList_Icon::OnButtonClick : "));
	switch (index)
	{
	case 1:
	{
        m_ParentUI->RemoveFromParent();
        
        if (!m_PakInfo.GamePath.IsEmpty())
        {
			AUserPawn::GetInstance()->TryCreateARActor(m_PakInfo);
        }
	}break;
	case 2:
	{
		FFileInfo info;
		info.Id = m_Data->modelId;
		info.FileSize = m_Data->pakSize;
		info.Url = m_Data->pakUrl;
		info.Md5 = m_Data->pakMd5;
		if (UFileDownloadManager::Get()->RequestDownloadFile(info))
		{
			m_IsDowning = true;
			m_downloadingProgress->SetVisibility(ESlateVisibility::Visible);
			UFileDownloadManager::Get()->OnFileDownloadCompleted().AddUObject(this, &UGoodsList_Icon::OnGetPakFinish);
		}
	}break;
	default:
		break;
	}
}
void UGoodsList_Icon::OnGetPakFinish(int _finish, FFileInfo _info)
{
	UE_LOG(LogTemp, Log, TEXT("zhx : UGoodsList_Icon::OnGetPakFinish : "));
	m_IsDowning = false;
	m_downloadingProgress->SetVisibility(ESlateVisibility::Hidden);
	if (_finish == 0 && _info.Id == m_Data->modelId && GFileManager::GetInstance()->FileIsExist(m_Data->modelId, m_Data->pakMd5))
	{
		m_DownloadButton->SetVisibility(ESlateVisibility::Hidden);
		m_DownOKImage->SetVisibility(ESlateVisibility::Visible);
		m_PakInfo = GFileManager::GetInstance()->PakMount(m_Data->modelId, m_Data->pakMd5);
	}
	else
	{
		m_DownloadButton->SetVisibility(ESlateVisibility::Visible);
		m_DownOKImage->SetVisibility(ESlateVisibility::Hidden);
	}


}
void UGoodsList_Icon::SetParentUI(UBaseUI * _ui)
{
	m_ParentUI = _ui;
}
void UGoodsList_Icon::SetData(GoodsData * _data)
{
	m_Data = _data;
	
	m_ImageHost->SetContent(SNew(SImage).Image(UFileDownloadManager::Get()->m_ImageCache.Download(*m_Data->thumbnailUrl)->Attr()));
	m_IconName->SetText(FText::FromString(m_Data->name));
    
    if(GFileManager::GetInstance()->FileIsExist(m_Data->modelId,m_Data->pakMd5))
    {
		m_DownloadButton->SetVisibility(ESlateVisibility::Hidden);
		m_DownOKImage->SetVisibility(ESlateVisibility::Visible);
		m_PakInfo = GFileManager::GetInstance()->PakMount(m_Data->modelId, m_Data->pakMd5);
	}
	else
	{
		m_DownloadButton->SetVisibility(ESlateVisibility::Visible);
		m_DownOKImage->SetVisibility(ESlateVisibility::Hidden);
	}
	m_downloadingProgress->SetVisibility(ESlateVisibility::Hidden);

    
}
