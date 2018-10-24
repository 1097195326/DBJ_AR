#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UpdateGameMode.generated.h"

UCLASS()
class DBJ_AR_API AUpdateGameMode : public AGameModeBase
{
	GENERATED_BODY()
private:
	FVector    m_TargetLocation;
public:
	AUpdateGameMode();

};