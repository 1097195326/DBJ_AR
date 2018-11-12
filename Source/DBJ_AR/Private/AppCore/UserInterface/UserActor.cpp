#include "UserActor.h"


AUserActor::AUserActor()
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("rootcomponent"));
    
    m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UserMesh"));
    
    m_Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    
}
