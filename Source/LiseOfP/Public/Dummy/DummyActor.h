// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Characters/PlayerCharacter.h"
#include "LOP_FunctionLibrary.h"
#include "DummyActor.generated.h"

class AWeaponBase;
class UDataAsset_PlayerWeaponDatas;

UCLASS()
class LISEOFP_API ADummyActor : public AActor
{
	GENERATED_BODY()
	

public:
	ADummyActor();

	void BeginPlay();

	// 바디 메쉬 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parts")
	USkeletalMeshComponent* Mesh;

	// 머리 메쉬 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parts")
	USkeletalMeshComponent* HeadMesh;

	// 머리카락 메쉬 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parts")
	USkeletalMeshComponent* HairMesh;

	// 팔 메쉬 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parts")
	USkeletalMeshComponent* ArmsMesh;


	// 현재 장착 중인 무기 액터
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	AWeaponBase* DummyWeapon;



	// 무기 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	EWeaponType CurrentWeaponType;

	// 무기 타입별 애니메이션
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimSequence* OneHandAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimSequence* TwoHandAnim;




	// 플레이어 외형 복사 함수
	UFUNCTION(BlueprintCallable, Category = "Appearance")
	void CopyAppearanceFrom();

	UFUNCTION(BlueprintCallable, Category = "Appearance")
	void ApplyAppearanceTo(class UClass* AnimBP);

	void ApplyItemMesh(EItemType ItemType, USkeletalMesh* Mesh, class UClass* AnimBP);

	// 무기 장착 함수
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EquipDummyWeapon(UDataAsset_PlayerWeaponDatas* WeaponData);

private:
	APlayerCharacter* TargetPlayer;

};
