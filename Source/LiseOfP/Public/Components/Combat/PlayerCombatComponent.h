// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "PlayerCombatComponent.generated.h"

class APlayerWeapon;
class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class LISEOFP_API UPlayerCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Warrior|Combat")
	float PlayerAttackPower;


public:
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	float CalculateWeaponAttackPower(const UDataAsset_WeaponDatas* WeaponData);

	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	APlayerWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	APlayerWeapon* GetHeroCarriedEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	float GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const;

	// 무기 등록;
	virtual void RegisterSpawnedWeapon(AWeaponBase* InWeaponToRegister, UDataAsset_WeaponDatas* WeaponData, bool bRegisterAsEquippedWeapon) override;

	virtual void OnHitTargetActor(AActor* HitActor, FVector vector) override;
	//virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;
	virtual void OnHitBlocking(AActor* HitActor, FVector vector, EPhysicalSurface SurfaceType) override;

};
