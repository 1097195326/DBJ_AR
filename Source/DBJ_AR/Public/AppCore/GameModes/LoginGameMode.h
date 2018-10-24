#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "LoginGameMode.generated.h"

UCLASS()
class DBJ_AR_API ALoginGameMode : public AGameModeBase
{
	GENERATED_BODY()
private:
	
public:
	ALoginGameMode();

	virtual void StartPlay()override;

	

};