#include "UserPlaneComponent.h"

#include "Materials/MaterialInstance.h"
#include "Engine/World.h"
#include "TimerManager.h"

static int sectionIndex = 0;
static TArray<FString> WhiteList;

UUserPlaneComponent::UUserPlaneComponent()
{
//    PrimaryComponentTick.bCanEverTick = true;
//    PrimaryComponentTick.SetTickFunctionEnable(true);
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 3002, this, &UUserPlaneComponent::ApplicationWillEnterBackground);
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 3003, this, &UUserPlaneComponent::ApplicationHasEnteredForeground);
}
UUserPlaneComponent::~UUserPlaneComponent()
{
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 3002, this);
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 3003, this);
}
void UUserPlaneComponent::ApplicationWillEnterBackground(msg_ptr _msg)
{
	StopUpdate();
	ClearAllMeshSections();
}
void UUserPlaneComponent::ApplicationHasEnteredForeground(msg_ptr _msg)
{
	StartUpdate();

}
void UUserPlaneComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("zhx : plane component BeginPlay"));

    StartUpdate();
}
void UUserPlaneComponent::StartUpdate()
{
	GetWorld()->GetTimerManager().SetTimer(m_TimerHeadle, this, &UUserPlaneComponent::UpdateSection, 0.1f, true, 0);
}
void UUserPlaneComponent::StopUpdate()
{
	GetWorld()->GetTimerManager().ClearTimer(m_TimerHeadle);
	ClearAllMeshSections();
}
void UUserPlaneComponent::UpdateSection()
{
#if PLATFORM_WINDOWS
	return;
#endif
	//    ClearAllMeshSections();
	WhiteList.Empty();

	TArray<UARPlaneGeometry*> planeGeometryArray = UARBlueprintLibrary::GetAllTrackedPlanes();
	if (planeGeometryArray.Num() > 0)
	{
		for (UARPlaneGeometry * planeGeometry : planeGeometryArray)
		{
			//            sectionIndex = 0;

			FString planeName = planeGeometry->GetDebugName().ToString();//TEXT("sss");//planeGeometry->GetDebugName().ToString();
			WhiteList.Add(planeName);

			TArray<FVector> TempVertices;
			TArray<FVector> Vertices;
			TArray<int32> Triangles;
			TArray<FVector> Normals;
			TArray<FVector2D> UV0;
			TArray<FColor> VertexColors;
			TArray<FProcMeshTangent> Tangents;
			GetVertexAndIndex(planeGeometry->GetCenter(), planeGeometry->GetExtent(), TempVertices, Triangles,UV0);
			//GetVertexAndIndex(FVector(73,58,95), FVector(100,100,0.5), Vertices, Triangles);

			for (int i = 0; i < TempVertices.Num(); i++)
			{
				FVector tvector = planeGeometry->GetLocalToWorldTransform().TransformPosition(TempVertices[i]);
				Vertices.Add(tvector);
			}
			if (m_PlaneMap.Contains(planeName))
			{
				int scetion = *(m_PlaneMap.Find(planeName));
				UpdateMeshSection(scetion, Vertices, Normals, UV0, VertexColors, Tangents);
			}
			else
			{
				CreateMeshSection(sectionIndex, Vertices, Triangles, Normals, UV0, VertexColors, Tangents, false);
                UMaterialInterface * materialIns = LoadObject<UMaterialInstance>(nullptr, TEXT("/Game/Materials/Ground_Wire_MT"));
//                UMaterialInterface * materialIns = LoadObject<UMaterialInstance>(nullptr, TEXT("/Game/Materials/Wirefame_MT"));
				SetMaterial(sectionIndex, materialIns);
				m_PlaneMap.Add(planeName, sectionIndex);
				//UE_LOG(LogTemp, Log, TEXT("zhx : create a plane ,name : %s index : %d track Num : %d, map Num : %d"), *planeName, sectionIndex, planeGeometryArray.Num(), m_PlaneMap.Num());
				/*for (UARPlaneGeometry * pGeometry : planeGeometryArray)
				{
					FString ss = pGeometry->GetDebugName().ToString();
					UE_LOG(LogTemp, Log, TEXT("zhx track name : %s"), *ss);
				}
				for (auto item : m_PlaneMap)
				{
					FString ss = item.Key;
					int section = item.Value;
					UE_LOG(LogTemp, Log, TEXT("zhx map name : %s ,ishave : %d"), *ss, section);
				}*/
				++sectionIndex;
			}
		}
	}
	for (auto item : m_PlaneMap)
	{
		FString name = item.Key;
		int section = item.Value;
		if (!WhiteList.Contains(name))
		{
			//UE_LOG(LogTemp, Log, TEXT("zhx : delete a plane ,name : %s index : %d"), *name, section);
			ClearMeshSection(section);
			m_PlaneMap.Remove(name);
		}
	}
	//    UE_LOG(LogTemp, Log, TEXT("zhx : m_PlaneMap num : %d, Sections num : %d, index : %d"),m_PlaneMap.Num(),GetNumSections(),sectionIndex);
}
void UUserPlaneComponent::GetVertexAndIndex(FVector Center, FVector Extent,  TArray<FVector>& Vertices,  TArray<int32>& Triangles, TArray<FVector2D> & UV0)
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
    
