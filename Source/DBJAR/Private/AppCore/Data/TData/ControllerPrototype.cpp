#include "ControllerPrototype.h"
#include "Engine.h"


G_REGISTER_CLASS(ControllerPrototype)

int ControllerPrototype::ScreenResolutionId = 0;

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
    
    
    if (ScreenResolution.Equals(TEXT("0.46")))
    {
		ControllerPrototype::ScreenResolutionId = 401;
    }else if (ScreenResolution.Equals(TEXT("0.75")))
    {
		GEngine->GetGameUserSettings()->SetResolutionScaleValueEx(0.5);
	}else
	{
		ControllerPrototype::ScreenResolutionId = 400;
	}
	GEngine->GetGameUserSettings()->SetResolutionScaleValueEx(0.3);

    UE_LOG(LogTemp,Log,TEXT("zhx : current Screen Resolution : %s = %d"),*ScreenResolution,ControllerPrototype::ScreenResolutionId);
}
