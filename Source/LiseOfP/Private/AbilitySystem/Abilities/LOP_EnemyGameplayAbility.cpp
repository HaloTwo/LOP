// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/Abilities/LOP_EnemyGameplayAbility.h"
#include "Characters/EnemyCharacter.h"
#include "AbilitySystem/LOP_AbilitySystemComponent.h"
#include "LOP_GameplayTags.h"

AEnemyCharacter* ULOP_EnemyGameplayAbility::GetEnemyCharacterFromActorinfo()  
{  
	if (!CachedEnemyCharacter.IsValid())  
	{  
		CachedEnemyCharacter = Cast<AEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}  

	return CachedEnemyCharacter.IsValid() ? CachedEnemyCharacter.Get() : nullptr;  
}

UEnemyCombatComponent* ULOP_EnemyGameplayAbility::GetEnemyCombatComponentFromActorinfo()
{
	return GetEnemyCharacterFromActorinfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle ULOP_EnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetLOPAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetLOPAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		LOP_GameplayTags::Shared_SetByCaller_BaseDamage,
		InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel())
	);

	return EffectSpecHandle;
}


