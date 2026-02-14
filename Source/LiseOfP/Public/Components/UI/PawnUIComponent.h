// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "PawnUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPercentChangedDelegate, float, NewPercent, int32, Damage);

/**
 * 
 */
UCLASS()
class LISEOFP_API UPawnUIComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
	


public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnCurrentHealthChanged;
};
