#pragma once

#include "GData.h"
#include <map>
#include "ProjectDataType.h"
#include "UIPrototype.h"

using namespace std;

#define Data_M DataManager::GetInstance()

class DBJ_AR_API DataManager : public GObject
{
private:
    map<int32, GData*>        m_DataMap;

private:
    bool LoadXMLFile(const FString & _xmlPath);

public:
    static DataManager * GetInstance();

    void LoadAllXMLData();


    GData * GetProtoType(PrototypeIndex _id);

};
