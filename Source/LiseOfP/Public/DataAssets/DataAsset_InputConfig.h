// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DataAsset_InputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

// 입력 액션 설정 구조체
USTRUCT(BlueprintType)
struct FInputActionConfig
{
	GENERATED_BODY()

public:
    // 입력을 식별할 태그
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "GameplayTags"))
    FGameplayTag InputTag;

    // 매핑될 입력 액션
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputAction;

    // 설정이 유효한지 확인
    bool IsVaild() const
    {
        return InputTag.IsValid() && InputAction;
    }

};


/**
 * 
 */
// 입력 구성을 저장하는 데이터 에셋
UCLASS()
class LISEOFP_API UDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()
	

public:
    // 기본 입력 매핑 컨텍스트
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputMappingContext* DefaultMappingContext;

    // 기본 입력 액션 목록
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
    TArray<FInputActionConfig> NativeInputActions;

    // 태그로 입력 액션 검색
    UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;

    // 어빌리티 입력 액션 목록
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
    TArray<FInputActionConfig> AbilityInputActions;
};
