#include "ControllerPrototype.h"



G_REGISTER_CLASS(ControllerPrototype)


void ControllerPrototype::InitWithXML(TiXmlElement * xml)
{
	for (TiXmlElement* elem = xml->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		const char * id = elem->Attribute("key");
		if (id != nullptr)
		{
			m_DataMap.Add(id, atof(elem->Attribute("value")));

		}

		m_UI_ID = 400;
			

	}
}