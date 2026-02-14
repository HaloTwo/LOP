// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Inventory/PawnInventoryComponent.h"
#include "DataTable/ItemData.h"
#include "PlayerInventoryComponent.generated.h"


UENUM(BlueprintType)
enum class EBeltType : uint8
{
	UpperBelt = 0 UMETA(DisplayName = "Upper Belt"),
	LowerBelt = 1 UMETA(DisplayName = "Lower Belt")
};

USTRUCT()
struct FInventoryLoc
{
	GENERATED_BODY()
	UPROPERTY() EItemType Type = EItemType::Misc; // 아무거나 기본
	UPROPERTY() int32 Index = INDEX_NONE;
};

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataAsset_PlayerWeaponDatas* WeaponDataAsset = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* SkeletalMesh = nullptr;
};

USTRUCT(BlueprintType)
struct FBeltSlots
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInventorySlot Slot1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInventorySlot Slot2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInventorySlot Slot3;
};


class UDataAsset_PlayerWeaponDatas;
class ADummyActor;
/**
 * 
 */
UCLASS()
class LISEOFP_API UPlayerInventoryComponent : public UPawnInventoryComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	ADummyActor* PreviewDummy;


protected:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<FInventorySlot> EquippedWeapons;


	UPROPERTY(BlueprintReadOnly)
	int32 CurrentWeaponIndex = -1;


	UPROPERTY(BlueprintReadOnly, Category = "Equipment")
	FInventorySlot EquippedClothes;

	UPROPERTY(BlueprintReadOnly, Category = "Equipment")
	FInventorySlot EquippedHelmet;


private:
	UPROPERTY()
	AWeaponBase* EquippedWeapon;

	UPROPERTY()
	FGameplayTag EquippedWeaponTag;

	// 종류별 인벤토리
	TMap<EItemType, TArray<FInventorySlot>> InventoryMap;

	// 빠른 검색: ItemID -> 위치(타입, 인덱스)
	TMap<FName, FInventoryLoc> ItemLocMap; 

public:

	/// <summary>
	/// Inventory Functions
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void AddItem(const FItemData& ItemData, int32 Amount);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(FName ItemID, int32 Amount);

	UFUNCTION(BlueprintCallable)
	int32 UseCurrentBeltItem(UDataTable* ItemDataTable);

	UFUNCTION(BlueprintCallable)
	void EquipItem(EItemType Type, FName ItemID);

	// UI용: 카테고리별 전체 아이템 가져오기
	UFUNCTION(BlueprintCallable)
	const TArray<FInventorySlot>& GetItemsByType(EItemType Type) const;

	FInventorySlot* FindItem(FName ItemID);


	/// <summary>
	/// Belt Functions
	/// </summary>

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	FBeltSlots UpperBelt;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	FBeltSlots LowerBelt;

	UPROPERTY(BlueprintReadOnly)
	EBeltType CurrentBelt = EBeltType::UpperBelt;

	UFUNCTION(BlueprintCallable)
	void EquipItemToBelt(FName ItemID, EBeltType Belt);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetCurrentBelt(EBeltType NewBelt);



	/// <summary>
	/// Weapon Inventory Functions
	/// </summary>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UDataAsset_PlayerWeaponDatas* GetEquippedWeaponData();

	//UFUNCTION(BlueprintCallable, Category = "Inventory")
	//void AddWeaponToInventory(UDataAsset_PlayerWeaponDatas* GetWeapon);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasWeapon();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SpawnWeapon();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UnequipWeapon();

	UFUNCTION()
	void ClearWeaponInventory();
};
