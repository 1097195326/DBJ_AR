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
	
	matchedProduct = nullptr;
	const TSharedPtr<FJsonObject> * m_d;
	if (obj->TryGetObjectField("matchedProduct",m_d))
	{
		matchedProduct = new GoodsData();
		matchedProduct->InitWithJson(*m_d);
	}
	//Object = nullptr;

}
GoodsData::~GoodsData()
{
	if (matchedProduct)
	{
		delete matchedProduct;
	}
}