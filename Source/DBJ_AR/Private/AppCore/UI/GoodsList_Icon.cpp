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
void UGoodsList_Icon::OnButtonClick(int index)
{
	/*if (m_IsDowning)
	{
		return;
	}*/

    UE_LOG(LogTemp, Log, TEXT("zhx : UGoodsList_Icon::OnButtonClick : "));
	switch (index)
	{
	case 1:
	{
        m_ParentUI->RemoveFromParent();
        m_PakInfo = GFileManager::GetInstance()->PakMount(m_Data->modelId, m_Data->pakMd5);
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
	if (_finish == 0 && _info.Id == m_Data->modelId)
	{
		m_PakInfo = GFileManager::GetInstance()->PakMount(m_Data->modelId, m_Data->pakMd5);

	}


}
void UGoodsList_Icon::SetParentUI(UBaseUI * _ui)
{
	m_ParentUI = _ui;
}
void UGoodsList_Icon::SetData(GoodsData * _data)
{
	m_Data = _data;
	
	//m_Image->SetBrush(*(UFileDownloadManager::Get()->m_ImageCache.Download(*m_Data->thumbnailUrl)->GetBrush()));
	m_ImageHost->SetContent(SNew(SImage).Image(UFileDownloadManager::Get()->m_ImageCache.Download(*m_Data->thumbnailUrl)->Attr()));
	m_IconName->SetText(FText::FromString(m_Data->name));
}
