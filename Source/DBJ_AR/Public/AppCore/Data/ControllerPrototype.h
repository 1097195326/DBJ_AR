#pragma once
#include "DataT.h"
#include "ProjectDataType.h"
#include "CoreMinimal.h"


class ControllerPrototype : public DataT
{
public:
	int					m_Platform;
	PrototypeIndex		m_Server_ID;
	PrototypeIndex		m_UI_ID;
	PrototypeIndex		m_Http_ID;

	float				m_AppVersion;
public:
	virtual void InitWithXML(TiXmlElement * _xml) override;


};