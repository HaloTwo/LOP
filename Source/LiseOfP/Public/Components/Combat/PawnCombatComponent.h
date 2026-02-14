// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"

class UDataAsset_WeaponDatas;
class UDataAsset_VFXData;   

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	OrginalEquippedWeapon,
	LeftHand,
	RightHand,
	Body
};

UENUM(BlueprintType)
enum class ECollsionToggle : uint8
{
	Start,
	Tick,
	End
};

/**
 * 
 */
UCLASS()
class LISEOFP_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, Category = "Combo")
	// 콤보 입력 가능 여부
	bool bCanAcceptComboInput = true;

	// 무기 관련 변수들
	UPROPERTY(BlueprintReadWrite, Category = "Warrior|Combat")
	AWeaponBase* EquippedWeapon;

	UPROPERTY(BlueprintReadWrite, Category = "Warrior|Combat")
	UDataAsset_WeaponDatas* WeaponDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Warrior|VFX")
	UDataAsset_VFXData* ImpactVFXData;



public:
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	// 무기 등록;
	virtual void RegisterSpawnedWeapon(AWeaponBase* InWeaponToRegister, UDataAsset_WeaponDatas* WeaponData, bool bRegisterAsEquippedWeapon);

	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	virtual void ToggleWeaponCollision(ECollsionToggle bShouldEnable, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	virtual void ToggleBodyCollision(ECollsionToggle bShouldEnable, EToggleDamageType ToggleDamageType);

	virtual void OnHitTargetActor(AActor* HitActor, FVector vector);
	//virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);
	virtual void OnHitBlocking(AActor* HitActor, FVector ImpactPoint, EPhysicalSurface SurfaceType);

protected:
	TArray<AActor*> OverlappedActors;


};
