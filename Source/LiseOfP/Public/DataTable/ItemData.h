#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"  // FTableRowBase 여기 들어있음
#include "Engine/DataAsset.h" // DataAsset 기본
#include "LOP_FunctionLibrary.h"
#include "DataAssets/WeaponDatas/DataAsset_PlayerWeaponDatas.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
    GENERATED_BODY();

    // 저장용
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemID;

    // UI 표시용 이름
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemType ItemType;

    // UI 설명
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
    FText Description;

    // UI 아이콘
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UTexture2D> ItemIcon01;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UTexture2D> ItemIcon02;
    

    // 인게임 액터 클래스 (무기, 아이템 등 스폰용)
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UDataAsset_PlayerWeaponDatas* WeaponDataAsset = nullptr;

    // 교체될 SkeletalMesh → **하드 참조**
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USkeletalMesh* SkeletalMesh = nullptr;

    // 최대 중첩 개수 (포션, 재료 등)
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxStack = 1;

    // 소비 아이템 효과 수치 (예: HP 회복량, 버프 값)
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 EffectValue = 0;
};
