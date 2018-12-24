#include "ControllerPrototype.h"



G_REGISTER_CLASS(ControllerPrototype)

FString ControllerPrototype::ScreenResolutionId = TEXT("");

void ControllerPrototype::InitWithXML(TiXmlElement * xml)
{
	for (TiXmlElement* elem = xml->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		const char * id = elem->Attribute("key");
		const char * value = elem->Attribute("value");
		if (id != nullptr)
		{
			m_DataMap.Add(id, atoi(value));
		}
	}

	m_UI_ID = 400;
	m_Server_ID = m_DataMap["server"];
	m_Http_ID = m_DataMap["http_url"];

}
void ControllerPrototype::SetScreenResolution(FString ScreenResolution)
{
    
}
