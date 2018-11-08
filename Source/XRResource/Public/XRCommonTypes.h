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
#include "XRTypes.h"
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
	//����
	PipeLine,

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
	Home = 0,
	//�決����
	CookedHome = 1,
	//���ƶ��ҵľ�ģ��
	MoveableMesh = 2,
	//��ͼ
	BlueprintClass = 3,
	//��ֽ��ש
	Material = 4,
	//���ͷ���
	Plan = 5,
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
	Texture = 15,
	//ˮ���ز�
	Hydropower = 16,
	//Ӳװ�����е�dxfģ������
	HardDXF = 17,
	//Ӳװ�����е�pakģ������
	HardPAK = 18,
	//������Ϣ
	ComponentDXF = 19,
    //�ŵĲ�������(��ʱ���)
    DoorTexture = 10000,
};

//����������
enum EMeshSnapType
{
	MST_None = 0,
	//ǽ��
	MST_Wall,
	//����
	MST_Bottom,
	//����
	MST_Top,
	//̨��
	MST_TableFace,
};

//ģ����ת�������
enum EMeshOriginType
{
	//0
	MOT_None = 0,
	//1.�������Ӵ�������
	MOT_BottomContactCenter,
	//2.ǽ�����Ӵ�������
	MOT_WallContactCenter,
	//3.�������Ӵ�������
	MOT_TopContactCenter,
	//4.ǽ�͵����Ӵ�������
	MOT_WallBottomContactCenter,
	//5.ǽ�Ͷ��Ӵ�������
	MOT_WallTopContactCenter,
	//6.ǽ��ǽ�Ӵ�������
	MOT_WallCornerContactCenter,
	//7.�Ӵ����ڶ���
	MOT_InnerTopContactCorner,
	//8.����������
	MOT_AlignPlaneContactCenter,
	//9.�˵����ĵ�
	MOT_PoleCenter,
	//10.��˽Ӵ�������ĵ�
	MOT_PoleContactCenter,
	//11.̨���ǽ��ĽӴ������ĵ�
	MOT_TableFaceWallContactCenter,
	//12.���Ӵ������ĵײ�
	MOT_MainBottomContactCenter,
	//13.��ҳ���ĵײ��Ӵ���
	MOT_BottomAxis,
	//��������������ľ��������������
	//14.��������������潻��
	MOT_NailAxisContactIntersectionPoint,
	//15.��װ������
	MOT_MountingHoleCenter,
	//16.������
	MOT_AxisCenter,
	//17.���λ��
	MOT_CabinetCorner,
	//18.���Ӵ�������
	MOT_MainContactCenter,
	//19.�Ӵ����밲װ������
	MOT_MountingHoleContactCenter,
	//20.�˹��ж�
	MOT_Manually,
	//21.���º�
	MOT_LeftBottomBack,
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

/**
* ˮ�繹��id
*/
enum EComponentID
{
  	EC_None,
	EC_Socket_Five_Point = 20,//��ײ���
	EC_Socket_Five_On_Point = 40,//��׿��ز���
	EC_Socket_Five_On_Dislocation= 1100,//��״�λ����
	EC_Socket_Five_Point_Dislocation,//��״�λ���ز���
	EC_Socket_Four_Point = 63, //�Ŀײ���
	EC_Socket_Four_On_Point = 64,//�Ŀ׿��ز���
	EC_Socket_Three_On_Point = 1000, //���׿��ز���
	EC_Socket_Three, //���ײ���
	EC_Socket_Three_On_Point_3A = 71,  //16A���׿��ز���
	EC_Socket_Three_3A = 70, //16A���ײ���
	EC_Socket_Three_On_Point_10A = 69,  //10A���׿��ز���
	EC_Socket_Air_Conditioner = 50,//�յ��һ����ײ���
	EC_Socket_USB = 68,//���USB����
	EC_Socket_Air_Conditionner_Normal = 53,//�յ��������
	EC_Socket_HotWater = 52,//��ˮ����ײ���
	EC_Socket_PaiYan = 51,//���̻���ײ���

	EC_Socket_White,//�װ�
	EC_Socket_Spatter = 72,//������
	EC_Socket_IT = 57,//���߲���
	EC_Socket_IT_TV = 65,//���ӵ��Բ���
	EC_Socket_TV = 56,//���Ӳ���
	EC_Socket_Phone = 58,//�绰����
	EC_Socket_IT_Phone = 67,//���Ե绰����
	EC_Socket_TV_Phone = 66,//���ӵ绰����
	EC_Socket_TP = 54, //��������ר�����Ų���
	EC_Socket_TV_Couplet = 42, //����ǽר�����Ų���

	EC_EleBoxL_Point = 15,//������
	EC_EleBoxH_Point = 16,//ǿ����

