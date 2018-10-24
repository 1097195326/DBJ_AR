#pragma once
#include "DataT.h"


struct ServerData
{
	FString m_Key;
	FString m_Value;
	FString m_Desc;

	ServerData()
	{
		m_Key = "";
		m_Value = "";
		m_Desc = "";
	}
};
class ServerPrototype : public DataT
{
private:
	TMap<FString, ServerData> m_ServerData;
public:
	virtual void InitWithXML(TiXmlElement * _xml) override;

	ServerData GetDataByKey(FString _key);
};