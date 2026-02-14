// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Inventory/PlayerInventoryComponent.h"
#include "Components/Combat/PlayerCombatComponent.h"


#include "AbilitySystemComponent.h"
#include "Characters/PlayerCharacter.h"
#include "Animation/AnimInstance.h"

#include "Dummy/DummyActor.h"
#include "Items/Weapons/WeaponBase.h"
#include "Characters/PlayerCharacter.h"
#include "AbilitySystem/LOP_AbilitySystemComponent.h"

#include "AnimInstances/Player/PlayerLinkedAnimLayer.h"
#include "DataAssets/WeaponDatas/DataAsset_PlayerWeaponDatas.h"

#include "LOP_GameplayTags.h"




void UPlayerInventoryComponent::AddItem(const FItemData& ItemData, int32 Amount)
{
	// 이미 있으면 수량만 증가
	if (FInventoryLoc* Loc = ItemLocMap.Find(ItemData.ItemID))
	{
		if (TArray<FInventorySlot>* Arr = InventoryMap.Find(Loc->Type))
		{
			if (Arr->IsValidIndex(Loc->Index))
			{
				(*Arr)[Loc->Index].Quantity += Amount;
				return;
			}
		}
		// 여기 오면 위치 정보가 꼬인 거니까 맵에서 지우고 아래에서 다시 추가
		ItemLocMap.Remove(ItemData.ItemID);
	}

	// 신규 추가
	FInventorySlot NewSlot;
	NewSlot.ItemID = ItemData.ItemID;
	NewSlot.Quantity = Amount;
	NewSlot.WeaponDataAsset = ItemData.WeaponDataAsset;
	NewSlot.SkeletalMesh = ItemData.SkeletalMesh;

	TArray<FInventorySlot>& Arr = InventoryMap.FindOrAdd(ItemData.ItemType);
	const int32 NewIndex = Arr.Add(NewSlot);

	ItemLocMap.Add(ItemData.ItemID, FInventoryLoc{ ItemData.ItemType, NewIndex });
}


FInventorySlot* UPlayerInventoryComponent::FindItem(FName ItemID)
{
	if (const FInventoryLoc* Loc = ItemLocMap.Find(ItemID))
	{
		if (TArray<FInventorySlot>* Arr = InventoryMap.Find(Loc->Type))
		{
			if (Arr->IsValidIndex(Loc->Index))
			{
				return &(*Arr)[Loc->Index];
			}
		}
	}
	return nullptr;
}


void UPlayerInventoryComponent::EquipItem(EItemType Type, FName ItemID)
{
	// 인벤토리에서 아이템 찾기
	FInventorySlot* SlotToEquip = FindItem(ItemID);
	if (!SlotToEquip)
	{
		UE_LOG(LogTemp, Warning, TEXT("EquipItem: Item %s not found in inventory"), *ItemID.ToString());
		return;
	}

	switch (Type)
	{
	case EItemType::Weapon01:
	case EItemType::Weapon02:
	case EItemType::Weapon03:
	{
		int32 WeaponIndex = 0;
		if (Type == EItemType::Weapon02) WeaponIndex = 1;
		else if (Type == EItemType::Weapon03) WeaponIndex = 2;

		if (EquippedWeapons.Num() < 3)
		{
			EquippedWeapons.SetNum(3); // 항상 3칸 보장
		}

		// 값 복사
		EquippedWeapons[WeaponIndex].ItemID = SlotToEquip->ItemID;
		EquippedWeapons[WeaponIndex].Quantity = SlotToEquip->Quantity;
		EquippedWeapons[WeaponIndex].WeaponDataAsset = SlotToEquip->WeaponDataAsset;

		CurrentWeaponIndex = WeaponIndex;

		UDataAsset_PlayerWeaponDatas* WeaponDA = EquippedWeapons[CurrentWeaponIndex].WeaponDataAsset;
		TSubclassOf<UAnimInstance> WeaponAnimLayer = nullptr;

		if (WeaponDA)
		{
			WeaponAnimLayer = WeaponDA->WeaponAnimLayerToLink;
		}

		// 더미 갱신 (무기)
		if (PreviewDummy && SlotToEquip->SkeletalMesh)
		{
			PreviewDummy->ApplyItemMesh(Type, SlotToEquip->SkeletalMesh, WeaponAnimLayer);
			PreviewDummy->EquipDummyWeapon(WeaponDA);
		}

		if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner()))
		{
			PlayerCharacter->GetBaseAbilitySystemComponent()->TryActivateAbilityByTag(LOP_GameplayTags::Player_Ability_Equip_UI);
		}
		break;
	}

	case EItemType::Clothes:
	{
		EquippedClothes.ItemID = SlotToEquip->ItemID;
		EquippedClothes.Quantity = SlotToEquip->Quantity;
		EquippedClothes.SkeletalMesh = SlotToEquip->SkeletalMesh;

		TSubclassOf<UAnimInstance> WeaponAnimLayer = nullptr;
		UDataAsset_PlayerWeaponDatas* WeaponDA = nullptr;

		// 현재 무기 애니메이션 레이어 가져오기
		if (EquippedWeapons.IsValidIndex(CurrentWeaponIndex))
		{
			WeaponDA = EquippedWeapons[CurrentWeaponIndex].WeaponDataAsset;
			if (WeaponDA) 
			{
				WeaponAnimLayer = WeaponDA->WeaponAnimLayerToLink;
			}
		}

		//더미 갱신
		if (PreviewDummy && SlotToEquip->SkeletalMesh)
		{
			PreviewDummy->ApplyItemMesh(Type, SlotToEquip->SkeletalMesh, WeaponAnimLayer);
			PreviewDummy->EquipDummyWeapon(WeaponDA);
		}
		break;
	}

	case EItemType::Helmet:
	{
		EquippedHelmet = *SlotToEquip;

		TSubclassOf<UAnimInstance> WeaponAnimLayer = nullptr;
		UDataAsset_PlayerWeaponDatas* WeaponDA = nullptr;

		if (EquippedWeapons.IsValidIndex(CurrentWeaponIndex))
		{
			WeaponDA = EquippedWeapons[CurrentWeaponIndex].WeaponDataAsset;
			if (WeaponDA)
			{
				WeaponAnimLayer = WeaponDA->WeaponAnimLayerToLink;
			}
		}

		if (PreviewDummy && SlotToEquip->SkeletalMesh)
		{
			PreviewDummy->ApplyItemMesh(Type, SlotToEquip->SkeletalMesh, WeaponAnimLayer);
			PreviewDummy->EquipDummyWeapon(WeaponDA);
		}
		break; //
	}

	default:
		UE_LOG(LogTemp, Warning, TEXT("EquipItem: Unsupported type %d"), (int32)Type);
		break;
	}
}



