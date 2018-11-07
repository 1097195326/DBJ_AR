// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object.h"
#include "IPlatformFilePak.h"
#include "Runtime/Engine/Classes/Animation/AnimSequence.h"
#include "XmlParser.h"
#include "ResTypes.h"
#include "GenericPlatformChunkInstall.h"
#include "XRCommonTypes.h"
#include "engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "Engine.h"
#include "Core.h"
#include "ResManager.generated.h"

class FSlateTextureRenderTarget2DResource;

#define ECC_VRSSM		ECC_GameTraceChannel2

USTRUCT()
struct XRRESOURCE_API FVRSObject
{
	GENERATED_USTRUCT_BODY()
	//数组元素内容定义如下	0:UStaticMesh/UMaterialInterface/UBlueprintClass  1:SkeltalMesh/UStaticMesh(Lamp)  2:UAnimSequence
	UPROPERTY()
		TArray<UObject*> Objects;
	UPROPERTY()
		TArray<FModelMaterialData> MaterialList;
	//服务器保存的参数个数跟模型的材质ID号不一致，匹配失败，给出红色字体警告
	bool MaterialParaMismatch;
	FVector BoundOrigin;
	FVector BoundExtent;
	TArray<FTransform> PointArray;
	TArray<FTransform> SpotArray;
	FLinearColor LampColor;
	float  LampIntensity;
	//服务器同步数据
	int32 ItemID;
	FString FileName;
	FString FilePath;
	EResourceType FileType;
	FString MaterialParameter;
	FString LightParameter;
	//标准化导入的pak（用工具导入制作的模型，必定有pak.xml文件）
	bool bNormalized;
	int32 SynID;
	int32 Version;

	FVRSObject()
	{
		FileType = EResourceType::None;
		bNormalized = false;
		MaterialParaMismatch = false;
		BoundOrigin = FVector::ZeroVector;
		BoundExtent = FVector::ZeroVector;
	}

	void ResetMaterialParameters()
	{
		if (MaterialList.IsValidIndex(0))
		{
			MaterialList[0].ResetToServer();
		}
	}

	UObject* GetFirstObject()
	{
		if (Objects.IsValidIndex(0))
		{
			return Objects[0];
		}
		else
			return NULL;
	}

	USkeletalMesh* GetSkeletalMeshObject()
	{
		if (Objects.IsValidIndex(1))
		{
			return Cast<USkeletalMesh>(Objects[1]);
		}
		else
			return NULL;
	}

	UAnimSequence* GetAnimSequenceObject()
	{
		if (Objects.IsValidIndex(2))
		{
			return Cast<UAnimSequence>(Objects[2]);
		}
		else
			return NULL;
	}

	UStaticMesh* GetLampMeshObject()
	{
		if (Objects.IsValidIndex(1))
		{
			return Cast<UStaticMesh>(Objects[1]);
		}
		else
			return NULL;
	}

	void SetFirstObject(UObject* _Object)
	{
		if (Objects.IsValidIndex(0))
		{
			Objects[0] = _Object;
		}
		else
		{
			Objects.Add(_Object);
		}
	}

	void SetObjects(TArray<UObject*> _Objects)
	{
		Objects = _Objects;
	}

	void SetSkeletalMeshObject(USkeletalMesh* _SkeletalObj)
	{
		if (Objects.Num() == 0)
		{
			Objects.Add(NULL);
			Objects.Add(_SkeletalObj);
		}
		else if (Objects.Num() == 1)
		{
			Objects.Add(_SkeletalObj);
		}
		else if (Objects.Num() == 2)
		{
			Objects[1] = _SkeletalObj;
		}
	}

	void SetLampMeshObject(UStaticMesh* _StaticObj)
	{
		if (Objects.Num() == 0)
		{
			Objects.Add(NULL);
			Objects.Add(_StaticObj);
		}
		else if (Objects.Num() == 1)
		{
			Objects.Add(_StaticObj);
		}
		else if (Objects.Num() == 2)
		{
			Objects[1] = _StaticObj;
		}
	}

	void SetAnimSequenceObject(UAnimSequence* _AnimObj)
	{
		if (Objects.Num() == 0)
		{
			Objects.Add(NULL);
			Objects.Add(NULL);
			Objects.Add(_AnimObj);
		}
		if (Objects.Num() == 1)
		{
			Objects.Add(NULL);
			Objects.Add(_AnimObj);
		}
		else if (Objects.Num() == 2)
		{
			Objects.Add(_AnimObj);
		}
		else if (Objects.Num() == 3)
		{
			Objects[2] = _AnimObj;
		}
	}
};

