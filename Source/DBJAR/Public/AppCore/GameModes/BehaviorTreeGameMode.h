//
//  BehaviorTreeGameMode.h
//  GameFrame_Index
//
//  Created by fafa on 2018/8/9.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/GameModeBase.h"
#include "BehaviorTreeGameMode.generated.h"

UCLASS()
class DBJAR_API ABehaviorTreeGameMode : public AGameModeBase
{
    GENERATED_BODY()
private:
    FVector    m_TargetLocation;
public:
    ABehaviorTreeGameMode();
    
    UFUNCTION(BlueprintCallable)
    void    SetTargetLocation(FVector targetLocation);
};
