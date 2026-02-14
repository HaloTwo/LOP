// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "GameplayTagContainer.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
struct FInputActionValue;

class UPlayerCombatComponent;
class UPlayerInventoryComponent;
class UPlayerUIComponent;

class ADummyActor;
/**
 *
 */
UCLASS()
class LISEOFP_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()


public:
	// 플레이어 캐릭터 생성자
	APlayerCharacter();

	// 머리 메쉬 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parts")
	USkeletalMeshComponent* HeadMesh;

	// 머리카락 메쉬 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parts")
	USkeletalMeshComponent* HairMesh;

	// 팔 메쉬 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parts")
	USkeletalMeshComponent* ArmsMesh;


	// PawnCombatInterface 
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	// PawnCombatinterface

	//~ Begin IPawnUIInterface Interface.
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UPlayerUIComponent* GetPlayerUIComponent() const override;
	//~ End IPawnUIInterface Interface

protected:
	// ~ Begin APawn InterFace
// 컨트롤러가 빙의될 때 호출
	virtual void PossessedBy(AController* NewController) override;
	// ~ End APawn InterFace

// 입력 컴포넌트 설정
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// 게임 시작 시 호출
	virtual void BeginPlay() override;

private:
#pragma region Components
	// 카메라 붐 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	// 팔로우 카메라 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	//전투 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UPlayerCombatComponent* PlayerCombatComponent;

	// 인벤토리 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UPlayerInventoryComponent* PlayerInventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UPlayerUIComponent* PlayerUIComponent;
#pragma endregion


#pragma region Input 
	// 입력 설정 데이터 에셋
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	// 타겟 락 상태에서 방향 전환 입력 처리
	UPROPERTY();
	FVector2D SwitchDirection = FVector2D::ZeroVector;

	// 이동 입력 처리
	void Input_Move(const FInputActionValue& InputActionValue);
	// 시점 입력 처리
	void Input_Look(const FInputActionValue& InputActionValue);

	// TargetLock일때 타겟 변경 입력 처리
	void Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue);
	void Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue);


	// 상호 작용 입력 처리
	void Input_Interactable(const FInputActionValue& InputActionValue);


	// 어빌리티 입력 시작
	void Input_AbilityInputPressed(FGameplayTag InputTag);
	// 어빌리티 입력 종료
	void Input_AbilityInputReleased(FGameplayTag InputTag);
#pragma endregion


public:
	FORCEINLINE UPlayerCombatComponent* GetPlayerCombatComponent() const { return PlayerCombatComponent; }
	FORCEINLINE UPlayerInventoryComponent* GetInventoryComponentComponent() const { return PlayerInventoryComponent; }

};
