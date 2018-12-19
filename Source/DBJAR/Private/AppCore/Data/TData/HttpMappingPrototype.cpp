#include "HttpMappingPrototype.h"


G_REGISTER_CLASS(HttpMappingPrototype)

void HttpMappingPrototype::InitWithXML(TiXmlElement * _xml)
{
	for (TiXmlElement* elem = _xml->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		const char * id = elem->Attribute("msgId");
		if (id != nullptr)
		{
			HttpData data;
			data.m_msgID = atoi(id);
			data.m_Channel = UTF8_TO_TCHAR(elem->Attribute("channel"));
			//data.m_Url = UTF8_TO_TCHAR(elem->Attribute("url"));
			data.m_Uri = UTF8_TO_TCHAR(elem->Attribute("uri"));
			data.m_desc = UTF8_TO_TCHAR(elem->Attribute("desc"));

			m_DataMap.Add(data.m_msgID, data);
		}
		
	}

}
HttpData HttpMappingPrototype::GetDataByKey(int _msgId)
{
	if (m_DataMap.Contains(_msgId))
	{
		return *m_DataMap.Find(_msgId);
	}
	HttpData d;
	return d;
}