/**
 * 
 */
UCLASS()
class XRRESOURCE_API UXRResourceManager : public UObject
{
	GENERATED_BODY()
	
public:
	
	UXRResourceManager();
	~UXRResourceManager();

	void Init();
	virtual void BeginDestroy() override;

	FString GetDebugInfo();

	static EResourceType GetFileType(FString _PakName);
	
	static FVector GetVecFromColor(FLinearColor _Color);
	//PakType 0 Home  1 Model  2 Material 3 Actor    例如：LR_0  =====>>  ../../../XR/Game/DBJCache/LR/LR_0.pak 
	static FString GetPathFromFileName(EResourceType _PakType, FString& _PakName, bool _Test = false);

	//传入一个UObject，返回ItemID，比如5001。如果WithPackageID为true，则返回5001::0
	int32 GetItemIDFromObj(UObject* _Obj);

	//传入一个AActor，返回ItemID，比如5001。如果WithPackageID为true，则返回5001::0
	int32 GetItemIDFromActor(AActor* _Actor);

	//传入一个ObjID，如果存在则返回一个FVRSObject指针
	FVRSObject* GetObjFromObjID(int32 _ObjID);

	//传入一个SynID，如果存在则返回一个FModelSynData指针
	TSharedPtr<FContentItemSpace::FContentItem> GetContentItemFromID(int32 _SynID);
	
	/**
	 * 根据资源ID和资源类型，获取ContentItem。比如当前如果只知道HomeID，则可以通过HomeID和ResourceType来获取ContentItem
	 * @param InResType - EResourceType - 资源类型
	 * @param InID - int32 - 资源ID
	 * @return FContentItemSpace::FContentItem* - 资源具体数据
	 */
	TSharedPtr<FContentItemSpace::FContentItem> GetContentItemFromItemID(EResourceType InResType, int32 InID);

	//传入一个UMaterialInterface，根据它父材质的类型，返回它的路径
	FString GetMaterialFullName(UMaterialInterface* _MI);

	//获取材质的父材质的每一层路径
	void GetParentMostPath(UMaterialInterface* _MI, TArray<FString>& _Paths);

	//遍历LevelPathMap映射表，根据当前加载的Level的路径，返回Level所在的Pak文件名称
	FString GetCurMapPakName();

	//遍历LevelPathMap映射表，根据Pak文件名称，返回Level的路径
	FString FindLevelPath(FString _HomePakName, bool _Test = false);
	
	//传入一个新的UObject和旧的UObject，如果旧的UObject存在于ObjList中，则复制一份，插入ObjList末尾，并把新的UObject设置进去。
	bool CloneObject(UObject* _NewObject, UObject* _OldObject);

	//传入一个UMaterialInterface，创建一个UMaterialInstanceDynamic。这个过程中会调用CloneObject。这样保证所有材质Object都独立信息不重复。
	UMaterialInstanceDynamic* CreateMID(UMaterialInterface* _MI);

	//传入AActor，如果它是一个AStaticMeshActor，则返回它的UStaticMeshComponent
	UStaticMeshComponent* GetActorSMC(AActor* _InActor);

	//获取AActor类型
	EActorType GetActorType(AActor* _InActor);

	//传入服务器同步数据，调用LoadObj，直接创建Actor，它会从硬盘中加载新资源。
	AActor* CreateActor(UWorld* _OwnerWorld, TSharedPtr<FContentItemSpace::FContentItem> _SynData, FVector _Location = FVector::ZeroVector, FRotator _Rotation = FRotator::ZeroRotator, FVector _Scale = FVector(1, 1, 1));
	//传入服务器同步数据，调用LoadObj，直接创建Material
	UMaterialInterface* CreateMaterial(UWorld* _OwnerWorld, TSharedPtr<FContentItemSpace::FContentItem> _SynData);
	
	//通过PakID来创建Actor，Actor所用得到的资源一定是已经存在于ObjList中，否则创建失败。它不会从硬盘中加载资源。
	AActor* CreateActorFromID(UWorld* _OwnerWorld, int32 _FileID, FVector _Location = FVector::ZeroVector, FRotator _Rotation = FRotator::ZeroRotator, FVector _Scale = FVector(1, 1, 1));
	
