#pragma once

#include "ToolButton.h"
#include "GoodsFilterButton.generated.h"


UCLASS()
class DBJ_AR_API  UGoodsFilterButton : public UToolButton
{
    GENERATED_BODY()

public:
    
	virtual void	SelectButton(bool _isSelect) override;


};