//    UV0.Add(FVector2D(0,0));
//    UV0.Add(FVector2D(0,1));
//    UV0.Add(FVector2D(1,1));
//    UV0.Add(FVector2D(1,0));
    
    FVector uv1 = FVector(Extent.X, Extent.Y, 0.f) - FVector(Extent.X, -Extent.Y, 0.f);
    FVector uv2 = FVector(Extent.X, -Extent.Y, 0.f) - FVector(-Extent.X, -Extent.Y, 0.f);
    UV0.Add(FVector2D(0,0));
    UV0.Add(FVector2D(0,uv1.Size() / 50));
    UV0.Add(FVector2D(uv2.Size() / 50,uv1.Size() / 50));
    UV0.Add(FVector2D(uv2.Size() / 50,0));
    
	/*Triangles.Append({ 4,5,6 });
	Triangles.Append({ 6,7,4 });*/

}
void UUserPlaneComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
#if PLATFORM_WINDOWS
    return;
#endif
    
    //    ClearAllMeshSections();
    WhiteList.Empty();
    
    TArray<UARPlaneGeometry*> planeGeometryArray = UARBlueprintLibrary::GetAllTrackedPlanes();
    if (planeGeometryArray.Num() > 0)
    {
        for (UARPlaneGeometry * planeGeometry : planeGeometryArray)
        {
            //            sectionIndex = 0;
            
            FString planeName = planeGeometry->GetDebugName().ToString();//TEXT("sss");//planeGeometry->GetDebugName().ToString();
            WhiteList.Add(planeName);
            
            TArray<FVector> TempVertices;
            TArray<FVector> Vertices;
            TArray<int32> Triangles;
            TArray<FVector> Normals;
            TArray<FVector2D> UV0;
            TArray<FColor> VertexColors;
            TArray<FProcMeshTangent> Tangents;
            GetVertexAndIndex(planeGeometry->GetCenter(), planeGeometry->GetExtent(), TempVertices, Triangles,UV0);
            //GetVertexAndIndex(FVector(73,58,95), FVector(100,100,0.5), Vertices, Triangles);
            
            for (int i = 0; i < TempVertices.Num(); i++)
            {
                FVector tvector = planeGeometry->GetLocalToWorldTransform().TransformPosition(TempVertices[i]);
                Vertices.Add(tvector);
            }
            if (m_PlaneMap.Contains(planeName))
            {
                int scetion = *(m_PlaneMap.Find(planeName));
                UpdateMeshSection(scetion, Vertices, Normals, UV0, VertexColors, Tangents);
            }
            else
            {
                CreateMeshSection(sectionIndex,Vertices,Triangles,Normals,UV0,VertexColors,Tangents,false);
                UMaterialInterface * materialIns = LoadObject<UMaterialInstance>(nullptr, TEXT("/Game/Materials/Wirefame_MT"));
                //                UMaterialInterface * materialIns = LoadObject<UMaterial>(nullptr, TEXT("/Game/Blueprints/Materials/SelfPlaneM"));
                SetMaterial(sectionIndex, materialIns);
                m_PlaneMap.Add(planeName, sectionIndex);
                UE_LOG(LogTemp, Log, TEXT("zhx : create a plane ,name : %s index : %d track Num : %d, map Num : %d"),*planeName,sectionIndex,planeGeometryArray.Num(),m_PlaneMap.Num());
                for (UARPlaneGeometry * pGeometry : planeGeometryArray)
                {
                    FString ss = pGeometry->GetDebugName().ToString();
                    UE_LOG(LogTemp, Log, TEXT("zhx track name : %s"),*ss);
                }
                for (auto item : m_PlaneMap)
                {
                    FString ss = item.Key;
                    int section = item.Value;
                    UE_LOG(LogTemp, Log, TEXT("zhx map name : %s ,ishave : %d"),*ss,section);
                }
                ++sectionIndex;
            }
        }
    }
    for (auto item : m_PlaneMap)
    {
        FString name = item.Key;
        int section = item.Value;
        if (!WhiteList.Contains(name))
        {
            UE_LOG(LogTemp, Log, TEXT("zhx : delete a plane ,name : %s index : %d"),*name,section);
            ClearMeshSection(section);
            m_PlaneMap.Remove(name);
        }
    }
    //    UE_LOG(LogTemp, Log, TEXT("zhx : m_PlaneMap num : %d, Sections num : %d, index : %d"),m_PlaneMap.Num(),GetNumSections(),sectionIndex);
}
