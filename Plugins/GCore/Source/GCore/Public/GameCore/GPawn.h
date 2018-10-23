//
//  GPawn.h
//  GameFrame_Index
//
//  Created by fafa on 2018/8/9.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "GObject.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GPawn.generated.h"

UCLASS()
class GCORE_API AGPawn : public APawn, public GObject
{
    GENERATED_BODY()
    
public:
	// feng zhuang APawn ,override AActor Functions 
	virtual void PostInitializeComponents();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:

};

