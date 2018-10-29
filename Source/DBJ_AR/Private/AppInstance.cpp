#include "AppInstance.h"
#include "UIManager.h"
#include "DataManager.h"
#include "ScenePrototype.h"




UAppInstance::UAppInstance()
{
	m_Instance = this;
}
void UAppInstance::On_Init()
{
    Data_M->LoadAllXMLData();

}
void UAppInstance::OpenLevel(const FString & _levelName)
{
	ScenePrototype * scene = Data_M->GetProtoType<ScenePrototype>(PrototypeIndex::E_Scene_IOS_ID);
	FString levelPath = scene->GetDataByKey(_levelName);
	levelPath.RemoveSpacesInline();

	UGameplayStatics::OpenLevel(this, *levelPath);
}