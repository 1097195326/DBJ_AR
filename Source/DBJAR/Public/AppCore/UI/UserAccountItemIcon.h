#pragma once
#include "BaseUI.h"
#include "UserAccountItemIcon.generated.h"


UCLASS()
class DBJAR_API  UUserAccountItemIcon : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;

	UPROPERTY()
    UNativeWidgetHost * m_ShowImage;

	void SetImageUrl(FString _url);
};
