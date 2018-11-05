#pragma once
#include "DataT.h"


class ScenePrototype : public DataT
{
private:
	TMap<FString, FString> m_SceneData;
public:
	virtual void InitWithXML(TiXmlElement * _xml) override;

	FString GetDataByKey(FString _key);
};