#pragma once
#include "ResTools.h"
#include "Engine.h"
#include "Core.h"
#include "ResTypes.generated.h"

struct FMeshMaterialData
{
	FString SlotName;
	int32 PakID;
	FString ParaStr;
	float RotateUV;
	float OffsetU;
	float OffsetV;
	float TilingU;
	float TilingV;
	bool bProjectiveUV;

	FMeshMaterialData() {}
	FMeshMaterialData(FString _SlotName, int32 _PakID, FString _ParaStr,
		float _RotateUV = 0.f, float _OffsetU = 0.f, float _OffsetV = 0.f, float _TilingU = 0.f, float _TilingV = 0.f, bool _bProjectiveUV = false)
		: SlotName(_SlotName), PakID(_PakID), ParaStr(_ParaStr),
		RotateUV(_RotateUV), OffsetU(_OffsetU), OffsetV(_OffsetV), TilingU(_TilingU), TilingV(_TilingV), bProjectiveUV(_bProjectiveUV)
	{
	}
};

//参数结构体
struct FXRParameter
{
	enum EVarType
	{
		E_Float,
		E_Vec3,
		E_Bool,
	};

	int32 ID;
	FString ParaDisplayName;
	FString ParaDisplayNameEN;
	FString ParaName;
	EVarType VarType;

	//实时变化的当前值
	float Value;
	//服务器保存的值
	float ServerValue;
	//导入时的原始值
	float OriginalValue;
	float MaxValue;
	float MinValue;
	float SliderMaxValue;
	float SliderMinValue;

	//实时变化的颜色值
	FVector Color;
	//服务器保存的颜色值
	FVector ServerColor;
	//导入时的原始颜色值
	FVector OriginalColor;

	bool bCheck;
	bool bOriginalCheck;
	bool bServerCheck;

	//当前数值与服务器数值不一致时为true，通常用来把材质参数保存的方案xml中时更新并使用
	bool bServerDirty;
	//当前数值与模型导入的初始值不一致时为true，通常用来把材质参数保存到服务器时更新并使用
	bool bOriginalDirty;

	void OverrideValue(FXRParameter& _Src)
	{
		if (VarType == EVarType::E_Float)
			Value = _Src.Value;
		else if (VarType == EVarType::E_Vec3)
			Color = _Src.Color;
		else if (VarType == EVarType::E_Bool)
			bCheck = _Src.bCheck;
	}

	void SetInitializedValue(float _Value)
	{
		Value = _Value;
		ServerValue = _Value;
		OriginalValue = _Value;
	}

	void SetInitializedVector(FVector _Vec)
	{
		Color = _Vec;
		ServerColor = _Vec;
		OriginalColor = _Vec;
	}

	void SetInitializedCheck(bool _bCheck)
	{
		bCheck = _bCheck;
		bServerCheck = _bCheck;
		bOriginalCheck = _bCheck;
	}

	FXRParameter() {
		SliderMinValue = 0;
		SliderMaxValue = 0;
	}

	FXRParameter(FString _DisplayName, FString _DisplayNameEN, FString _ParaName, float _MinValue, float _MaxValue, float _Value = 0.f)
	{
		ID = 0;
		ParaDisplayName = _DisplayName;
		ParaDisplayNameEN = _DisplayNameEN;
		ParaName = _ParaName;
		VarType = EVarType::E_Float;
		Value = _Value;
		ServerValue = _Value;
		OriginalValue = _Value;
		Color = FVector::ZeroVector;
		ServerColor = FVector::ZeroVector;
		OriginalColor = FVector::ZeroVector;
		bCheck = false;
		bOriginalCheck = false;
		bServerCheck = false;
		MinValue = _MinValue;
		MaxValue = _MaxValue;
		SliderMinValue = 0;
		SliderMaxValue = 0;
	}

	FXRParameter(FString _DisplayName, FString _DisplayNameEN, FString _ParaName, FVector _Color = FVector::ZeroVector)
	{
		ID = 0;
		ParaDisplayName = _DisplayName;
		ParaDisplayNameEN = _DisplayNameEN;
		ParaName = _ParaName;
		VarType = EVarType::E_Vec3;
		Value = 0.f;
		Color = _Color;
		ServerValue = 0.f;
		ServerColor = _Color;
		OriginalValue = 0.f;
		OriginalColor = _Color;
		bCheck = false;
		bOriginalCheck = false;
		bServerCheck = false;
		MinValue = 0.f;
		MaxValue = 1.f;
		SliderMinValue = 0;
		SliderMaxValue = 0;
	}

	FXRParameter(FString _DisplayName, FString _DisplayNameEN, FString _ParaName, bool _bCheck)
	{
		ID = 0;
		ParaDisplayName = _DisplayName;
		ParaDisplayNameEN = _DisplayNameEN;
		ParaName = _ParaName;
		VarType = EVarType::E_Bool;
		Value = 0.f;
		Color = FVector::ZeroVector;
		ServerValue = 0.f;
		ServerColor = FVector::ZeroVector;
		OriginalValue = 0.f;
		OriginalColor = FVector::ZeroVector;
		bCheck = _bCheck;
		bOriginalCheck = _bCheck;
		bServerCheck = _bCheck;
		MinValue = 0.f;
		MaxValue = 1.f;
		SliderMinValue = 0;
		SliderMaxValue = 0;
	}

