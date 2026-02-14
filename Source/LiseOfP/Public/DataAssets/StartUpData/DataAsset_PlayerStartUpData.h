// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "DataAssets/WeaponDatas/DataAsset_PlayerWeaponDatas.h"

#include "GameplayTagContainer.h"
#include "DataAsset_PlayerStartUpData.generated.h"

class UDataAsset_PlayerWeaponDatas;
struct FLOP_PlayerAbilitySet;

//USTRUCT(BlueprintType)
//struct FDefaultItemData
//{
//	GENERATED_BODY();
//
//	// 아이템 ID (데이터 테이블에서 참조)
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//	FName ItemID;
//
//	// 시작 수량
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//	int32 Quantity = 1;
//};
/**
 *
 */
UCLASS()
class LISEOFP_API UDataAsset_PlayerStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(ULOP_AbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
	UDataTable* ItemDataTable;

	//// 게임 시작 시 기본으로 주어지는 무기 데이터 에셋들
	//UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (TitleProperty = "DefaultWeapon"))
	//TArray<UDataAsset_PlayerWeaponDatas*> DefaultPlayerWeapons;

	// 게임 시작 시 기본으로 주어지는 아이템 데이터들
	//UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (TitleProperty = "DefaultItem"))
	//TArray<FDefaultItemData> DefaultPlayerItems;

	//웨폰 입력 매핑 컨텍스트
	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (TitleProperty = "WeaponMapping"))
	UInputMappingContext* WeaponInputMappingContext;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FLOP_PlayerAbilitySet> PlayerStartUpAbilitySets;


};

