// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/PlayerGameplayAbility_TargetLock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/PlayerCharacter.h"
#include "Characters/BaseCharacter.h"
#include "Widgets/LOP_WidgetBase.h"
#include "Controllers/PlayerCharacterController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "EnhancedInputSubsystems.h"
#include "MotionWarpingComponent.h"


#include "LOP_FunctionLibrary.h"
#include "LOP_GameplayTags.h"

#include "LOP_DebugHelper.h"

void UPlayerGameplayAbility_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	TryLockOnTarget();

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UPlayerGameplayAbility_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ResetTargetLockMappingContext();
	CleanUp();

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UPlayerGameplayAbility_TargetLock::OnTargetLockTick(float DeltaTime)
{
	// 타겟이 죽었거나, 플레이어가 죽었을 때 타겟 잠금 해제
	if (!CurrentLockedActor ||
		ULOP_FunctionLibrary::NativeDoesActorHaveTag(CurrentLockedActor, LOP_GameplayTags::Shared_Status_Dead) ||
		ULOP_FunctionLibrary::NativeDoesActorHaveTag(GetPlayerCharacterFromActorInfo(), LOP_GameplayTags::Shared_Status_Dead)
		)
	{
		CancelTargetLockAbility();
		return;
	}

	//타겟위치 추적
	SetTargetLockWidgetPosition();

	APlayerController* PC = GetPlayerControllerFromActorInfo();
	APlayerCharacter* CH = GetPlayerCharacterFromActorInfo();
	if (!PC || !CH) return;

	SetWarpTarget(CurrentLockedActor->GetActorLocation());


	// 달리기/대쉬 태그 여부 
	const bool bIsDashingOrRunning = ULOP_FunctionLibrary::NativeDoesActorHaveTag(CH, LOP_GameplayTags::Player_Status_DashAndRun);

	// 카메라 위치 기준
	const FVector From = PC->PlayerCameraManager->GetCameraLocation();

	USkeletalMeshComponent* Mesh = CurrentLockedActor->FindComponentByClass<USkeletalMeshComponent>();

	// 소켓 위치 또는 액터 위치
	FVector To = Mesh ? Mesh->GetSocketLocation(TargetLockWidgetSocketName) : CurrentLockedActor->GetActorLocation();

	// LookAt 회전 계산
	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(From, To);
	FRotator CurrentCR = PC->GetControlRotation();

	// ---- Yaw 보간 (그대로 사용) ----
	const float InterpYaw = FMath::RInterpTo(
		FRotator(0.f, CurrentCR.Yaw, 0.f),
		FRotator(0.f, LookAtRot.Yaw, 0.f),
		DeltaTime,
		TargetLockRotationInterpSpeed).Yaw;

	// ---- Pitch 처리 ----
	float TargetPitch = LookAtRot.Pitch;

	// 카메라 시점 제한 (항상 위에서 내려보는 각도 유지)
	TargetPitch = FMath::Clamp(TargetPitch, -30.f, -5.f);

	//  Normalize해서 튀는 거 방지
	float NormalizedCurrentPitch = FRotator::NormalizeAxis(CurrentCR.Pitch);
	float NormalizedTargetPitch = FRotator::NormalizeAxis(TargetPitch);

	// 보간
	const float InterpPitch = FMath::FInterpTo(
		NormalizedCurrentPitch,
		NormalizedTargetPitch,
		DeltaTime,
		TargetLockRotationInterpSpeed
	);

	// 최종 적용
	PC->SetControlRotation(FRotator(InterpPitch, InterpYaw, 0.f));

	// 캐릭터 회전 처리
	if (bIsDashingOrRunning)
	{
		CH->bUseControllerRotationYaw = false; // 이동 방향 기준
	}
	else
	{
		CH->bUseControllerRotationYaw = true;
		CH->SetActorRotation(FRotator(0.f, InterpYaw, 0.f));
	}

}

void UPlayerGameplayAbility_TargetLock::SwitchTarget(const FGameplayTag& InSwitchDirectionTag)
{

	TArray<AActor*> ActorsOnLeft;
	TArray<AActor*> ActorsOnRight;
	AActor* NewTargetToLock = nullptr;

	GetAvailableActorsAroundTarget(ActorsOnLeft, ActorsOnRight);

	if (InSwitchDirectionTag == LOP_GameplayTags::Player_Event_SwitchTarget_Left)
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsOnLeft);
	}
	else
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsOnRight);
	}

	if (NewTargetToLock)
	{
		CurrentLockedActor = NewTargetToLock;
	}
}

void UPlayerGameplayAbility_TargetLock::TryLockOnTarget()
{
	GetAvailableActorsToLock();

	if (AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}

	CurrentLockedActor = GetNearestTargetFromAvailableActors(AvailableActorsToLock);

	if (CurrentLockedActor)
	{
		DrawTargetLockWidget();
		SetTargetLockWidgetPosition();
		InitTargetLockMappingContext();
	}
	else
	{
		CancelTargetLockAbility();
	}
}

void UPlayerGameplayAbility_TargetLock::GetAvailableActorsToLock()
{
	AvailableActorsToLock.Empty();

	TArray<FHitResult> BoxTraceHits;

	// 카메라 정보
	APlayerController* PC = GetPlayerControllerFromActorInfo();
	FVector CameraLoc;
	FRotator CameraRot;
	PC->GetPlayerViewPoint(CameraLoc, CameraRot);

	// Pitch 제거 → Yaw만 사용
	FRotator FlatRot = FRotator(0.f, CameraRot.Yaw, 0.f);

	const FVector Start = CameraLoc + FlatRot.Vector() * 100.f;
	const FVector End = Start + FlatRot.Vector() * BoxTraceDistance;

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		this,
		Start,
		End,
		TraceBoxSize / 2.f,
		FlatRot,
		BoxTraceChannel,
		false,
		TArray<AActor*>(),
		bShowPersistentDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		BoxTraceHits,
		true
	);

	for (const FHitResult& TraceHit : BoxTraceHits)
	{
		if (AActor* HitActor = TraceHit.GetActor())
		{
			if (HitActor != GetPlayerCharacterFromActorInfo())
			{
				AvailableActorsToLock.AddUnique(HitActor);
			}
		}
	}
}

