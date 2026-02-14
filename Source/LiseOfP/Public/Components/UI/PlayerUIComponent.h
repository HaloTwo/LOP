// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LOP_FunctionLibrary.h"
#include "Components/UI/PawnUIComponent.h"
#include "Components/Inventory/PlayerInventoryComponent.h"
#include "PlayerUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnEquippedWeaponChangedDelegate, TSoftObjectPtr<UTexture2D>, SoftWeaponIcon, TSoftObjectPtr<UTexture2D>, SoftHandleIcon, int32, CurrentWeaponIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnEquippedItemBagChangedDelegate, FText, itemName, TSoftObjectPtr<UTexture2D>, SoftItemIcon, int32, itemCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquippedItemBagSelectedDelegate, EBeltType, SelectedBelt);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractedDelegate, bool, bShouldDisplayInputKey, FText, Text);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemChoiseSelectedDelegate, EItemType, EquipType, FName, CurrentEquipItem);


class ADummyActor;
/**
 *
 */
UCLASS()
class LISEOFP_API UPlayerUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TMap<FName, UUserWidget*> WidgetMap;

	// 미리보기용 더미 액터
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	ADummyActor* PreviewDummy;

	// 저장된 인벤토리 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UPlayerInventoryComponent* CachedInventory;

private:
	UPROPERTY()
	TArray<FName> WidgetStack;




public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void PushWidget(FName WidgetName);

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool PopWidget();

	// 위젯 추가 (BP에서도 호출 가능)
	UFUNCTION(BlueprintCallable, Category = "UI")
	void RegisterWidget(FName WidgetName, UUserWidget* Widget);

	// 위젯 가져오기
	UFUNCTION(BlueprintCallable, Category = "UI")
	UUserWidget* GetWidget(FName WidgetName) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<FInventorySlot> GetItemsByType(EItemType Type) const;


	/// <summary>
	/// 델리게이트
	/// </summary>
public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnCurrentStaminaChanged;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnEquippedWeaponChangedDelegate OnEquippedWeaponChanged;



	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnEquippedItemBagChangedDelegate OnEquippedItemUpperBagChanged;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnEquippedItemBagChangedDelegate OnEquippedItemLowerBagChanged;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnEquippedItemBagSelectedDelegate OnInventoryItemBagChanged;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnInteractedDelegate OnInteracted;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnItemChoiseSelectedDelegate OnItemChoiseSelectDelegate;
};
