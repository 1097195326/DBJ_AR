#pragma once

#include "GAppInstance.h"
#include "AppCore/Managers/ManagerHeader.h"
#include "AppInstance.generated.h"

UCLASS()
class DBJ_AR_API UAppInstance : public UGAppInstance
{
	GENERATED_BODY()
	
public:
	UAppInstance();

	virtual void On_Init() override;

};
