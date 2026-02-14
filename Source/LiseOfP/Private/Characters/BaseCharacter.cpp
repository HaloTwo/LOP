// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "AbilitySystem/LOP_AbilitySystemComponent.h"
#include "AbilitySystem/LOP_AttributeSet.h"
#include "Components/Inventory/PawnInventoryComponent.h"

// 생성자
ABaseCharacter::ABaseCharacter()
{
	// 기본 설정
	PrimaryActorTick.bCanEverTick = false;

	//우선 멀티 없으니까 대기
	bReplicates = false;
	SetReplicateMovement(false);

	GetMesh()->bReceivesDecals = false;

	AbilitySystemComponent = CreateDefaultSubobject<ULOP_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<ULOP_AttributeSet>(TEXT("AttributeSet"));
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return GetBaseAbilitySystemComponent();
}

UPawnCombatComponent* ABaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

UPawnUIComponent* ABaseCharacter::GetPawnUIComponent() const
{
	return nullptr;
}


void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());

	// Possessed된 후에 필요한 초기화 작업을 여기에 추가할 수 있습니다.
}


