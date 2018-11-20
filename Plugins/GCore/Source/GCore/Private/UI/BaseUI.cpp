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
void UBaseUI::On_Init()
{

}
void UBaseUI::On_Tick(float delta)
{

}
void UBaseUI::On_Delete()
{

}
void UBaseUI::SetParentUI(UBaseUI * _ui)
{
	m_ParentUI = _ui;
}