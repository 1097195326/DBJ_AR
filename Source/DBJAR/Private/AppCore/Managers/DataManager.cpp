#include "DataManager.h"
#include "FileHelper.h"
#include "Base64.h"
//#include "EncryptDecryptTool.h"
#include "ServerPrototype.h"
#include "HttpMappingPrototype.h"
#include "ControllerPrototype.h"


DataManager * DataManager::GetInstance()
{
    static DataManager m;
    return &m;
}
void DataManager::LoadAllXMLData()
{
    //
    FString mContentDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
    FString mLocalConfigPath = FString::Printf(TEXT("%s%s"), *mContentDir, TEXT("Configs/"));

    UE_LOG(LogTemp,Log,TEXT("zhx : DataManager::LoadAllXMLData : %s"),*mLocalConfigPath);
    
	LoadXMLFile(FString::Printf(TEXT("%s%s"), *mLocalConfigPath, TEXT("ControllerPrototype.xml")));
	LoadXMLFile(FString::Printf(TEXT("%s%s"), *mLocalConfigPath, TEXT("HttpMappingPrototype.xml")));
	LoadXMLFile(FString::Printf(TEXT("%s%s"), *mLocalConfigPath, TEXT("ServerPrototype.xml")));
	LoadXMLFile(FString::Printf(TEXT("%s%s"), *mLocalConfigPath, TEXT("UIPrototype.xml")));
	LoadXMLFile(FString::Printf(TEXT("%s%s"), *mLocalConfigPath, TEXT("ScenePrototype.xml")));

}
bool DataManager::LoadXMLFile(const FString & _xmlPath)
{
    TiXmlDocument doc;
    FString mStrContent;

    if (!FFileHelper::LoadFileToString(mStrContent, *_xmlPath))
    {
        return false;
    }
    // ¼ÓÃÜ.
    /*if (!_xmlPath.Contains(TEXT("ChinesePrototype.xml")) && !_xmlPath.Contains(TEXT("EnglishPrototype.xml")))
    {
        FString mEncryptStr = EncryptAndDecryptTool::Decrypt(mStrContent, EncryptKey);
        FBase64::Decode(mEncryptStr, mStrContent);
    }*/
    UE_LOG(LogTemp,Log,TEXT("zhx : DataManager::LoadXMLFile : %s"),*mStrContent);
    
    FString mContent = mStrContent;
    std::string stdContent = TCHAR_TO_UTF8(*mContent);
    const char * xmlContent = stdContent.c_str();
    doc.Parse(xmlContent);

    TiXmlElement* root = doc.FirstChildElement();
    if (root == NULL)
    {
        doc.Clear();
        return false;
    }
    const char * nodeType = root->Attribute("type");
    for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
    {
        GData * mData;
        const char * pid = elem->Attribute("pid");
        std::map<int32, GData*>::iterator it = m_DataMap.find(atoi(pid));
        if (it != m_DataMap.end())
        {
            mData = it->second;
            mData->InitWithXML(elem);
        }
        else
        {
            mData = (GData*)(ReflectManager::Get()->GetClassByName(nodeType));
            mData->InitWithXML(elem);
            m_DataMap.insert(std::make_pair(atoi(pid), mData));
        }
    }
    doc.Clear();
    return true;
}

FString DataManager::GetURL(int index)
{
	ControllerPrototype * controller = GetProtoType<ControllerPrototype>(PrototypeIndex::E_Controller_ID);
	ServerPrototype * server = GetProtoType<ServerPrototype>(controller->m_Server_ID);
	HttpMappingPrototype * http = GetProtoType<HttpMappingPrototype>(controller->m_Http_ID);
	ServerData serverData = server->GetDataByKey("serverUrl");
	HttpData httpData = http->GetDataByKey(index);
	FString url = FString::Printf(TEXT("%s%s"), *serverData.m_Value, *httpData.m_Uri);
	return url;
}