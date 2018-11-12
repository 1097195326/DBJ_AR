#pragma once



#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "UserActor.generated.h"

UCLASS()
class AUserActor : public AActor
{
    GENERATED_BODY()
    
public:
    AUserActor();
    
    
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent * m_Mesh;
    
    
};

