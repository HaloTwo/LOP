// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "Kismet/GameplayStatics.h"   
#include "NiagaraFunctionLibrary.h"   
#include "NiagaraSystem.h"            
#include "DataAssets/DataAsset_VFXData.h"
#include "Characters/EnemyCharacter.h"
#include "Components/BoxComponent.h"

#include "LOP_GameplayTags.h"
#include "LOP_FunctionLibrary.h"

#include "LOP_DebugHelper.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor, FVector vector)
{
	//중복 타격 방지
	if (OverlappedActors.Contains(HitActor)) return;
	OverlappedActors.AddUnique(HitActor);

	//블록여부가 있는지 확인
	bool bIsValidBlock = false;

	//플레이어가 블록중인지 확인
	const bool bIsPlayerBlocking = ULOP_FunctionLibrary::NativeDoesActorHaveTag(HitActor, LOP_GameplayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnblockable = false;

	//블록이 가능하다면 블록 여부를 확인한다.
	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		bIsValidBlock = ULOP_FunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, LOP_GameplayTags::Player_Event_SuccessfulBlock, EventData);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), LOP_GameplayTags::Shared_Event_MeleeHit, EventData);
	}

	if (ImpactVFXData)
	{
		UNiagaraSystem* VFXToSpawn = nullptr;

		//Pawn 담당
		if (ImpactVFXData->SurfaceImpactVFX.Contains(SurfaceType3))
		{
			VFXToSpawn = ImpactVFXData->SurfaceImpactVFX[SurfaceType3];

			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), VFXToSpawn, vector, FRotator::ZeroRotator, FVector(0.1f));
			DrawDebugSphere(GetWorld(), vector, 10.f, 12, FColor::Red, false, 2.f);
		}
	}
}


void UEnemyCombatComponent::OnHitBlocking(AActor* HitActor, FVector ImpactPoint, EPhysicalSurface SurfaceType)
{
	if (!HitActor) return;

	// 이미 처리한 액터라면 무시
	if (OverlappedActors.Contains(HitActor)) return;
	OverlappedActors.AddUnique(HitActor);

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



void UEnemyCombatComponent::ToggleBodyCollision(ECollsionToggle bShouldEnable, EToggleDamageType ToggleDamageType)
{
	AEnemyCharacter* OwningEnemy = GetOwningPawn<AEnemyCharacter>();
	if (!OwningEnemy) return;

	switch (bShouldEnable)
	{
	case ECollsionToggle::Start:
	{
		UBoxComponent* TargetBox = nullptr;

		switch (ToggleDamageType)
		{
		case EToggleDamageType::LeftHand:
			TargetBox = OwningEnemy->GetLeftHandCollisionBox();
			break;

		case EToggleDamageType::RightHand:
			TargetBox = OwningEnemy->GetRightHandCollisionBox();
			break;

		case EToggleDamageType::Body:
			TargetBox = OwningEnemy->GetBodyCollisionBox();
			break;

		case EToggleDamageType::OrginalEquippedWeapon:
			TargetBox = OwningEnemy->GetWeaponCollisionBox();
			break;

		default:
			return;
		}

		if (TargetBox)
		{
			LastTraceLocation = TargetBox->GetComponentLocation();
		}
		break;
	}

	case ECollsionToggle::Tick:
		PerformAttackTrace(ToggleDamageType);
		break;

	case ECollsionToggle::End:
		LastTraceLocation = FVector::ZeroVector;
		OverlappedActors.Empty();
		break;
	}
}



void UEnemyCombatComponent::PerformAttackTrace(EToggleDamageType ToggleDamageType)
{
	AEnemyCharacter* OwningEnemyCharacter = GetOwningPawn<AEnemyCharacter>();
	if (!OwningEnemyCharacter) return;

	UBoxComponent* TargetBox = nullptr;
	switch (ToggleDamageType)
	{
	case EToggleDamageType::LeftHand:   TargetBox = OwningEnemyCharacter->GetLeftHandCollisionBox(); break;
	case EToggleDamageType::RightHand:  TargetBox = OwningEnemyCharacter->GetRightHandCollisionBox(); break;
	case EToggleDamageType::Body:       TargetBox = OwningEnemyCharacter->GetBodyCollisionBox(); break;
	case EToggleDamageType::OrginalEquippedWeapon: TargetBox = OwningEnemyCharacter->GetWeaponCollisionBox(); break;
	default: return;
	}

	if (!TargetBox) return;

	FVector CurrentLocation = TargetBox->GetComponentLocation();

	FCollisionQueryParams Params(SCENE_QUERY_STAT(BodyTrace), false, OwningEnemyCharacter);
	Params.bReturnPhysicalMaterial = true;

	TArray<FHitResult> HitResults;
	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		LastTraceLocation,
		CurrentLocation,
		TargetBox->GetComponentQuat(),
		ECC_Pawn,
		TargetBox->GetCollisionShape(),
		Params
	);

	// Debug
	DrawDebugLine(GetWorld(), LastTraceLocation, CurrentLocation, FColor::Yellow, false, 0.05f);
	DrawDebugBox(GetWorld(), CurrentLocation, TargetBox->GetScaledBoxExtent(), TargetBox->GetComponentQuat(), FColor::Green, false, 0.05f);

	if (bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			AActor* OtherActor = Hit.GetActor();

			if (APawn* HitPawn = Cast<APawn>(OtherActor))
			{
				OnHitTargetActor(OtherActor, Hit.ImpactPoint);
			}
			else if (Hit.Component.IsValid() && Hit.Component->GetCollisionObjectType() == ECC_WorldStatic)
			{
				EPhysicalSurface SurfaceType = SurfaceType_Default;
				if (UPhysicalMaterial* PhysMat = Hit.PhysMaterial.Get())
				{
					SurfaceType = UPhysicalMaterial::DetermineSurfaceType(PhysMat);
				}
				OnHitBlocking(OtherActor, Hit.ImpactPoint, SurfaceType);
			}
		}
	}

	LastTraceLocation = CurrentLocation;
}

