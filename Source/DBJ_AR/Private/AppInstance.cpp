#include "AppInstance.h"




UAppInstance::UAppInstance()
{
	m_Instance = this;
}
void UAppInstance::On_Init()
{
    Data_M->LoadAllXMLData();

}
