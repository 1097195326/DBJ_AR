#pragma once

#include "DataT.h"

struct UIData
{
    FString m_Key;
    FString m_Value;
    FString m_Desc;

    UIData()
    {
        m_Key = "";
        m_Value = "";
        m_Desc = "";
    }
};

class DBJ_AR_API UIPrototype : public DataT
{
private:
    TMap<FString, UIData> m_UIXMLData;
public:
    virtual void InitWithXML(TiXmlElement * _xml) override;

public:
    UIData GetDataByKey(FString _key);

};