	void ResetToOriginal()
	{
		Value = OriginalValue;
		Color = OriginalColor;
		bCheck = bOriginalCheck;
	}

	void ResetToServer()
	{
		Value = ServerValue;
		Color = ServerColor;
		bCheck = bServerCheck;
	}

	bool CheckServerDirty()
	{
		bServerDirty = false;
		if (VarType == EVarType::E_Float)
		{
			if (Value != ServerValue)
				bServerDirty = true;
		}
		else if (VarType == EVarType::E_Vec3)
		{
			if (Color != ServerColor)
				bServerDirty = true;
		}
		else if (VarType == EVarType::E_Bool)
		{
			if (bCheck != bServerCheck)
				bServerDirty = true;
		}
		return bServerDirty;
	}

	bool CheckOriginalDirty()
	{
		bOriginalDirty = false;
		if (VarType == EVarType::E_Float)
		{
			if (Value != OriginalValue)
				bOriginalDirty = true;
		}
		else if (VarType == EVarType::E_Vec3)
		{
			if (Color != OriginalColor)
				bOriginalDirty = true;
		}
		else if (VarType == EVarType::E_Bool)
		{
			if (bCheck != bOriginalCheck)
				bOriginalDirty = true;
		}
		return bOriginalDirty;
	}
};

//记录了Common9中的新材质系统V7版本的材质球名称及其所要暴露的参数信息
USTRUCT()
struct FCommonMaterialData
{
	GENERATED_BODY()
		enum EMaterialType
	{
		E_None = -1,
		//壁纸（塑料）
		E_Plastic = 0,
		//瓷砖（石材）
		E_Ceramics,
		//地板（木质）
		E_Wood,
		//金属
		E_Metal,
		//镜面
		E_Mirror,
		//泥土
		E_Soil,
		//发光
		E_Emissive,
		//延展
		//E_Extend,
		//普通布料
		E_Simple,
		//皮革
		E_Leather,
		//丝绸
		E_Silk,
		//透光
		E_SSS,
		//植物
		E_SSS_Plant,
		//双层
		E_Layer,
		//普通玻璃
		E_Glass_Simple,
		//水晶玻璃
		E_Glass_Caustic,
		//模糊玻璃
		E_Glass_Blur,
		//纱帘
		E_Yarn,
		//阴影
		E_Shadow,

	};

	FCommonMaterialData() {}
	FCommonMaterialData(FString _MaterialName, FString _MaterialDisplayName, TArray<int32> _ExposedParameters)
		: MaterialName(_MaterialName), MaterialDisplayName(_MaterialDisplayName), ExposedParameters(_ExposedParameters)
	{
		MaterialPath = TEXT("/Game/DLC/Common/9/Materials/") + MaterialName;
	}

	//材质球在Common9中的相对位置
	FString MaterialPath;
	//材质球的名称
	FString MaterialName;
	//材质球显示的中文名称
	FString MaterialDisplayName;
	//材质球所需要暴露的参数表
	TArray<int32> ExposedParameters;
	UPROPERTY()
		UMaterialInterface* MI;
};

//模型外接信息
USTRUCT()
struct FModelMaterialData
{
	GENERATED_USTRUCT_BODY()
		FString SlotName;
	//V7材质球类型
	FCommonMaterialData::EMaterialType MaterialType;
	//正在使用的动态材质
	UPROPERTY()
		UMaterialInstanceDynamic* DIM;
	UTexture* DiffuseMap;
	UPROPERTY()
		UTexture* NormalMap;
	UTexture* NormalMap_Override;
	UTexture* OpacityMap;
	//只有父材质球名称前缀位"V7_"，即新材质系统，才会显示材质类型下拉列表，允许替换V7版的其他材质
	bool bReplaceable;

	TArray<FXRParameter> ParaList;
	FModelMaterialData()
	{
		DiffuseMap = NULL;
		NormalMap = NULL;
		NormalMap_Override = NULL;
		OpacityMap = NULL;
		DIM = NULL;
		bReplaceable = false;
	}
	FModelMaterialData(FString _SlotName, FCommonMaterialData::EMaterialType _MaterialType, UMaterialInstanceDynamic* _DIM, TArray<FXRParameter>& _ParaList, bool _bReplaceable = false)
		:SlotName(_SlotName), MaterialType(_MaterialType), DIM(_DIM), ParaList(_ParaList), bReplaceable(_bReplaceable)
	{
		DiffuseMap = NULL;
		NormalMap = NULL;
		NormalMap_Override = NULL;
		OpacityMap = NULL;
		bReplaceable = false;
	}

	void ResetToOriginal()
	{
		for (auto& It : ParaList)
		{
			It.ResetToOriginal();
		}
		NormalMap_Override = NULL;
	}

	void ResetToServer()
	{
		for (auto& It : ParaList)
		{
			It.ResetToServer();
			if (It.VarType == FXRParameter::EVarType::E_Float)
			{
				DIM->SetScalarParameterValue(FName(*It.ParaName), It.Value);
			}
			else if (It.VarType == FXRParameter::EVarType::E_Vec3)
			{
				FLinearColor ColorValue;
				ColorValue.R = It.Color.X;
				ColorValue.G = It.Color.Y;
				ColorValue.B = It.Color.Z;
				ColorValue.A = 1;
				DIM->SetVectorParameterValue(FName(*It.ParaName), ColorValue);
			}
		}
	}
};