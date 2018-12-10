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
#include "Internationalization/Regex.h"

UGAppInstance *  UGAppInstance::m_Instance = nullptr;

UGAppInstance * UGAppInstance::GetInstance()
{
    return m_Instance;
}
void UGAppInstance::Init()
{
    Super::Init();
    
	On_Init();
}

void UGAppInstance::PostInitProperties()
{
    Super::PostInitProperties();
    UE_LOG(LogTemp, Log, TEXT("zhx : ---UAppInstance::PostInitProperties"));
    
    FCoreDelegates::ApplicationWillEnterBackgroundDelegate.AddUObject(this, &UGAppInstance::ApplicationWillEnterBackground_Hander);
    FCoreDelegates::ApplicationHasEnteredForegroundDelegate.AddUObject(this, &UGAppInstance::ApplicationHasEnteredForeground_Hander);
}
void UGAppInstance::BeginDestroy()
{
    FCoreDelegates::ApplicationWillEnterBackgroundDelegate.RemoveAll(this);
    FCoreDelegates::ApplicationHasEnteredForegroundDelegate.RemoveAll(this);
	
	On_Delete();
    
	Super::BeginDestroy();
}
void UGAppInstance::Shutdown()
{
    UE_LOG(LogTemp,Log,TEXT("zhx : --- UGAppInstance::Shutdown"));
    
    Super::Shutdown();
}
void UGAppInstance::ApplicationWillEnterBackground_Hander()
{
    ApplicationWillEnterBackground();
}
void UGAppInstance::ApplicationHasEnteredForeground_Hander()
{
    ApplicationHasEnteredForeground();
}
void UGAppInstance::ApplicationWillEnterBackground()
{
    
    
}
void UGAppInstance::ApplicationHasEnteredForeground()
{
    
}
void UGAppInstance::OpenLevel(const FString & _levelName)
{
	
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
bool UGAppInstance::CheckStringIsValid(const FString& str, const FString& Reg)
{
	FRegexPattern Pattern(Reg);
	FRegexMatcher regMatcher(Pattern, str);
	regMatcher.SetLimits(0, str.Len());
	return regMatcher.FindNext();
}
bool UGAppInstance::CheckPhone(const FString& str)
{
	if (str.Len() != 11) return false;
	FString reg = TEXT("^1\\d{10}$");
	return UGAppInstance::CheckStringIsValid(str, reg);
}