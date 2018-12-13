#include "UserPlaneActor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"


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
#if PLATFORM_WINDOWS
	return;
#endif
	TArray<UARPlaneGeometry*> planeGeometryArray = UARBlueprintLibrary::GetAllTrackedPlanes();
	if (planeGeometryArray.Num() > 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(m_timerHandle);
		m_LoadingComponent->SetVisibility(false);
	}
	else
	{
		APlayerCameraManager * cameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
		FVector location = cameraManager->GetCameraLocation();
		FVector forward = cameraManager->GetCameraRotation().Vector();
		location = location + forward.GetSafeNormal() * 150;
		
		SetActorLocation(UKismetMathLibrary::VInterpTo(GetActorLocation(), location, 0.1f, 6.f));

		rotator += 1;
		if (rotator >= 100)
		{
			rotator -= 100;
		}
		float yawProcess = rotator / 100.f;
		m_LoadingComponent->SetScalarParameterValueOnMaterials(TEXT("Percent"), yawProcess);
	}
}
void AUserPlaneActor::ResetLoading()
{
	m_LoadingComponent->SetVisibility(true);
	GetWorld()->GetTimerManager().SetTimer(m_timerHandle, this, &AUserPlaneActor::UpdateLoadingComponent, 0.1f, true, 0.f);
}