	//加载新资源，如果资源已存在于ObjList中，则直接使用。
	FVRSObject* LoadObj(TSharedPtr<FContentItemSpace::FContentItem> _SynData, int32& _OutObjID, int32& _OutSynID);
	
	//通过PakID直接加载已存在于ObjList中的资源，否则创建失败。他不会从硬盘中加载资源。
	FVRSObject* LoadObjFromFileID(int32 _FileID, int32& _OutObjID, int32& _OutSynID);

	//载入Common包Pak
	void LoadCommonData();

	//载入本地的pak文件，可能是模型，材质，交互物体，交互灯
	FVRSObject LoadPakFile(FString InFilePath);

	AActor* CreateCustomActor(UWorld* _OwnerWorld, FString _FilePath, FVector _Location = FVector(0, 0, 0), FRotator _Rotation = FRotator::ZeroRotator, FVector _Scale = FVector(1, 1, 1));
	UMaterialInterface* CreateCustomMaterial(FString _FilePath);
	FVRSObject* LoadCustomObj(TSharedPtr<FContentItemSpace::FContentItem> _SynData, int32& _OutObjID, int32& _OutSynID);


	//获取BSP的材质
	//UMaterialInterface* GetMaterialFromBSP(UXRModelComponent* _MC);
	//UMaterialInterface* GetMaterialFromBSP(const FXRBspSurf& _Surface);//add to htwen 2016.10.27

	//设置BSP的材质
	//void SetBSPMaterial(UXRModelComponent* _MC, UMaterialInterface* _Material);
	//void SetBSPMaterial(FXRBspSurf* _Surface, UMaterialInterface* _Material);//add to htwen 2016.10.27

	//是否开启UseProjectiveUV功能，会对应两套不同的材质参数。
	void SetMaterialRotation(UMaterialInstanceDynamic* _MID, float _Angle);
	void SetMaterialOffsetU(UMaterialInstanceDynamic* _MID, float _OffsetU);
	void SetMaterialOffsetV(UMaterialInstanceDynamic* _MID, float _OffsetV);
	void SetMaterialTilingU(UMaterialInstanceDynamic* _MID, float _TilingU);
	void SetMaterialTilingV(UMaterialInstanceDynamic* _MID, float _TilingV);

	float GetMaterialRotation(UMaterialInstanceDynamic* _MID);
	float GetMaterialOffsetU(UMaterialInstanceDynamic* _MID);
	float GetMaterialOffsetV(UMaterialInstanceDynamic* _MID);
	float GetMaterialTilingU(UMaterialInstanceDynamic* _MID);
	float GetMaterialTilingV(UMaterialInstanceDynamic* _MID);
	bool GetMaterialUseProjectiveUV(UMaterialInstanceDynamic* _MID);

	//恢复模型的默认材质
	void ClearActorOverridenMaterials(AActor* _Actor);
	//恢复模型的尺寸信息
	void ResetActorTransform(AActor* _Actor);

	//颠倒U和V的值
	void SwitchMaterialUV(UMaterialInstanceDynamic* _MID);
	//映射旧的材质球名称到新的V7版，如 WallPaper->V7_Base_Plastic, Floor->V7_Base_Wood, GroundTile->V7_Base_Ceramics
	static FString ConvertOldMaterialNameToV7(FString _OldMaterialName);
	//映射旧的材质参数到新的V7版，主要是0-19
	static int32 ConvertOldMaterialIDToV7(int32 _OldID);
	//6200版本之前的材质OffsetUV取值范围为-1-1，6200及之后版本范围0-100，要做一个映射
	static float ConvertOldOffsetToV7(float _OldOffset);
	//6200版本之前的材质Tiling映射到V7版本需要乘0.4f（UseProjectiveUV==1）
	static float ConvertOldProjectiveTilingToV7(float _OldTiling);

