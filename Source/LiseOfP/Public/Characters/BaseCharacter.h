// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MotionWarpingComponent.h"

#include "AbilitySystemInterface.h"

#include "Interfaces/PawnCombatInterface.h"
#include "Interfaces/PawnUIInterface.h"

#include "DataAssets/WeaponDatas/DataAsset_WeaponDatas.h"

#include "BaseCharacter.generated.h"

class ULOP_AbilitySystemComponent;
class ULOP_AttributeSet;

class UDataAsset_StartUpDataBase;
class UMotionWarpingComponent;

UCLASS()
// 모든 캐릭터의 기본 클래스
class LISEOFP_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUIInterface
{
	GENERATED_BODY()

	// 기본 생성자
public:
	ABaseCharacter();

	// AbilitySystemComponent interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// AbilitySystemComponent interface

	// PawnCombatInterface 
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	// PawnCombatinterface

	//~ Begin IPawnUIInterface Interface.
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	//~ End IPawnUIInterface Interface

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	// GAS 컴포넌트
	ULOP_AbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	// 속성 세트
	ULOP_AttributeSet* AttributeSet;

	// 모션 워핑 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MotionWarping")
	UMotionWarpingComponent* MotionWarpingComponent;

	// 캐릭터의 시작 데이터
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;


	// 컨트롤러가 빙의될 때 호출
	virtual void PossessedBy(AController* NewController) override;

public:
	// AbilitySystemComponent 접근 함수
	FORCEINLINE ULOP_AbilitySystemComponent* GetBaseAbilitySystemComponent() const { return AbilitySystemComponent; }

	// AttributeSet 접근 함수
	FORCEINLINE ULOP_AttributeSet* GetBaseAttributeSet() const { return AttributeSet; }

	// 모션워핑 접근 함수
	FORCEINLINE UMotionWarpingComponent* GetMotionWarpingComponent() const { return MotionWarpingComponent; }

};
