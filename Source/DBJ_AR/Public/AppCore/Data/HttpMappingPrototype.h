#pragma once
#include "DataT.h"

struct HttpData
{
	int		m_msgID;
	FString		m_Channel;
	//FString		m_Url;
	FString		m_Uri;
	FString		m_desc;
	HttpData()
	{
		m_msgID = 0;
		m_Channel = "";
		//m_Url = "";
		m_Uri = "";
		m_desc = "";
	}
};

class HttpMappingPrototype : public DataT
{
private:
	TMap<int, HttpData>		m_DataMap;

public:
	virtual void InitWithXML(TiXmlElement * _xml) override;

	HttpData GetDataByKey(int _msgId);
};