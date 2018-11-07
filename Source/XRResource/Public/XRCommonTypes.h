/**
 * Copyright 2018 美屋三六五(天津)科技有限公司.
 * All Rights Reserved.
 * http://www.dabanjia.com
 *
 * @File XRCommonTypes.h
 * @Description 全局通用的结构定义，通常只需要引入该模块就可以直接使用
 *
 * @Author 马云龙
 * @Date 2018年4月3日
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
 *	一个Actor在场景中的类型：静态MeshActor，可移动MeshActor，蓝图Actor，环境组件Actor（光源，反射球，热点球）
 */
enum EActorType
{
	//烘焙户型中的导入自FBX的静态模型
	Static,
	//可移动的家具
	Moveable,
	//蓝图类型
	Blueprint,
	//窗户
	Blueprint_Window,
	//光源，反射球等环境组件
	EnvironmentAsset,

	Other,
};

//硬盘上的文件类型：户型，模型，材质，音频，蓝图类，蒙皮网格，交互灯，方案文件等；该类型直接取决于加载过程的解析方式
enum EResourceType
{
	//带动画的模型
	SkeletalMesh = -3,
	//可交互的灯
	Light = -2,
	//无
	None = -1,
	//绘制户型
	DrawHome = 0,
	//烘焙户型
	CookedHome = 1,
	//可移动家的具模型
	MoveableMesh = 2,
	//蓝图
	BlueprintClass = 3,
	//壁纸瓷砖
	Material = 4,
	//户型方案
	LevelPlan = 5,
	//组方案
	GroupPlan = 6,
	//项目
	Project = 9,
	//施工图Json
	Construction = 10,
	//施工图图片包
	ConstructionImages = 11,
	//地板拼花
	CustomlizedFloor = 12,
	//吊顶
	CustomlizedCeling = 13,
	//造型墙
	CustomlizedWall = 14,
	//墙顶地纹理
	Texture = 15
};

//硬盘上的文件的完整性状态：不存在，正在下载中，已经完整下载完
enum EFileExistenceState
{
	//不存在硬盘上
	NotExist,
	//正在下载等待队列
	PendingDownload,
	//已存在，但不确定完整性
	Exist,
	//完整合法
	Complete,
};

enum EContentItemFlag
{
	PF_NoFlags = 0x00000000,
	//是否为家具
	PF_Furniture = 0x00000001,
	//是否为户型
	PF_Home = 0x00000002,
	//是否为方案
	PF_Plan = 0x00000004,
	//户型方案
	PF_LevelPlan = 0x00000008,
	//家具组
	PF_GroupPlan = 0x00000010,
	//是否同时加载户型
	PF_LoadHome = 0x00000020,
	//是否是最新的物品
	PF_Newest = 0x00000040,
	//是否可编辑
	PF_Editable = 0x00000080,
	//是否为已收藏的物品
	PF_InFavorite = 0x00000100,
	//是否属套餐物品
	PF_InPackage = 0x00000200,
	//是否为自动设计组
	PF_AutoDesignGroup = 0x00000400,
	//可替换物品
	PF_Replacement = 0x00000800,
};

//瓷砖地板铺法
enum EPavingMethodType
{
	//无
	NoneMethod = -1,
	//连续直铺
	Continue,
	//人字铺
	People,
	//工字铺法
	Worker, 
	//旋风铺法
	Wind, 
	//间隔铺法
	Space,
	//交错铺法
	Interlace,
	//三六九铺
	TrapeZoid,
	//水刀拼花
	WaterKnifeMethod,
	//波打线
	//WaveLine,
	//有角砖
	CornerBrickMethod,
	//无角砖
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
	//商品信息结构体
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

	//资源信息结构体
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

	//模型信息
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
	* 户型信息
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

		/** 户型id */
		int32 HomeId;

		/** 户型名称 */
		FString HomeName;

		/** 卧室数量 */
		int32 BedroomNum;

		/** 客厅数量 */
		int32 LivingRoomNum;

		/** 厨房数量 */
		int32 KitchenNum;

		/** 卫生间数量 */
		int32 BathroomNum;

		/** 户型面积 */
		float FloorArea;

		/** 套内面积 */
		float InnerArea;

		/** 省id */
		int32 ProvinceId;

		/** 市id */
		int32 CityId;

		/** 区id */
		int32 AreaId;

		/** 小区id */
		int32 VillageId;

		/** 消息地址 */
		FString AddressDetail;

		/** 朝向id */
		int32 OrientationId;

		/** 房屋类型id */
		int32 BuildingTypeId;
	};

	/**
	* 项目信息
	*/
	class FProjectRes : public FResObj
	{
	public:
		FProjectRes(FString FileName, FString FilePath, FString FileURL, FString FileMD5, int64 InCreateDate, int64 InUpdateDate)
			: FResObj(FileName, FilePath, FileURL, FileMD5)
			, CreateDate(InCreateDate)
			, UpdateDate(InUpdateDate)
		{}

		//创建时间
		int64 CreateDate;
		//最后修改时间
		int64 UpdateDate;
	};

	//标准内容单元
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

		//资源唯一ID
		int32 ID;
		//显示名称
		FString Name;
		//显示缩略图地址
		FString ThumbnailURL;
		//该资源的属性
		EContentItemFlag ItemFlag;
		//资源类型，用来对应的解析ResObj数据
		EResourceType ResourceType;

		//存放资源数据
		TSharedPtr<FResObj> ResObj;
		//存放对应的商品信息
		TSharedPtr<FProductObj> ProObj;

		//EPavingMethodType PavingMethod;
	};

	/**
	* 纹理信息
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

		/** 纹理宽度*/
		int32 Width;

		/** 纹理高度 */
		int32 Height;

		/** 铺贴方式 */
		EPavingMethodType EPavingMethod;

		/**临时使用，后台对接后可删除*/
		//真实材质数据
		FString FileRealURL1;
		//真实材质数据
		FString FileRealURL2;
		//缩略图
		FString FileThumbnailURL2;

		FString FileRealURLReplace;
		/*******************/

	};
}

/*
*	类目层级数据
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