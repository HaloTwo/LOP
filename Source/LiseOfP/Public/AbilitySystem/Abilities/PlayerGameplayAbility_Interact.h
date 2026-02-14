// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/LOP_PlayerGameplayAbility.h"
#include "PlayerGameplayAbility_Interact.generated.h"


class AInteractableBase;
/**
 * 
 */
UCLASS()
class LISEOFP_API UPlayerGameplayAbility_Interact : public ULOP_PlayerGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (ToolTip = "플레이어에게 보이는 설명"))
	FText ToolText;

	UPROPERTY(EditDefaultsOnly)
	float BoxTraceDistance = 50.f;

	UPROPERTY(EditDefaultsOnly)
	FVector TraceBoxSize = FVector(100.f);

	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> InteractTraceChannels;

	UPROPERTY(EditDefaultsOnly)
	bool bDrawDebugShape = false;

	UPROPERTY()
	AInteractableBase* FoundInteractableObject;

protected:
	//~ Begin UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface

	// 상호작용 가능한 오브젝트를 수집
	UFUNCTION(BlueprintCallable)
	void CollectInteractable(); 

	// 상호작용 수행
	UFUNCTION(BlueprintCallable)
	void PerformInteract(); 

};
