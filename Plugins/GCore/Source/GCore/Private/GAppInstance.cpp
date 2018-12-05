//
//  GAppInstance.cpp
//  GameFrame
//
//  Created by fafa on 2018/8/9.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

#include "GCore.h"
#include "GAppInstance.h"
#include "Reachability.h"

UGAppInstance *  UGAppInstance::m_Instance = nullptr;

UGAppInstance * UGAppInstance::GetInstance()
{
    return m_Instance;
}
UGAppInstance::UGAppInstance()
{
	FCoreDelegates::ApplicationWillEnterBackgroundDelegate.AddUObject(this, &UGAppInstance::ApplicationWillEnterBackground);
	FCoreDelegates::ApplicationWillEnterBackgroundDelegate.AddUObject(this, &UGAppInstance::ApplicationHasEnteredForeground);

}
void UGAppInstance::Init()
{
    Super::Init();
    
	On_Init();
}
void UGAppInstance::OpenLevel(const FString & _levelName)
{
	
}
void UGAppInstance::ApplicationWillEnterBackground()
{
	UE_LOG(LogTemp, Log, TEXT("zhx : UGAppInstance::ApplicationWillEnterBackground"));

}
void UGAppInstance::ApplicationHasEnteredForeground()
{
	UE_LOG(LogTemp, Log, TEXT("zhx : UGAppInstance::ApplicationHasEnteredForeground"));

}
ENetworkStatus UGAppInstance::GetNetworkStatus()
{
	ENetworkStatus state = EReachableViaWWAN;
	//return state;
#if PLATFORM_IOS
    Reachability *tekuba_net = [Reachability reachabilityWithHostName];
    switch ([tekuba_net currentReachabilityStatus])
    {
    case NotReachable:
        // 没有网络连接
        state = ENotReachable;
        break;
    case ReachableViaWWAN:
        // 使用2G/3G/4G网络
        state = EReachableViaWWAN;
        break;
    case ReachableViaWiFi:
        // 使用WiFi网络
        state = EReachableViaWiFi;
        break;
    }
#endif
	return state;
}
