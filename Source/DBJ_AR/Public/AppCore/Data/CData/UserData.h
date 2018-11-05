// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"




struct  FSaveUserData
{


public:

	FString token;
	int32 id;
	FString phone;
	FString renterName;
	FString companyName;
	int32 provinceId;
	int32 cityId;
	int32 districtId;
	FString address;
	FString detailAddress;
	bool limit;
	FString gmtCreate;
	FSaveUserData() {}
};



struct  FUserData
{




public:


	FUserData() {}

};


