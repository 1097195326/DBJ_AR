#include "LoginGameMode.h"
#include "LoginGameModule.h"

ALoginGameMode::ALoginGameMode()
{
	LoginGameModule::GetInstance()->On_Init();

}

void ALoginGameMode::StartPlay()
{
	Super::StartPlay();

	LoginGameModule::GetInstance()->On_Start();

}
