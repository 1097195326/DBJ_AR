#pragma once
#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "ARBlueprintLibrary.h"
#include "UserPlaneComponent.generated.h"

UCLASS()
class UUserPlaneComponent : public UProceduralMeshComponent
{
	GENERATED_BODY()

public:
	UUserPlaneComponent();
	/*~UserPlaneComponent();*/
	/*virtual void BeginDestroy() override;
	virtual void BeginPlay() override;*/

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void	GetVertexAndIndex(FVector Center,FVector Extent, TArray<FVector>& Vertices,  TArray<int32>& Triangles);
private:
	TMap<FString, int>	m_PlaneMap;

};
