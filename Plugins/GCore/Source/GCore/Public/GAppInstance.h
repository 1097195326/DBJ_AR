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
#include "Engine/Texture2D.h"
#include "Misc/CoreDelegates.h"
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
    

    static UGAppInstance * GetInstance();
    
    virtual void Init() override;
    virtual void PostInitProperties() override;
    virtual void BeginDestroy() override;
    virtual void Shutdown() override;
    
    virtual    void ApplicationWillEnterBackground();
    virtual    void ApplicationHasEnteredForeground();
    

    virtual	void OpenLevel(const FString & _levelName);

	ENetworkStatus GetNetworkStatus();

	static bool CheckStringIsValid(const FString& str, const FString& Reg);
	static bool CheckPhone(const FString& str);

	static UTexture2D* LoadImageFromDisk(UObject* Outer, const FString& ImagePath);
	
private:
	
	static UTexture2D* CreateTexture(UObject* Outer, const TArray<uint8>& PixelData, int32 InSizeX, int32 InSizeY, EPixelFormat PixelFormat = EPixelFormat::PF_B8G8R8A8, FName BaseName = NAME_None);

    void ApplicationWillEnterBackground_Hander();
    void ApplicationHasEnteredForeground_Hander();
};

