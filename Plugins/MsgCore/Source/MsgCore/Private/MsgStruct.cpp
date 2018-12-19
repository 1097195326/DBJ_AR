
#include "MsgStruct.h"


MsgStruct::MsgStruct()
{

}
MsgStruct::MsgStruct(void * _msgContent)
{
	m_MsgContent = _msgContent;
}
MsgStruct::MsgStruct(TSharedPtr<FJsonObject> _jsonObject)
{
	m_JsonObject = _jsonObject;
}
MsgStruct::~MsgStruct()
{
    UE_LOG(LogTemp,Log,TEXT("zhx MsgStruct delete"));
}

int MsgStruct::GetMsgId()
{
    return m_MsgId;
}
void* MsgStruct::GetMsgContent()
{
    return m_MsgContent;
}
TSharedPtr<FJsonObject> MsgStruct::GetJsonObject()
{
	return m_JsonObject;
}
MsgChanelId MsgStruct::GetMsgChannelId()
{
    return m_MsgChannelId;
}
char * MsgStruct::GetMsgError()
{
    return m_MsgError;
}
