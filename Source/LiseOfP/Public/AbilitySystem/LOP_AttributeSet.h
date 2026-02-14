// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/LOP_AbilitySystemComponent.h"
#include "LOP_AttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


class IPawnUIInterface;
/**
 *
 */
UCLASS()
class LISEOFP_API ULOP_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()


public:
	ULOP_AttributeSet();
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	// 체력 관련
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(ULOP_AttributeSet, CurrentHealth)

		UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(ULOP_AttributeSet, MaxHealth)

		// 지구력
		UPROPERTY(BlueprintReadOnly, Category = "Stamina")
	FGameplayAttributeData CurrentStamina;
	ATTRIBUTE_ACCESSORS(ULOP_AttributeSet, CurrentStamina)


		UPROPERTY(BlueprintReadOnly, Category = "Stamina")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(ULOP_AttributeSet, MaxStamina)



		// 적재력
		UPROPERTY(BlueprintReadOnly, Category = "Capacity")
	FGameplayAttributeData Capacity;
	ATTRIBUTE_ACCESSORS(ULOP_AttributeSet, Capacity)




		// 동력 (힘 계열 공격력 보정)
		UPROPERTY(BlueprintReadOnly, Category = "Motivity")
	FGameplayAttributeData Motivity;
	ATTRIBUTE_ACCESSORS(ULOP_AttributeSet, Motivity)

		// 기술 (민첩 계열 공격력 보정)
		UPROPERTY(BlueprintReadOnly, Category = "Technique")
	FGameplayAttributeData Technique;
	ATTRIBUTE_ACCESSORS(ULOP_AttributeSet, Technique)

		// 진화 (속성/상태이상 계열 공격력 보정)
		UPROPERTY(BlueprintReadOnly, Category = "Advance")
	FGameplayAttributeData Advance;
	ATTRIBUTE_ACCESSORS(ULOP_AttributeSet, Advance)

		UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(ULOP_AttributeSet, DamageTaken)




private:
	TWeakInterfacePtr<IPawnUIInterface> CachedPawnUIInterface;
};
