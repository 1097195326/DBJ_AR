#pragma once

#include "GAppInstance.h"
#include "AppCore/Managers/DataManager.h"
#include "AppInstance.generated.h"

UCLASS()
class DBJ_AR_API UAppInstance : public UGAppInstance
{
	GENERATED_BODY()
	
public:
	UAppInstance();

	virtual void On_Init() override;
	virtual void OpenLevel(const FString & _levelName) override;

	UFUNCTION(Exec)
		void PakMount();
};
