#include "UserPlaneComponent.h"



void UUserPlaneComponent::BeginPlay()
{
	Super::BeginPlay();

}
void UUserPlaneComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	TArray<UARPlaneGeometry*> planeGeometryArray = UARBlueprintLibrary::GetAllTrackedPlanes();
	if (planeGeometryArray.Num() > 0)
	{
		for (UARPlaneGeometry * planeGeometry : planeGeometryArray)
		{
			FString planeName = planeGeometry->GetDebugName().ToString();

			TArray<FVector> Vertices;
			TArray<int32> Triangles;
			TArray<FVector> Normals;
			TArray<FVector2D> UV0;
			TArray<FColor> VertexColors;
			TArray<FProcMeshTangent> Tangents;
			GetVertexAndIndex(planeGeometry->GetCenter(), planeGeometry->GetExtent(), Vertices, Triangles);

			if (m_PlaneMap.Contains(planeName))
			{
				int32 section = *(m_PlaneMap.Find(planeName));
				UpdateMeshSection(section, Vertices, Normals, UV0, VertexColors, Tangents);
			}
			else
			{
				int32 section = m_PlaneMap.Num() + 1;
				CreateMeshSection(section,Vertices,Triangles,Normals,UV0,VertexColors,Tangents,false);
				m_PlaneMap.Add(planeName, section);
			}
		}
	}
}
void UUserPlaneComponent::GetVertexAndIndex(FVector Center, FVector Extent,  TArray<FVector>& Vertices,  TArray<int32>& Triangles)
{
	Vertices.Add(Center + FVector(Extent.X, Extent.Y, Extent.Z));
	Vertices.Add(Center + FVector(Extent.X, -Extent.Y, Extent.Z));
	Vertices.Add(Center + FVector(-Extent.X, -Extent.Y, Extent.Z));
	Vertices.Add(Center + FVector(-Extent.X, Extent.Y, Extent.Z));

	Vertices.Add(Center + FVector(Extent.X, Extent.Y, -Extent.Z));
	Vertices.Add(Center + FVector(Extent.X, -Extent.Y, -Extent.Z));
	Vertices.Add(Center + FVector(-Extent.X, -Extent.Y, -Extent.Z));
	Vertices.Add(Center + FVector(-Extent.X, Extent.Y, -Extent.Z));

	Vertices.Add(Center + FVector(Extent.X, Extent.Y, Extent.Z));
	Vertices.Add(Center + FVector(Extent.X, -Extent.Y, Extent.Z));
	Vertices.Add(Center + FVector(-Extent.X, -Extent.Y, Extent.Z));
	Vertices.Add(Center + FVector(-Extent.X, Extent.Y, Extent.Z));

	Triangles.Append({ 0,1,2 });
	Triangles.Append({ 1,2,3 });

	Triangles.Append({ 4,5,6 });
	Triangles.Append({ 5,6,7 });

	Triangles.Append({ 8,9,10 });
	Triangles.Append({ 9,10,11 });
}