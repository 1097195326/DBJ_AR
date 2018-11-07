/**
 * Copyright 2018 ����������(���)�Ƽ����޹�˾.
 * All Rights Reserved.
 * http://www.dabanjia.com
 *
 * @File XRCommonTypes.h
 * @Description ȫ��ͨ�õĽṹ���壬ͨ��ֻ��Ҫ�����ģ��Ϳ���ֱ��ʹ��
 *
 * @Author ������
 * @Date 2018��4��3��
 * @Version 1.0
 */
#pragma once

DECLARE_DELEGATE(FVoidDelegate);
DECLARE_DELEGATE_OneParam(FInputKeyDelegate, const struct FKeyEvent&);
DECLARE_DELEGATE_OneParam(FInt32Delegate, const int32);
DECLARE_DELEGATE_FourParams(FFourInt32Delegate, const int32, const int32, const int32, const int32);
DECLARE_DELEGATE_OneParam(FFStringDelegate, const FString);
DECLARE_DELEGATE_OneParam(FFloatDelegate, const float);
DECLARE_DELEGATE_OneParam(FVectorDelegate, const FVector&);
DECLARE_DELEGATE_OneParam(FVector2DDelegate, const FVector2D&);
DECLARE_DELEGATE_OneParam(FBoolDelegate, bool);
DECLARE_DELEGATE_OneParam(FObjectDelegate, UObject*);
DECLARE_DELEGATE_OneParam(FActorDelegate, class AActor*);
DECLARE_DELEGATE_OneParam(FOnDelegateColor, const FLinearColor&);
DECLARE_DELEGATE_TwoParams(FLine2DDelegate, const FVector2D&, const FVector2D&);
DECLARE_DELEGATE_ThreeParams(FCircle2DDelegate, const FVector2D&, const FVector2D&, const FVector2D&);
DECLARE_DELEGATE_RetVal(TSharedPtr<class SWidget>, FGetWidgetDelegate);
DECLARE_DELEGATE_OneParam(FXRObjectesDelegate, TArray<TSharedPtr< class FXRObject>>);


 /*
 *	һ��Actor�ڳ����е����ͣ���̬MeshActor�����ƶ�MeshActor����ͼActor���������Actor����Դ���������ȵ���
 */
enum EActorType
{
	//�決�����еĵ�����FBX�ľ�̬ģ��
	Static,
	//���ƶ��ļҾ�
	Moveable,
	//��ͼ����
	Blueprint,
	//����
	Blueprint_Window,
	//��Դ��������Ȼ������
	EnvironmentAsset,

	Other,
};

//Ӳ���ϵ��ļ����ͣ����ͣ�ģ�ͣ����ʣ���Ƶ����ͼ�࣬��Ƥ���񣬽����ƣ������ļ��ȣ�������ֱ��ȡ���ڼ��ع��̵Ľ�����ʽ
enum EResourceType
{
	//��������ģ��
	SkeletalMesh = -3,
	//�ɽ����ĵ�
	Light = -2,
	//��
	None = -1,
	//���ƻ���
	DrawHome = 0,
	//�決����
	CookedHome = 1,
	//���ƶ��ҵľ�ģ��
	MoveableMesh = 2,
	//��ͼ
	BlueprintClass = 3,
	//��ֽ��ש
	Material = 4,
	//���ͷ���
	LevelPlan = 5,
	//�鷽��
	GroupPlan = 6,
	//��Ŀ
	Project = 9,
	//ʩ��ͼJson
	Construction = 10,
	//ʩ��ͼͼƬ��
	ConstructionImages = 11,
	//�ذ�ƴ��
	CustomlizedFloor = 12,
	//����
	CustomlizedCeling = 13,
	//����ǽ
	CustomlizedWall = 14,
	//ǽ��������
	Texture = 15
};

//Ӳ���ϵ��ļ���������״̬�������ڣ����������У��Ѿ�����������
enum EFileExistenceState
{
	//������Ӳ����
	NotExist,
	//�������صȴ�����
	PendingDownload,
	//�Ѵ��ڣ�����ȷ��������
	Exist,
	//�����Ϸ�
	Complete,
};

enum EContentItemFlag
{
	PF_NoFlags = 0x00000000,
	//�Ƿ�Ϊ�Ҿ�
	PF_Furniture = 0x00000001,
	//�Ƿ�Ϊ����
	PF_Home = 0x00000002,
	//�Ƿ�Ϊ����
	PF_Plan = 0x00000004,
	//���ͷ���
	PF_LevelPlan = 0x00000008,
	//�Ҿ���
	PF_GroupPlan = 0x00000010,
	//�Ƿ�ͬʱ���ػ���
	PF_LoadHome = 0x00000020,
	//�Ƿ������µ���Ʒ
	PF_Newest = 0x00000040,
	//�Ƿ�ɱ༭
	PF_Editable = 0x00000080,
	//�Ƿ�Ϊ���ղص���Ʒ
	PF_InFavorite = 0x00000100,
	//�Ƿ����ײ���Ʒ
	PF_InPackage = 0x00000200,
	//�Ƿ�Ϊ�Զ������
	PF_AutoDesignGroup = 0x00000400,
	//���滻��Ʒ
	PF_Replacement = 0x00000800,
};

