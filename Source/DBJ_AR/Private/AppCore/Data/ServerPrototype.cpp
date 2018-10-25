#include "ServerPrototype.h"

G_REGISTER_CLASS(ServerPrototype)

void ServerPrototype::InitWithXML(TiXmlElement * _xml)
{
	for (TiXmlElement* elem = _xml->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		const char * id = elem->Attribute("key");
		if (id != nullptr)
		{
			ServerData data;
			data.m_Key = UTF8_TO_TCHAR(id);
			data.m_Value = UTF8_TO_TCHAR(elem->Attribute("value"));
			data.m_Desc = UTF8_TO_TCHAR(elem->Attribute("desc"));

			m_ServerData.Add(data.m_Key, data);
		}
		
	}

}

ServerData ServerPrototype::GetDataByKey(FString _key)
{
	if (m_ServerData.Contains(_key))
	{
		return *m_ServerData.Find(_key);
	}
	ServerData d;
	return d;
}