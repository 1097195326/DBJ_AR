#pragma once
#include "GData.h"

class GCORE_API DataC : public GData
{
protected:
	int		m_Tid;
	int		m_Rid;
	int		m_Cid;
public:
	int	GetTid();
	int GetRid();
	int GetCid();


};