//��ש�ذ��̷�
enum EPavingMethodType
{
	//��
	NoneMethod = -1,
	//����ֱ��
	Continue,
	//������
	People,
	//�����̷�
	Worker, 
	//�����̷�
	Wind, 
	//����̷�
	Space,
	//�����̷�
	Interlace,
	//��������
	TrapeZoid,
	//ˮ��ƴ��
	WaterKnifeMethod,
	//������
	//WaveLine,
	//�н�ש
	CornerBrickMethod,
	//�޽�ש
	AntiCornerBrickMethod
};

FORCEINLINE EContentItemFlag operator|(EContentItemFlag Arg1, EContentItemFlag Arg2)
{
	return EContentItemFlag(uint32(Arg1) | uint32(Arg2));
}

FORCEINLINE EContentItemFlag operator&(EContentItemFlag Arg1, EContentItemFlag Arg2)
{
	return EContentItemFlag(uint32(Arg1) & uint32(Arg2));
}

FORCEINLINE EContentItemFlag operator~(EContentItemFlag Arg)
{
	return EContentItemFlag(RF_AllFlags & ~uint32(Arg));
}

FORCEINLINE void operator&=(EContentItemFlag& Dest, EContentItemFlag Arg)
{
	Dest = EContentItemFlag(Dest & Arg);
}
FORCEINLINE void operator|=(EContentItemFlag& Dest, EContentItemFlag Arg)
{
	Dest = EContentItemFlag(Dest | Arg);
}

namespace FContentItemSpace
{
	//��Ʒ��Ϣ�ṹ��
	class FProductObj
	{
		FProductObj() {}
		FProductObj(float _Price, float _PriceDiscount, FString _URL, float _Length, float _Width, float _Height)
			:Price(_Price), PriceDiscount(_PriceDiscount), URL(_URL), Length(_Length), Width(_Width), Height(_Height)
		{}

		float Price;
		float PriceDiscount;
		FString URL;

		float Length = 0;
		float Width = 0;
		float Height = 0;
	};

	//��Դ��Ϣ�ṹ��
	class FResObj : public TSharedFromThis<FResObj>
	{
	public:
		FResObj() {}
		FResObj(FString _FileName, FString _FilePath, FString _FileURL, FString _FileMD5)
			: FileName(_FileName), FilePath(_FilePath), FileURL(_FileURL), FileMD5(_FileMD5)
		{}
		~FResObj() {}

		FString FileName;
		FString FilePath;
		FString FileURL;
		FString FileMD5;
		int32 Version;
		EFileExistenceState FileState;
	};

	//ģ����Ϣ
	class FModelRes : public FResObj
	{
	public:
		FModelRes(FString FileName, FString FilePath, FString FileURL, FString FileMD5, FString _MaterialParameter, FString _LightParameter)
			: FResObj(FileName, FilePath, FileURL, FileMD5)
			, MaterialParameter(_MaterialParameter)
			, LightParameter(_LightParameter)
		{}

		FString MaterialParameter;
		FString LightParameter;
	};

	/**
	* ������Ϣ
	*/
	class FXRHomeRes : public FResObj
	{
	public:
		FXRHomeRes() {}

		FXRHomeRes(
			const FString& FileName,
			const FString& FilePath,
			const FString& FileURL,
			const FString& FileMD5,
			int32 InHomeId,
			const FString& InHomeName,
			int32 InBedroomNum,
			int32 InLivingRoomNum,
			int32 InKitchenNum,
			int32 InBathroomNum,
			float InFloorArea,
			float InInnerArea,
			int32 InProvinceId,
			int32 InCityId,
			int32 InAreaId,
			int32 InVillageId,
			const FString& InAddressDetail,
			int32 InOrientationId,
			int32 InBuildingTypeId
		)
			: FResObj(FileName, FilePath, FileURL, FileMD5)
			, HomeId(InHomeId)
			, HomeName(InHomeName)
			, BedroomNum(InBedroomNum)
			, LivingRoomNum(InLivingRoomNum)
			, KitchenNum(InKitchenNum)
			, BathroomNum(InBathroomNum)
			, FloorArea(InFloorArea)
			, InnerArea(InInnerArea)
			, ProvinceId(InProvinceId)
			, CityId(InCityId)
			, AreaId(InAreaId)
			, VillageId(InVillageId)
			, AddressDetail(InAddressDetail)
			, OrientationId(InOrientationId)
			, BuildingTypeId(InBuildingTypeId)
		{}

