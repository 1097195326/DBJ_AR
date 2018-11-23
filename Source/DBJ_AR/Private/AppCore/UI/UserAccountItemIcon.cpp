#include "UserAccountItemIcon.h"




void UUserAccountItemIcon::On_Init()
{
	if (UImage * widget = (UImage*)GetWidgetFromName("ShowImage"))
	{
		m_ShowImage = widget;
	}


}
void UUserAccountItemIcon::SetImageUrl(FString _url)
{
	UE_LOG(LogTemp, Log, TEXT("zhx : UUserAccountItemIcon::SetImageUrl : "));

}
