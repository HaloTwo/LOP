// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PlayerCombatComponent.h"
#include "Items/Weapons/PlayerWeapon.h"
#include "DataAssets/WeaponDatas/DataAsset_WeaponDatas.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/LOP_AttributeSet.h"
#include "GameFramework/Character.h"

#include "Kismet/GameplayStatics.h"   
#include "NiagaraFunctionLibrary.h"   
#include "NiagaraSystem.h"            
#include "DataAssets/DataAsset_VFXData.h"

#include "DrawDebugHelpers.h"         

#include "LOP_GameplayTags.h"

#include "LOP_DebugHelper.h"

void UPlayerCombatComponent::RegisterSpawnedWeapon(AWeaponBase* InWeaponToRegister, UDataAsset_WeaponDatas* WeaponData, bool bRegisterAsEquippedWeapon)
{
	Super::RegisterSpawnedWeapon(InWeaponToRegister, WeaponData, bRegisterAsEquippedWeapon);

	// 보정 포함된 공격력 계산
	PlayerAttackPower = CalculateWeaponAttackPower(WeaponData);

	//Debug::Print(TEXT("PlayerAttackPower:"), PlayerAttackPower);
}


APlayerWeapon* UPlayerCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<APlayerWeapon>(EquippedWeapon);
}

APlayerWeapon* UPlayerCombatComponent::GetHeroCarriedEquippedWeapon() const
{
	return Cast<APlayerWeapon>(EquippedWeapon);
}

float UPlayerCombatComponent::GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
	return WeaponDataAsset->WeaponDamage;
}


void UPlayerCombatComponent::OnHitTargetActor(AActor* HitActor, FVector vector)
{
	if (OverlappedActors.Contains(HitActor)) return;

	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		LOP_GameplayTags::Shared_Event_MeleeHit,
		Data);

	if (ImpactVFXData)
	{
		UNiagaraSystem* VFXToSpawn = nullptr;

		//Pawn 담당
		if (ImpactVFXData->SurfaceImpactVFX.Contains(SurfaceType3))
		{
			VFXToSpawn = ImpactVFXData->SurfaceImpactVFX[SurfaceType3];

			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),VFXToSpawn,vector,FRotator::ZeroRotator, FVector(0.1f));
			DrawDebugSphere(GetWorld(), vector, 10.f, 12, FColor::Red, false, 2.f);
		}
	}
}

//void UPlayerCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
//{
//	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), LOP_GameplayTags::Player_Event_HitPause, FGameplayEventData());
//}

void UPlayerCombatComponent::OnHitBlocking(AActor* HitActor, FVector ImpactPoint, EPhysicalSurface SurfaceType)
{
	if (!HitActor) return;

	// 이미 처리한 액터라면 무시
	if (OverlappedActors.Contains(HitActor)) return;
	OverlappedActors.AddUnique(HitActor);

	// WorldStatic / Blocking 전용
	UE_LOG(LogTemp, Log, TEXT("OnHitBlocking: %s"), *GetNameSafe(HitActor));


	if (ImpactVFXData)
	{
		if (ImpactVFXData->SurfaceImpactVFX.Contains(SurfaceType))
		{
			UNiagaraSystem* VFXToSpawn = ImpactVFXData->SurfaceImpactVFX[SurfaceType];

			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), VFXToSpawn, ImpactPoint, FRotator::ZeroRotator);
			DrawDebugSphere(GetWorld(), ImpactPoint, 10.f, 12, FColor::Green, false, 2.f);
		}
	}
}




float UPlayerCombatComponent::CalculateWeaponAttackPower(const UDataAsset_WeaponDatas* WeaponData)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());
	if (!WeaponData || !ASC) return 0.f;

	const ULOP_AttributeSet* AttributeSet = ASC->GetSet<ULOP_AttributeSet>();
	if (!AttributeSet) return 0.f;

	// 플레이어 능력치
	const float Motivity = AttributeSet->GetMotivity();
	const float Technique = AttributeSet->GetTechnique();
	const float Advance = AttributeSet->GetAdvance();

	// 스케일링 등급 → 계수 변환
	const float MotivityFactor = WeaponData->ConvertGradeToFloat(WeaponData->MotivityGrade);
	const float TechniqueFactor = WeaponData->ConvertGradeToFloat(WeaponData->TechniqueGrade);
	const float AdvanceFactor = WeaponData->ConvertGradeToFloat(WeaponData->AdvanceGrade);

	// 스케일 보정치 계산 (보정 계수 적용)
	constexpr float ScalingCoefficient = 0.0118f;
	const float AttributeScaling = ((Motivity * MotivityFactor) +
		(Technique * TechniqueFactor) +
		(Advance * AdvanceFactor)) * ScalingCoefficient;

	// 보정이 하나라도 적용됐으면 계산된 값 사용, 아니면 순수 무기 데미지 리턴
	const bool bHasScaling =
		MotivityFactor > 0.f ||
		TechniqueFactor > 0.f ||
		AdvanceFactor > 0.f;

	if (bHasScaling)
	{
		return FMath::RoundToFloat(WeaponData->WeaponDamage * (1.f + AttributeScaling));;
	}
	else
	{
		return WeaponData->WeaponDamage;
	}
}
