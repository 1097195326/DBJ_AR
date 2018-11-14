#pragma once

#include "DataT.h"


enum GoodsDataType
{
	P_StaticMesh,
	P_Material,
	P_Blueprint,

};

class DBJ_AR_API GoodsData : public DataT
{
public:
	
	int			id;//": 5,
	FString		name;//" : "zhx1",
	int			typeId;// : 2,
	bool		shelf;// : true,
	FString		categoryIdList;// : null,
	int			modelId;// : 9,
	FString		modelName;// : null,
	int			supplyId;// : 2,
	FString		supplyName;// : "��Ӧ�����Ӳ���",
	int			salePrice;// : 30,
	FString		thumbnailUrl;// : "http://test.ali.res.dabanjia.com/res/20181105/AR_BOTANY__1541410677559_4017.png",
	FString		thumbnailMd5;// : "f1492dae35087a0a54ae4d9d47577b2f",
	FString		pakUrl;// : "http://test.ali.res.dabanjia.com/res/20181105/AR_BOTANY__1541410588562_6936.pak",
	FString		pakMd5;// : "01d222cb4f9f18fd1316328e4bb2a007",
	int		pakSize;// : 13838704,
	int			externalLength;// : 80,
	int			externalWidth;// : 80,
	int			externalHeight;// : 80,
	GoodsData *	matchedProduct;//" : null

	FString		GamePath;
	FString		FilePath;
	UObject *	Object;

	GoodsDataType m_Type;
public:
    
	virtual void InitWithJson(const TSharedPtr<FJsonObject> &obj) override;
	~GoodsData();
	
	void CloneData(GoodsData * data);

public:

};
