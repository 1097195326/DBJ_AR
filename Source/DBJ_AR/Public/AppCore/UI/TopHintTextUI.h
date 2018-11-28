#pragma once

#include "BaseUI.h"
#include "Engine/World.h"
#include "TopHintTextUI.generated.h"


UCLASS()
class DBJ_AR_API  UTopHintTextUI : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;

    UVerticalBox * m_ShowTextView;

	void	InitText(const FString & hintText, float showSecond);

    UFUNCTION()
        void OnTimerUpdate();
private:
	FTimerHandle m_TimerHandle;
	bool		m_IsUpdate;
	float		m_ShowTime;
};