	EC_Switch_BathHeater = 49,//ԡ�Կ���
	EC_Switch_Double = 48,//˫�����߿���
	EC_Switch_Single = 47,//�������߿���
	EC_Switch4O2_Point =46,//����˫�ؿ���
	EC_Switch4O1_Point =45,//�������ؿ���
	EC_Switch3O2_Point =44,//����˫�ؿ���
	EC_Switch3O1_Point = 43,//�������ؿ���
	EC_Switch2O2_Point = 30,//˫��˫�ؿ���
	EC_Switch2O1_Point = 25,//˫�����ؿ���
	EC_Switch1O2_Point,//����˫�ؿ���
	EC_Switch1O1_Point = 24,//�������ؿ���

	
	EC_Water_Chilled_Point = 17,//��ˮ��λ
	EC_Water_Hot_Chilled_Point = 18,//����ˮ
	EC_Dewatering_Point = 400,//��ˮ��λ
	EC_Water_Supply=62, // ��ˮ��λ,
	EC_Drain_Point=61,//����ˮ��
	EC_Basin=60,//��©��ˮ
	EC_Water_Basin = 59,//ˮ����ˮ
	EC_Water_Hot_Point = 55,//��ˮ��λ
	EC_Closestool = 31,//��Ͱ��ˮ
	EC_Gas = 32,//ȼ����λ

	EC_Supply_Same_Tee = 73,//��ˮ�ܵȾ�����ͨ
	EC_Supply_Diff_Tee = 75,//��ˮ���쾶����ͨ
	EC_Supply_Same_45_Tee = 94,//��ˮ�ܵȾ�45б��ͨ
	EC_Supply_Diff_45_Tee=95,//��ˮ���쾶45б��ͨ
	EC_Supply_NoPlane_Same_Tee=117, //��ˮ������Ⱦ���ͨ
	EC_Supply_NoPlane_Diff_Tee=116, //��ˮ�������쾶��ͨ

	EC_Supply_Same_90_Flexure = 96,//��ˮ�ܵȾ�90��ͷ
	EC_Supply_Diff_90_Flexure = 97,//��ˮ���쾶90��ͷ
	EC_Supply_Same_45_Flexure=98,//��ˮ���쾶45��ͷ
	EC_Supply_Diff_45_Flexure=99,//��ˮ���쾶45��ͷ

	EC_Supply_Same_Direct = 108,//��ˮ�ܵȾ�ֱ��
	EC_Supply_Diff_Direct = 109,//��ˮ���쾶ֱ��
	
	EC_Supply_Plane_Same_FourLinks=114, //��ˮ��ƽ��Ⱦ���ͨ
	EC_Supply_Plane_Diff_FourLinks=115, //��ˮ��ƽ���쾶��ͨ
	EC_Supply_NoPlane_Same_FourLinks=118, //��ˮ������Ⱦ���ͨ
	EC_Supply_NoPlane_Diff_FourLinks=119, //��ˮ�������쾶��ͨ

	EC_Drain_Bottle_Tee = 113,// ��ˮ��ƿ����ͨ
	EC_Drain_Same_Tee = 76,//��ˮ�ܵȾ�����ͨ
	EC_Drain_Diff_Tee = 74,//��ˮ���쾶����ͨ
	EC_Drain_Same_45_Tee = 77,//��ˮ�ܵȾ�45��б��ͨ
	EC_Drain_Diff_45_Tee = 78,//��ˮ���쾶45��б��ͨ

	EC_Drain_Same_Direct = 79,//��ˮ�ܵȾ�ֱ��
	EC_Drain_Diff_Direct = 80,//��ˮ���쾶ֱ��

	EC_Drain_Same_45_Flexure = 81, //��ˮ�ܵȾ�45��ͷ
	EC_Drain_Diff_45_Flexure = 82, //��ˮ���쾶45��ͷ
	EC_Drain_Same_90_Flexure = 83, //��ˮ�ܵȾ�90��ͷ
	EC_Drain_Diff_90_Flexure = 84, //��ˮ���쾶90��ͷ

	EC_Drain_Plane_Same_FourLinks = 85, //��ˮ��ƽ��Ⱦ���ͨ
	EC_Drain_Plane_Diff_FourLinks = 86, //��ˮ��ƽ���쾶��ͨ
	EC_Drain_Same_45_FourLinks = 87,//��ˮ�ܵȾ�45��ͨ
	EC_Drain_Diff_45_FourLinks = 88,//��ˮ���쾶45��ͨ
	EC_Drain_NoPlane_Same_FourLinks = 89, //��ˮ������Ⱦ���ͨ
	EC_Drain_NoPlane_Diff_FourLinks = 92, //��ˮ�������쾶��ͨ

	EC_Trap_P = 90,//P�ʹ�ˮ��
	EC_Trap_S = 91,//S�ʹ�ˮ��
	EC_Trap_U = 93,//U�ʹ�ˮ��

	EC_Bridge_Same = 120, //�Ⱦ�������
	EC_Bridge_Diff = 121, //�쾶������


