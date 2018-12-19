#pragma once

#include "UIController.h"

class LoginUIController : public UIController
{
private:

protected:

public:
	virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Delete() override;


	void OpenLoginUI();

};