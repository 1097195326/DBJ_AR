#include "UserPlaneActor.h"


AUserPlaneActor::AUserPlaneActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	m_PlaneComponent = CreateDefaultSubobject<UUserPlaneComponent>(TEXT("PlaneComponent"));
	m_PlaneComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    
}
void AUserPlaneActor::BeginPlay()
{
	Super::BeginPlay();

}