	EC_Max
};

enum CategryType
{
	CT_None = 0,
	//����
	CT_Floor = 1,
	//ǽ��
	CT_Wall = 2,
	//����
	CT_Ceiling = 3,
	//ˮ���ò�
	CT_HydroelectricMaterials = 4,
	//���ƹ���
	CT_DrawPipeline = 5,
	//��ש
	CT_FloorTile = 6,
	//�ذ�
	CT_FloorFloor = 7,
	//ˮ��ƴ��
	CT_FloorWaterKnife = 8,
	//������
	CT_FloorWaveLine = 9,
	//�߽���
	CT_FloorKickingLine = 10,
	//����ֱ��
	CT_Continue = 11,
	//�����̷�
	CT_Worker = 12,
	//�����̷�
	CT_Wind = 13,
	//����̷�
	CT_Space = 14,
	//�����̷�
	CT_Interlace = 15,
	//������
	CT_People = 18,
	//��������
	CT_TrapeZoid = 19,
	//�н�ש
	CT_CornerBrickMethod = 20,
	//�޽�ש
	CT_AntiCornerBrickMethod = 21,
	//ǽש
	CT_WallTile = 22,
	//ǽ��
	CT_WallFloor = 23,
	//ǽ��
	CT_WallPaint = 24,
	//����ǽ
	CT_WallBackground = 25,
	//�Ʋ�
	CT_LampSlot = 26,
	//������
	CT_CrownMoulding = 27,
	//��ֽ
	CT_WallPaper = 28,
	//���۰�
	CT_AluminousGussetPlate = 30,
	//������
	CT_CeilingLamp = 43,
	//ԡ��
	CT_BathHeater = 44,
	//�ŷ���
	CT_VentilatingFan = 45,
	//�������
	CT_SteelKeel = 47,
	//ľ����
	CT_WoodKeel = 48,	
	//������
	CT_MoldingLine = 58,
	// �����
	CT_EleBox = 31,
	// ����
	CT_SWITCH = 32,
	// ǿ�����
	CT_Socket_Strong = 33,
	//�������
	CT_Socket_Weak = 34,
	// ˮ·��λ
	CT_Water_Point =600180004,
	// Ԥװ��λ
	CT_Preload = 60028,
	//2.5ƽ��ǿ����·
	CT_Strong_25h = 400190001,
	//4ƽ��ǿ����·
	CT_Strong_4 = 400190002,
	//����ǿ����·
	CT_Strong_Single = 400190003,
	//˫��ǿ����·
	CT_Strong_Double = 400190004,
	//���� ������
	CT_WeakElectricity_TV = 4002200001,
	//���磬 ����
	CT_WeakElectricity_Net =4002200003,
	//���磬�绰��
	CT_WeakElectricity_Phone =4002200002,
	//��ˮ��
	CT_ColdWaterTube = 600180001,
	//��ˮ��
	CT_HotWaterTube =600180002,
	//��ˮ��
	CT_Drain =600180003,
};


//ģ�ͷ���λ��
struct PlacePosition
{
	//true����ɷ��ã�false���治�ɷ���
	bool bFloor;
	//trueǽ��ɷ��ã�falseǽ�治�ɷ���
	bool bWall;
	//true����ɷ��ã�false���治�ɷ���
	bool bCeiling;
	//truę��ɷ��ã�falsę�治�ɷ���
	bool bMesa;
};
enum CategryApplicationType
{
	CAT_None = 0,
	//����ֱ��
	CAT_Continue = 1,
	//�����̷�
	CAT_Worker = 2,
	//�����̷�
	CAT_Wind = 3,
	//����̷�
	CAT_Space = 4,
	//�����̷�
	CAT_Interlace = 5,
	//������
	CAT_People = 8,
	//��������
	CAT_TrapeZoid = 9,
	//�н�ש
	CAT_CornerBrickMethod = 10,
	//�޽�ש
	CAT_AntiCornerBrickMethod = 11,
	//ǽֽ
	CAT_WallPaper = 12,
	//�Ʋ�
	CAT_LampSlot = 13,
	//������
	CAT_CrownMoulding = 14,
	//������
	CAT_MoldingLine = 15,
	//�߽���
	CAT_FloorKickingLine = 16,
	//PAKģ��
	CAT_PAKModel = 17,
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
    public:
		FProductObj() {}
		FProductObj(float _Price, float _PriceDiscount, FString _URL, float _Length, float _Width, float _Height)
			:Price(_Price), PriceDiscount(_PriceDiscount), URL(_URL), Length(_Length), Width(_Width), Height(_Height)
		{}

        void SerializeToJson(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter)
        {
            JsonWriter->WriteValue("price", FString::Printf(TEXT("%.1f"), Price));
            JsonWriter->WriteValue("priceDiscount", FString::Printf(TEXT("%.1f"), PriceDiscount));
            JsonWriter->WriteValue("url", *URL);
            JsonWriter->WriteValue("length", FString::Printf(TEXT("%.1f"), Length));
            JsonWriter->WriteValue("width", FString::Printf(TEXT("%.1f"), Width));
            JsonWriter->WriteValue("height", FString::Printf(TEXT("%.1f"), Height));
        }

        void Deserialization(const TSharedPtr<FJsonObject>& InJsonData)
        {
            Price = InJsonData->GetNumberField("price");
            PriceDiscount = InJsonData->GetNumberField("priceDiscount");
            URL = InJsonData->GetStringField("url");
            Length = InJsonData->GetNumberField("length");
            Width = InJsonData->GetNumberField("width");
            Height = InJsonData->GetNumberField("height");
        }
		float Price;//�۸�
		float purchasePrice;//�ɹ��۸�
		FString unit;//��λ
		FString brandName;//Ʒ��
		FString model;//�ͺ�
		FString introduce;//��ע��Ϣ

