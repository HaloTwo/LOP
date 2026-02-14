// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/LOP_PlayerGameplayAbility.h"
#include "PlayerGameplayAbility_TargetLock.generated.h"

class ULOP_WidgetBase;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class LISEOFP_API UPlayerGameplayAbility_TargetLock : public ULOP_PlayerGameplayAbility
{
	GENERATED_BODY()
	
private:
	//타겟 잠금 관련 변수들
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float BoxTraceDistance = 5000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	FVector TraceBoxSize = FVector(5000.f, 5000.f, 300.f);

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	TArray< TEnumAsByte < EObjectTypeQuery > > BoxTraceChannel;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	bool bShowPersistentDebugShape = false;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	TSubclassOf<ULOP_WidgetBase> TargetLockWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float TargetLockRotationInterpSpeed = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	UInputMappingContext* TargetLockMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float TargetLockCameraOffsetDistance = 20.f;

	UPROPERTY()
	TArray<AActor*> AvailableActorsToLock;

	UPROPERTY()
	AActor* CurrentLockedActor;

	UPROPERTY()
	ULOP_WidgetBase* DrawnTargetLockWidget;

	UPROPERTY()
	FVector2D TargetLockWidgetSize = FVector2D::ZeroVector;

	UPROPERTY()
	FName TargetLockWidgetSocketName = "LockOnSocket";


protected:
	//~ Begin UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface

	//타겟 잠금 틱
	UFUNCTION(BlueprintCallable)
	void OnTargetLockTick(float DeltaTime);

	//타겟 전환
	UFUNCTION(BlueprintCallable)
	void SwitchTarget(const FGameplayTag& InSwitchDirectionTag);
	

private:
	void TryLockOnTarget(); //타겟 잠금 시도
	void GetAvailableActorsToLock(); //잠금 가능한 액터들 얻기
	AActor* GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors); //가장 가까운 타겟 얻기

	void GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft, TArray<AActor*>& OutActorsOnRight); //현재 타겟 주변의 잠금 가능한 액터들 얻기

	void DrawTargetLockWidget(); // 타겟 잠금 위젯 그리기
	void SetTargetLockWidgetPosition(); // 타겟 잠금 위젯 위치 설정
	void InitTargetLockMappingContext(); // 타겟 잠금 맵핑 컨텍스트 초기화

	void CancelTargetLockAbility(); // 타겟 잠금 어빌리티 취소
	void CleanUp(); // 정리
	void ResetTargetLockMappingContext(); // 타겟 잠금 맵핑 컨텍스트 리셋


	void SetWarpTarget(const FVector& TargetLocation); // TargetName이 이미 존재하면 갱신, 없으면 새로 등록
	void ClearWarpTarget(); // TargetName이 존재하면 제거
};
