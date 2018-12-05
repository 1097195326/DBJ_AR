#include "AppInstance.h"
#include "UIManager.h"
#include "DataManager.h"
#include "ScenePrototype.h"
#include "GFileManager.h"
#include "ARBlueprintLibrary.h"


UAppInstance::UAppInstance()
{
	m_Instance = this;
	
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 110, this, &UAppInstance::OnGloablMsg);
}
void UAppInstance::PostInitProperties()
{
    Super::PostInitProperties();
    UE_LOG(LogTemp, Log, TEXT("zhx : ---UAppInstance::PostInitProperties"));
    
    FCoreDelegates::ApplicationWillEnterBackgroundDelegate.AddUObject(this, &UAppInstance::ApplicationWillEnterBackground);
    FCoreDelegates::ApplicationHasEnteredForegroundDelegate.AddUObject(this, &UAppInstance::ApplicationHasEnteredForeground);
}
void UAppInstance::BeginDestroy()
{
    FCoreDelegates::ApplicationWillEnterBackgroundDelegate.RemoveAll(this);
    FCoreDelegates::ApplicationHasEnteredForegroundDelegate.RemoveAll(this);
    
    Super::BeginDestroy();
}

void UAppInstance::On_Init()
{
	GFileManager::GetInstance()->On_Init();

    Data_M->LoadAllXMLData();

    
    UGameUserSettings* mGameUserSettings = GEngine->GetGameUserSettings();
    FIntPoint mPoint = mGameUserSettings->GetScreenResolution();
    GEngine->AddOnScreenDebugMessage(-1, 999999, FColor::Red, FString::Printf(TEXT("ScreenResolution x=%d,y=%d"), mPoint.X,mPoint.Y));
    
}
void UAppInstance::On_Delete()
{
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 110, this);
}
void UAppInstance::ApplicationWillEnterBackground()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : ---UGAppInstance::ApplicationWillEnterBackground"));
	UARBlueprintLibrary::StopARSession();

}
void UAppInstance::ApplicationHasEnteredForeground()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : ---UGAppInstance::ApplicationHasEnteredForeground"));
    
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


}
