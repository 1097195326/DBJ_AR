#include "LoginGameModule.h"
#include "LoginUIController.h"

LoginGameModule * LoginGameModule::GetInstance()
{
	static LoginGameModule m;
	return &m;
}
void LoginGameModule::On_Init()
{
	m_CurrentUIController = new LoginUIController();
	m_CurrentUIController->On_Init();

}
void LoginGameModule::On_Start()
{
	m_CurrentUIController->On_Start();

}
void LoginGameModule::On_Delete()
{

	if (m_CurrentUIController != nullptr)
	{
		delete m_CurrentUIController;
	}
}