		float PriceDiscount;
		FString URL;

		float Length = 0;
		float Width = 0;
		float Height = 0;
	};
	/**
	* ˮ����Ʒ��Ϣ
	*/
	class FHydropowerProductObj : public FProductObj
	{
	public:
		float Radius = 0;
	public:
		FHydropowerProductObj() {}
		FHydropowerProductObj(float _Price,float _PriceDiscount,FString _URL,float _Length,float _Width,float _Height,float InRadius)
			:FProductObj(_Price,PriceDiscount,_URL,_Length,_Width,_Height),Radius(InRadius)
		{}

		void SerializeToJson(TSharedRef<TJsonWriter<TCHAR,TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter)
		{
			FProductObj::SerializeToJson(JsonWriter);
			JsonWriter->WriteValue("radius",FString::Printf(TEXT("%.1f"),Radius));
		}

		void Deserialization(const TSharedPtr<FJsonObject>& InJsonData)
		{
			FProductObj::Deserialization(InJsonData);
			Radius = InJsonData->GetNumberField("radius");
		}

	};

	//��Դ��Ϣ�ṹ��
	class FResObj : public TSharedFromThis<FResObj>
	{
	public:
		FResObj() {}
		FResObj(FString _FileName, FString _FilePath, FString _FileURL, FString _FileMD5, EResourceType _ResourceType, PlacePosition _placePosition = {false})
			: FileName(_FileName), FilePath(_FilePath), FileURL(_FileURL), FileMD5(_FileMD5),ResourceType(_ResourceType),placePosition(_placePosition)
		{}
		virtual ~FResObj() {}

		virtual void SerializeToJson(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter)
        {
            JsonWriter->WriteValue("fileName", *FileName);
            JsonWriter->WriteValue("filePath", *FilePath);
            JsonWriter->WriteValue("fileURL", *FileURL);
            JsonWriter->WriteValue("fileMD5", *FileMD5);
            JsonWriter->WriteValue("version", FString::Printf(TEXT("%d"), Version));
			JsonWriter->WriteValue("fileState", FString::Printf(TEXT("%d"), (int32)FileState));
			JsonWriter->WriteValue("resourceType", FString::Printf(TEXT("%d"), (int32)ResourceType));
        }

		virtual void Deserialization(const TSharedPtr<FJsonObject>& InJsonData)
        {
            FileName = InJsonData->GetStringField("fileName");
            FilePath = InJsonData->GetStringField("filePath");
            FileURL = InJsonData->GetStringField("fileURL");
            FileMD5 = InJsonData->GetStringField("fileMD5");
            Version = InJsonData->GetIntegerField("version");
			FileState = (EFileExistenceState)(InJsonData->GetIntegerField("fileState"));
			ResourceType = (EResourceType)(InJsonData->GetIntegerField("resourceType"));
        }

		FString FileName;
		FString FilePath;
		FString FileURL;
		FString FileMD5;
		int32 Version;
		EFileExistenceState FileState;

		////��Ź�����Ϣ
		//TSharedPtr<FContentItemSpace::FComponentRes> ComponentObj;

		//��Դ���ͣ�������Ӧ�Ľ���ResObj����
		EResourceType ResourceType;

		//����λ��
		PlacePosition placePosition;
	};

    /**
     * �ŵĲ�����Դ
     */
    class FXRDoorTextureRes : public FResObj
    {
    public:
        struct FTextureRes
        {
            //��ʵ��������
            FString FileURL;

            //���ʻ��浽���ص�·��
            FString FilePath;

            FString MD5;

            void SerializeToJson(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter)
            {
                JsonWriter->WriteValue("fileURL", FileURL);
                JsonWriter->WriteValue("filePath", FilePath);
                JsonWriter->WriteValue("md5", MD5);
            }

            void Deserialization(const TSharedPtr<FJsonObject>& InJsonData)
            {
                FileURL = InJsonData->GetStringField("fileURL");
                FilePath = InJsonData->GetStringField("filePath");
                MD5 = InJsonData->GetStringField("md5");
            }

        } Texture, Normal;

        FXRDoorTextureRes() {}

        FXRDoorTextureRes(FTextureRes InTexture, FTextureRes InNormal)
            : Texture(InTexture)
            , Normal(InNormal)
        {}

        virtual void SerializeToJson(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter)
        {
            FResObj::SerializeToJson(JsonWriter);

            JsonWriter->WriteObjectStart("texture");
            Texture.SerializeToJson(JsonWriter);
            JsonWriter->WriteObjectEnd();

            JsonWriter->WriteObjectStart("normal");
            Normal.SerializeToJson(JsonWriter);
            JsonWriter->WriteObjectEnd();
        }

        virtual void Deserialization(const TSharedPtr<FJsonObject>& InJsonData)
        {
            FResObj::Deserialization(InJsonData);

            TSharedPtr<FJsonObject> TextureData = InJsonData->GetObjectField("texture");
            if (TextureData.IsValid())
            {
                Texture.Deserialization(TextureData);
            }

            TSharedPtr<FJsonObject> NormalData = InJsonData->GetObjectField("normal");
            if (NormalData.IsValid())
            {
                Normal.Deserialization(NormalData);
            }
        }
    };

