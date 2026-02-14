// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/CharacterAnimInstance.h"
#include "PlayerAnimInstance.generated.h"

class APlayerCharacter;
/**
 *
 */
// 플레이어 전용 애님 인스턴스
UCLASS()
class LISEOFP_API UPlayerAnimInstance : public UCharacterAnimInstance
{
	GENERATED_BODY()

public:
// 애님 인스턴스 초기화
// 틱마다 애님 갱신
// 소유중인 플레이어 캐릭터
// 릴랙스 상태 진입 여부
// 릴랙스 상태 전환 시간
// 대기 시간 누적값
// 걷기 상태 여부
	//애니메이션 인스턴스가 생성될 때 호출되며, 필요한 초기 설정을 수행합니다.
	virtual void NativeInitializeAnimation() override;

	//매 프레임마다 호출되어 애니메이션 상태를 업데이트합니다.
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Refrences")
	APlayerCharacter* OwningPlayerCharacter;

	// 릴렉스 상태로 전환할지 여부를 나타내는 변수
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bShouldEnterRelaxState;

	// 릴렉스 상태로 전환하기 위한 임계값
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float  EnterRelaxtStateThreshold = 0.5f;

	// 현재 플레이어가 릴렉스 상태인지
	float IdleElpasedTime = 0.f;

	// 현재 플레이어가 걷는	상태인지
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bWalkState;
};
