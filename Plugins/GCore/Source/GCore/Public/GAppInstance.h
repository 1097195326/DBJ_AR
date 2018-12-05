//
//  GAppInstance.hpp
//  GameFrame
//
//  Created by fafa on 2018/8/9.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

#pragma once


#include "CoreMinimal.h"
#include "GObject.h"
#include "Engine/GameInstance.h"
#include "GAppInstance.generated.h"

typedef enum {
	ENotReachable = 0,
	EReachableViaWiFi,
	EReachableViaWWAN
} ENetworkStatus;

UCLASS()
class GCORE_API UGAppInstance : public UGameInstance, public GObject
{
    GENERATED_BODY()
protected:
    static UGAppInstance *  m_Instance;
public:
	UGAppInstance();

    static UGAppInstance * GetInstance();
    
    virtual void Init() override;
    
	UFUNCTION()
		void ApplicationWillEnterBackground();
	UFUNCTION()
		void ApplicationHasEnteredForeground();

    virtual	void OpenLevel(const FString & _levelName);

	ENetworkStatus GetNetworkStatus();
};

