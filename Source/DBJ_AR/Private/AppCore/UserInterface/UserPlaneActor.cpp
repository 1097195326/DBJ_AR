#include "UserPlaneActor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"

static float rotator = 0.f;


AUserPlaneActor::AUserPlaneActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	m_PlaneComponent = CreateDefaultSubobject<UUserPlaneComponent>(TEXT("PlaneComponent"));
	m_PlaneComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	m_LoadingComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LoadingComponent"));
	m_LoadingComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}
void AUserPlaneActor::BeginPlay()
{
	Super::BeginPlay();

	ResetLoading();
}
void  AUserPlaneActor::UpdateLoadingComponent()
{
	TArray<UARPlaneGeometry*> planeGeometryArray = UARBlueprintLibrary::GetAllTrackedPlanes();
	if (planeGeometryArray.Num() > 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(m_timerHandle);
	}
	else
	{
		APlayerCameraManager * cameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
		FVector location = cameraManager->GetCameraLocation();
		FVector forward = cameraManager->GetCameraRotation().Vector();
		location = location + forward.GetSafeNormal() * 150;
		SetActorLocation(location);

		rotator += 0.5;
		if (rotator >= 360.f)
		{
			rotator -= 360.f;
		}
		float yawProcess = rotator / 360.f;
		m_LoadingComponent->SetScalarParameterValueOnMaterials(TEXT("Percent"), yawProcess);
	}
}
void AUserPlaneActor::ResetLoading()
{
	GetWorld()->GetTimerManager().SetTimer(m_timerHandle, this, &AUserPlaneActor::UpdateLoadingComponent, 0.1f, true, 0.f);

}