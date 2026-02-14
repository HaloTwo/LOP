// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/LOP_PlayerGameplayAbility.h"
#include "Characters/PlayerCharacter.h"
#include "Controllers/PlayerCharacterController.h"
#include "AbilitySystem/LOP_AbilitySystemComponent.h"
#include "AbilitySystem/LOP_AttributeSet.h"

#include "LOP_GameplayTags.h"

#include "LOP_DebugHelper.h"

APlayerCharacter* ULOP_PlayerGameplayAbility::GetPlayerCharacterFromActorInfo()
{
	if (!CachedPlayerCharacter.IsValid())
	{
		CachedPlayerCharacter = Cast<APlayerCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedPlayerCharacter.IsValid() ? CachedPlayerCharacter.Get() : nullptr;
}

APlayerCharacterController* ULOP_PlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
	if (!CachedPlayerController.IsValid())
	{
		CachedPlayerController = Cast<APlayerCharacterController>(CurrentActorInfo->PlayerController);
	}

	return CachedPlayerController.IsValid() ? CachedPlayerController.Get() : nullptr;
}

UPlayerCombatComponent* ULOP_PlayerGameplayAbility::GetPlayerCombatComponentFromActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetPlayerCombatComponent();
}

UPlayerInventoryComponent* ULOP_PlayerGameplayAbility::GetPlayerInventoryComponentFromActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetInventoryComponentComponent();
}

UPlayerUIComponent* ULOP_PlayerGameplayAbility::GetPlayerUIComponentFromActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetPlayerUIComponent();
}

FGameplayEffectSpecHandle ULOP_PlayerGameplayAbility::MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InCurrentComboCount)
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

	EffectSpecHandle.Data->SetSetByCallerMagnitude(LOP_GameplayTags::Shared_SetByCaller_BaseDamage, InWeaponBaseDamage);

	if (InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InCurrentComboCount);
	}

	return EffectSpecHandle;
}



bool ULOP_PlayerGameplayAbility::TryApplyStaminaCost(TSubclassOf<UGameplayEffect> EffectClass, float StaminaDelta)
{
	check(EffectClass);

	ULOP_AbilitySystemComponent* ASC = GetLOPAbilitySystemComponentFromActorInfo();
	if (!ASC) return false;

	// 현재 스태미너 가져오기
	const float CurrentStamina = ASC->GetNumericAttribute(ULOP_AttributeSet::GetCurrentStaminaAttribute());

	// 감소(소모)일 때 → 조건 체크
	if (StaminaDelta < 0.f && CurrentStamina < FMath::Abs(StaminaDelta))
	{
		return false; // 스태미너 부족
	}

	// EffectContext 생성
	FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());

	// Outgoing Spec 생성
	FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(
		EffectClass,
		1.0f,
		ContextHandle
	);

	if (EffectSpecHandle.IsValid())
	{
		// SetByCallerMagnitude 값 세팅 (회복/소모 모두 처리 가능)
		EffectSpecHandle.Data->SetSetByCallerMagnitude(LOP_GameplayTags::Player_SetByCaller_Stamina, StaminaDelta);

		// Apply
		ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);
		return true;
	}

	return false;
}


bool ULOP_PlayerGameplayAbility::CanApplyHealItem(int32 HealValue) const
{
	ULOP_AbilitySystemComponent* ASC = GetLOPAbilitySystemComponentFromActorInfo();
	if (!ASC) return false;

	const float CurrentHP = ASC->GetNumericAttribute(ULOP_AttributeSet::GetCurrentHealthAttribute());
	const float MaxHP = ASC->GetNumericAttribute(ULOP_AttributeSet::GetMaxHealthAttribute());

	// 체력이 가득 차면 불가능
	return (CurrentHP < MaxHP && HealValue > 0);
}

void ULOP_PlayerGameplayAbility::ApplyHealItem(TSubclassOf<UGameplayEffect> EffectClass, int32 HealValue)
{
	if (!EffectClass) return;

	ULOP_AbilitySystemComponent* ASC = GetLOPAbilitySystemComponentFromActorInfo();
	if (!ASC) return;

	// EffectContext 생성
	FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());

	// Outgoing Spec 생성
	FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(
		EffectClass,
		1.0f, // 아이템은 보통 레벨 고정
		ContextHandle
	);

	if (EffectSpecHandle.IsValid())
	{
		// HealValue 적용
		EffectSpecHandle.Data->SetSetByCallerMagnitude(
			LOP_GameplayTags::Player_SetByCaller_Health,
			HealValue
		);

		ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);
	}
}

