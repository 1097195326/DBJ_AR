#pragma once

#include "GObject.h"
#include "UIController.h"

class GameModule : public GObject
{
private:

protected:
	//list<UIController*>		m_UIControllers;

	UIController * m_CurrentUIController;
public:
	
	void SetUIController(UIController * _uiController);

	UIController * GetCurrentUIController();
};