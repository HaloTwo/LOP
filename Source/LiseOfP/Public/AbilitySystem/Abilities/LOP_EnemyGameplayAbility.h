// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/LOP_GameplayAbility.h"
#include "LOP_EnemyGameplayAbility.generated.h"

class AEnemyCharacter;
class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class LISEOFP_API ULOP_EnemyGameplayAbility : public ULOP_GameplayAbility
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintPure, Category = "Ability")
	AEnemyCharacter* GetEnemyCharacterFromActorinfo();

	UFUNCTION(BlueprintPure, Category = "Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorinfo();

	UFUNCTION(BlueprintPure, Category = "Ability")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat);
private:
	TWeakObjectPtr<AEnemyCharacter> CachedEnemyCharacter;
};
