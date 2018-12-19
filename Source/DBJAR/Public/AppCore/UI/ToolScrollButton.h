#pragma once
#include "ToolButton.h"
#include "ToolScrollButton.generated.h"


UCLASS()
class DBJAR_API  UToolScrollButton : public UToolButton
{
	GENERATED_BODY()

public:

	virtual void	SetData(const IdData & _data, SelectButtonDelegate * _delegate);

};