	//ģ����Ϣ
	class FModelRes : public FResObj
	{
	public:
		FModelRes(FString FileName,
			FString FilePath,
			FString FileURL,
			FString FileMD5,
			EResourceType _ResourceType,
			FString _MaterialParameter,
			FString _LightParameter,
			PlacePosition _placePosition = {false})
			: FResObj(FileName, FilePath, FileURL, FileMD5, _ResourceType, _placePosition)
			, MaterialParameter(_MaterialParameter)
			, LightParameter(_LightParameter)
		{}
		FModelRes()
		{
		}
		FString MaterialParameter;
		FString LightParameter;



		virtual void SerializeToJson(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter)
		{
			FResObj::SerializeToJson(JsonWriter);
			JsonWriter->WriteValue("placeposition_floor", placePosition.bFloor);
			JsonWriter->WriteValue("placeposition_wall", placePosition.bWall);
			JsonWriter->WriteValue("placeposition_ceiling", placePosition.bCeiling);
			JsonWriter->WriteValue("placeposition_mesa", placePosition.bMesa);

			JsonWriter->WriteValue("MaterialParameter", *MaterialParameter);
			JsonWriter->WriteValue("LightParameter", *LightParameter);

		}

		virtual void Deserialization(const TSharedPtr<FJsonObject>& InJsonData)
		{
			FResObj::Deserialization(InJsonData);
			placePosition.bFloor = InJsonData->GetBoolField("placeposition_floor");
			placePosition.bWall = InJsonData->GetBoolField("placeposition_wall");
			placePosition.bCeiling = InJsonData->GetBoolField("placeposition_ceiling");
			placePosition.bMesa = InJsonData->GetBoolField("placeposition_mesa");

			MaterialParameter = InJsonData->GetStringField("MaterialParameter");
			LightParameter = InJsonData->GetStringField("LightParameter");
		}
	};
	/**
	* ������Ϣ
	*/
	class FComponentRes : public FResObj
	{
	public:
        FComponentRes()
            : FResObj()
            , TypeID(0)
            , ComponentID(0)
        {}
		FComponentRes(FString FileName, FString FilePath, FString FileURL, FString FileMD5, EResourceType _resourceType, uint32 InTypeID, uint32 InID = 0)
			: FResObj(FileName, FilePath, FileURL, FileMD5, _resourceType)
			, TypeID(InTypeID), ComponentID(InID)
		{}

		virtual ~FComponentRes() {}

        virtual void SerializeToJson(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter)
        {
            FResObj::SerializeToJson(JsonWriter);

            JsonWriter->WriteValue("typeID", FString::Printf(TEXT("%d"), TypeID));
            JsonWriter->WriteValue("componentID", FString::Printf(TEXT("%d"), ComponentID));
			JsonWriter->WriteValue(TEXT("SwitchCoupletNum"),SwitchCoupletNum);
            JsonWriter->WriteArrayStart("altitudes");
            for (auto& It : Altitudes)
            {
                JsonWriter->WriteValue(FString::Printf(TEXT("%d"), It));
            }
            JsonWriter->WriteArrayEnd();
        }

		virtual void Deserialization(const TSharedPtr<FJsonObject>& InJsonData)
        {
            FResObj::Deserialization(InJsonData);

            TypeID = InJsonData->GetIntegerField("typeID");
            ComponentID = InJsonData->GetIntegerField("componentID");
			SwitchCoupletNum = InJsonData->GetIntegerField(TEXT("SwitchCoupletNum"));
            TArray<FString> AltitudesArray;
            InJsonData->TryGetStringArrayField("altitudes", AltitudesArray);
            for (auto& It : AltitudesArray)
            {
                Altitudes.Add(FCString::Atoi(*It));
            }
        }

		uint32 TypeID = 0;
		uint32 ComponentID = 0;
		float ProductLength = 0;
		float ProductWidth = 0;
		float ProductHeight = 0;

		int32 SwitchCoupletNum = -1;// ��λ�İ�����

		TArray<int32> Altitudes;
	};

    /**
	 * ��Ŀ��Ϣ
	 */
	class FProjectRes : public FResObj
	{
	public:
		FProjectRes(
            FString FileName,
            FString FilePath,
            FString FileURL,
            FString FileMD5,
			EResourceType _ResourceType,
            int64 InCreateDate,
            int64 InUpdateDate,
            FString InCreateUserName,
            FString InCustomerName,
            FString InCustomerPhone,
            FString InRemarks			
        )
			: FResObj(FileName, FilePath, FileURL, FileMD5, _ResourceType)
			, CreateDate(InCreateDate)
			, UpdateDate(InUpdateDate)
            , CreateUserName(InCreateUserName)
            , CustomerName(InCustomerName)
            , CustomerPhone(InCustomerPhone)
            , Remarks(InRemarks)
		{}

		/** ����ʱ�� */
		int64 CreateDate;

		/** ����޸�ʱ�� */
		int64 UpdateDate;

		/**	�ײͱ��*/
		int32 GroupID;

