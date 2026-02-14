// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/LOP_GameplayAbility.h"
#include "LOP_PlayerGameplayAbility.generated.h"

class APlayerCharacter;
class APlayerCharacterController;
class UPlayerUIComponent;

/**
 * 
 */
UCLASS()
class LISEOFP_API ULOP_PlayerGameplayAbility : public ULOP_GameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	APlayerCharacter* GetPlayerCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	APlayerCharacterController* GetPlayerControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	UPlayerCombatComponent* GetPlayerCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	UPlayerInventoryComponent* GetPlayerInventoryComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	UPlayerUIComponent* GetPlayerUIComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	FGameplayEffectSpecHandle MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InCurrentComboCount);

	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability")
	bool TryApplyStaminaCost(TSubclassOf<UGameplayEffect> EffectClass, float NewStaminaValue);

	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability")
	bool CanApplyHealItem(int32 HealValue) const;

	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability")
	void ApplyHealItem(TSubclassOf<UGameplayEffect> EffectClass, int32 HealValue);

private:
	TWeakObjectPtr<APlayerCharacter> CachedPlayerCharacter;
	TWeakObjectPtr<APlayerCharacterController> CachedPlayerController;

};