void UPlayerInventoryComponent::EquipItemToBelt(FName ItemID, EBeltType BeltType)
{
	FInventorySlot* FoundSlot = FindItem(ItemID);
	if (!FoundSlot || FoundSlot->Quantity <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("EquipItemToBelt: Item %s not found in Inventory (Have: %d)"),
			*ItemID.ToString(), FoundSlot ? FoundSlot->Quantity : 0);
		return;
	}

	// UpperBelt or LowerBelt 선택
	FBeltSlots& Belt = (BeltType == EBeltType::UpperBelt) ? UpperBelt : LowerBelt;
	FInventorySlot* TargetSlots[3] = { &Belt.Slot1, &Belt.Slot2, &Belt.Slot3 };

	for (int32 i = 0; i < 3; i++)
	{
		if (TargetSlots[i]->ItemID.IsNone())
		{
			// 벨트 슬롯에 아이템ID와 "인벤토리 갯수"를 그대로 반영
			TargetSlots[i]->ItemID = ItemID;
			TargetSlots[i]->Quantity = FoundSlot->Quantity;

			UE_LOG(LogTemp, Log, TEXT("Equipped %s to %s Slot%d (Inventory Count: %d)"),
				*ItemID.ToString(),
				(BeltType == EBeltType::UpperBelt ? TEXT("UpperBelt") : TEXT("LowerBelt")),
				i + 1, FoundSlot->Quantity);

			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("EquipItemToBelt: No empty slots in %s"),
		(BeltType == EBeltType::UpperBelt ? TEXT("UpperBelt") : TEXT("LowerBelt")));
}

void UPlayerInventoryComponent::SetCurrentBelt(EBeltType NewBelt)
{
	CurrentBelt = NewBelt;
}

const TArray<FInventorySlot>& UPlayerInventoryComponent::GetItemsByType(EItemType Type) const
{

	if (Type == EItemType::Weapon01 || Type == EItemType::Weapon02 || Type == EItemType::Weapon03)
	{
		static TArray<FInventorySlot> Combined;
		Combined.Reset();

		for (EItemType WeaponType : {EItemType::Weapon01, EItemType::Weapon02, EItemType::Weapon03})
		{
			if (const auto* Found = InventoryMap.Find(WeaponType))
			{
				Combined.Append(*Found);
			}
		}
		return Combined;
	}

	if (const auto* Found = InventoryMap.Find(Type))
	{
		return *Found;
	}

	static const TArray<FInventorySlot> Empty;
	return Empty;
}



bool UPlayerInventoryComponent::RemoveItem(FName ItemID, int32 Amount)
{
	if (FInventoryLoc* Loc = ItemLocMap.Find(ItemID))
	{
		if (TArray<FInventorySlot>* Arr = InventoryMap.Find(Loc->Type))
		{
			if (!Arr->IsValidIndex(Loc->Index)) { ItemLocMap.Remove(ItemID); return false; }

			FInventorySlot& Slot = (*Arr)[Loc->Index];
			if (Slot.Quantity < Amount) return false;

			Slot.Quantity -= Amount;
			if (Slot.Quantity == 0)
			{
				const int32 RemoveIdx = Loc->Index;
				const int32 LastIdx = Arr->Num() - 1;

				if (RemoveIdx != LastIdx)
				{
					// 마지막 원소를 앞으로 가져오고, 그 원소의 인덱스 갱신
					FName MovedID = (*Arr)[LastIdx].ItemID;

					(*Arr)[RemoveIdx] = (*Arr)[LastIdx];  // RAW 포인터만 있으니 통째 복사 OK
					if (FInventoryLoc* MovedLoc = ItemLocMap.Find(MovedID))
					{
						MovedLoc->Index = RemoveIdx;
					}
				}
				Arr->RemoveAt(LastIdx);
				ItemLocMap.Remove(ItemID);
			}
			return true;
		}
	}
	return false;
}