		/**	�ײ�����*/
		FString GroupName;

        /** ��ͬ��� */
        FString ContractNo;

        /** ���������� */
        FString CreateUserName;

        /** ҵ������ */
        FString CustomerName;

        /** ҵ����ϵ�绰 */
        FString CustomerPhone;

		FString VillagesAddress;

		/** ʡid */
		int32 ProvinceId;

		/** ��id */
		int32 CityId;

		/** ��id */
		int32 AreaId;

		/** ʡName */
		FString ProvinceName;

		/** ��Name */
		FString CityName;

		/** ��Name */
		FString AreaName;

		/** �������� */
		int32 BedroomNum;

		/** �������� */
		int32 LivingRoomNum;

		/** �������� */
		int32 KitchenNum;

		/** ���������� */
		int32 BathroomNum;

		/** ������� */
		float BuildingArea;

        /** ��Ŀ���� */
        FString Remarks;
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
			EResourceType _ResourceType,
			int32 InBedroomNum,
			int32 InLivingRoomNum,
			int32 InKitchenNum,
			int32 InBathroomNum,
			float InFloorArea,
			int32 InProvinceId,
			int32 InCityId,
			int32 InAreaId,
            FString InVillageName
		)
			: FResObj(FileName, FilePath, FileURL, FileMD5, _ResourceType)
			, BedroomNum(InBedroomNum)
			, LivingRoomNum(InLivingRoomNum)
			, KitchenNum(InKitchenNum)
			, BathroomNum(InBathroomNum)
			, FloorArea(InFloorArea)
			, ProvinceId(InProvinceId)
			, CityId(InCityId)
			, AreaId(InAreaId)
            , VillageName(InVillageName)
		{}

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

		/** ʡid */
		int32 ProvinceId;

		/** ��id */
		int32 CityId;

		/** ��id */
		int32 AreaId;