AActor* UPlayerGameplayAbility_TargetLock::GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors)
{
	float ClosestDistance = 0.f;
	return UGameplayStatics::FindNearestActor(GetPlayerCharacterFromActorInfo()->GetActorLocation(), InAvailableActors, ClosestDistance);
}

void UPlayerGameplayAbility_TargetLock::GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft, TArray<AActor*>& OutActorsOnRight)
{
	if (!CurrentLockedActor || AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}

	const FVector PlayerLocation = GetPlayerCharacterFromActorInfo()->GetActorLocation();
	const FVector PlayerToCurrentNormalized = (CurrentLockedActor->GetActorLocation() - PlayerLocation).GetSafeNormal();

	for (AActor* AvailableActor : AvailableActorsToLock)
	{
		if (!AvailableActor || AvailableActor == CurrentLockedActor) continue;

		const FVector PlayerToAvailableNormalized = (AvailableActor->GetActorLocation() - PlayerLocation).GetSafeNormal();

		const FVector CrossResult = FVector::CrossProduct(PlayerToCurrentNormalized, PlayerToAvailableNormalized);

		if (CrossResult.Z > 0.f)
		{
			OutActorsOnRight.AddUnique(AvailableActor);
		}
		else
		{
			OutActorsOnLeft.AddUnique(AvailableActor);
		}
	}
}

void UPlayerGameplayAbility_TargetLock::DrawTargetLockWidget()
{
	if (!DrawnTargetLockWidget)
	{
		checkf(TargetLockWidgetClass, TEXT("Forgot to assign a valid widget class in Blueprint"));

		DrawnTargetLockWidget = CreateWidget<ULOP_WidgetBase>(GetPlayerControllerFromActorInfo(), TargetLockWidgetClass);

		check(DrawnTargetLockWidget);

		DrawnTargetLockWidget->AddToViewport();
	}
}

void UPlayerGameplayAbility_TargetLock::SetTargetLockWidgetPosition()
{
	if (!DrawnTargetLockWidget || !CurrentLockedActor)
	{
		CancelTargetLockAbility();
		return;
	}

	FVector2D ScreenPosition;
	//UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
	//	GetPlayerControllerFromActorInfo(),
	//	CurrentLockedActor->GetActorLocation(),
	//	ScreenPosition,
	//	true
	//);

	USkeletalMeshComponent* Mesh = CurrentLockedActor->FindComponentByClass<USkeletalMeshComponent>();
	FVector TargetPos = Mesh ? Mesh->GetSocketLocation(TargetLockWidgetSocketName) : CurrentLockedActor->GetActorLocation();

	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
		GetPlayerControllerFromActorInfo(),
		TargetPos,
		ScreenPosition,
		true
	);

	if (TargetLockWidgetSize == FVector2D::ZeroVector)
	{
		DrawnTargetLockWidget->WidgetTree->ForEachWidget(
			[this](UWidget* FoundWidget)
			{
				if (USizeBox* FoundSizeBox = Cast<USizeBox>(FoundWidget))
				{
					TargetLockWidgetSize.X = FoundSizeBox->GetWidthOverride();
					TargetLockWidgetSize.Y = FoundSizeBox->GetHeightOverride();
				}
			}
		);
	}

	ScreenPosition -= (TargetLockWidgetSize / 2.f);

	DrawnTargetLockWidget->SetPositionInViewport(ScreenPosition, false);
}

void UPlayerGameplayAbility_TargetLock::CancelTargetLockAbility()
{
	ClearWarpTarget();

	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

void UPlayerGameplayAbility_TargetLock::CleanUp()
{
	AvailableActorsToLock.Empty();

	CurrentLockedActor = nullptr;
	ClearWarpTarget();

	GetPlayerCharacterFromActorInfo()->bUseControllerRotationYaw = false;

	if (DrawnTargetLockWidget)
	{
		DrawnTargetLockWidget->RemoveFromParent();
	}
}

void UPlayerGameplayAbility_TargetLock::InitTargetLockMappingContext()
{
	const ULocalPlayer* LocalPlayer = GetPlayerControllerFromActorInfo()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem)

		Subsystem->AddMappingContext(TargetLockMappingContext, 3);
}

void UPlayerGameplayAbility_TargetLock::ResetTargetLockMappingContext()
{
	if (!GetPlayerControllerFromActorInfo())
	{
		return;
	}

	const ULocalPlayer* LocalPlayer = GetPlayerControllerFromActorInfo()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem)

		Subsystem->RemoveMappingContext(TargetLockMappingContext);
}


void UPlayerGameplayAbility_TargetLock::SetWarpTarget(const FVector& TargetLocation)
{
	if (APlayerCharacter* CH = GetPlayerCharacterFromActorInfo()) 
	{
		CH->GetMotionWarpingComponent()->AddOrUpdateWarpTargetFromLocation(TEXT("Target"), TargetLocation);
	}

}

void UPlayerGameplayAbility_TargetLock::ClearWarpTarget()
{
	if (APlayerCharacter* CH = GetPlayerCharacterFromActorInfo())
	{
		CH->GetMotionWarpingComponent()->RemoveWarpTarget(TEXT("Target"));
	}
}
