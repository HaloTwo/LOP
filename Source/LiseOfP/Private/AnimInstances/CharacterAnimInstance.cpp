// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/CharacterAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"

/**
 * 애니메이션 초기화 함수
 *
 * 언리얼 엔진이 애니메이션 인스턴스가 생성될 때 자동으로 호출하는 함수입니다.
 * 이 함수에서는 애니메이션 인스턴스를 소유한 폰(Pawn)을 찾아 저장합니다.
 */
void UCharacterAnimInstance::NativeInitializeAnimation()
{
    // TryGetPawnOwner()를 통해 이 애니메이션 인스턴스를 사용하는 폰을 가져오고
    // WarriorBaseCharacter 타입으로 캐스팅합니다.
    OwningCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());

    // 소유 캐릭터가 유효한 경우 추가 초기화를 수행합니다.
    if (OwningCharacter)
    {
        // CharacterMovement 컴포넌트를 가져옵니다.
        // 주의: 이 결과값이 사용되지 않고 있습니다. 이는 미완성 코드나 실수일 수 있습니다.
        // 일반적으로 이 값을 멤버 변수에 저장하거나 초기화에 사용합니다.
        owningMovementComponent = OwningCharacter->GetCharacterMovement();
    }
}

/**
 * 스레드 안전 애니메이션 업데이트 함수
 *
 * 매 프레임마다 애니메이션을 업데이트하기 위해 호출됩니다.
 * 이 함수는 스레드 안전하게 설계되어야 하며, 게임 스레드가 아닌
 * 애니메이션 스레드에서 실행될 수 있습니다.
 *
 * @param DeltaSeconds - 마지막 프레임 이후 경과된 시간(초)
 */
void UCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
    // 일반적으로 여기서는 캐릭터의 속도, 방향, 상태 등을 확인하여
    // 애니메이션 변수들을 업데이트합니다.

    //캐릭터가 없거나, 무브 컴포넌트가 없다면 return
    if (!OwningCharacter || !owningMovementComponent)
    {
        return;
    }

    GroundSpeed = OwningCharacter->GetVelocity().Size2D();
    bHasAcceleration = owningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
    LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
}