        /** С������ */
        FString VillageName;
	};
	class FXRHardModeRes;
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

        ~FContentItem()
        {
            int32 i = 0;
        }

		FContentItem(
			EResourceType _ResourceType,
			int32 _ID,
			FString _Name,
			FString _ThumbnailURL,
			TArray<TSharedPtr<FResObj> > _ResObjArr,
			bool _isSale,
			//EPavingMethodType _PavingMethodType = EPavingMethodType::NoneMethod,			
			TSharedPtr<FProductObj> _ProObj = NULL,
			EContentItemFlag _ItemFlag = EContentItemFlag::PF_NoFlags
			//TSharedPtr<FComponentRes> _ComponentObj = NULL
		)
			: ResourceType(_ResourceType), ID(_ID), Name(_Name), ThumbnailURL(_ThumbnailURL), ResObjArr(_ResObjArr), ProObj(_ProObj), bIsSale(_isSale)/*,ComponentObj(_ComponentObj)*/
		{
			ItemFlag = EContentItemFlag::PF_NoFlags;
			ItemFlag |= _ItemFlag;
		}

		FContentItem(
			EResourceType _ResourceType,
			int32 _ID,
			FString _Name,
			FString _ThumbnailURL,
			TArray<TSharedPtr<FResObj> > _ResObjArr,
			//EPavingMethodType _PavingMethodType = EPavingMethodType::NoneMethod,
			TSharedPtr<FProductObj> _ProObj = NULL,
			EContentItemFlag _ItemFlag = EContentItemFlag::PF_NoFlags			
		)
			: ResourceType(_ResourceType), ID(_ID), Name(_Name), ThumbnailURL(_ThumbnailURL), ResObjArr(_ResObjArr), ProObj(_ProObj), bIsSale(false)
		{
			ItemFlag = EContentItemFlag::PF_NoFlags;
			ItemFlag |= _ItemFlag;
		}

        /** ���ݲ�ͬ����Դ���ʹ���Ĭ�ϵ�ResObj */
        TSharedPtr<FResObj> CreateDefaultResObj(EResourceType InResourceType)
        {
            if (InResourceType == EResourceType::DoorTexture)
            {
                return MakeShareable(new FXRDoorTextureRes());
            }

            return MakeShareable(new FResObj());
        }

        void SerializeToJson(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter)
        {
            JsonWriter->WriteValue("bIsSale", bIsSale);
            JsonWriter->WriteValue("id", FString::Printf(TEXT("%d"), ID));
            JsonWriter->WriteValue("name", *Name);
            JsonWriter->WriteValue("thumbnailURL", *ThumbnailURL);
            JsonWriter->WriteValue("itemFlag", FString::Printf(TEXT("%d"), (int32)ItemFlag));
            JsonWriter->WriteValue("resourceType", FString::Printf(TEXT("%d"), (int32)ResourceType));
			JsonWriter->WriteValue("categryid", FString::Printf(TEXT("%d"), CategryID));

			JsonWriter->WriteArrayStart("resObjArr");
			for (auto& it : ResObjArr)
			{
				JsonWriter->WriteObjectStart();
				it->SerializeToJson(JsonWriter);
				JsonWriter->WriteObjectEnd();
			}
			JsonWriter->WriteArrayEnd();

            if (ProObj.IsValid())
            {
                JsonWriter->WriteObjectStart("proObj");
                ProObj->SerializeToJson(JsonWriter);
                JsonWriter->WriteObjectEnd();
            }
            
            //if (ComponentObj.IsValid())
            //{
            //    JsonWriter->WriteObjectStart("componentObj");
            //    ComponentObj->SerializeToJson(JsonWriter);
            //    JsonWriter->WriteObjectEnd();
            //}
        }

        void Deserialization(const TSharedPtr<FJsonObject>& InJsonData)
        {
            bIsSale = InJsonData->GetBoolField("bIsSale");
            ID = InJsonData->GetIntegerField("id");
            Name = InJsonData->GetStringField("name");
            ThumbnailURL = InJsonData->GetStringField("thumbnailURL");
            ItemFlag = (EContentItemFlag)(InJsonData->GetIntegerField("itemFlag"));
            ResourceType = (EResourceType)(InJsonData->GetIntegerField("resourceType"));

			const TArray<TSharedPtr<FJsonValue> > ResObj = InJsonData->GetArrayField("resObjArr");
			int i = 0;
			for (auto & it : ResObj)
			{
				TSharedPtr<FJsonObject> itRes = it->AsObject();
				if (itRes.IsValid())
				{
                    if (i >= 0 && i < ResObjArr.Num())
                    {
                        TSharedPtr<FContentItemSpace::FXRHardModeRes> res = StaticCastSharedPtr<FContentItemSpace::FXRHardModeRes>(ResObjArr[i]);
                        if (!res.IsValid())
                        {
                            ResObjArr[i] = CreateDefaultResObj(ResourceType);
                        }
                    }
                    else
                    {
                        ResObjArr.Add(CreateDefaultResObj(ResourceType));
                    }
					
					ResObjArr[i]->Deserialization(itRes);
					//ResObjArr.Add(Res);
					i++;
				}
			}
            ProObj = MakeShareable(new FContentItemSpace::FProductObj());
            ProObj->Deserialization(InJsonData->GetObjectField("proObj"));
            //ComponentObj = MakeShareable(new FComponentRes());
            //ComponentObj->Deserialization(InJsonData->GetObjectField("componentObj"));
			CategryID = InJsonData->GetIntegerField("categryid");

        }

		//����Դ���ͻ�ȡ��Դ����
		TArray<TSharedPtr<FResObj> >& GetResObjByType(EResourceType type)
		{
			TArray<TSharedPtr<FResObj> > resArr;
			 for (auto & It : ResObjArr)
			 {
				 if (It->ResourceType == type)
					 resArr.Add(It);
			 }
			 return resArr;
		}

		//��ȡ���������������Դ
		TArray<TSharedPtr<FResObj> > GetResObjNoComponent()
		{
			TArray<TSharedPtr<FResObj> > resArr;
			for (auto & It : ResObjArr)
			{
				if (It->ResourceType != EResourceType::ComponentDXF)
					resArr.Add(It);
			}
			return resArr;
		}

		//������ڹ��������ش���Ʒ����
		TSharedPtr<FComponentRes> GetComponent()
		{
			TArray<TSharedPtr<FResObj> > resArr;
			for (auto & It : ResObjArr)
			{
				if (It->ResourceType == EResourceType::ComponentDXF)
				{
					return StaticCastSharedPtr<FComponentRes>(It);
				}
			}
			return nullptr;
		}

		/**@��ҵ˳�Ƿ�����Ʒ�ı�ʶ*/
		bool bIsSale;
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
		TArray<TSharedPtr<FResObj> > ResObjArr;
		//��Ŷ�Ӧ����Ʒ��Ϣ
		TSharedPtr<FProductObj> ProObj;
		//��Ź�����Ϣ
		//TSharedPtr<FContentItemSpace::FComponentRes> ComponentObj;

		//�����Ʒ������ĿID
		int32 CategryID;
	};

	/**
	* Ӳװģ����Ϣ
	*/
	class FXRHardModeRes : public FModelRes
	{
	public:
		FXRHardModeRes(
			const FString _FileName,
			const FString _FilePath,
			const FString _FileURL,
			const FString _FileMD5,
			const EResourceType _ResourceType,
			const FString _MaterialParameter = "",
			const FString _LightParameter = "",
			const PlacePosition _placePosition = {false},
			const int32 _DefaultPavingMethod = 0,
			//const TArray<TSharedPtr<FXRKeyValue> > _PavingMethodArr = NULL,
			const CategryApplicationType _ResourceCategryType = CategryApplicationType::CAT_None)
			: FModelRes(_FileName, _FilePath, _FileURL, _FileMD5, _ResourceType, _MaterialParameter, _LightParameter, _placePosition)
			,DefaultPavingMethod(_DefaultPavingMethod)
			//,PavingMethodArr(_PavingMethodArr)
			,ResourceCategryType(_ResourceCategryType)
		{}
		FXRHardModeRes()
		{}

		//����Ʒ֧�ֵ��̷��б�
		TArray<TSharedPtr<FXRKeyValue> > PavingMethodArr;
		//Ĭ���̷�
		int32 DefaultPavingMethod;

		//��Դ������Ŀ����ײ�ö�٣�������ֱ�̡�ˮ��ƴ����ǽ��
		CategryApplicationType ResourceCategryType;

		virtual void SerializeToJson(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter)
		{
			FModelRes::SerializeToJson(JsonWriter);
			JsonWriter->WriteValue("ResourceCategryType", (int32)ResourceCategryType);
			JsonWriter->WriteValue("DefaultPavingMethod", FString::Printf(TEXT("%d"), DefaultPavingMethod));
			JsonWriter->WriteArrayStart("PavingMethodArr");
			for (int32 j = 0; j < PavingMethodArr.Num(); j++)
			{
				JsonWriter->WriteObjectStart();
				JsonWriter->WriteValue("PavingMethod", *PavingMethodArr[j]->ToString());
				JsonWriter->WriteObjectEnd();
			}
			JsonWriter->WriteArrayEnd();
		}

		virtual void Deserialization(const TSharedPtr<FJsonObject>& InJsonData)
		{
			FModelRes::Deserialization(InJsonData);
			ResourceCategryType = CategryApplicationType(InJsonData->GetIntegerField("ResourceCategryType"));
			
			DefaultPavingMethod = InJsonData->GetIntegerField("DefaultPavingMethod");

			const TArray<TSharedPtr<FJsonValue> > JPavingMethod = InJsonData->GetArrayField("PavingMethodArr");
			for (auto & PavingMethodIt : JPavingMethod)
			{
				TSharedPtr<FJsonObject> ItPavingMethodIt = PavingMethodIt->AsObject();
				if (ItPavingMethodIt.IsValid())
				{
					TSharedPtr<FXRKeyValue> PavingMethod = MakeShareable(new FXRKeyValue());
					FString PavingMethodStr = ItPavingMethodIt->GetStringField("PavingMethod");
					PavingMethod->InitFromString(*PavingMethodStr);
					PavingMethodArr.Add(PavingMethod);
				}
			}

		}
	};	
	/**
	* Ӳװ��Ʒ������Ϣ
	*/
	class FXRHardModeProduct : public FProductObj
	{
		//����Ӳװ��������Ϣ��������ӣ���ʱΪ��
		//TODO
	};
	/**
	* ˮ����Ϣ
	*/
	class FXRPipeRes : public FModelRes
	{
	public:
		FXRPipeRes (
			const FString& FileName,
			const FString& FilePath,
			const FString& FileURL,
			const FString& FileMD5,
			const EResourceType _resourcetype,
			const FString& InClass,
			const FString& InName,
			const PlacePosition _placePosition = {false}
		) : FModelRes(FileName, FilePath, FileURL, FileMD5, _resourcetype, "", "", _placePosition),
			ClassName (InClass),
			Raduis(0.f),
			Name (InName)
		{
		}
	public:
		int32 Categry0Type;//1���˵�
		int32 ClassType; // ��Դ����
		int32 ObjectType; // ��;
		FString ClassName; //��������
		FString Name; //����
		FString FileThumbnailURL;//����ͼ
		int32 ID; //��ƷID

		TArray<float> Altitudes; // ��ظ߶�
								 /** �زĳ��� */
		int32 Length;
		/** �زĿ��*/
		int32 Width;
		/** �زĸ߶� */
		int32 Height;
		int32 ComponentID;//����ID
		FColor Color; //������ɫ
		FColor RefromColor;//�ϵ����ɫ
		FColor PointColor;//���ӽڵ���ɫ
		FColor PointReformColor;//���ӽڵ�ϵ����ɫ
		float  Raduis;// �ܾ� ����
	};
}

