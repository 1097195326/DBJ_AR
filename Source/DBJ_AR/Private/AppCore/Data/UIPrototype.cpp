#include "UIPrototype.h"

G_REGISTER_CLASS(UIPrototype)

void UIPrototype::InitWithXML(TiXmlElement * _xml)
{
    for (TiXmlElement* elem = _xml->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
    {
		const char * id = elem->Attribute("key");
		if (id != nullptr)
		{
			UIData data;
			data.m_Key = UTF8_TO_TCHAR(id);
			data.m_Value = UTF8_TO_TCHAR(elem->Attribute("value"));
			data.m_Desc = UTF8_TO_TCHAR(elem->Attribute("desc"));

			m_UIXMLData.Add(data.m_Key, data);
		}
       
    }
}
UIData UIPrototype::GetDataByKey(FString _key)
{
    if (m_UIXMLData.Contains(_key))
    {
        return *m_UIXMLData.Find(_key);
    }
    UIData d;
    return d;
}
