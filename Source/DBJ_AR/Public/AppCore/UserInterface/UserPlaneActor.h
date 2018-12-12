#pragma once


#include "CoreMinimal.h"
#include "UserPlaneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UserPlaneActor.generated.h"

UCLASS()
class AUserPlaneActor : public AActor
{
	GENERATED_BODY()

public:
	AUserPlaneActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UUserPlaneComponent * m_PlaneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent * m_LoadingComponent;

	void UpdateLoadingComponent();
	void ResetLoading();

	FTimerHandle m_timerHandle;

	virtual void BeginPlay() override;

};

