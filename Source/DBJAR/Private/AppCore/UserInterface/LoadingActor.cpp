#include "LoadingActor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "ARBlueprintLibrary.h"

static float rotator = 0.f;


ALoadingActor::ALoadingActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	m_LoadingComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LoadingComponent"));
	m_LoadingComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}
void ALoadingActor::BeginPlay()
{
	Super::BeginPlay();

	ResetLoading();
}
void  ALoadingActor::UpdateLoadingComponent()
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

		/*rotator += 1;
		if (rotator >= 100)
		{
			rotator -= 100;
		}
		float yawProcess = rotator / 100.f;
		m_LoadingComponent->SetScalarParameterValueOnMaterials(TEXT("Percent"), yawProcess);*/
	}
}
void ALoadingActor::ResetLoading()
{
	m_LoadingComponent->SetVisibility(true);
	GetWorld()->GetTimerManager().SetTimer(m_timerHandle, this, &ALoadingActor::UpdateLoadingComponent, 0.1f, true, 0.f);
}
