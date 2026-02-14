// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/LOP_AbilitySystemComponent.h"
#include "AbilitySystem/Abilities/LOP_PlayerGameplayAbility.h"

#include "DataAssets/WeaponDatas/DataAsset_PlayerWeaponDatas.h"
#include "DataAssets/WeaponDatas/DataAsset_WeaponDatas.h"

#include "LOP_GameplayTags.h"

void ULOP_AbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}

	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (!Spec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;

		Spec.InputPressed = true;

		if (Spec.IsActive())
		{
			//토글 가능한 Ability라면 
			if (InInputTag.MatchesTag(LOP_GameplayTags::InputTag_Toggleable))
			{
				CancelAbilityHandle(Spec.Handle);
			}
			// 이미 실행 중인 Ability라면 InputPressed 이벤트를 트리거 (WaitInputPress용)
			else 
			{
				InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
			}
		}
		else
		{
			TryActivateAbility(Spec.Handle);
		}
	}


}


void ULOP_AbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}

	//홀드면 때면 캔슬
	if (InInputTag.MatchesTag(LOP_GameplayTags::InputTag_MustBeHeld))
	{
		for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
		{
			if (AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag) && AbilitySpec.IsActive())
			{
				CancelAbilityHandle(AbilitySpec.Handle);
			}
		}
		return;
	}


	// InputTag에 해당하는 모든 Ability의 InputPressed 상태를 false로 설정하고 InputReleased 이벤트를 트리거
	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (!Spec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;

		Spec.InputPressed = false;

		// **WaitInputRelease를 트리거하는 공식 방식**
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
	}
}




void ULOP_AbilitySystemComponent::GrantPlayerWeaponAbilities(const TArray<FLOP_PlayerAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	if (InDefaultWeaponAbilities.IsEmpty())
	{
		return;
	}

	for (const FLOP_PlayerAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		if (!AbilitySet.IsValid()) continue;

		// 중복된 InputTag 가진 기존 Ability 제거
		TArray<FGameplayAbilitySpecHandle> HandlesToClear;

		for (const FGameplayAbilitySpec& ExistingSpec : GetActivatableAbilities())
		{
			if (ExistingSpec.DynamicAbilityTags.HasTagExact(AbilitySet.InputTag))
			{
				HandlesToClear.Add(ExistingSpec.Handle);
			}
		}

		for (const FGameplayAbilitySpecHandle& Handle : HandlesToClear)
		{
			ClearAbility(Handle);
		}

		// AbilitySpec 생성
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant, ApplyLevel);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		// Ability 부여
		FGameplayAbilitySpecHandle GrantedHandle = GiveAbility(AbilitySpec);
		OutGrantedAbilitySpecHandles.Add(GrantedHandle);

		UE_LOG(LogTemp, Log, TEXT("[GAS] Granted Ability: %s | InputTag: %s"),
			*AbilitySet.AbilityToGrant->GetName(),
			*AbilitySet.InputTag.ToString());
	}
}

bool ULOP_AbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate)
{
	check(AbilityTagToActivate.IsValid());

	TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagToActivate.GetSingleTagContainer(), FoundAbilitySpecs);

	if (!FoundAbilitySpecs.IsEmpty())
	{
		const int32 RandomAbilityIndex = FMath::RandRange(0, FoundAbilitySpecs.Num() - 1);
		FGameplayAbilitySpec* SpecToActivate = FoundAbilitySpecs[RandomAbilityIndex];

		check(SpecToActivate);


		if (!SpecToActivate->IsActive())
		{
			return TryActivateAbility(SpecToActivate->Handle);
		}
	}

	return false;
}
