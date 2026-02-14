// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/LOP_GameplayAbility.h"
#include "AbilitySystem/LOP_AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "GameFramework/Character.h"

#include "Components/Combat/PawnCombatComponent.h"
#include "Components/Inventory/PawnInventoryComponent.h"

#include "LOP_FunctionLibrary.h"


void ULOP_GameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == EAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void ULOP_GameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == EAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UPawnCombatComponent* ULOP_GameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

ULOP_AbilitySystemComponent* ULOP_GameplayAbility::GetLOPAbilitySystemComponentFromActorInfo() const
{
	return Cast<ULOP_AbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

UPawnInventoryComponent* ULOP_GameplayAbility::GetPawnInventoryComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnInventoryComponent>();

}

FActiveGameplayEffectHandle ULOP_GameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	check(TargetASC && InSpecHandle.IsValid());

	return GetLOPAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data,TargetASC);
}

FActiveGameplayEffectHandle ULOP_GameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EWarriorSuccessType& OutSuccessType)
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);

	OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? EWarriorSuccessType::Successful : EWarriorSuccessType::Failed;

	return ActiveGameplayEffectHandle;
}

bool ULOP_GameplayAbility::IsAttackerBehindTarget(AActor* Target, AActor* Attacker, float DotThreshold)
{
	if (!Target || !Attacker) return false;

	// 위치 벡터 계산
	const FVector TargetLocation = Target->GetActorLocation();
	const FVector AttackerLocation = Attacker->GetActorLocation();
	const FVector DirectionToAttacker = (AttackerLocation - TargetLocation).GetSafeNormal();

	// 타겟의 ForwardVector (가능하면 SkeletalMesh 기준)
	FVector ForwardVector = Target->GetActorForwardVector();

	if (const ACharacter* Character = Cast<ACharacter>(Target))
	{
		if (const USkeletalMeshComponent* Mesh = Character->GetMesh())
		{
			ForwardVector = Mesh->GetForwardVector();
		}
	}

	// Dot 계산
	const float Dot = FVector::DotProduct(ForwardVector, DirectionToAttacker);

	// Dot이 임계값보다 작으면 뒤에서 공격한 것
	return Dot < DotThreshold;
}

