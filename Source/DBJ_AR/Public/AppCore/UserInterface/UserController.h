//
//  UserController.h
//  GameFrame_Index
//
//  Created by fafa on 2018/8/14.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

#pragma once


#include "GameController.h"
#include "ScreenshotComponent.h"
#include "UserController.generated.h"
//
UCLASS()
class DBJ_AR_API AUserController : public AGameController
{
    GENERATED_BODY()
public:
	

	static AUserController * GetInstance();

    virtual void On_Init() override;
    virtual void On_Start() override;
    virtual void On_Tick(float DeltaSeconds) override;
    virtual void On_Delete() override;
    
    virtual bool InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, float Force, FDateTime DeviceTimestamp, uint32 TouchpadIndex) override;
    
	UFUNCTION(BlueprintCallable, Category = "GamePlayerController")
		void ScreenShot_Callback(FScreenshotImage Image);
	void MakeScreenShot();

public:
    
    
};
