#pragma once

#include "ToolButton.h"
#include "GoodsFilterButton.generated.h"


UCLASS()
class DBJAR_API  UGoodsFilterButton : public UToolButton
{
    GENERATED_BODY()

public:
    
	virtual void	SelectButton(bool _isSelect) override;


};