		/** ����id */
		int32 HomeId;

		/** �������� */
		FString HomeName;

		/** �������� */
		int32 BedroomNum;

		/** �������� */
		int32 LivingRoomNum;

		/** �������� */
		int32 KitchenNum;

		/** ���������� */
		int32 BathroomNum;

		/** ������� */
		float FloorArea;

		/** ������� */
		float InnerArea;

		/** ʡid */
		int32 ProvinceId;

		/** ��id */
		int32 CityId;

		/** ��id */
		int32 AreaId;

		/** С��id */
		int32 VillageId;

		/** ��Ϣ��ַ */
		FString AddressDetail;

		/** ����id */
		int32 OrientationId;

		/** ��������id */
		int32 BuildingTypeId;
	};

	/**
	* ��Ŀ��Ϣ
	*/
	class FProjectRes : public FResObj
	{
	public:
		FProjectRes(FString FileName, FString FilePath, FString FileURL, FString FileMD5, int64 InCreateDate, int64 InUpdateDate)
			: FResObj(FileName, FilePath, FileURL, FileMD5)
			, CreateDate(InCreateDate)
			, UpdateDate(InUpdateDate)
		{}

		//����ʱ��
		int64 CreateDate;
		//����޸�ʱ��
		int64 UpdateDate;
	};

	//��׼���ݵ�Ԫ
	class FContentItem
	{
	public:
		FContentItem(int32 InID)
		{
			ItemFlag = EContentItemFlag::PF_NoFlags;
			ID = InID;
		}

		FContentItem()
		{
			ItemFlag = EContentItemFlag::PF_NoFlags;
			ID = -1;
		}

		FContentItem(FResObj _ResObj)
		{
		}

		FContentItem(
			EResourceType _ResourceType,
			int32 _ID,
			FString _Name,
			FString _ThumbnailURL,
			TSharedPtr<FResObj> _ResObj,
			EPavingMethodType _PavingMethodType = EPavingMethodType::NoneMethod,
			TSharedPtr<FProductObj> _ProObj = NULL,
			EContentItemFlag _ItemFlag = EContentItemFlag::PF_NoFlags
		)
			: ResourceType(_ResourceType), ID(_ID), Name(_Name), ThumbnailURL(_ThumbnailURL), ResObj(_ResObj), ProObj(_ProObj)
		{
			ItemFlag = EContentItemFlag::PF_NoFlags;
			ItemFlag |= _ItemFlag;
		}

		//��ԴΨһID
		int32 ID;
		//��ʾ����
		FString Name;
		//��ʾ����ͼ��ַ
		FString ThumbnailURL;
		//����Դ������
		EContentItemFlag ItemFlag;
		//��Դ���ͣ�������Ӧ�Ľ���ResObj����
		EResourceType ResourceType;

		//�����Դ����
		TSharedPtr<FResObj> ResObj;
		//��Ŷ�Ӧ����Ʒ��Ϣ
		TSharedPtr<FProductObj> ProObj;

		//EPavingMethodType PavingMethod;
	};

	/**
	* ������Ϣ
	*/
	class FXRTextureRes : public FResObj
	{
	public:
		FXRTextureRes() {}

		FXRTextureRes(
			const FString& FileName,
			const FString& FilePath,
			const FString& FileURL,
			const FString& FileMD5,
			int32 InWidth,
			int32 InHeight,
			EPavingMethodType InPavingMethod
		)
			: FResObj(FileName, FilePath, FileURL, FileMD5)
			, Width(InWidth)
			, Height(InHeight)	
			, EPavingMethod(InPavingMethod)
		{}

		/** ������*/
		int32 Width;

		/** ����߶� */
		int32 Height;

		/** ������ʽ */
		EPavingMethodType EPavingMethod;

		/**��ʱʹ�ã���̨�ԽӺ��ɾ��*/
		//��ʵ��������
		FString FileRealURL1;
		//��ʵ��������
		FString FileRealURL2;
		//����ͼ
		FString FileThumbnailURL2;

		FString FileRealURLReplace;
		/*******************/

	};
}

/*
*	��Ŀ�㼶����
*/
struct FCategoryContentItem
{
	FCategoryContentItem() {}
	FCategoryContentItem(FString _Name, int32 _Key, int32 _Value)
		: Name(_Name), Key(_Key), Value(_Value)
	{}
	~FCategoryContentItem() {}

	FString Name;
	int32 Key;
	int32 Value;

	TArray<FCategoryContentItem> CategoryList;
};