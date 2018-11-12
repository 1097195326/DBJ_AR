#include "UserActor.h"


AUserActor::AUserActor()
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("rootcomponent"));
    
    m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UserMesh"));
    
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