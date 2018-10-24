#pragma once

#include "GObject.h"
#include "UIController.h"

class GameModule : public GObject
{
private:

protected:
	UIController * m_UIController;
public:
	
	void SetUIController(UIController * _uiController);

	
};