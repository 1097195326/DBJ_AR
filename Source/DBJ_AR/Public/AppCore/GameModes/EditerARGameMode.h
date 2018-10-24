#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EditerARGameMode.generated.h"

UCLASS()
class DBJ_AR_API AEditerARGameMode : public AGameModeBase
{
	GENERATED_BODY()
private:
	FVector    m_TargetLocation;
public:
	AEditerARGameMode();

};