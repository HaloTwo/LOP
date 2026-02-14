// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class ULOP_GameplayAbility;
class ULOP_AbilitySystemComponent;
class UDataAsset_WeaponDatas;
class UGameplayEffect;

/**
 *
 */
UCLASS()
class LISEOFP_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	// 게임 시작 시 활성화되는 능력들을 AbilitySystemComponent에 적용합니다.
	virtual void GiveToAbilitySystemComponent(ULOP_AbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	// 사용자가 게임 시작 시 활성화되는 능력들
	TArray< TSubclassOf < ULOP_GameplayAbility > > ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	// 사용자가 반응할 때 활성화되는 능력들
	TArray< TSubclassOf < ULOP_GameplayAbility > > ReactiveAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	// 게임 시작 시 적용되는 GameplayEffect들
	TArray<TSubclassOf<UGameplayEffect>> StartUpGameplayEffects;

	// ActivateOnGivenAbilities와 ReactiveAbilities를 InASCToGive에 적용합니다.
	void GrantAbilities(const TArray< TSubclassOf < ULOP_GameplayAbility > >& InAbilitiesToGive, ULOP_AbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

};
