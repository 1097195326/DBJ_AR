#include "UserActor.h"
#include "Engine.h"

AUserActor::AUserActor()
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("rootcomponent"));
    
	m_PlaneRotateComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneRotateComponent"));
	m_PlaneRotateComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
    m_Mesh = CreateDefaultSubobject<UUserComponent>(TEXT("UserMesh"));
    m_Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	m_SoketIndex = 0;
}
AUserActor::~AUserActor()
{
	UE_LOG(LogTemp, Log, TEXT("zhx : AUserActor::~AUserActor"));
}
void AUserActor::BeginPlay()
{
	Super::BeginPlay();
	m_PlaneRotateComponent->SetVisibility(false);

}
void AUserActor::BeginDestroy()
{
	m_Mesh->m_Data = nullptr;
	m_GoodsDatas.Empty();
	UE_LOG(LogTemp, Log, TEXT("zhx : AUserActor::BeginDestroy"));
    
	Super::BeginDestroy();
}
void AUserActor::ShowPlaneComponent(bool visiable)
{
	if (m_PlaneRotateComponent)
	{
		m_PlaneRotateComponent->SetVisibility(visiable);

	}
}
void AUserActor::RemoveGoodsData(GoodsData * _data)
{
	if (m_GoodsDatas.Contains(_data))
	{
		m_GoodsDatas.Remove(_data);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("zhx : user actor change goods fail"));
	}
}
void AUserActor::AddGoodsData(GoodsData * _data)
{
	m_GoodsDatas.Add(_data);
}
void AUserActor::AddUserComponent(UUserComponent * _userComponent)
{
    if(m_Type == User_Pen)
    {
        m_HuaList.Add(_userComponent);
    }
}
bool AUserActor::MergeOtherActor(AUserActor * _otherActor)
{
    if(m_Type == User_Pen)
    {
        FString socketName = FString::Printf(TEXT("Socket%d"), m_SoketIndex + 1);
        
        if (m_Mesh->GetSocketByName(*socketName))
        {
            GoodsData * otherData = _otherActor->m_Mesh->m_Data;
            
            UUserComponent * component = NewObject<UUserComponent>(this,TEXT("HuaComponent"));
            UStaticMesh * hua = _otherActor->m_Mesh->GetStaticMesh();
            component->SetStaticMesh(hua);
            component->AttachToComponent(m_Mesh, FAttachmentTransformRules::KeepRelativeTransform, *socketName);
            component->RegisterComponent();//WithWorld(GetWorld());
            component->SetGoodsData(otherData,socketName);
            m_HuaList.Add(component);
            
            m_GoodsDatas.Add(otherData);
            
            m_SoketIndex += 1;
            _otherActor->Destroy();
            GEngine->ForceGarbageCollection(true);
            return true;
        }
    }
    return false;
}
void AUserActor::ResetHuaComponent()
{
//    m_Mesh->RegisterComponent();
    for(int i = 0; i< m_HuaList.Num(); i++)
    {
        UUserComponent * component = m_HuaList[i];
        FString socketName = component->m_SocketName;
        if (m_Mesh->GetSocketByName(*socketName))
        {
            UE_LOG(LogTemp,Log,TEXT("zhx : user actor reset hua socket"));
            component->AttachToComponent(m_Mesh, FAttachmentTransformRules::KeepRelativeTransform, *socketName);
//            component->RegisterComponent();
        }
    }
}
void AUserActor::SetMatchId(int mainId, int matchId)
{
	m_MatchMap.Empty();
	m_MatchMap.Add(mainId, matchId);
	m_MatchMap.Add(matchId, mainId);
}
