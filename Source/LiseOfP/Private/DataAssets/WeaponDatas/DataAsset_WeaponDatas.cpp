// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/WeaponDatas/DataAsset_WeaponDatas.h"

float UDataAsset_WeaponDatas::ConvertGradeToFloat(EWeaponScalingGrade Grade) const
{
	switch (Grade)
	{
	case EWeaponScalingGrade::S: return 1.2f;
	case EWeaponScalingGrade::A: return 1.0f;
	case EWeaponScalingGrade::B: return 0.8f;
	case EWeaponScalingGrade::C: return 0.6f;
	case EWeaponScalingGrade::D: return 0.3f;
	default: return 0.0f;
	}
}
