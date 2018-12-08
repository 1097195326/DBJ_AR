#include "GoodsList_Icon.h"
#include "UserPawn.h"
#include "UIManager.h"
#include "GoodsChangeUI.h"
#include "UserInfo.h"
#include "AppInstance.h"


bool UGoodsList_Icon::CanDownPak = true;

void UGoodsList_Icon::On_Init()
{
    if (UButton * button = (UButton*)GetWidgetFromName("IconButton"))
    {
		m_IconButton = button;
		UI_M->RegisterButton(1, m_IconButton, this, &UGoodsList_Icon::OnButtonClick);
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
	if (UImage * image = (UImage*)GetWidgetFromName("SelectIcon"))
	{
		m_SelectIcon = image;
	}
	if (UNativeWidgetHost * host = (UNativeWidgetHost*)GetWidgetFromName("ImageHost"))
	{
		m_ImageHost = host;
	}
	if (UTextBlock * text = (UTextBlock*)GetWidgetFromName("IconName"))
	{
		m_IconName = text;
	}
    
	m_DownIndex = 0;
}
void UGoodsList_Icon::On_Delete()
{
	UI_M->UnRegisterButton(m_IconButton);
	UI_M->UnRegisterButton(m_DownloadButton);

}
void UGoodsList_Icon::On_Tick(float delta)
{
    if(m_IsDowning)
    {
        int progess = UFileDownloadManager::Get()->GetDownloadProgress(m_DownFiles[m_DownIndex].Id);
        //UE_LOG(LogTemp,Log,TEXT("zhx : pregess : %d"),progess);
        
        float pbar = (100 * m_DownIndex + progess) / (100.0f * m_DownFiles.Num());
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
        if (m_Data->m_FilePathList.Num() > 0)
        {
			if (m_IsChange)
			{
				UGoodsChangeUI * changeUI = (UGoodsChangeUI *)m_ParentUI;
				changeUI->SelectChangeIcon(this);
			}
			else
			{
				m_ParentUI->RemoveFromViewport();
				AUserPawn::GetInstance()->TryCreateMergeActor(m_Data);
			}
        }
	}break;
	case 2:
	{
		if (UAppInstance::GetInstance()->GetNetworkStatus() == ENotReachable)
		{
			UIManager::GetInstance()->TopHintText(TEXT("没有网络"));
			break;
		}
		if (UAppInstance::GetInstance()->GetNetworkStatus() == EReachableViaWWAN)
		{
			if (!UserInfo::Get()->IsAllow4G())
			{
				UIManager::GetInstance()->TopHintText(TEXT("请在设置中打开4G下载"));
				break;
			}
		}
		if (CanDownPak)
		{
			GetDownFiles();
			m_downloadingProgress->SetVisibility(ESlateVisibility::Visible);
			m_DelegateHandle = UFileDownloadManager::Get()->OnFileDownloadCompleted().AddUObject(this, &UGoodsList_Icon::OnGetPakFinish);
			DownFiles(m_DownIndex);
		}
		else
		{
			UIManager::GetInstance()->TopHintText(TEXT("正在下载中..."));
		}
	}break;
	default:
		break;
	}
}
void UGoodsList_Icon::DownFiles(int _index)
{
	if (CanDownPak)
	{
		if (m_DownIndex >= m_DownFiles.Num())
		{
			return;
		}
		if (UFileDownloadManager::Get()->RequestDownloadFile(m_DownFiles[_index]))
		{
			CanDownPak = false;
			m_IsDowning = true;
			
		}
	}
}
void UGoodsList_Icon::OnGetPakFinish(int _finish, FFileInfo _info)
{
	UE_LOG(LogTemp, Log, TEXT("zhx : UGoodsList_Icon::OnGetPakFinish : %d"),m_DownIndex);
	m_IsDowning = false;
	CanDownPak = true;
	if (_finish == 0 && _info.Id == m_DownFiles[m_DownIndex].Id &&
		GFileManager::GetInstance()->FileIsExist(m_DownFiles[m_DownIndex].Id, m_DownFiles[m_DownIndex].Md5))
	{
		++m_DownIndex;
		if (m_DownIndex < m_DownFiles.Num())
		{
			DownFiles(m_DownIndex);
			return;
		}
		
		m_DownIndex = 0;
		m_downloadingProgress->SetVisibility(ESlateVisibility::Hidden);

		UFileDownloadManager::Get()->OnFileDownloadCompleted().Remove(m_DelegateHandle);
		m_DownloadButton->SetVisibility(ESlateVisibility::Hidden);
		m_DownOKImage->SetVisibility(ESlateVisibility::Visible);
		GFileManager::GetInstance()->PakMount(m_Data);
		if (m_Data->matchedProduct != nullptr)
		{
			GFileManager::GetInstance()->PakMount(m_Data->matchedProduct);
		}
	}
	else
	{
		m_DownloadButton->SetVisibility(ESlateVisibility::Visible);
		m_DownOKImage->SetVisibility(ESlateVisibility::Hidden);
	}


}
void UGoodsList_Icon::GetDownFiles()
{
	m_DownFiles.Empty();
	m_DownIndex = 0;

	FFileInfo info;
	info.Id = m_Data->modelId;
	info.FileSize = m_Data->pakSize;
	info.Url = m_Data->pakUrl;
	info.Md5 = m_Data->pakMd5;

	if (!GFileManager::GetInstance()->FileIsExist(info.Id, info.Md5))
	{
		m_DownFiles.Add(info);
	}
	if (m_Data->matchedProduct != nullptr)
	{
		FFileInfo maInfo;
		maInfo.Id = m_Data->matchedProduct->modelId;
		maInfo.FileSize = m_Data->matchedProduct->pakSize;
		maInfo.Url = m_Data->matchedProduct->pakUrl;
		maInfo.Md5 = m_Data->matchedProduct->pakMd5;
		
		if (!GFileManager::GetInstance()->FileIsExist(maInfo.Id, maInfo.Md5))
		{
			m_DownFiles.Add(maInfo);
		}
	}
}
void UGoodsList_Icon::SetData(GoodsData * _data,bool _isChange)
{
	m_Data = _data;
	m_IsChange = _isChange;

    //UE_LOG(LogTemp,Log,TEXT("zhx : set data name : %s,url:%s"),*m_Data->name,*m_Data->thumbnailUrl);

	m_ImageHost->SetContent(SNew(SImage).Image(UFileDownloadManager::Get()->m_ImageCache.Download(*m_Data->thumbnailUrl)->Attr()));
	m_IconName->SetText(FText::FromString(m_Data->name));
    
    if(GFileManager::GetInstance()->FileIsExist(m_Data))
    {
        m_DownloadButton->SetVisibility(ESlateVisibility::Hidden);
        m_DownOKImage->SetVisibility(ESlateVisibility::Visible);
        GFileManager::GetInstance()->PakMount(m_Data);
		if (m_Data->matchedProduct != nullptr)
		{
			GFileManager::GetInstance()->PakMount(m_Data->matchedProduct);
		}
    }
    else
    {
        m_DownloadButton->SetVisibility(ESlateVisibility::Visible);
        m_DownOKImage->SetVisibility(ESlateVisibility::Hidden);
    }
    m_downloadingProgress->SetVisibility(ESlateVisibility::Hidden);
	if (m_SelectIcon)
	{
		m_SelectIcon->SetVisibility(ESlateVisibility::Hidden);
	}
}
void UGoodsList_Icon::ShowSelectIcon(bool _isSelect)
{
	if (_isSelect)
	{
		m_SelectIcon->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		m_SelectIcon->SetVisibility(ESlateVisibility::Hidden);
	}
}
