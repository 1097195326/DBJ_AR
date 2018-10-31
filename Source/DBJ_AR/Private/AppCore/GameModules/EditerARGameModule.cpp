#include "EditerARGameModule.h"
#include "EditerARUIController.h"
#include "DataManager.h"
#include "MsgCenter.h"


EditerARGameModule * EditerARGameModule::GetInstance()
{
    static EditerARGameModule m;
    return &m;
}
void EditerARGameModule::On_Init()
{
    m_CurrentUIController = new EditerARUIController();
    m_CurrentUIController->On_Init();
    
}
void EditerARGameModule::On_Start()
{
    m_CurrentUIController->On_Start();
    
}
void EditerARGameModule::On_Delete()
{
    
    if (m_CurrentUIController != nullptr)
    {
        delete m_CurrentUIController;
    }
}
