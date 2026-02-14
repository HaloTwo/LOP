// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_PlayerStartUpData.h"
#include "DataAssets/WeaponDatas/DataAsset_PlayerWeaponDatas.h"

#include "AbilitySystem/LOP_AbilitySystemComponent.h"
#include "AbilitySystem/Abilities/LOP_GameplayAbility.h"

bool FLOP_PlayerAbilitySet::IsValid() const
{
    return InputTag.IsValid() && AbilityToGrant;
}

void UDataAsset_PlayerStartUpData::GiveToAbilitySystemComponent(ULOP_AbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
    Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

    for (const FLOP_PlayerAbilitySet& AbilitySet : PlayerStartUpAbilitySets)
    {
        if (!AbilitySet.IsValid()) continue;

        FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
        AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
        AbilitySpec.Level = ApplyLevel;
        AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

        InASCToGive->GiveAbility(AbilitySpec);
    }
}