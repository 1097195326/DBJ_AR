#pragma once

#include "GObject.h"
#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"  
#include "Runtime/UMG/Public/UMGStyle.h"  
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"  
#include "Runtime/UMG/Public/IUMGModule.h"

#include "BaseUI.generated.h"

UCLASS()
class GCORE_API UBaseUI : public UUserWidget, public GObject
{
	GENERATED_UCLASS_BODY()

	//
public:

	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeDestruct() override;

public:
	virtual void On_Init() override;
	virtual void On_Tick(float delta) override;
	virtual void On_Delete() override;


};