	//把从服务器获取的材质参数Json字符串转换为模型材质参数列表
	bool ConvertJsonToModelMaterialList(bool _bConverToV7, FString _ParaStr, TArray<FModelMaterialData>& _OutMaterialList);
	//把模型材质列表信息转换成Json字符串。bOnlyDirty为true时，会先调用CheckDirty，只有发生变化的值才会保存转换成Json
	FString ConvertModelMaterialListToJson(TArray<FModelMaterialData>& _MaterialList, bool _bOnlyServerDirty, bool _bOnlyOriginalDirty = false);
	//根据输入的材质名称，创建MID，生成新的FModelMaterialData
	FModelMaterialData CreateMaterialData(FString _MaterialName, FVector2D _TextureSize = FVector2D(800,800), UTexture* _DiffuseMap = NULL, UTexture* _NormalMap = NULL);
	//解析模型文件中的XML，创建材质。
	FModelMaterialData CreateModelMaterialData(int32 _Version, FXmlNode* _MaterialNode, TMap<FString, UTexture*>& _TextureMap);
	//解析模型文件中的XML，创建材质。V7之前就材质系统使用。
	FModelMaterialData CreateModelMaterialData_Internal_BeforeV7(FXmlNode* _MaterialNode, TMap<FString, UTexture*>& _TextureMap);
	//解析模型文件中的XML，创建材质。V7使用。
	FModelMaterialData CreateModelMaterialData_Internal_V7(FXmlNode* _MaterialNode, TMap<FString, UTexture*>& _TextureMap);
	//根据V7材质名称，创建一个MID，并设置所涉及的参数默认值
	FModelMaterialData CreateModelMaterialDataFromName_V7(int32 _MaterialTypeIndex);
	//为传入的MaterialData添加自定义的一些参数到ParaList中，比如是否启用漫反射贴图，法线贴图序号，材质类型序号等
	void AddCustomMaterialParametersForMaterialData_V7(FModelMaterialData& _OutMaterialData);
	//获取材质类型序号 布料0-99 金属100-199 木质200-299 皮革300-399
	int32 GetNormalTextureIndex(UTexture* _Texture);
	UTexture* GetNormalTexture(int32 _Index);
	//根据传入的材质名称返回材质序号
	int32 GetMaterialTypeIndex(FString _MaterialName, bool _bDisplayName = false);
	//根据材质名称修改已存在的MaterialData
	void ChangeModelMaterialData(int32 _NewMaterialTypeIndex, FModelMaterialData* _OldMaterialData);

	//把从服务器获取的参数Json字符串转换为模型属性参数列表
	bool ConvertJsonToModelSettingsList(FString _ParaStr, TArray<FXRParameter>& _OutSettingsList);
	FString ConvertModelSettingsListToJson(TArray<FXRParameter>& _SettingsList);
	void CollectActorLightComponentsParameters(AActor* _Actor, TArray<FXRParameter>& _OutSettingsList);
	void SetActorLightComponentParameters(AActor* _Actor, TArray<FXRParameter>& _SettingsList);

	//从Actor中查找第一个网格组件，如果是StaticMeshActor，则返回它的StaticMeshComponent，如果是蓝图物体遍历它的Components，返回第一个MeshComponent
	UMeshComponent* GetFirstMeshComponent(AActor* _Actor);

	//把一份材质参数数据覆盖到另一份数据上。其中_SrcData的Object不会覆盖_DesData中的Object，仅仅是覆盖ParaList参数，最后会_DesData.ParaList[i].DIM->SetParameters...
	bool OverrideMaterialData(FModelMaterialData& _DesData, FModelMaterialData& _SrcData);

	//传入一个XML Node，得出材质信息，以及ActorName
	void GetMeshMaterialDataFromXMLNode(const FXmlNode* _InNode, FMeshMaterialData& _OutData, FString& _OutActorName);

	void AppendSynList(TArray<TSharedPtr<FContentItemSpace::FContentItem>> _NewList);
	//退出户型时调用
	void ClearData();

	UFUNCTION()
	void OnActorPasted(AActor* _Actor);
	AActor* CreateActorInternal(FVRSObject* InObjectInfo);
	UMaterialInterface* CreateMaterialInternal(FVRSObject* InObjectInfo);
private:
	
	bool LoadObjInternal(FVRSObject& _OutObj);
	void MountPakReturnFiles(FString _PakPath, TArray<FString>& OutPakFilenameList, int32 _Order = 3, bool _IDontWantToMount = false);
	void MountPak(FString _PakPath);
	//卸载所有模型资源
	void UnloadModelPak();
	void GetParentMostPathInternal(UMaterialInterface* _MI);
	TArray<FString> TempPaths;
public:
	FName PendingLevelName;
	//XML路径。如果该变量不为空，则会在打开任意户型时，尝试加载户型方案
	FString PendingLoadHomePlanXMLPath;
	//XML路径。如果该变量不为空，则会在打开任意户型时，尝试加载家具组方案
	FString PendingLoadGroupPlanXMLPath;
	//XML路径。如果该变量不为空，则在打开DIYTemplate地图时，第一件事就是加载该xml文件，解析并构建户型
	FString PendingLoadDIYHomeXML;

