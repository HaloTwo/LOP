// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "EnemyCombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class LISEOFP_API UEnemyCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
	
public:
	virtual void OnHitTargetActor(AActor* HitActor, FVector vector) override;
	virtual void OnHitBlocking(AActor* HitActor, FVector vector, EPhysicalSurface SurfaceType) override;

protected:
	virtual void ToggleBodyCollision(ECollsionToggle bShouldEnable, EToggleDamageType ToggleDamageType) override;



private:
	FVector LastTraceLocation;

	void PerformAttackTrace(EToggleDamageType ToggleDamageType);
};
