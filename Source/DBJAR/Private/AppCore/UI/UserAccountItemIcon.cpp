#include "UserAccountItemIcon.h"
#include "FileDownloadManager.h"



void UUserAccountItemIcon::On_Init()
{
	if (UNativeWidgetHost * widget = (UNativeWidgetHost*)GetWidgetFromName("ShowImage"))
	{
		m_ShowImage = widget;
	}

}
void UUserAccountItemIcon::SetImageUrl(FString _url)
{
	UE_LOG(LogTemp, Log, TEXT("zhx : UUserAccountItemIcon::SetImageUrl : "));
	m_ShowImage->SetContent(SNew(SImage).Image(UFileDownloadManager::Get()->m_ImageCache.Download(*_url)->Attr()));

}
