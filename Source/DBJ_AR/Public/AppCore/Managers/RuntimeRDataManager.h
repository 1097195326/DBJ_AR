#pragma once

#include "GObject.h"
#include "CoreMinimal.h"
#include "GoodsData.h"

struct R_Order
{
	int Id;//":0, // 新建状态时订单id为0， 编辑状态时为订单ID
	int Status;//" : 1, // 1表示预订单、2表示已提交订单。 已经提交的订单不允许编辑
	FString ReceiverCompanyName;//" : "收货公司名称",
	FString ReceiverName;// : "收货人姓名",
	FString ReceiverPhone;// : "收货人联系方式",
	int64 ExpectReceiveTime;// : 1537243577876, // 期望到货时间
	FString	ReceiveTime;
	bool Morning;// : true, // 是否为上午
	int DeliverType;// : 1, // 配送方式 1送货上门 2自提
	int ProvinceId;// : 3, //省份ID
	int CityId;// : 55, //城市ID
	int DistrictId;// : 243, // 区县ID
	FString	Address;//  : "详细地址",
	FString DetailAddress;
	FString	Remark;// : "备注",
	FString CommitTime;
	TArray<GoodsData*>	ProductList;
	int	totalQuantity;
	int totalPrice;
};

class DBJ_AR_API RuntimeRDataManager : public GObject
{
private:
	TArray<GoodsData*>		m_RuntimeGoodsList;
	R_Order	*				m_CurrentOrder;
	R_Order	*				m_EditOrder;
	RuntimeRDataManager();
public:
	static RuntimeRDataManager * GetInstance();

	GoodsData * AddGoodsToList(GoodsData* _data);
	GoodsData * ChangeListGoods(GoodsData* _preData,GoodsData * _changeData);
	void RemoveGoodsFromList(TArray<GoodsData*> _datas);
	TArray<GoodsData*>	GetRuntimeGoodsList();

	TMap<int, GoodsData*> GetOrderDatas();

	R_Order *	MakeOrder();
	void		EditOrder(R_Order * order);
	bool		IsEditOrder();

	R_Order	*	GetCurrentOrder();
	void	ClearOrder();

};