	//材质参数静态对照表
	TMap<int32, FXRParameter> StaticMIParaList;
	//模型设置参数静态对照表
	TMap<int32, FXRParameter> StaticModelParaList;
	//Common9中的新材质球（V7版）名称信息对照表 
	UPROPERTY()
		TArray<FCommonMaterialData> StaticCommonMaterialList;
	UPROPERTY()
		UTexture* EmptyTexture;
	UPROPERTY()
		TArray<UTexture*> IESList;
	UPROPERTY()
		TArray<UTexture*> NormalMapList_Cloth;
	UPROPERTY()
		TArray<UTexture*> NormalMapList_Metal;
	UPROPERTY()
		TArray<UTexture*> NormalMapList_Wood;
	UPROPERTY()
		TArray<UTexture*> NormalMapList_Leather;

	//int32 FindCommonMaterialIndex(FString _MaterialName);
	//点击进入户型，通过户型的Pak名称，来尝试加载Pak文件，然后找出LevelPath，并且Open之
	TMap<FString, FString> LevelPathMap;
	//载入方案的xml版本不同，会有不同的处理
	int32 CurLoadPlanVersion;

	TSharedPtr<FPakPlatformFile> PakPlatform;
	IPlatformFile* LocalPlatformFile;
	//0:uasset 1:pak 2:other
	int8 DLCFileMode;
	bool bGodMode;
	UPROPERTY()
		TArray<FVRSObject> ObjList;
	TArray<TSharedPtr<FContentItemSpace::FContentItem>> SynList;

	//缩略图渲染资源
	//UPROPERTY()
	//	UXRMaterialInstanceThumbnailRenderer* Render_ThumbnailMI;
	//UPROPERTY()
	//	UXRTextureThumbnailRenderer* Render_ThumbnailTexture;
	//FSlateTextureRenderTarget2DResource* SharedThumbnailRT;
	//TSharedPtr<const FWebImage> TheWebImage;
	//TSet<FString> CommentateActors;
	//TEnumAsByte<EVRSCameraMode> CameraMode;

	/*class AXRPointLightActor* AddPointLight(UWorld* InWorld, float _AttenuationRadius = 700.f, float _Intensity = 5000.f);
	class AXRSpotLightActor* AddSpotLight(UWorld* InWorld);
	class AXRReflectionCaptureActor* AddReflectionSphere(UWorld* InWorld);
	class AXRLevelAssetBoardActor* AddLevelAssetBoard(UWorld* InWorld);*/

	//int32 GetHomeID();
	//int32 GetPlanID();
	
	//当前户型为绘制户型
	bool bDIYHome;
	//当前加载了之前保存的绘制户型，而不是从新开始绘制
	bool bLoadDIYHome;
	//记录了当前户型载入过程中是否载入了光源等物体，如果是，则在清空方案的时候不会清空。
	bool bLoadEnvironmentAssets;
	//当前加载的户型的所有信息
	//FContentItemSpace::FContentItem LoadedHomeItemData;
	//FContentItemSpace::FContentItem LoadedPlanItemData;

	FActorDelegate OnLevelActorAdded;
	FActorDelegate OnLevelActorRemoved;
	FSimpleDelegate OnLevelActorCleared;

	struct ActorSizeInfo
	{
		FString ID = TEXT("-1");
		int32 TypeID = 0;
		float Length = 0;
		float Width = 0;
		float Height = 0;
		//void ComputeFromActor(AActor* InActor, FString InID, int32 InTypeID = 0);
		//void ComputeFromGroupActor(AXRGroupActor* InActor, FString InID, int32 InTypeID = 0);
	};
	//void addGroupActorSizeInfo(AXRGroupActor* InGroupActor, FString InID, int32 InTypeID);
	//void UploadActorSize();
	//void Callback_UpdateActorSize(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessful);
	TArray<ActorSizeInfo> UpdateSizeActorList;

	UWorld* CurWorld;

};
