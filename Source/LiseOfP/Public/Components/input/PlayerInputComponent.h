// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/DataAsset_InputConfig.h"
#include "PlayerInputComponent.generated.h"


//UEnhancedInputComponent를 상속받아 추가 기능을 구현합니다.
UCLASS()
class LISEOFP_API UPlayerInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	

public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);

	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputRelasedFunc);
};

template<class UserObject, typename CallbackFunc>
inline void UPlayerInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	// 입력 설정 애셋이 유효한지 확인하고, 그렇지 않으면 오류 메시지와 함께 실행 중단
	checkf(InInputConfig, TEXT("Input config data asset is null, can not proceed with binding"));

	// 게임플레이 태그를 사용하여 입력 액션 객체를 찾음
	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		// 찾은 입력 액션을 지정된 트리거 이벤트, 컨텍스트 객체, 콜백 함수와 함께 바인딩
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
}

template<class UserObject, typename CallbackFunc>
inline void UPlayerInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputRelasedFunc)
{
	// 입력 설정 애셋이 유효한지 확인하고, 그렇지 않으면 오류 메시지와 함께 실행 중단
	checkf(InInputConfig, TEXT("Input config data asset is null, can not proceed with binding"));

	for (const auto& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (!AbilityInputActionConfig.IsVaild()) continue;

		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, AbilityInputActionConfig.InputTag);
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputRelasedFunc, AbilityInputActionConfig.InputTag);
	}
}
