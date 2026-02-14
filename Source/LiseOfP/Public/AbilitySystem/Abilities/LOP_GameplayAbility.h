// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "LOP_GameplayAbility.generated.h"

class UPawnCombatComponent;
class ULOP_AbilitySystemComponent;
class UPawnInventoryComponent;

UENUM(BlueprintType)
enum class EAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

/**
 * 
 */
UCLASS()
class LISEOFP_API ULOP_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	

protected:
	//~ Begin UGameplayAbility Interface.
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);
	//~ End UGameplayAbility Interface

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	EAbilityActivationPolicy AbilityActivationPolicy = EAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category = "Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "Ability")
	ULOP_AbilitySystemComponent* GetLOPAbilitySystemComponentFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Ability")
	UPawnInventoryComponent* GetPawnInventoryComponentFromActorInfo() const;

	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EWarriorSuccessType& OutSuccessType);

	UFUNCTION(BlueprintCallable, Category = "Warrior|Utility", meta = (DisplayName = "Is Attacker Behind Target"))
	static bool IsAttackerBehindTarget(AActor* Target, AActor* Attacker, float DotThreshold = -0.7f);
};
