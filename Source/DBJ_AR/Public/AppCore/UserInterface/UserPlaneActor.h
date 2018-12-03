#pragma once


#include "CoreMinimal.h"
#include "UserPlaneComponent.h"
#include "UserPlaneActor.generated.h"

UCLASS()
class AUserPlaneActor : public AActor
{
	GENERATED_BODY()

public:
	/*UserPlaneActor();
	~UserPlaneActor();
	virtual void BeginDestroy() override;
	virtual void BeginPlay() override;*/
	virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

};

