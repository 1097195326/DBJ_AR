#include "GoodsData.h"


void GoodsData::InitWithJson(const TSharedPtr<FJsonObject> &obj)
{
	
	obj->TryGetNumberField("id", id);
	obj->TryGetStringField("name", name);
	obj->TryGetNumberField("typeId", typeId);
	obj->TryGetBoolField("shelf", shelf);
	obj->TryGetStringField("categoryIdList", categoryIdList);
	obj->TryGetNumberField("modelId", modelId);
	obj->TryGetStringField("modelName", modelName);
	obj->TryGetNumberField("supplyId", supplyId);
	obj->TryGetStringField("supplyName", supplyName);
	obj->TryGetNumberField("salePrice", salePrice);
	obj->TryGetStringField("thumbnailUrl", thumbnailUrl);
	obj->TryGetStringField("thumbnailMd5", thumbnailMd5);
	obj->TryGetStringField("pakUrl", pakUrl);
	obj->TryGetStringField("pakMd5", pakMd5);
	obj->TryGetNumberField("pakSize", pakSize);
	obj->TryGetNumberField("externalLength", externalLength);
	obj->TryGetNumberField("externalWidth", externalWidth);
	obj->TryGetNumberField("externalHeight", externalHeight);
	obj->TryGetNumberField("quantity", quantity);
	obj->TryGetNumberField("totalPrice", totalPrice);


	matchedProduct = nullptr;
	const TSharedPtr<FJsonObject> * m_d;
	if (obj->TryGetObjectField("matchedProduct",m_d))
	{
		matchedProduct = new GoodsData();
		matchedProduct->InitWithJson(*m_d);
	}
	Object = nullptr;

}
GoodsData::~GoodsData()
{
	if (matchedProduct)
	{
		delete matchedProduct;
	}
}
void GoodsData::CloneData(GoodsData * data)
{
	data->id = id;
	data->name = name;//" : "zhx1",
	data->typeId = typeId;// : 2,
	data->shelf = shelf;// : true,
	data->categoryIdList = categoryIdList;// : null,
	data->modelId= modelId;// : 9,
	data->modelName= modelName;// : null,
	data->supplyId = supplyId;// : 2,
	data->supplyName = supplyName;// : "供应商添加测试",
	data->salePrice = salePrice;// : 30,
	data->thumbnailUrl = thumbnailUrl;// : "http://test.ali.res.dabanjia.com/res/20181105/AR_BOTANY__1541410677559_4017.png",
	data->thumbnailMd5 = thumbnailMd5;// : "f1492dae35087a0a54ae4d9d47577b2f",
	data->pakUrl = pakUrl;// : "http://test.ali.res.dabanjia.com/res/20181105/AR_BOTANY__1541410588562_6936.pak",
	data->pakMd5 = pakMd5;// : "01d222cb4f9f18fd1316328e4bb2a007",
	data->pakSize = pakSize;// : 13838704,
	data->externalLength = externalLength;// : 80,
	data->externalWidth = externalWidth;// : 80,
	data->externalHeight = externalHeight;// : 80,
	
	if (matchedProduct)
	{
		data->matchedProduct = new GoodsData();
		matchedProduct->CloneData(data->matchedProduct);
	}

	data->GamePath = GamePath;
	data->FilePath = FilePath;
	data->Object = Object;
	data->m_Type = m_Type;
}
UStaticMesh * GoodsData::LoadMesh()
{
	UStaticMesh * mesh = nullptr;

	for (FString fileName : m_FilePathList)
	{
		if (fileName.EndsWith(TEXT(".uasset")))
		{
			//拼出UObject的加载路径
			fileName.RemoveFromEnd(TEXT(".uasset"), ESearchCase::IgnoreCase);
			int32 pos = fileName.Find(TEXT("/Content/"), ESearchCase::IgnoreCase);
			fileName = fileName.RightChop(pos + 8);
			fileName = TEXT("/Game") + fileName;
			
			mesh = LoadObject<UStaticMesh>(nullptr, *fileName);
			if (mesh)
			{
				return mesh;
			}
		}
	}
	return mesh;
}