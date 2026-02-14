// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/PlayerGameplayAbility_Interact.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/PlayerCharacter.h"
#include "Components/UI/PlayerUIComponent.h"
#include "Items/InteractableBase.h"

#include "LOP_DebugHelper.h"

void UPlayerGameplayAbility_Interact::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	GetPlayerUIComponentFromActorInfo()->OnInteracted.Broadcast(true, ToolText);

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UPlayerGameplayAbility_Interact::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	GetPlayerUIComponentFromActorInfo()->OnInteracted.Broadcast(false, ToolText);

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UPlayerGameplayAbility_Interact::CollectInteractable()
{
    // 박스 트레이스 실행
    TArray<FHitResult> TraceHits;
    UKismetSystemLibrary::BoxTraceMultiForObjects(
        GetPlayerCharacterFromActorInfo(),
        GetPlayerCharacterFromActorInfo()->GetActorLocation(),
        GetPlayerCharacterFromActorInfo()->GetActorLocation() + -GetPlayerCharacterFromActorInfo()->GetActorUpVector() * BoxTraceDistance,
        TraceBoxSize / 2.f,
        (-GetPlayerCharacterFromActorInfo()->GetActorUpVector()).ToOrientationRotator(),
        InteractTraceChannels,
        false,
        TArray<AActor*>(),
        bDrawDebugShape ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
        TraceHits,
        true
    );

    // 가장 가까운 Interactable 찾기
    AInteractableBase* ClosestObject = nullptr;
    float ClosestDistSq = FLT_MAX;

    for (const FHitResult& TraceHit : TraceHits)
    {
        if (AInteractableBase* Found = Cast<AInteractableBase>(TraceHit.GetActor()))
        {
            float DistSq = FVector::DistSquared(
                GetPlayerCharacterFromActorInfo()->GetActorLocation(),
                Found->GetActorLocation()
            );

            if (DistSq < ClosestDistSq)
            {
                ClosestDistSq = DistSq;
                ClosestObject = Found;
            }
        }
    }

    // 결과 처리
    if (ClosestObject)
    {
        // 새로운 대상이 기존 것과 다르면 갱신
        if (FoundInteractableObject != ClosestObject)
        {
            FoundInteractableObject = ClosestObject;
        }
    }
    else
    {
        // 이전에 대상이 있었는데 지금은 없음 → Cancel
        if (FoundInteractableObject)
        {
            FoundInteractableObject = nullptr;

            CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
        }
    }
}

void UPlayerGameplayAbility_Interact::PerformInteract()
{
	if (FoundInteractableObject == nullptr)
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
		return;
	}

	FoundInteractableObject->ExecuteInteract(GetPlayerCharacterFromActorInfo());
}