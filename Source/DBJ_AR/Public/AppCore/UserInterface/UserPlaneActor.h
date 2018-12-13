#pragma once


#include "CoreMinimal.h"
#include "UserPlaneComponent.h"
#include "UserPlaneActor.generated.h"

UCLASS()
class AUserPlaneActor : public AActor
{
	GENERATED_BODY()

public:
	AUserPlaneActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UUserPlaneComponent * m_PlaneComponent;

	virtual void BeginPlay() override;

};

