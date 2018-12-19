#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UpdateGameMode.generated.h"

UCLASS()
class DBJAR_API AUpdateGameMode : public AGameModeBase
{
	GENERATED_BODY()
private:
	FVector    m_TargetLocation;
public:
	AUpdateGameMode();

};
