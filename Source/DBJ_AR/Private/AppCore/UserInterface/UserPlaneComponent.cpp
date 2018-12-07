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
static int sectionIndex = 0;

void UUserPlaneComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
#if PLATFORM_WINDOWS
	return;
#endif

//    ClearAllMeshSections();
    
	TArray<UARPlaneGeometry*> planeGeometryArray = UARBlueprintLibrary::GetAllTrackedPlanes();
	if (planeGeometryArray.Num() > 0)
	{
		for (UARPlaneGeometry * planeGeometry : planeGeometryArray)
		{
//            sectionIndex = 0;
            
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
                PlaneStatus & st = *(m_PlaneMap.Find(planeName));
                st.IsHave = true;
                UpdateMeshSection(st.Section, Vertices, Normals, UV0, VertexColors, Tangents);
            }
            else
            {
                ++sectionIndex;
                PlaneStatus st;
                st.Section = sectionIndex;
                st.IsHave = true;
                CreateMeshSection(sectionIndex,Vertices,Triangles,Normals,UV0,VertexColors,Tangents,false);
//                UMaterialInterface * materialIns = LoadObject<UMaterialInstance>(nullptr, TEXT("/Game/Blueprints/Materials/Wirefame_MT"));
                UMaterialInterface * materialIns = LoadObject<UMaterial>(nullptr, TEXT("/Game/Blueprints/Materials/SelfPlaneM"));
                SetMaterial(sectionIndex, materialIns);
                m_PlaneMap.Add(planeName, st);
//                UE_LOG(LogTemp,Log,TEXT(""))
            }
		}
	}
    for (auto item : m_PlaneMap)
    {
        FString name = item.Key;
        PlaneStatus & st = item.Value;
        if (st.IsHave)
        {
            st.IsHave = false;
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("zhx : delete a plane ,name : %s"),*name);
            ClearMeshSection(st.Section);
            m_PlaneMap.Remove(name);
        }
    }
    UE_LOG(LogTemp, Log, TEXT("zhx : m_PlaneMap num : %d, Sections num : %d, index : %d"),m_PlaneMap.Num(),GetNumSections(),sectionIndex);
}
void UUserPlaneComponent::GetVertexAndIndex(FVector Center, FVector Extent,  TArray<FVector>& Vertices,  TArray<int32>& Triangles)
{
	//Vertices.Add(Center + FVector(Extent.X, Extent.Y, Extent.Z)); // 0
	//Vertices.Add(Center + FVector(Extent.X, -Extent.Y, Extent.Z));// 1
	//Vertices.Add(Center + FVector(-Extent.X, -Extent.Y, Extent.Z));// 2
	//Vertices.Add(Center + FVector(-Extent.X, Extent.Y, Extent.Z));// 3

	//Vertices.Add(Center + FVector(Extent.X, Extent.Y, -Extent.Z)); //4
	//Vertices.Add(Center + FVector(Extent.X, -Extent.Y, -Extent.Z));// 5
	//Vertices.Add(Center + FVector(-Extent.X, -Extent.Y, -Extent.Z));// 6
	//Vertices.Add(Center + FVector(-Extent.X, Extent.Y, -Extent.Z));//7

	Vertices.Add(Center + FVector(Extent.X, Extent.Y, 0.f)); // 0
	Vertices.Add(Center + FVector(Extent.X, -Extent.Y, 0.f));// 1
	Vertices.Add(Center + FVector(-Extent.X, -Extent.Y, 0.f));// 2
	Vertices.Add(Center + FVector(-Extent.X, Extent.Y, 0.f));// 3

	Triangles.Append({ 0,1,2 });
	Triangles.Append({ 2,3,0 });

	/*Triangles.Append({ 4,5,6 });
	Triangles.Append({ 6,7,4 });*/

}
