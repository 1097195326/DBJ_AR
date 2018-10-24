#include "ControllerPrototype.h"



G_REGISTER_CLASS(ControllerPrototype)


void ControllerPrototype::InitWithXML(TiXmlElement * xml)
{
	for (TiXmlElement* elem = xml->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		m_Platform = atoi(elem->Attribute("platform"));

		int server = atoi(elem->Attribute("server"));
		switch (server)
		{
		case 0:
		{
			m_Server_ID = E_Server_IOS_ID;
		}
		default:
			break;
		}
		
		int http_url = atoi(elem->Attribute("http_url"));
		switch (http_url)
		{
		case 0:
		{
			m_Http_ID = E_Http_IOS_ID;
		}
		default:
			break;
		}
		
		m_UI_ID = E_UI_IOS_ID;

		m_AppVersion = atoi(elem->Attribute("appVersion"));
			

	}
}