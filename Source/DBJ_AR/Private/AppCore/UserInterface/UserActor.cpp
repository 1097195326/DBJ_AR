#include "UserActor.h"


AUserActor::AUserActor()
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("rootcomponent"));
    
    m_Mesh = CreateDefaultSubobject<UUserComponent>(TEXT("UserMesh"));
    
    m_Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    
	m_SoketIndex = 0;
}
AUserActor::~AUserActor()
{
	UE_LOG(LogTemp, Log, TEXT("zhx : AUserActor::~AUserActor"));
}
void AUserActor::BeginDestroy()
{
	Super::BeginDestroy();

	UE_LOG(LogTemp, Log, TEXT("zhx : AUserActor::BeginDestroy"));
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