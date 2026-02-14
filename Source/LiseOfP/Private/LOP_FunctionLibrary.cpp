// Fill out your copyright notice in the Description page of Project Settings.


#include "LOP_FunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/LOP_AbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Characters/PlayerCharacter.h"

#include "LOP_GameInstance.h"   
#include "LOP_GameplayTags.h"

#include "LOP_DebugHelper.h"

ULOP_AbilitySystemComponent* ULOP_FunctionLibrary::NativeGetWarriorASCFromActor(AActor* InActor)
{
	check(InActor);

	return CastChecked<ULOP_AbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void ULOP_FunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	ULOP_AbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void ULOP_FunctionLibrary::RemoveGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	ULOP_AbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool ULOP_FunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	ULOP_AbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void ULOP_FunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EWarriorConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EWarriorConfirmType::Yes : EWarriorConfirmType::No;
}

// 컴뱃 컴포넌트를 가져오는 함수
UPawnCombatComponent* ULOP_FunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	if (!InActor)
	{
		return nullptr;
	}

	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

//컴뱃 컴포넌트를 가져오고, 유효성 타입을 반환하는 함수
UPawnCombatComponent* ULOP_FunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, EWarriorValidType& OutValidType)
{
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	OutValidType = CombatComponent ? EWarriorValidType::Valid : EWarriorValidType::Invalid;

	return CombatComponent;
}

bool ULOP_FunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);

	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}

	return false;
}

// 적의 공격 방향을 계산하고, 부호 있는 각도를 반환하는 함수
FGameplayTag ULOP_FunctionLibrary::HitReactDirectionTag(const AActor* InAttacker, const AActor* InTarget, float& OutHitAngle)
{
	check(InAttacker && InTarget);

	//상대방 방향을 계산
	FVector TargetForward = InTarget->GetActorForwardVector();  TargetForward.Z = 0.f;
	FVector ToAttacker = InAttacker->GetActorLocation() - InTarget->GetActorLocation();
	ToAttacker.Z = 0.f;

	if (!TargetForward.Normalize() || !ToAttacker.Normalize())
	{
		OutHitAngle = 0.f;
		return LOP_GameplayTags::Shared_Status_HitReact_Front;
	}

	//부호 있는 각도 
	const float Dot = FMath::Clamp(FVector::DotProduct(TargetForward, ToAttacker), -1.f, 1.f);
	const float CrossZ = FVector::CrossProduct(TargetForward, ToAttacker).Z;
	OutHitAngle = FMath::RadiansToDegrees(FMath::Atan2(CrossZ, Dot));

	//구간 분류
	constexpr float FRONT_45 = 45.f;
	constexpr float SIDE_135 = 135.f;

	if (OutHitAngle >= -FRONT_45 && OutHitAngle <= FRONT_45)
		return LOP_GameplayTags::Shared_Status_HitReact_Front;

	if (OutHitAngle < -FRONT_45 && OutHitAngle >= -SIDE_135)
		return LOP_GameplayTags::Shared_Status_HitReact_Left;

	if (OutHitAngle > FRONT_45 && OutHitAngle <= SIDE_135)
		return LOP_GameplayTags::Shared_Status_HitReact_Right;


	return LOP_GameplayTags::Shared_Status_HitReact_Back;
}

bool ULOP_FunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	check(InAttacker && InDefender);

	const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector());

	//const FString DebugString = FString::Printf(TEXT("Dot Result: %f %s"), DotResult, DotResult < -0.1f ? TEXT("Valid Block") : TEXT("InvalidBlock"));

	//Debug::Print(DebugString, DotResult < -0.1f ? FColor::Green : FColor::Red);

	return DotResult < -0.1f ? true : false;
}

ECardinal8 ULOP_FunctionLibrary::DirectionLocalFromPlayer(const APlayerCharacter* Player)
{
	if (!Player) return ECardinal8::Front;

	// 1) 월드 방향: 입력 → 속도 → 전방
	FVector Dir = Player->GetLastMovementInputVector();
	if (Dir.IsNearlyZero()) Dir = Player->GetVelocity();
	if (Dir.IsNearlyZero()) Dir = Player->GetActorForwardVector();

	Dir.Z = 0.f;
	if (!Dir.Normalize())
		return ECardinal8::Back;

	// 2) 기준: 컨트롤러 Yaw(카메라 기준)
	float BasisYaw = Player->GetActorRotation().Yaw;
	if (const AController* C = Player->GetController())
		BasisYaw = C->GetControlRotation().Yaw;

	const FRotator BasisYawOnly(0.f, BasisYaw, 0.f);

	// 3) 로컬 변환 (X=앞/뒤, Y=오/왼)
	const FVector Local = BasisYawOnly.UnrotateVector(Dir);

	// 4) 각도 → 8방향 (0°=Front(+X), +90°=Right(+Y))
	float AngleDeg = FMath::RadiansToDegrees(FMath::Atan2(Local.Y, Local.X));
	int32 Index = FMath::FloorToInt((AngleDeg + 22.5f) / 45.f);
	Index = (Index % 8 + 8) % 8;

	switch (Index)
	{
	case 0:  return ECardinal8::Front;       //  -22.5 ~  +22.5
	case 1:  return ECardinal8::FrontRight;  //  +22.5 ~  +67.5
	case 2:  return ECardinal8::Right;       //  +67.5 ~ +112.5
	case 3:  return ECardinal8::BackRight;   // +112.5 ~ +157.5
	case 4:  return ECardinal8::Back;        // +157.5 ~ -157.5
	case 5:  return ECardinal8::BackLeft;    // -157.5 ~ -112.5
	case 6:  return ECardinal8::Left;        // -112.5 ~  -67.5
	case 7:  return ECardinal8::FrontLeft;   //  -67.5 ~  -22.5
	default: return ECardinal8::Front;
	}
}

void ULOP_FunctionLibrary::ToggleInputMode(const UObject* WorldContextObject, EWarriorInputMode InInputMode)
{
	APlayerController* PlayerController = nullptr;

	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			PlayerController = World->GetFirstPlayerController();
		}
	}

	if (!PlayerController)
	{
		return;
	}

	FInputModeGameOnly GameOnlyMode;
	FInputModeUIOnly UIOnlyMode;
	FInputModeGameAndUI GameAndUIMode;

	switch (InInputMode)
	{
	case EWarriorInputMode::GameOnly:
		PlayerController->SetInputMode(GameOnlyMode);
		PlayerController->bShowMouseCursor = false;
		break;

	case EWarriorInputMode::UIOnly:
		PlayerController->SetInputMode(UIOnlyMode);
		PlayerController->bShowMouseCursor = true;
		break;

	case EWarriorInputMode::GameAndUI:
		GameAndUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		GameAndUIMode.SetHideCursorDuringCapture(false);
		PlayerController->SetInputMode(GameAndUIMode);
		PlayerController->bShowMouseCursor = true;
		break;

	default:
		break;
	}
}

ULOP_GameInstance* ULOP_FunctionLibrary::GetLOP_GameInstance(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			return World->GetGameInstance<ULOP_GameInstance>();
		}
	}
	return nullptr;
}

