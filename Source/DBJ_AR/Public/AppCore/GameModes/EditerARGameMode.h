#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EditerARGameMode.generated.h"

UCLASS()
class DBJ_AR_API AEditerARGameMode : public AGameModeBase
{
	GENERATED_BODY()
private:
	
public:
	AEditerARGameMode();

	virtual void StartPlay()override;
};
