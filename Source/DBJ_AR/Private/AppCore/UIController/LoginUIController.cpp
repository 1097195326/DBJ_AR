#include "LoginUIController.h"
#include "ManagerHeader.h"

void LoginUIController::On_Init()
{

}
void LoginUIController::On_Start()
{
	OpenLoginUI();

}
void LoginUIController::On_Delete()
{

}
void LoginUIController::OpenLoginUI()
{
	UBaseUI * loginUI = UI_M->OpenUI(TEXT("LoginUI"));
	loginUI->AddToViewport();

}