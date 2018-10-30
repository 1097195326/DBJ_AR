#include "EditerARGameMode.h"
#include "EditerARGameModule.h"
#include "UserController.h"


AEditerARGameMode::AEditerARGameMode()
{
//    PlayerControllerClass = AUserController::StaticClass();
    
    
	EditerARGameModule::GetInstance()->On_Init();

}

void AEditerARGameMode::StartPlay()
{
	EditerARGameModule::GetInstance()->On_Start();


}
