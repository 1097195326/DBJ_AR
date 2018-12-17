#include "GCore.h"
#include "BaseUI.h"


UBaseUI::UBaseUI(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	//

}

bool UBaseUI::Initialize()
{
	if (!Super::Initialize())
	{
		
		return false;
	}
	On_Init();
	return true;
}
void UBaseUI::NativeConstruct()
{
	Super::NativeConstruct();

	On_Start();
}
void UBaseUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	On_Tick(InDeltaTime);
}
void UBaseUI::NativeDestruct()
{
	Super::NativeDestruct();
	On_Delete();
}
//FReply UBaseUI::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
//{
//	On_FocusReceived();
//	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
//}
//void UBaseUI::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
//{
//	On_FocusLost();
//	Super::NativeOnFocusLost(InFocusEvent);
//}

void UBaseUI::On_Init()
{

}
void UBaseUI::On_Tick(float delta)
{

}
void UBaseUI::On_Delete()
{

}
//void UBaseUI::On_FocusReceived()
//{
//
//}
//void UBaseUI::On_FocusLost()
//{
//
//}
void UBaseUI::SetParentUI(UBaseUI * _ui)
{
	m_ParentUI = _ui;
}