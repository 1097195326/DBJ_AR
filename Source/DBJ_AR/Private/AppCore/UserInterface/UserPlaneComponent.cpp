#include "UserPlaneComponent.h"

#include "Materials/MaterialInstance.h"




UUserPlaneComponent::UUserPlaneComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.SetTickFunctionEnable(true);

}
void UUserPlaneComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("zhx : plane component BeginPlay"));

	
}
void UUserPlaneComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
#if PLATFORM_WINDOWS
	return;
#endif

	TArray<UARPlaneGeometry*> planeGeometryArray = UARBlueprintLibrary::GetAllTrackedPlanes();
	if (planeGeometryArray.Num() > 0)
	{
		for (UARPlaneGeometry * planeGeometry : planeGeometryArray)
		{
			FString planeName = planeGeometry->GetDebugName().ToString();//TEXT("sss");//planeGeometry->GetDebugName().ToString();

			TArray<FVector> TempVertices;
			TArray<FVector> Vertices;
			TArray<int32> Triangles;
			TArray<FVector> Normals;
			TArray<FVector2D> UV0;
			TArray<FColor> VertexColors;
			TArray<FProcMeshTangent> Tangents;
			GetVertexAndIndex(planeGeometry->GetCenter(), planeGeometry->GetExtent(), TempVertices, Triangles);
			//GetVertexAndIndex(FVector(73,58,95), FVector(100,100,0.5), Vertices, Triangles);

			for (int i = 0; i < TempVertices.Num(); i++)
			{
				 FVector tvector = planeGeometry->GetLocalToWorldTransform().TransformPosition(TempVertices[i]);
				 Vertices.Add(tvector);
			}
			if (m_PlaneMap.Contains(planeName))
			{
				int32 section = *(m_PlaneMap.Find(planeName));
				UpdateMeshSection(section, Vertices, Normals, UV0, VertexColors, Tangents);
			}
			else
			{
				int32 section = m_PlaneMap.Num() + 1;
				CreateMeshSection(section,Vertices,Triangles,Normals,UV0,VertexColors,Tangents,false);
				UMaterialInterface * materialIns = LoadObject<UMaterialInstance>(nullptr, TEXT("/Game/Blueprints/Materials/Wirefame_MT"));
				SetMaterial(section, materialIns);
				m_PlaneMap.Add(planeName, section);
			}
			
		}
	}
}
void UUserPlaneComponent::GetVertexAndIndex(FVector Center, FVector Extent,  TArray<FVector>& Vertices,  TArray<int32>& Triangles)
{
	Vertices.Add(Center + FVector(Extent.X, Extent.Y, Extent.Z)); // 0
	Vertices.Add(Center + FVector(Extent.X, -Extent.Y, Extent.Z));// 1
	Vertices.Add(Center + FVector(-Extent.X, -Extent.Y, Extent.Z));// 2
	Vertices.Add(Center + FVector(-Extent.X, Extent.Y, Extent.Z));// 3

	Vertices.Add(Center + FVector(Extent.X, Extent.Y, -Extent.Z)); //4
	Vertices.Add(Center + FVector(Extent.X, -Extent.Y, -Extent.Z));// 5
	Vertices.Add(Center + FVector(-Extent.X, -Extent.Y, -Extent.Z));// 6
	Vertices.Add(Center + FVector(-Extent.X, Extent.Y, -Extent.Z));//7

	Triangles.Append({ 0,1,2 });
	Triangles.Append({ 2,3,0 });

	Triangles.Append({ 4,5,6 });
	Triangles.Append({ 6,7,4 });

}