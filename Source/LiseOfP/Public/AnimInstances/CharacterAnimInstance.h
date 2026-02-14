// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/BaseAnimInstance.h"
#include "CharacterAnimInstance.generated.h"

class ABaseCharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class LISEOFP_API UCharacterAnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()
	

public:

	//애니메이션 인스턴스가 생성될 때 호출되며, 필요한 초기 설정을 수행합니다.
	//UAnimInstance 클래스의 동일한 함수를 오버라이드합니다.
	virtual void NativeInitializeAnimation() override;

	//매 프레임마다 호출되어 애니메이션 상태를 업데이트합니다.
	//이 함수는 별도의 스레드에서 안전하게 실행될 수 있도록 설계되어야 합니다.
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:

	UPROPERTY()
	ABaseCharacter* OwningCharacter;

	//캐릭터의 움직임을 제어
	UPROPERTY()
	UCharacterMovementComponent* owningMovementComponent;

	//캐릭터의 현재 속도
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed;

	//캐릭터 움직임 여부
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;

	//방향 정보
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float LocomotionDirection;
};
