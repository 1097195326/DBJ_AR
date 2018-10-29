#include "EditerARGameMode.h"
#include "EditerARGameModule.h"



AEditerARGameMode::AEditerARGameMode()
{
	EditerARGameModule::GetInstance()->On_Init();

}

void AEditerARGameMode::StartPlay()
{
	EditerARGameModule::GetInstance()->On_Start();


}