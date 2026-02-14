// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/WeaponDatas/DataAsset_WeaponDatas.h"
#include "DataAsset_PlayerWeaponDatas.generated.h"


USTRUCT(BlueprintType)
struct FLOP_PlayerAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ULOP_GameplayAbility> AbilityToGrant;

	bool IsValid() const;
};

/**
 * 
 */
UCLASS()
class LISEOFP_API UDataAsset_PlayerWeaponDatas : public UDataAsset_WeaponDatas
{
	GENERATED_BODY()
	

public:
	//링크용 애니메이션 레이어 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UPlayerLinkedAnimLayer> WeaponAnimLayerToLink;

	// 무기 아이콘 텍스처들
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> SoftWeaponIconTexture;

	// 무기 핸들 아이콘 텍스처들
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> SoftHandleIconTexture;

	// 게임 시작 시 기본으로 주어지는 무기 능력 세트들
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponAbility")
	TArray<FLOP_PlayerAbilitySet> WeaponAbilities;
};
