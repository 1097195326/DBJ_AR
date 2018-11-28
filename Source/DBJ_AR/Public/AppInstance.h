#pragma once

#include "GAppInstance.h"
#include "AppCore/Managers/DataManager.h"
#include "Misc/CoreDelegates.h"
#include "AppInstance.generated.h"

UCLASS()
class DBJ_AR_API UAppInstance : public UGAppInstance
{
	GENERATED_BODY()
	
public:
	UAppInstance();

	virtual void On_Init() override;
	virtual void OpenLevel(const FString & _levelName) override;

	void ApplicationWillEnterBackground();
	void ApplicationHasEnteredForeground();

	UFUNCTION(Exec)
		void PakMount();
};
