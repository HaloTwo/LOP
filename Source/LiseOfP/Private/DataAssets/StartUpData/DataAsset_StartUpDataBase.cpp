// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "AbilitySystem/LOP_AbilitySystemComponent.h"
#include "AbilitySystem/Abilities/LOP_GameplayAbility.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(ULOP_AbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);

	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);

	if (!StartUpGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf < UGameplayEffect >& EffectClass : StartUpGameplayEffects)
		{
			if (!EffectClass) continue;

			
			UGameplayEffect* EffectCDO = EffectClass->GetDefaultObject<UGameplayEffect>(); // 이펙트 CDO 가져오기

			// 이펙트가 CDO가 아닌 경우, ApplyGameplayEffectToSelf를 호출할 때는 CDO를 사용해야 합니다.
			InASCToGive->ApplyGameplayEffectToSelf(EffectCDO, ApplyLevel, InASCToGive->MakeEffectContext());
		}
	}
}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<ULOP_GameplayAbility>>& InAbilitiesToGive, ULOP_AbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())return;


	//어빌리티 시스템 컴포넌트가 유효한지 확인	
	for (const TSubclassOf<ULOP_GameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InASCToGive->GiveAbility(AbilitySpec);
	}
}