typedef TSharedPtr<class FContentItemSpace::FContentItem> FContentItemPtr;

/*
*	��Ŀ����
*/
//class XRUSER_API FProjectContentItem
//{
//public:
//	FProjectContentItem()
//		: ID(-1)
//	{}
//
//	FProjectContentItem(
//		int32 _ID,
//		FString _Name,
//		FString _ThumbnailURL,
//		int64 _CreateDate,
//		int64 _UpdateDate
//	)
//		: ID(_ID), Name(_Name), ThumbnailURL(_ThumbnailURL), CreateDate(_CreateDate), UpdateDate(_UpdateDate)
//	{}
//
//	~FProjectContentItem() {}
//
//	//��ԴΨһID
//	int32 ID;
//	//��ʾ����
//	FString Name;
//	//��ʾ����ͼ��ַ
//	FString ThumbnailURL;
//	//����ʱ��
//	int64 CreateDate;
//	//����޸�ʱ��
//	int64 UpdateDate;
//};

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
struct FObjectThirdItem
{
	FString DirectoryName;
	TArray<int32> CategoryList;
};
struct FObjectGroupContentItem
{
	FObjectGroupContentItem() {}
	~FObjectGroupContentItem() {}

	FString ModelName;
	int32 ModelID;
	int32 VisibleInOtherModel;

	FString ItemPath;
	FObjectThirdItem ThirdItem;
	TArray<int32> CategoryList;
};
DECLARE_DELEGATE_TwoParams(FXRFComponentResDelegate, TSharedPtr<FContentItemSpace::FComponentRes>, AActor*);