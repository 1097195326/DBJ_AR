#include "GoodsList_Icon.h"
#include "FileDownloadManager.h"


void UGoodsList_Icon::On_Init()
{
    if (UButton * button = (UButton*)GetWidgetFromName("IconButton"))
    {
        m_SelectButton = button;
		m_SelectButton->OnClicked.AddDynamic(this, &UGoodsList_Icon::OnButtonClick);
    }
	if (UButton * button = (UButton*)GetWidgetFromName("DownButton"))
	{
		m_DownloadButton = button;
		m_DownloadButton->OnClicked.AddDynamic(this, &UGoodsList_Icon::OnButtonClick);
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
void UGoodsList_Icon::OnButtonClick()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIB::OnButtonClick : "));

}
void UGoodsList_Icon::SetData(GoodsData * _data)
{
	m_Data = _data;
	
	//m_Image->SetBrush(*(UFileDownloadManager::Get()->m_ImageCache.Download(*m_Data->thumbnailUrl)->GetBrush()));
	m_ImageHost->SetContent(SNew(SImage).Image(UFileDownloadManager::Get()->m_ImageCache.Download(*m_Data->thumbnailUrl)->Attr()));
	m_IconName->SetText(FText::FromString(m_Data->name));
}
