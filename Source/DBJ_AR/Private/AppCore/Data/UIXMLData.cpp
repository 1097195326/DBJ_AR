#include "UIXMLData.h"

G_REGISTER_CLASS(UIXMLData)

void UIXMLData::InitWithXML(TiXmlElement * xml)
{
    for (TiXmlElement* elem = xml->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
    {
        UIData data;
        data.m_Key = UTF8_TO_TCHAR(elem->Attribute("key"));
        data.m_Value = UTF8_TO_TCHAR(elem->Attribute("value"));
        data.m_Desc = UTF8_TO_TCHAR(elem->Attribute("desc"));

        m_UIXMLData.Add(data.m_Key, data);
    }
}
UIData UIXMLData::GetUIDataByKey(FString _key)
{
    if (m_UIXMLData.Contains(_key))
    {
        return *m_UIXMLData.Find(_key);
    }
    UIData d;
    return d;
}
