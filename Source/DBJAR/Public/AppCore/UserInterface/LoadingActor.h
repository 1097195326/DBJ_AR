#pragma once


#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "LoadingActor.generated.h"

UCLASS()
class ALoadingActor : public AActor
{
	GENERATED_BODY()

public:
	ALoadingActor();


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent * m_LoadingComponent;

	void UpdateLoadingComponent();
	void ResetLoading();

	FTimerHandle m_timerHandle;

	virtual void BeginPlay() override;

};

