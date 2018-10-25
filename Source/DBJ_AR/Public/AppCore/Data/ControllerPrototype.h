#pragma once
#include "DataT.h"
#include "ProjectDataType.h"
#include "CoreMinimal.h"

struct ControllerData
{

};

class ControllerPrototype : public DataT
{
private:
	TMap<FString, float>	m_DataMap;
public:
	int					m_Platform;
	int					m_Server_ID;
	int					m_UI_ID;
	int					m_Http_ID;

	float				m_AppVersion;
public:
	virtual void InitWithXML(TiXmlElement * _xml) override;


};