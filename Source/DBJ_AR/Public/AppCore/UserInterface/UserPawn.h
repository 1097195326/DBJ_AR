//
//  UserPawn.h
//  GameFrame_Index
//
//  Created by fafa on 2018/8/14.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "GPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "UserPawn.generated.h"


UCLASS()
class DBJ_AR_API AUserPawn : public AGPawn
{
    GENERATED_BODY()
public:
    AUserPawn(const FObjectInitializer& ObjectInitializer);

    virtual void On_Init() override;
private:
    
    UPROPERTY(VisibleAnywhere)
    UCameraComponent * m_Camera;
    
public:
    
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    //PC
    void OneFingerPress();
    // mobile
    void OnFingerTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
};
