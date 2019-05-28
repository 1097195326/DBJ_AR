#include "AppInstance.h"
#include "UIManager.h"
#include "DataManager.h"
#include "ScenePrototype.h"
#include "GFileManager.h"
#include "ARBlueprintLibrary.h"
#include "UserPawn.h"
#include "AlertUI.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ControllerPrototype.h"

UAppInstance::UAppInstance()
{
	m_Instance = this;
	
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 110, this, &UAppInstance::OnGloablMsg);
}
void UAppInstance::On_Init()
{
	GFileManager::GetInstance()->On_Init();

    Data_M->LoadAllXMLData();

	FIntPoint sPoint = GEngine->GetGameUserSettings()->GetScreenResolution();
	FString strPoint = FString::Printf(TEXT("%0.2f"),sPoint.X/(float)sPoint.Y);
	ControllerPrototype::SetScreenResolution(strPoint);
    
//    UGameUserSettings* mGameUserSettings = GEngine->GetGameUserSettings();
//    FIntPoint mPoint = mGameUserSettings->GetScreenResolution();
//    GEngine->AddOnScreenDebugMessage(-1, 999999, FColor::Red, FString::Printf(TEXT("ScreenResolution x=%d,y=%d"), mPoint.X,mPoint.Y));
//#if PLATFORM_IOS
//    [[UIApplication sharedApplication] setStatusBarHidden:NO];
//#endif
    
}
void UAppInstance::On_Delete()
{
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 110, this);
}
void UAppInstance::ApplicationWillEnterBackground()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : ---UGAppInstance::ApplicationWillEnterBackground"));
	
//    MsgCenter::GetInstance()->SendMsg(msg_ptr(new LocalMsg(Msg_Local, 3002, nullptr)));

}
void UAppInstance::ApplicationHasEnteredForeground()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : ---UGAppInstance::ApplicationHasEnteredForeground"));
    
//    MsgCenter::GetInstance()->SendMsg(msg_ptr(new LocalMsg(Msg_Local, 3003, nullptr)));

}
void UAppInstance::OpenLevel(const FString & _levelName)
{
	ScenePrototype * scene = Data_M->GetProtoType<ScenePrototype>(PrototypeIndex::E_Scene_IOS_ID);
	FString levelPath = scene->GetDataByKey(_levelName);
	levelPath.RemoveSpacesInline();

	UGameplayStatics::OpenLevel(this, *levelPath);
}
void UAppInstance::PakMount()
{
	GFileManager::GetInstance()->TestPak();
}

void UAppInstance::OnGloablMsg(msg_ptr _msg)
{
	UE_LOG(LogTemp, Log, TEXT("zhx : APP Instance On Gloable Msg"));
	UAlertUI * fullAlert = (UAlertUI*)UIManager::GetInstance()->OpenUI(TEXT("FullAlertUI"));
	fullAlert->AddToViewport(999);
	fullAlert->BindSureFunctionCall(this, &UAppInstance::GloablMsgSure);
	fullAlert->SetContentText(TEXT("网络连接失败,请检查网络设置"));
}
void UAppInstance::GloablMsgSure()
{
	UE_LOG(LogTemp, Log, TEXT("zhx : APP Instance Sure Gloabl Msg"));
	MsgCenter::GetInstance()->RerequestHttp();
	

}
void UAppInstance::GloablMsgCancel()
{
	MsgCenter::GetInstance()->ContineHttp();
}
