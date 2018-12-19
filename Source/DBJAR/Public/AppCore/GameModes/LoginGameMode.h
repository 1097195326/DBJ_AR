#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "LoginGameMode.generated.h"

UCLASS()
class DBJAR_API ALoginGameMode : public AGameModeBase
{
	GENERATED_BODY()
private:
	
public:
	ALoginGameMode();

	virtual void StartPlay()override;

	
	

};