int32 UPlayerInventoryComponent::UseCurrentBeltItem(UDataTable* ItemDataTable)
{
	// 현재 선택된 벨트 가져오기
	FBeltSlots* CurrentSlots = (CurrentBelt == EBeltType::UpperBelt) ? &UpperBelt : &LowerBelt;

	// 첫 번째 슬롯만 예시로, 필요하면 Slot1/2/3 중 선택 로직 추가
	FInventorySlot& SelectedSlot = CurrentSlots->Slot1;

	if (SelectedSlot.ItemID.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("[Inventory] No item equipped in current belt slot."));
		return 0;
	}

	if (!ItemDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("[Inventory] ItemDataTable is nullptr."));
		return 0;
	}

	FItemData* FoundData = ItemDataTable->FindRow<FItemData>(SelectedSlot.ItemID, TEXT("UseCurrentBeltItem"));
	if (!FoundData)
	{
		UE_LOG(LogTemp, Error, TEXT("[Inventory] Item %s not found in DataTable."), *SelectedSlot.ItemID.ToString());
		return 0;
	}

	if (FoundData->ItemType == EItemType::Consumable)
	{
		if (SelectedSlot.Quantity > 0)
		{
			// 수량 감소
			SelectedSlot.Quantity--;

			// 효과 적용 (체력 회복 값은 로그나 ASC에서 처리)
			UE_LOG(LogTemp, Log, TEXT("[Inventory] Used %s | Heal: %d | Remaining: %d"),
				*SelectedSlot.ItemID.ToString(), FoundData->EffectValue, SelectedSlot.Quantity);

			// 남은 수량 리턴
			return SelectedSlot.Quantity;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("[Inventory] Item %s is empty."), *SelectedSlot.ItemID.ToString());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[Inventory] Item %s is not consumable."), *SelectedSlot.ItemID.ToString());
	}

	return 0;
}




void UPlayerInventoryComponent::ClearWeaponInventory()
{
	EquippedWeapons.Empty();
}


void UPlayerInventoryComponent::UnequipWeapon()
{
	// 기존 무기 제거
	if (EquippedWeapon)
	{
		EquippedWeapon->Destroy();
		EquippedWeapon = nullptr;
		EquippedWeaponTag = FGameplayTag::EmptyTag;
	}

	UE_LOG(LogTemp, Log, TEXT("[Inventory] Inventory cleared."));
}




bool UPlayerInventoryComponent::HasWeapon()
{
	for (const FInventorySlot& Slot : EquippedWeapons)
	{
		if (!Slot.ItemID.IsNone() && Slot.WeaponDataAsset != nullptr)
		{
			return true; // 진짜 무기 있음
		}
	}
	return false; // 다 빈 슬롯
}

UDataAsset_PlayerWeaponDatas* UPlayerInventoryComponent::GetEquippedWeaponData()
{
	const int32 WeaponCount = EquippedWeapons.Num();
	if (WeaponCount == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Inventory] No weapons equipped."));
		return nullptr;
	}

	for (int i = 0; i < WeaponCount; i++)
	{
		CurrentWeaponIndex = (CurrentWeaponIndex + 1) % WeaponCount;

		UDataAsset_PlayerWeaponDatas* WeaponData = EquippedWeapons[CurrentWeaponIndex].WeaponDataAsset;
		if (WeaponData)
		{
			UE_LOG(LogTemp, Log, TEXT("[Inventory] GetEquippedWeaponData | Index: %d | Weapon: %s"), CurrentWeaponIndex, *GetNameSafe(WeaponData));
			return WeaponData;
		}
		else UE_LOG(LogTemp, Warning, TEXT("[Inventory] Slot %d is empty, skipping"), CurrentWeaponIndex);
	}

	UE_LOG(LogTemp, Error, TEXT("[Inventory] No valid weapon found in any slot"));
	return nullptr;
}


void UPlayerInventoryComponent::SpawnWeapon()
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());

	UDataAsset_PlayerWeaponDatas* WeaponData = EquippedWeapons[CurrentWeaponIndex].WeaponDataAsset;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = OwnerCharacter;

	AWeaponBase* NewWeapon = OwnerCharacter->GetWorld()->SpawnActor<AWeaponBase>(
		WeaponData->WeaponClass,
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		SpawnParams
	);

	if (!NewWeapon) return;
	

	NewWeapon->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("BN_Weapon_R"));
	EquippedWeapon = NewWeapon;
	EquippedWeaponTag = WeaponData->WeaponTag;

	if (UPlayerCombatComponent* CombatComponent = OwnerCharacter->GetComponentByClass<UPlayerCombatComponent>())
	{
		CombatComponent->RegisterSpawnedWeapon(EquippedWeapon, WeaponData, true);
	}
}
