#include "EditerARUIController.h"
#include "UIManager.h"

void EditerARUIController::On_Init()
{
    
}
void EditerARUIController::On_Start()
{
    OpenARUI();
    
}
void EditerARUIController::On_Delete()
{
    
}
void EditerARUIController::OpenARUI()
{
    UBaseUI * loginUI = UI_M->OpenUI(TEXT("EditerARUI"));
    loginUI->AddToViewport();
    
}

