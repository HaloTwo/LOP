// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NativeGameplayTags.h"
#include "LOP_FunctionLibrary.h"

#include "DataAsset_WeaponDatas.generated.h"

class AWeaponBase;
class UPlayerLinkedAnimLayer;
class UInputMappingContext;
class ULOP_GameplayAbility;
class UTexture2D;

/**
 *
 */
UCLASS()
class LISEOFP_API UDataAsset_WeaponDatas : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// 무기 타입
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EWeaponType WeaponType;

	//무기 태그
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag WeaponTag;

	//무기 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly )
	TSubclassOf<AWeaponBase> WeaponClass;

	// 무기 기본 공격력
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float WeaponDamage;



	//보정 수치
	UPROPERTY(EditDefaultsOnly, Category = "WeaponValue")
	EWeaponScalingGrade MotivityGrade;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponValue")
	EWeaponScalingGrade TechniqueGrade;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponValue")
	EWeaponScalingGrade AdvanceGrade;


	UFUNCTION(BlueprintCallable, Category = "Weapon")
	float ConvertGradeToFloat(EWeaponScalingGrade Grade) const;
};

