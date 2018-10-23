#pragma once

#include "GData.h"
#include <map>
#include "UIXMLData.h"

using namespace std;

enum DataIndex
{
    E_UIXMLData = 100


};

class DBJ_AR_API DataManager : public GObject
{
private:
    map<int32, GData*>        m_DataMap;

private:
    bool LoadXMLFile(const FString & _xmlPath);

public:
    static DataManager * GetInstance();

    void LoadAllXMLData();


    UIXMLData * GetUIXMLData();

};
