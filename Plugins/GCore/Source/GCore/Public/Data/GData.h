#pragma once


#include "GObject.h"
#include "Json/Public/Json.h"
#include "tinyxml.h"
#include "tinystr.h"

class GCORE_API GData : public GObject
{

public :
	virtual void InitWithJson(const TSharedPtr<FJsonObject> &obj);
	virtual void InitWithXML(TiXmlElement * elem);
};
