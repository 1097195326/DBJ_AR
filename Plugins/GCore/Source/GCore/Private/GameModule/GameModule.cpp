#include "GCore.h"
#include "GameModule.h"



void GameModule::SetUIController(UIController * _uiController)
{
	m_CurrentUIController = _uiController;

}
UIController * GameModule::GetCurrentUIController()
{
	return m_CurrentUIController;
}