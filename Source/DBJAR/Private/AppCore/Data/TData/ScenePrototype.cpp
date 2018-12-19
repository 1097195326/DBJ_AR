#include "ScenePrototype.h"


G_REGISTER_CLASS(ScenePrototype)


void ScenePrototype::InitWithXML(TiXmlElement * xml)
{
	for (TiXmlElement* elem = xml->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		const char * id = elem->Attribute("key");
		const char * value = elem->Attribute("value");
		if (id != nullptr)
		{
			m_SceneData.Add(id, value);
		}
	}

}
FString ScenePrototype::GetDataByKey(FString _key)
{
	if (m_SceneData.Contains(_key))
	{
		return *m_SceneData.Find(_key);
	}
	return "";
}